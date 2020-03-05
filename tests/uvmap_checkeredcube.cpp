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
#include <cube.h>
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>

#include <pattern.h>
#include <texturemap.h>
#include <uv_aligncheck.h>

#include <transformation.h>

Colour red = Colour(1, 0, 0);
Colour yellow = Colour(1, 1, 0);
Colour brown = Colour(1, 0.5, 0);
Colour green = Colour(0, 1, 0);
Colour cyan = Colour(0, 1, 1);
Colour blue = Colour(0, 0, 1);
Colour purple = Colour(1, 0, 1);
Colour white = Colour(1, 1, 1);

UVAlignCheck left = UVAlignCheck(yellow, cyan, red, blue, brown);
UVAlignCheck front = UVAlignCheck(cyan, red, yellow, brown, green);
UVAlignCheck right = UVAlignCheck(red, yellow, purple, green, white);
UVAlignCheck back = UVAlignCheck(green, purple, cyan, white, blue);
UVAlignCheck up = UVAlignCheck(brown, cyan, purple, red, yellow);
UVAlignCheck down = UVAlignCheck(purple, brown, green, blue, white);

Shape *MappedCube()
{
    Cube *ret = new Cube();
    TextureMap *tm =  new TextureMap(CUBIC_MAP, nullptr);
    tm->setCubePattern(&front, &left, &right, &back, &up, &down);
    ret->material.pattern = tm;
    ret->material.ambient = 0.2;
    ret->material.specular = 0;
    ret->material.diffuse = 0.8;

    return ret;
}

int main()
{
    World w = World();

    Light light1 = Light(POINT_LIGHT, Point(0, 100, -100), Colour(0.25, 0.25, 0.25));
    w.addLight(&light1);
    Light light2 = Light(POINT_LIGHT, Point(0, -100, -100), Colour(0.25, 0.25, 0.25));
    w.addLight(&light2);
    Light light3 = Light(POINT_LIGHT, Point(-100, 0, -100), Colour(0.25, 0.25, 0.25));
    w.addLight(&light3);
    Light light4 = Light(POINT_LIGHT, Point(100, 0, -100), Colour(0.25, 0.25, 0.25));
    w.addLight(&light4);

    Shape *s;

    s = MappedCube();
    s->setTransform(translation(-6, 2, 0) * rotationX(0.7854) * rotationY(0.7854));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(-2, 2, 0) * rotationX(0.7854) * rotationY(2.3562));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(2, 2, 0) * rotationX(0.7854) * rotationY(3.927));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(6, 2, 0) * rotationX(0.7854) * rotationY(5.4978));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(-6, -2, 0) * rotationX(-0.7854) * rotationY(0.7854));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(-2, -2, 0) * rotationX(-0.7854) * rotationY(2.3562));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(2, -2, 0) * rotationX(-0.7854) * rotationY(3.927));
    w.addObject(s);

    s = MappedCube();
    s->setTransform(translation(6, -2, 0) * rotationX(-0.7854) * rotationY(5.4978));
    w.addObject(s);

    /* Set the camera */
    Camera camera = Camera(800, 400, 0.8);
    camera.setTransform(viewTransform(Point(0, 0, -20),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("uvmap_checkeredcube.png");

    return 0;
}