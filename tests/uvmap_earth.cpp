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
#include <cylinder.h>

#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>

#include <pattern.h>
#include <texturemap.h>
#include <uv_image.h>

#include <transformation.h>

int main()
{
    World w = World();

    Light light = Light(POINT_LIGHT, Point(-100, 100, -100), Colour(1, 1, 1));
    w.addLight(&light);

    Plane p = Plane();
    p.material.colour = Colour(1, 1, 1);
    p.material.diffuse = 0.1;
    p.material.specular = 0;
    p.material.ambient = 0;
    p.material.reflective = 0.4;
    w.addObject(&p);

    Cylinder cyl = Cylinder();
    cyl.minCap = 0;
    cyl.maxCap = 0.1;
    cyl.isClosed = true;
    cyl.material.colour = Colour(1, 1, 1);
    cyl.material.diffuse = 0.2;
    cyl.material.specular = 0;
    cyl.material.ambient = 0;
    cyl.material.reflective = 0.1;
    w.addObject(&cyl);

    Sphere sp = Sphere();

    UVImage sphereTexture = UVImage("earthmap1k.png");
    TextureMap tm = TextureMap(SPHERICAL_MAP, &sphereTexture);
    sp.setTransform(translation(0, 1.1, 0) * rotationY(1.9));
    sp.material.pattern = &tm;
    sp.material.ambient = 0.1;
    sp.material.specular = 0.1;
    sp.material.shininess = 10;
    sp.material.diffuse = 0.9;
    w.addObject(&sp);

    /* Set the camera */
    Camera camera = Camera(800, 400, 0.8);
    camera.setTransform(viewTransform(Point(1, 2, -10),
                                      Point(0, 1.1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("uvmap_earth.png");

    return 0;
}