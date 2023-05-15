#ifndef __SCREEN_H__
#define __SCREEN_H__

#define MAX_SCREEN_DIMENSION 256

typedef struct {unsigned char x, y;} xy;

typedef struct {
  xy dimensions;
  unsigned char* buffer; // X=0,Y=0 is upper left
} screen;

void screen_init(screen *scr, unsigned char width, unsigned char height);
void screen_free(screen *scr);

#endif /* ifndef __SCREEN_H__ */
