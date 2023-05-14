#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "../simulation.h"
#include "../args.h"
#include "../render.h"
#include "../version.h"

int main(int argc, char** argv) {
  simulation sim;

  if (0 == args_process(argc, argv, &sim))
    return 1;

  // ###TODO - disentangle CLI-specific screen size / buffer from simulation state
  // allocate screen buffer
  sim.screen_dimensions.x = 75;
  sim.screen_dimensions.y = 18;
  sim.screen = (unsigned char*)malloc(sizeof(unsigned char) * sim.screen_dimensions.x * sim.screen_dimensions.y);

  /* Run simulation until terminated manually */
  while (1) {
    system("clear");
    render_frontbuffer(&sim);
    simulation_swap_buffers(&sim);
    simulation_tick(&sim);
    // nanosleep((const struct timespec[]){{0, sim.tick_frequency_nanoseconds}}, NULL);
  }

  simulation_free(&sim);
  return 0;
}
