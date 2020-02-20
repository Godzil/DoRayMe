/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Canvas header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CANVAS_H
#define DORAYME_CANVAS_H

#include <stdint.h>
#include <colour.h>

class Canvas
{
private:
    uint8_t *bitmap;
    uint32_t stride;
public:
    uint32_t width, height;

    Canvas(uint32_t width, uint32_t height);
    Canvas(const Canvas *c);
    Canvas(const Canvas &c);
    ~Canvas();

    void putPixel(uint32_t x, uint32_t y, Tuple c);
    Colour getPixel(uint32_t x, uint32_t y);

    bool SaveAsPNG(const char *filename);
};

#endif /* DORAYME_CANVAS_H */
