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

#include <iostream>
#include "image.h"
#include "line.h"

#define PROFILE_CODE 0

int main()
{
    Image image("linedrawing", 640, 480);

#if PROFILE_CODE
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
#else

    line(13, 20, 80, 40, image, Colours::White); 
    line(20, 13, 40, 80, image, Colours::Red); 
    line(80, 40, 13, 20, image, Colours::Red);
    image.show();

#endif

    return 0;
}