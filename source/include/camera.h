/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Camera header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CAMERA_H
#define DORAYME_CAMERA_H

#include <matrix.h>
#include <stdint.h>
#include <ray.h>
#include <canvas.h>
#include <world.h>

class Camera
{
private:
    double halfWidth;
    double halfHeight;
public:
    uint32_t verticalSize;
    uint32_t horizontalSize;
    double fieldOfView;
    double pixelSize;
    Matrix transformMatrix;
    Matrix inverseTransform;

public:
    Camera(uint32_t hsize, uint32_t vsize, double fov);
    void setTransform(Matrix transform);
    Ray rayForPixel(uint32_t pixelX, uint32_t pixelY);
    Canvas render(World w, uint32_t depth = 5);
};

#endif /* DORAYME_CAMERA_H */
