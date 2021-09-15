#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "simulation.h"
#include "render.h"
#include "file.h"
#include "version.h"

#define USAGE_STR "<configuration file>"

int main(int argc, char** argv) {
  simulation sim;
  simulation_config sim_config;
  int load_config_status;

  if (argc != 2) {
    printf("Usage: %s %s\n", argv[0], USAGE_STR);
    return 1;
  }

  printf("mini-universe %s\n", VERSION_STRING);

  /* Populate configuration for simulation from file... */
  load_config_status = file_read_config(argv[1], &sim_config);
  if (!load_config_status) {
    printf("Error loading configuration file!\n");
    return 1;
  }   

  /* Initialize simulator using above configuration and specified seed value */
  simulation_init(&sim, &sim_config);

  /* Run simulation until terminated manually */
  while (1) {
    system("clear");
    render_frontbuffer(&sim);
    simulation_swap_buffers(&sim);
    simulation_tick(&sim);
    nanosleep((const struct timespec[]){{0, sim.tick_frequency_nanoseconds}}, NULL);
  }

  simulation_free(&sim);
  return 0;
}

