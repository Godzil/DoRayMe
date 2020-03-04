/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for chapter 10
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <sphere.h>
#include <plane.h>
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

    Sphere sp = Sphere();
    UVCheckers checkers = UVCheckers(20, 10, Colour(0, 0.5, 0), Colour(1, 1, 1));
    TextureMap tm = TextureMap(SPHERICAL_MAP, &checkers);
    sp.material.pattern = &tm;
    sp.material.ambient = 0.1;
    sp.material.specular = 0.4;
    sp.material.shininess = 10;
    sp.material.diffuse = 0.6;

    w.addObject(&sp);

    /* Set the camera */
    Camera camera = Camera(400, 400, 0.5);
    camera.setTransform(viewTransform(Point(0, 0, -5),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("uvmap_checkeredsphere.png");

    return 0;
}