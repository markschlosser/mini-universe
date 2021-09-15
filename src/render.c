#include <stdio.h>
#include <string.h>
#include <math.h>

#include "render.h"

static void find_range_of_particles(particle* buffer, unsigned int num_particles, fp_xy* range) {
  int i;

  range[0].x = range[1].x = buffer[0].position.x;
  range[0].y = range[1].y = buffer[0].position.y;

  for(i = 1; i < num_particles; i++) { // find min max
    particle* pe = &buffer[i];
    if(pe->position.x < range[0].x) {
      range[0].x = pe->position.x;
    }
    else if(pe->position.x > range[1].x) {
      range[1].x = pe->position.x;
    }
    if(pe->position.y < range[0].y) {
      range[0].y = pe->position.y;
    }
    else if(pe->position.y > range[1].y) {
      range[1].y = pe->position.y;
    }
  }
}

#define RENDER_SYMBOLS " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+"
static unsigned char get_render_symbol(unsigned char old_symbol) {
  char* found_location;

  found_location = strchr(RENDER_SYMBOLS, old_symbol);
  if ('+' == *found_location) {
    return '+';
  }

  return *(++found_location);
}

void render_frontbuffer(simulation* sim) {
  int i, x, y, screen_ndx;
  fp_xy world_range[2], world_dimensions, screen_dimensions;

  find_range_of_particles(sim->frontbuffer, sim->num_particles, world_range);

  world_dimensions.x = world_range[1].x - world_range[0].x;
  world_dimensions.y = world_range[1].y - world_range[0].y;

  screen_dimensions.x = (double)sim->screen_dimensions.x;
  screen_dimensions.y = (double)sim->screen_dimensions.y;

  memset(sim->screen, ' ', sim->screen_dimensions.x * sim->screen_dimensions.y);

  if (world_range[0].x == world_range[1].x && world_range[0].y == world_range[1].y) {
    y = sim->screen_dimensions.y / 2;
    x = sim->screen_dimensions.x / 2;
    screen_ndx = y * sim->screen_dimensions.x + x;
    sim->screen[screen_ndx] = '+';
  } else {
    for (i = 0; i < sim->num_particles; i++) {
      double part_screen_x = ((sim->frontbuffer[i].position.x - world_range[0].x) * (screen_dimensions.x - 0.5)) / world_dimensions.x;
      double part_screen_y = ((sim->frontbuffer[i].position.y - world_range[0].y) * (screen_dimensions.y - 0.5)) / world_dimensions.y;
      x = (int)floor(part_screen_x - 0.0);
      y = (int)floor(part_screen_y - 0.0);

      if (x < 0 || x > sim->screen_dimensions.x - 1)
        printf("Error: x=%d (%f) is out of range\n", x, part_screen_x);
      if (y < 0 || y > sim->screen_dimensions.y - 1)
        printf("Error: y=%d (%f) is out of range\n", y, part_screen_y);

      screen_ndx = y * sim->screen_dimensions.x + x;
      sim->screen[screen_ndx] = get_render_symbol(sim->screen[screen_ndx]);
    }
  }

  printf("."); 
  for (x = 0; x < sim->screen_dimensions.x; x++)
    printf("-");
  printf(".\n");

  for (y = 0; y < sim->screen_dimensions.y; y++) {
    printf("|");
    for (x = 0; x < sim->screen_dimensions.x; x++) {
      screen_ndx = y * sim->screen_dimensions.x + x;
      printf("%c", sim->screen[screen_ndx]);
    }
    printf("|\n");
  }

  printf("`");
  for (x = 0; x < sim->screen_dimensions.x; x++)
    printf("-");
  printf("'\n");

  printf("world dimensions: width=%f, height=%f\n", world_dimensions.x, world_dimensions.y);
}

