#include <stdio.h>
#include <stdlib.h>

#include "simulation.h"
#include "xymath.h"

#define RANDOM_DOUBLE(min,max) ((double)((rand() / (RAND_MAX + 1.0)) * (max - min) + min))
#define RANDOM_UCHAR(min,max) ((unsigned char)((rand() % (max - min + 1)) + min))
#define RANDOM_UINT(min,max) ((unsigned int)((rand() % (max - min + 1)) + min))

static void solve_particle(int, unsigned int, particle*, particle*, double);

void simulation_find_range_of_particles(particle* buffer, unsigned int num_particles, fp_xy* range) {
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

void simulation_init(simulation* sim, simulation_config* config){
  int i, ndx;

  // copy configuration into simulation object
  sim->num_particles = config->num_particles;
  sim->max_speed = config->max_speed;
  sim->tick_frequency_nanoseconds = config->tick_frequency_nanoseconds;

  printf("num_particles = %d\n", sim->num_particles);
  printf("max_speed = %f\n", sim->max_speed);
  printf("seed = %d\n", config->seed);
  printf("initial_direction_range = {xmin=%f,xmax=%f,ymin=%f,ymax=%f}\n", config->initial_direction_range[0].x, config->initial_direction_range[1].x, config->initial_direction_range[0].y, config->initial_direction_range[1].y);
  printf("num_initial_positions = %d\n", config->num_initial_positions);
  for (i = 0; i < config->num_initial_positions; i++) {
    printf("initial_positions[%d] = %f,%f\n", i, config->initial_positions[i].x, config->initial_positions[i].y);
  }

  // seed the universe with the chosen value
  srand(config->seed);

  // allocate particle buffers
  sim->backbuffer = (particle*)malloc(sizeof(particle) * sim->num_particles);
  sim->frontbuffer = (particle*)malloc(sizeof(particle) * sim->num_particles);

  // seed the universe's initial state
  for(i = 0; i < sim->num_particles; i++) {
    ndx = RANDOM_UINT(0, config->num_initial_positions - 1);
    XY_COPY(sim->frontbuffer[i].position, config->initial_positions[ndx]);
printf("setting pos = %f,%f\n", sim->frontbuffer[i].position.x, sim->frontbuffer[i].position.y);
    sim->frontbuffer[i].direction.x = RANDOM_DOUBLE(config->initial_direction_range[0].x, config->initial_direction_range[1].x);
    sim->frontbuffer[i].direction.y = RANDOM_DOUBLE(config->initial_direction_range[0].y, config->initial_direction_range[1].y);
printf("setting dir = %f,%f\n", sim->frontbuffer[i].direction.x, sim->frontbuffer[i].direction.y);
  } 
}

void simulation_free(simulation* sim) {
  free(sim->backbuffer);
  free(sim->frontbuffer);
}

void simulation_tick(simulation* sim) {
  int i;

  for (i = 0; i < sim->num_particles; i++) {
    solve_particle(i, sim->num_particles, sim->backbuffer, sim->frontbuffer, sim->max_speed);
  }
}

void simulation_swap_buffers(simulation* sim) {
  particle* tmp = sim->frontbuffer;
  sim->frontbuffer = sim->backbuffer;
  sim->backbuffer = tmp;
}

static void solve_particle(int part_ndx, unsigned int num_particles, particle* backbuffer, particle* frontbuffer, double max_speed) {
  fp_xy p1, total_dir;
  int i;

  XY_COPY(total_dir, backbuffer[part_ndx].direction); /* total_dir begins with current direction for point 1 */
  XY_COPY(p1, backbuffer[part_ndx].position); /* assign position for point 1 */

  for (i = 0; i < num_particles; i++) {
    fp_xy p2;
    fp_xy dir;
    double dist;

    if(i == part_ndx) { /* do not affect self */
      continue;
    }

    XY_COPY(p2, backbuffer[i].position); /* assign position for point 2 */
    XY_COPY(dir, backbuffer[i].position); /* assign direction to p2 for calculation below */

    dist = XY_DIST(p1, p2); /* find distance between the two points */
    if(dist > 0.0) {
      /* find a normalized direction vector from point p1 to p2 */
      XY_SUB(dir, p1);
      XY_NORMALIZE(dir);

      /* divide the direction vector by the distance - farther away results in less effect */
      XY_SCALE(dir, 1.0 / dist);

      XY_ADD(total_dir, dir); /* accumulate direction in total direction */
    }
  }

  /* clamp total_dir.x to max speed */
  if (total_dir.x > max_speed)
    total_dir.x = max_speed;
  else if (total_dir.x < -max_speed)
    total_dir.x = -max_speed;

  /* clamp total_dir.x to max speed */
  if (total_dir.y > max_speed)
    total_dir.y = max_speed;
  else if (total_dir.y < -max_speed)
    total_dir.y = -max_speed;

  /* add total direction to p1 and assign to frontbuffer */
  XY_ADD(p1, total_dir);
  XY_COPY(frontbuffer[part_ndx].position, p1); /* save new position in frontbuffer */
  XY_COPY(frontbuffer[part_ndx].direction, total_dir); /* assign new total direction */
} /* solve_particle */
