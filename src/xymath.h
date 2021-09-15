#ifndef __XYMATH_H__
#define __XYMATH_H__

#include <math.h>

#define XY_ADD(a,b) {a.x += b.x; a.y += b.y;}
#define XY_ADDW(a,b,w) {a.x += b.x * w; a.y += b.y * w;}
#define XY_SCALE(a,w) {a.x *= w; a.y *= w;}
#define XY_SUB(a,b) {a.x -= b.x; a.y -= b.y;}
#define XY_DIST2(a,b) ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))
#define XY_DIST(a,b) (sqrt(XY_DIST2(a,b)))
#define XY_COPY(dst,src) {dst.x = src.x; dst.y = src.y;}
#define XY_NEGATE(a) {a.x = -a.x; a.y = -a.y;}
#define XY_NORMALIZE(a) {double d = sqrt(a.x * a.x + a.y * a.y);  if(d) {a.x /= d; a.y /= d;}}

#endif /* ifndef __XYMATH_H__ */

