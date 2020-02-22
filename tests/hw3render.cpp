/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Renderer using hw3 files as world builder.
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <stdio.h>

#include <world.h>
#include <worldbuilder.h>
#include <light.h>
#include <sphere.h>
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>
#include <transformation.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usage: %s file.hw3\n", argv[0]);
        return -1;
    }

    Hw3File world = Hw3File(argv[1]);

    /* Set the camera resolution */
    Camera cam = Camera(640, 480, world.camFoV);

    cam.setTransform(world.cam);

    /* Now render it */
    Canvas image = cam.render(world);

    image.SaveAsPNG("hw3render.png");

    return 0;
}