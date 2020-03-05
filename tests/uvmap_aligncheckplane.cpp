/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Plane with alignment check pattern for bonus chapter UV Mapping
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
#include <uv_aligncheck.h>

#include <transformation.h>

int main()
{
    World w = World();

    Light light = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));
    w.addLight(&light);

    Plane sp = Plane();
    UVAlignCheck checkers = UVAlignCheck(Colour(1, 1, 1),
                                         Colour(1, 0, 0),
                                         Colour(1, 1, 0),
                                         Colour(0, 1, 0),
                                         Colour(0, 1, 1)
                                         );
    TextureMap tm = TextureMap(PLANAR_MAP, &checkers);
    sp.material.pattern = &tm;
    sp.material.ambient = 0.1;
    sp.material.diffuse = 0.8;

    w.addObject(&sp);

    /* Set the camera */
    Camera camera = Camera(400, 400, 0.5);
    camera.setTransform(viewTransform(Point(1, 2, -5),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("uvmap_aligncheckplane.png");

    return 0;
}