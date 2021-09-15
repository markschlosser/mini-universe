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
    } else if (0 == strcmp(property, "screen_dimensions")) {
      num_matched = sscanf(value, "w=%hhu,h=%hhu", &config->screen_dimensions.x, &config->screen_dimensions.y);
      if (2 != num_matched)
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

