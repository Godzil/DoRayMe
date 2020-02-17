/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Canvas implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <canvas.h>
#include <lodepng.h>

#define BPP (24)
#define BytePP (BPP / 8)

#define MIN(_a, _b) ((_a)<(_b)?(_a):(_b))
#define MAX(_a, _b) ((_a)>(_b)?(_a):(_b))

Canvas::Canvas(uint32_t width, uint32_t height) : width(width), height(height)
{
    this->bitmap = (uint8_t *)calloc(4, width * height);
    this->stride = BytePP * width;
}

Canvas::~Canvas()
{
    if (this->bitmap != nullptr)
    {
        free(this->bitmap);
    }
}

void Canvas::put_pixel(uint32_t x, uint32_t y, Colour c)
{
    uint32_t offset = y * this->stride + x * BytePP;
    this->bitmap[offset + 0] = MAX(MIN(c.red() * 255, 255), 0);
    this->bitmap[offset + 1] = MAX(MIN(c.green() * 255, 255), 0);
    this->bitmap[offset + 2] = MAX(MIN(c.blue() * 255, 255), 0);
}

Colour Canvas::get_pixel(uint32_t x, uint32_t y)
{
    uint32_t offset = y * this->stride + x * BytePP;
    return Colour(this->bitmap[offset + 0] / 255, this->bitmap[offset + 1] / 255, this->bitmap[offset + 2] / 255);
}

bool Canvas::SaveAsPNG(const char *filename)
{
    uint32_t ret = lodepng_encode24_file(filename, this->bitmap, this->width, this->height);

    return ret == 0;
}