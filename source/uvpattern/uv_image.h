/*
 *  DoRayMe - a quick and dirty Raytracer
 *  UV Image pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#ifndef DORAYME_UV_IMAGE_H
#define DORAYME_UV_IMAGE_H

#include <stdint.h>

#include <uv_pattern.h>
#include <canvas.h>
#include <tuple.h>

class UVImage : public UVPattern
{
public:
    Canvas *image;

    UVImage(Canvas *image) : UVPattern(1, 1, Colour(0, 0, 0), Colour(0, 0, 0)),
            image(image) {};

    UVImage(const char *filepath) : UVPattern(1, 1, Colour(0, 0, 0), Colour(0, 0, 0)) {
        this->image = new Canvas(filepath);
        this->width = this->image->width;
        this->height = this->image->height;
    };

    Colour uvPatternAt(double u, double v) {
        v = 1 - v;
        double x = u * (this->image->width/2.0 - 1);
        double y = v * (this->image->height/2.0 - 1);

        Colour ret = this->image->getPixel(round(x), round(y));
        return ret;
    };
};

#endif /* DORAYME_UV_IMAGE_H */
