#pragma once

#include <stdint.h>
#include <chrono>

/**
 * @brief simple RGBA colour struct (32-bit)
 * 
 * For convenience you can use 4 bytes of R, G, B and A,
 * or opt for a 32-bit integer version.
 * 
 */
struct Colour
{
    union {
        struct {
            uint8_t r, g, b, a;
        };
        uint32_t col = 0x0;
    };

    Colour(uint8_t rin, uint8_t gin, uint8_t bin, uint8_t ain=0xff)
        : r(rin)
        , g(gin)
        , b(bin)
        , a(ain) {}

    Colour(uint32_t cin)
        : col(cin)
        {}

    Colour():col(0) {}

};

namespace Colours
{
    const Colour Red = Colour(0xff, 0x00, 0x00);
    const Colour Blue = Colour(0x00, 0x00, 0xff);
    const Colour White = Colour(0xff, 0xff, 0xff);
    const Colour Grey = Colour(0xaa, 0xaa, 0xaa);
    const Colour Yellow = Colour(0xff, 0xff, 0x00);
    const Colour Orange = Colour(0xff, 0x80, 0x00);
}

class Image
{
public:
    Image(const char *title, unsigned int width, unsigned int height);
    ~Image();
    void set(unsigned int x, unsigned int y, const Colour &color);
    void show();
    unsigned int get_width() const { return m_width; }
    unsigned int get_height() const { return m_height; }
protected:
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_size;
    struct Pimpl;
    Pimpl *m_pimpl = nullptr;

};



class Timer
{
public:
    void start();
    void stop();
    double elapsedMilliseconds();
    double elapsedSeconds();

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};