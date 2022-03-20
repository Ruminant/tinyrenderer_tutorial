#include "triangle.h"
#include "line.h"
void triangle(const Vec2i &t0, const Vec2i &t1, const Vec2i &t2, Image &image, const Colour &col)
{
    line(t0.x, t0.y, t1.x, t1.y, image, col);
    line(t1.x, t1.y, t2.x, t2.y, image, col);
    line(t2.x, t2.y, t0.x, t0.y, image, col);
}