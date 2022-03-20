/**
 * @file modeldraw.cpp
 * @author pritpal s panesar (pritpal.panesar@sony.com)
 * @brief in which we attempt to render a wavefront model using lines
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <filesystem>
#include "image.h"
#include "line.h"
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
        for (int i = 0; i < face.size(); i++)
        {
            int previous_idx = i==0 ? face.back() : face[i - 1];
            int idx = face[i];
            Vec3f v0 = model.vert(previous_idx);
            Vec3f v1 = model.vert(idx);
            int x0 = static_cast<int>((v0.x + 1.f) * width/2.f);
            int y0 = static_cast<int>((v0.y + 1.f) * height/2.f);
            int x1 = static_cast<int>((v1.x + 1.f) * width/2.f);
            int y1 = static_cast<int>((v1.y + 1.f) * height/2.f);
            line(x0, y0, x1, y1, image, Colours::White);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::filesystem::path model_path(argv[1]);
        if (!std::filesystem::exists(model_path))
        {
            std::cout << "failed to open file " << model_path << std::endl;
            return 1;
        }

        Model model(model_path.u8string().c_str());
        
        Image image("modeldraw", 512, 512);
        draw_model(image, model);
        image.show();

    }
    return 0;
}