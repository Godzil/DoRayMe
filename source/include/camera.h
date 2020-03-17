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
    double focalDistance;
    double apertureSize;
    uint32_t rayCount;

    uint32_t verticalSize;
    uint32_t horizontalSize;
    double fieldOfView;
    double pixelSize;
    Matrix transformMatrix;
    Matrix inverseTransform;

public:
    Camera(uint32_t hsize, uint32_t vsize, double fov, double focal = 1, double aperture = 0, uint32_t rayCount = 1);
    void setTransform(Matrix transform);
    Ray rayForPixel(uint32_t pixelX, uint32_t pixelY, double horzOffset = 0, double vertOffset = 0);
    Canvas render(World w, uint32_t depth = 5);
};

#endif /* DORAYME_CAMERA_H */
