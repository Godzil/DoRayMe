/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Skybox test for bonus chapter UV Mapping
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <sphere.h>
#include <plane.h>
#include <cube.h>
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

    Light light = Light(POINT_LIGHT, Point(0, 100, 0), Colour(1, 1, 1));
    w.addLight(&light);

    Sphere sp = Sphere();
    sp.setTransform(translation(0, 0, 5) * scaling(0.75, 0.75, 0.75));
    sp.material.diffuse = 0.4;
    sp.material.specular = 0.6;
    sp.material.shininess = 20;
    sp.material.reflective = 0.6;
    sp.material.ambient = 0;
    w.addObject(&sp);

    UVImage left = UVImage("negx.jpg");
    UVImage right = UVImage("posx.jpg");
    UVImage front = UVImage("posz.jpg");
    UVImage back = UVImage("negz.jpg");
    UVImage up = UVImage("posy.jpg");
    UVImage down = UVImage("negy.jpg");

    Cube cb = Cube();
    TextureMap tm = TextureMap(CUBIC_MAP, nullptr);
    tm.setCubePattern(&front, &left, &right, &back, &up, &down);
    cb.material.pattern = &tm;
    cb.material.diffuse = 0;
    cb.material.specular = 0;
    cb.material.ambient = 1;
    cb.setTransform(scaling(1000, 1000, 1000));
    w.addObject(&cb);

    /* Set the camera */
    Camera camera = Camera(800, 400, 1.2);
    camera.setTransform(viewTransform(Point(0, 0, 0),
                                      Point(0, 0, 5),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("uvmap_skybox.png");

    return 0;
}