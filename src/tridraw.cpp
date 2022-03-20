/**
 * @file tridraw.cpp
 * @author pritpal s panesar (pritpal.panesar@sony.com)
 * @brief draw triangles
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include "image.h"
#include "line.h"
#include "triangle.h"
#include "model.h"

/**
 * @brief Draw a wavefront obj model using lines
 * 
 * @param model A valid loaded model instance
 */
void draw_model(Image &image, const Model &model)
{
    const int face_count = model.nfaces();
    const int width = image.get_width();
    const int height = image.get_height();

    for (int f = 0; f < face_count; ++f)
    {
        const auto &face = model.face(f);
        int previous_idx = 0;
        const Vec3f &v0 = model.vert(face[0]);
        const Vec3f &v1 = model.vert(face[1]);
        const Vec3f &v2 = model.vert(face[2]);
        int x0 = static_cast<int>((v0.x + 1.f) * width/2.f);
        int y0 = static_cast<int>((v0.y + 1.f) * height/2.f);
        int x1 = static_cast<int>((v1.x + 1.f) * width/2.f);
        int y1 = static_cast<int>((v1.y + 1.f) * height/2.f);
        int x2 = static_cast<int>((v2.x + 1.f) * width/2.f);
        int y2 = static_cast<int>((v2.y + 1.f) * height/2.f);
            
        triangle(
            Vec2i(x0, y0),
            Vec2i(x1, y1),
            Vec2i(x2, y2), image, Colours::White);
    }
}

int main()
{
      
    Image image("tri", 200, 200);
    
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
    triangle(t0[0], t0[1], t0[2], image, Colours::Red); 
    triangle(t1[0], t1[1], t1[2], image, Colours::White); 
    triangle(t2[0], t2[1], t2[2], image, Colours::Grey);

    image.show();

    
    return 0;
}