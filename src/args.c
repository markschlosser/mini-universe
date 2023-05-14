#include <string.h>
#include <stdio.h>

#include "args.h"
#include "file.h"

#define USAGE_STR "\
Usage: %s --new <config file> | --restore <save state file>\n\
\n\
The options are as follows:\n\
\n\
--new       Seeds a simulation from a specified configuration file.\n\
--restore   Restores a simulation from a specified binary file.\n\
"

int args_process(int argc, char** argv, simulation *sim) {
  simulation_config sim_config;
  int load_config_status;

  if (argc != 3) {
    printf(USAGE_STR, argv[0]);
    return 0;
  }

  if (0 == strcmp("--new", argv[1])) {
    /* Populate configuration for simulation from file... */
    load_config_status = file_read_config(argv[2], &sim_config);
    if (!load_config_status) {
      printf("Error loading configuration file! Load status = %d\n", load_config_status);
      return 0;
    }
    simulation_init(sim, &sim_config);
  } else if (0 == strcmp("--restore", argv[1])) {
    if (0 == file_read_simulation(argv[2], sim)) {
      printf("Error opening restore state from %s\n", argv[2]);
      return 0;
    }
  } else {
    printf(USAGE_STR, argv[0]);
    return 0;
  }

  return 1;
}
