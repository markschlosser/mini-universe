#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"

int file_read_config(char* path, simulation_config* config) {
  FILE* fp;
  char property[64], value[64];
  int i, num_matched;

  fp = fopen(path, "r");
  if (!fp)
    return 0;

  num_matched = fscanf(fp, "%s %s\n", property, value);

  config->num_initial_positions = 0;

  while (2 == num_matched) {
    if (0 == strcmp(property, "num_particles")) {
      num_matched = sscanf(value, "%u", &config->num_particles);
      if (1 != num_matched)
        return 0;
    } else if (0 == strcmp(property, "seed")) {
      num_matched = sscanf(value, "%u", &config->seed);
      if (1 != num_matched)
        return 0;
    } else if (0 == strcmp(property, "max_speed")) {
      num_matched = sscanf(value, "%lf", &config->max_speed);
      if (1 != num_matched)
        return 0;
    } else if (0 == strcmp(property, "initial_direction_range")) {
      num_matched = sscanf(value, "xmin=%lf,xmax=%lf,ymin=%lf,ymax=%lf", &config->initial_direction_range[0].x, &config->initial_direction_range[1].x, &config->initial_direction_range[0].y, &config->initial_direction_range[1].y);
      if (4 != num_matched)
        return 0;
    } else if (0 == strcmp(property, "initial_positions")) {
      num_matched = sscanf(value, "num=%u", &config->num_initial_positions);
      if (1 != num_matched)
        return 0;

      config->initial_positions = (fp_xy*)malloc(sizeof(fp_xy) * config->num_initial_positions);

      if (config->num_initial_positions < 1)
        return 0;

      for(i = 0; i < config->num_initial_positions; i++) {
        num_matched = fscanf(fp, "x=%lf,y=%lf\n", &config->initial_positions[i].x, &config->initial_positions[i].y);
        if (2 != num_matched)
          return 0;
      }
    } else if (0 == strcmp(property, "tick_frequency_nanoseconds")) {
      num_matched = sscanf(value, "%ld", &config->tick_frequency_nanoseconds);
      if (1 != num_matched)
        return 0;
    } else {
      return 0; // unknown property
    }

    num_matched = fscanf(fp, "%s %s\n", property, value);
  }

  fclose(fp);
  return 1;
}

int file_read_simulation(char* path, simulation* sim) {
  FILE* fp;
  int i;

  fp = fopen(path, "rb");
  if (!fp)
    return 0;

  fread(&sim->max_speed, sizeof(double), 1, fp);
  fread(&sim->num_particles, sizeof(unsigned int), 1, fp);

  // allocate particle buffers
  sim->backbuffer = (particle*)malloc(sizeof(particle) * sim->num_particles);
  sim->frontbuffer = (particle*)malloc(sizeof(particle) * sim->num_particles);

  for (i = 0; i < sim->num_particles; i++) {
    fread(&sim->frontbuffer[i].position.x, sizeof(double), 1, fp);
    fread(&sim->frontbuffer[i].position.y, sizeof(double), 1, fp);
    fread(&sim->frontbuffer[i].direction.x, sizeof(double), 1, fp);
    fread(&sim->frontbuffer[i].direction.y, sizeof(double), 1, fp);
  }

  fread(&sim->orig_world_range[0].x, sizeof(double), 1, fp);
  fread(&sim->orig_world_range[0].y, sizeof(double), 1, fp);
  fread(&sim->orig_world_range[1].x, sizeof(double), 1, fp);
  fread(&sim->orig_world_range[1].y, sizeof(double), 1, fp);

  fclose(fp);
  return 1;
}

int file_write_simulation(char* path, simulation* sim) {
  FILE* fp;
  int i;

  fp = fopen(path, "wb");
  if (!fp)
    return 0;
  
  fwrite(&sim->max_speed, sizeof(double), 1, fp);
  fwrite(&sim->num_particles, sizeof(unsigned int), 1, fp);
  for (i = 0; i < sim->num_particles; i++) {
    fwrite(&sim->frontbuffer[i].position.x, sizeof(double), 1, fp);
    fwrite(&sim->frontbuffer[i].position.y, sizeof(double), 1, fp);
    fwrite(&sim->frontbuffer[i].direction.x, sizeof(double), 1, fp);
    fwrite(&sim->frontbuffer[i].direction.y, sizeof(double), 1, fp);
  }

  fwrite(&sim->orig_world_range[0].x, sizeof(double), 1, fp);
  fwrite(&sim->orig_world_range[0].y, sizeof(double), 1, fp);
  fwrite(&sim->orig_world_range[1].x, sizeof(double), 1, fp);
  fwrite(&sim->orig_world_range[1].y, sizeof(double), 1, fp);

  fclose(fp);
  return 1;
}
