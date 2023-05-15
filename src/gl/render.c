#include <stdio.h>
#include <string.h>
#include <math.h>
#include <OpenGL/gl.h>

#include "../render.h"

void render_frontbuffer(simulation* sim, void* anything) {
  int i;
  fp_xy world_range[2];

  simulation_find_range_of_particles(sim->frontbuffer, sim->num_particles, world_range);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(world_range[0].x, world_range[1].x, world_range[0].y, world_range[1].y, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  glBegin(GL_POINTS);
  for (i = 0; i < sim->num_particles; i++) {
    glVertex2f(sim->frontbuffer[i].position.x, sim->frontbuffer[i].position.y);
  }
  glEnd();

  glDisable(GL_BLEND);
  glFlush();
}
