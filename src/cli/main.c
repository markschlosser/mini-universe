#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "../simulation.h"
#include "../args.h"
#include "../render.h"
#include "../version.h"
#include "screen.h"

int main(int argc, char** argv) {
  simulation sim;
  screen scr;

  if (0 == args_process(argc, argv, &sim))
    return 1;

  screen_init(&scr, 75, 18);

  /* Run simulation until terminated manually */
  while (1) {
    system("clear");
    render_frontbuffer(&sim, &scr);
    simulation_swap_buffers(&sim);
    simulation_tick(&sim);
    // nanosleep((const struct timespec[]){{0, sim.tick_frequency_nanoseconds}}, NULL);
  }

  simulation_free(&sim);
  screen_free(&scr);
  return 0;
}
