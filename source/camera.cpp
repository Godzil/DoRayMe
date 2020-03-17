/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Camera implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <matrix.h>
#include <stdint.h>
#include <math.h>
#include <ray.h>
#include <camera.h>

#include <stdio.h>
#include <renderstat.h>

Camera::Camera(uint32_t hsize, uint32_t vsize, double fov) : verticalSize(vsize),
               horizontalSize(hsize), fieldOfView(fov), focalDistance(1), apertureSize(0), rayCount(1)
{
    double aspectRatio = (double)hsize / (double)vsize;
    double halfView = tan(fov / 2.0) * this->focalDistance;

    if (aspectRatio >= 1)
    {
        this->halfWidth = halfView;
        this->halfHeight = halfView / aspectRatio;
    }
    else
    {
        this->halfWidth = halfView * aspectRatio;
        this->halfHeight = halfView;
    }

    this->pixelSize = (this->halfWidth * 2) / this->horizontalSize;

    this->setTransform(Matrix4().identity());
}

void Camera::setTransform(Matrix transform)
{
    this->transformMatrix = transform;
    this->inverseTransform = transform.inverse();
}

Ray Camera::rayForPixel(uint32_t pixelX, uint32_t pixelY, double horzOffset, double vertOffset)
{
    double xOffset = ((double)pixelX + 0.5) * this->pixelSize;
    double yOffset = ((double)pixelY + 0.5) * this->pixelSize;

    double worldX = this->halfWidth - xOffset;
    double worldY = this->halfHeight - yOffset;

    Tuple pixel = this->inverseTransform * Point(worldX, worldY, -this->focalDistance);
    Tuple origin = this->inverseTransform * Point(horzOffset,  vertOffset, 0);
    Tuple direction = (pixel - origin).normalise();

    stats.addCastedRay();
    return Ray(origin, direction);
}

Canvas Camera::render(World world, uint32_t depth)
{
    uint32_t x, y;
    Canvas image = Canvas(this->horizontalSize, this->verticalSize);

    #pragma omp parallel default(shared) private(x, y) shared(image, stats)
    {
        #pragma omp for schedule(dynamic, 5)
        for (y = 0 ; y < this->verticalSize ; y++)
        {
            for (x = 0 ; x < this->horizontalSize ; x++)
            {
                Tuple colour;
                if (this->apertureSize > 0)
                {
                    int i;
                    for (i = 0 ; i < this->rayCount ; i++)
                    {
                        double horz = frandclip(-this->apertureSize/2, this->apertureSize / 2);
                        double vert = frandclip(-this->apertureSize/2, this->apertureSize / 2);
                        Ray r = this->rayForPixel(x, y, horz, vert);
                        colour = colour + world.colourAt(r, depth);
                    }

                    colour = colour / this->rayCount;
                }
                else
                {
                    Ray r = this->rayForPixel(x, y);
                    colour = world.colourAt(r, depth);
                }
                stats.addPixel();
                image.putPixel(x, y, colour);
            }
        }
    }

    stats.printStats();

    return image;
}