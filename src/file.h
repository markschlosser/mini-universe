#ifndef __FILE_H__
#define __FILE_H__

#include "simulation.h"

int file_read_config(char* path, simulation_config* config);
int file_read_simulation(char* path, simulation* sim);
int file_write_simulation(char* path, simulation* sim);

#endif /* ifndef __FILE_H__ */

