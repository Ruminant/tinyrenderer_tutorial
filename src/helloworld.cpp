#include <PixelToaster.h>

namespace pt = PixelToaster;

int main()
{
    pt::Display display("Hello, World", 640, 480);
    pt::TrueColorPixel *pixels = new pt::TrueColorPixel[640*480];
    for (auto y = 32; y < 480-32; ++y)
        for (auto x = 32; x < 640-32; ++x)
        {
            pixels[y * 640 + x].integer = 0xffffffff;
        }
        
    while (display.open())
    {
        display.update(pixels);
    }
    return 0;
}