/**
 * @file linedrawing.cpp
 * @author pritpal s panesar (pritpal.panesar@sony.com)
 * @brief in which we attempt to render a line using Bresenham's line algorithm
 * @version 0.1
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <cstdlib>
#include <utility>
#include <iostream>
#include "image.h"
/**
 * @brief Draw a line from x0,y0 to x1,y1
 * 
 * naive first approach, fill in the line in tiny increments.
 * We use interpolation between points.
 *  
 */
void line1(int x0, int y0, int x1, int y1, Image &image, const Colour &colour)
{
    const float step_size = 0.01f;
    for (float t=0.f; t < 1.f; t += step_size)
    {
        int x = lerp(x0, x1, t);
        int y = lerp(y0, y1, t);
        image.set(x, y, colour);
    }
}

/**
 * @brief second line approach
 * 
 * Instead of assuming tiny increments, we move along one axis in pixels.
 * As we move, we work out how far along we are (from 0 to 1), and use that
 * to calculate the other axis (as an interpolation).
 * 
 * For 10,000,000 iterations, took 3873 ms
 */
void line2(int x0, int y0, int x1, int y1, Image &image, const Colour &colour)
{
    bool bSwappedAxis = false;

    // if Y is taller, just switch with X, giving us more accuracy
    if (std::abs(x0-x1) < std::abs(y0-y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        bSwappedAxis = true;
    }

    // ensure we draw in one direction
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    // move along the X in fixed steps
    for (int x = x0; x < x1; ++x)
    {
        // find out how far along the X we are
        float t = (x-x0) / (float)(x1-x0);
        int y = lerp(y0, y1, t);
        if (bSwappedAxis)
            image.set(y, x, colour);    // fix our swapped axis
        else
            image.set(x, y, colour);
    }
}

/* For 10,000,000 iterations, took 1818 ms */
void line2_optimised(int x0, int y0, int x1, int y1, Image &image, const Colour &colour)
{
    bool bSwappedAxis = false;

    // if Y is taller, just switch with X, giving us more accuracy
    if (std::abs(x0-x1) < std::abs(y0-y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        bSwappedAxis = true;
    }

    // ensure we draw in one direction
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    // move along the X in fixed steps
    const int dx = x1 - x0;
    const int dy = y1 - y0;

    // why is float faster?
#define USE_FLOAT 1
#if USE_FLOAT
    float derror = std::abs(dy/float(dx)); 
    float error = 0.f;
    #define wrap_error if ((error += derror) > 0.5f) { y += yincr; error -= 1.f; }
#else
    const int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    #define wrap_error if ((error2 += derror2) > dx) { y += yincr; error2 -= dx2; }
#endif


    int y = y0;
    int yincr = y1 > y0? 1 : -1;
    int dx2 = dx * 2;
    if (bSwappedAxis)
        for (int x = x0; x < x1; ++x)
        {
            image.set(y, x, colour);    // fix our swapped axis
            wrap_error;
        }
    else
        for (int x = x0; x < x1; ++x)
        {
            image.set(x, y, colour);    // fix our swapped axis
            wrap_error;
        }

#undef USE_FLOAT
}

#define line line2_optimised

int main()
{
    Image image("linedrawing", 640, 480);

    Timer timer;
    timer.start();

    for (int i = 0; i < 10000000; ++i)
    {
        line(13, 20, 80, 40, image, Colours::White); 
        line(20, 13, 40, 80, image, Colours::Red); 
        line(80, 40, 13, 20, image, Colours::Red);
    }

    timer.stop();

    std::cout << "time taken: " << timer.elapsedMilliseconds() << std::endl;

    image.show();


    return 0;
}