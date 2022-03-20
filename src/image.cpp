#pragma once
#include "image.h"
#include <PixelToaster.h>
#include <ctime>
#include <cmath>

namespace pt = PixelToaster;

struct Image::Pimpl
{
    pt::Display *display;
    pt::TrueColorPixel *pixels;
};

Image::Image(const char *title, unsigned int width, unsigned int height)
    : m_width(width)
    , m_height(height)
    
{
    m_size = width * height;
    m_pimpl = new Image::Pimpl;
    m_pimpl->display = new pt::Display(title, width, height);
    m_pimpl->pixels = new pt::TrueColorPixel[m_size];
}

Image::~Image()
{   
    if (m_pimpl)
    {
        delete m_pimpl->display;
        delete m_pimpl->pixels;
        delete m_pimpl;
    }
}

void Image::set(unsigned int x, unsigned int y, const Colour &colour)
{
    if (y < m_height && x < m_width)
    {
        const unsigned int index = (m_height - y) * m_width + x;
        m_pimpl->pixels[index] = pt::TrueColorPixel(colour.col);
    }
}

void Image::show()
{
    while (m_pimpl && m_pimpl->display && m_pimpl->display->open())
    {
        m_pimpl->display->update(m_pimpl->pixels);
    }
}

void Timer::start()
{
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void Timer::stop()
{
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double Timer::elapsedMilliseconds()
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

double Timer::elapsedSeconds()
{
    return elapsedMilliseconds() / 1000.0;
}
