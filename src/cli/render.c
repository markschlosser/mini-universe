#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../render.h"
#include "screen.h"

#define RENDER_SYMBOLS " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+"
static unsigned char get_render_symbol(unsigned char old_symbol) {
  char* found_location;

  found_location = strchr(RENDER_SYMBOLS, old_symbol);
  if ('+' == *found_location) {
    return '+';
  }

  return *(++found_location);
}

void render_frontbuffer(simulation* sim, void* anything) {
  int i, x, y, screen_ndx;
  fp_xy world_range[2], world_dimensions, screen_dimensions;
  screen* scr;

  scr = (screen*)anything;

  simulation_find_range_of_particles(sim->frontbuffer, sim->num_particles, world_range);

  world_dimensions.x = world_range[1].x - world_range[0].x;
  world_dimensions.y = world_range[1].y - world_range[0].y;

  screen_dimensions.x = (double)scr->dimensions.x;
  screen_dimensions.y = (double)scr->dimensions.y;

  memset(scr->buffer, ' ', screen_dimensions.x * screen_dimensions.y);

  if (world_range[0].x == world_range[1].x && world_range[0].y == world_range[1].y) {
    y = screen_dimensions.y / 2;
    x = screen_dimensions.x / 2;
    screen_ndx = y * screen_dimensions.x + x;
    scr->buffer[screen_ndx] = '+';
  } else {
    for (i = 0; i < sim->num_particles; i++) {
      double part_screen_x = ((sim->frontbuffer[i].position.x - world_range[0].x) * (screen_dimensions.x - 0.5)) / world_dimensions.x;
      double part_screen_y = ((sim->frontbuffer[i].position.y - world_range[0].y) * (screen_dimensions.y - 0.5)) / world_dimensions.y;
      x = (int)floor(part_screen_x - 0.0);
      y = (int)floor(part_screen_y - 0.0);

      if (x < 0 || x > screen_dimensions.x - 1)
        printf("Error: x=%d (%f) is out of range\n", x, part_screen_x);
      if (y < 0 || y > screen_dimensions.y - 1)
        printf("Error: y=%d (%f) is out of range\n", y, part_screen_y);

      screen_ndx = y * screen_dimensions.x + x;
      scr->buffer[screen_ndx] = get_render_symbol(scr->buffer[screen_ndx]);
    }
  }

  printf("."); 
  for (x = 0; x < screen_dimensions.x; x++)
    printf("-");
  printf(".\n");

  for (y = 0; y < screen_dimensions.y; y++) {
    printf("|");
    for (x = 0; x < screen_dimensions.x; x++) {
      screen_ndx = y * screen_dimensions.x + x;
      printf("%c", scr->buffer[screen_ndx]);
    }
    printf("|\n");
  }

  printf("`");
  for (x = 0; x < screen_dimensions.x; x++)
    printf("-");
  printf("'\n");

  printf("world dimensions: width=%f, height=%f\n", world_dimensions.x, world_dimensions.y);
}
