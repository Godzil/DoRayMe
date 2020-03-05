/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Checkered cylinder for bonus chapter UV Mapping
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <sphere.h>
#include <plane.h>
#include <cylinder.h>
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>

#include <pattern.h>
#include <texturemap.h>
#include <uv_checkers.h>

#include <transformation.h>

int main()
{
    World w = World();

    Light light = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));
    w.addLight(&light);

    Cylinder sp = Cylinder();
    sp.minCap = 0;
    sp.maxCap = 1;
    sp.setTransform(scaling(1, 3.1415, 1) * translation(0, -0.5, 0));
    UVCheckers checkers = UVCheckers(16, 8, Colour(0, 0.5, 0), Colour(1, 1, 1));
    TextureMap tm = TextureMap(CYLINDRICAL_MAP, &checkers);
    sp.material.pattern = &tm;
    sp.material.ambient = 0.1;
    sp.material.specular = 0.6;
    sp.material.shininess = 15;
    sp.material.diffuse = 0.8;

    w.addObject(&sp);

    /* Set the camera */
    Camera camera = Camera(400, 400, 0.5);
    camera.setTransform(viewTransform(Point(0, 0, -10),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("uvmap_checkeredcylinder.png");

    return 0;
}