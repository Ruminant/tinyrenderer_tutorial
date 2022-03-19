#include <PixelToaster.h>
#include <chrono>
#include <ctime>
#include <cmath>

namespace pt = PixelToaster;

using Colour = PixelToaster::TrueColorPixel;

namespace Colours
{
    Colour Red = Colour(0xff, 0x00, 0x00);
    Colour Blue = Colour(0x00, 0x00, 0xff);
    Colour White = Colour(0xff, 0xff, 0xff);
    Colour Grey = Colour(0xaa, 0xaa, 0xaa);
    Colour Yellow = Colour(0xff, 0xff, 0x00);
    Colour Orange = Colour(0xff, 0x80, 0x00);
}

class Image
{
public:
    Image(const char *title, unsigned int width, unsigned int height)
        : m_width(width)
        , m_height(height)
        , m_display(title, width, height)
    {
        m_size = width * height;
        m_pixels = new Colour[m_size];
    }

    ~Image()
    {   
        delete [] m_pixels;
    }

    void set(unsigned int x, unsigned int y, const Colour &color)
    {
        if (y < m_height && x < m_width)
        {
            const unsigned int index = (m_height - y) * m_width + x;
            m_pixels[index] = color;
        }
    }

    void show()
    {
        while (m_display.open())
        {
            m_display.update(m_pixels);
        }
    }

protected:
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_size;
    pt::Display m_display;
    Colour *m_pixels;
};

template<typename T>
T lerp(T a, T b, float alpha)
{
    return a + static_cast<T>((b - a) * alpha);
}

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count());
    }
    
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};