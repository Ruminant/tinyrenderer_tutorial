#include "triangle.h"
#include "line.h"


/**
 * @brief draw the triangle outline
 * 
 */
void triangle_outline(const Vec2i &t0, const Vec2i &t1, const Vec2i &t2, Image &image, const Colour &col)
{
    line(t0.x, t0.y, t1.x, t1.y, image, col);
    line(t1.x, t1.y, t2.x, t2.y, image, col);
    line(t2.x, t2.y, t0.x, t0.y, image, col);
}

/**
 * @brief naive filling of triangle, we fill lines in horizontally
 * 
 */
void triangle( Vec2i t0, Vec2i t1, Vec2i t2, Image &image, const Colour &col)
{
    // sort by Y
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);

    int total_height = t2.y - t0.y;

    for (int y=t0.y; y <= t1.y; ++y) 
    {
        int segment_height = t1.y - t0.y + 1;
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t0.y) / segment_height;
        Vec2i A = t0 + (t2-t0) * alpha;
        Vec2i B = t0 + (t1-t0) * beta;
        if (A.x>B.x) std::swap(A, B); 
        for (int x=A.x; x<=B.x; ++x)
            image.set(x, y, col);
    }

    for (int y=t1.y; y <= t2.y; ++y) 
    {
        int segment_height = t2.y - t1.y + 1;
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t1.y) / segment_height;
        Vec2i A = t0 + (t2-t0) * alpha;
        Vec2i B = t1 + (t2-t1) * beta;
        if (A.x>B.x) std::swap(A, B); 
        for (int x = A.x; x<=B.x; ++x)
            image.set(x, y, col);

    }

    // line(t0.x, t0.y, t1.x, t1.y, image, Colours::Yellow);
    // line(t1.x, t1.y, t2.x, t2.y, image, Colours::Yellow);
    // line(t2.x, t2.y, t0.x, t0.y, image, Colours::Red);
}