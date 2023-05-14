#include <stdio.h>
#include <string.h>
#include <math.h>
#include <OpenGL/gl.h>

#include "../render.h"

static void find_range_of_particles(particle* buffer, unsigned int num_particles, fp_xy* range) {
  int i;

  range[0].x = range[1].x = buffer[0].position.x;
  range[0].y = range[1].y = buffer[0].position.y;

  for(i = 1; i < num_particles; i++) { // find min max
    particle* pe = &buffer[i];
    if(pe->position.x < range[0].x) {
      range[0].x = pe->position.x;
    }
    else if(pe->position.x > range[1].x) {
      range[1].x = pe->position.x;
    }
    if(pe->position.y < range[0].y) {
      range[0].y = pe->position.y;
    }
    else if(pe->position.y > range[1].y) {
      range[1].y = pe->position.y;
    }
  }
}

void render_frontbuffer(simulation* sim) {
  int i;
  fp_xy world_range[2];

  find_range_of_particles(sim->frontbuffer, sim->num_particles, world_range);

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

