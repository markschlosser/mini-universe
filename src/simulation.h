#ifndef __SIMULATION_H__
#define __SIMULATION_H__

typedef struct {unsigned char x, y;} xy;
typedef struct {double x, y;} fp_xy;

typedef struct {
  fp_xy position;
  fp_xy direction;
} particle;

#define MAX_SCREEN_DIMENSION 256

typedef struct {
  particle* backbuffer;
  particle* frontbuffer;
  unsigned int num_particles;
  double max_speed;
  long tick_frequency_nanoseconds;
  xy screen_dimensions;
  unsigned char* screen; // X=0,Y=0 is upper left
} simulation;

typedef struct {
  unsigned int num_particles; /* the number of particles that exist in the world */
  double max_speed; /* the maximum speed a particle travel in X or Y */
  unsigned int seed; /* the value used to seed the random number generator */
  long tick_frequency_nanoseconds; /* how frequently the world ticks forward one slice of world time */
  xy screen_dimensions; /* dimensions of the screen viewport in pixels */
  fp_xy initial_direction_range[2]; /* range of initial directions for the particles */
  unsigned int num_initial_positions; /* number of initial positions of the particles */
  fp_xy* initial_positions; /* array of initial positions; randomly used for each particle */
} simulation_config;

void simulation_init(simulation* sim, simulation_config* config);
void simulation_free(simulation* sim);
void simulation_tick(simulation* sim);
void simulation_swap_buffers(simulation* sim);

#endif /* ifndef __SIMULATION_H__ */

