#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <GLUT/glut.h>

#include "../args.h"
#include "../simulation.h"
#include "../render.h"
#include "../file.h"

static simulation sim;
static int last_frame_time = 0;
static int frame_counter = 0;

static void on_display() {
  glClear(GL_COLOR_BUFFER_BIT);

  render_frontbuffer(&sim, 0);
  simulation_swap_buffers(&sim);
  simulation_tick(&sim);

  glutSwapBuffers();
}

static void on_reshape(int w, int h) {
}

static void on_keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // ESC key
      file_write_simulation("sim.bin", &sim);
      simulation_free(&sim);
      exit(0);
      break;
    default:
      break;
  }
}

static void on_timer(int id) {
  if (id == 1) {
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    int delta_time = current_time - last_frame_time;
    last_frame_time = current_time;

    // simulation_tick(&sim);
    glutPostRedisplay();

    frame_counter++;
    if (frame_counter % 10 == 0) {
      char title[256];
      sprintf(title, "mini-universe (%d FPS)", (int)(10.0 / ((double)delta_time / 1000.0)));
      glutSetWindowTitle(title);
      frame_counter = 0;
    }
  }

  glutTimerFunc(16, on_timer, 1);
}

int main(int argc, char** argv) {
  if (0 == args_process(argc, argv, &sim))
    return 1;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("mini-universe");

  glutReshapeFunc(on_reshape);
  glutDisplayFunc(on_display);
  glutKeyboardFunc(on_keyboard);
  glutTimerFunc(0, on_timer, 1);

  glutMainLoop();

  return 0;
}
