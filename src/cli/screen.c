#include <stdlib.h>

#include "screen.h"

void screen_init(screen *scr, unsigned char width, unsigned char height) {
  scr->dimensions.x = width;
  scr->dimensions.y = height;
  scr->buffer = (unsigned char*)malloc(sizeof(unsigned char) * scr->dimensions.x * scr->dimensions.y);
}

void screen_free(screen *scr) {
    free(scr->buffer);
}
