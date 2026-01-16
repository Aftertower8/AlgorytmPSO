#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"

void logger_init(const char *filename);

void log_swarm(const char *filename, int iteration, int id, particle *drones);

#endif

