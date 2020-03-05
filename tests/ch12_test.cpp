/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for cubes in chapter 12.
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
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>
#include <checkerspattern.h>
#include <ringpattern.h>

#include <transformation.h>

int main()
{
    World w = World();

    /* Add light */
    Light light = Light(POINT_LIGHT, Point(0, 6.9, -5), Colour(1, 1, 0.9));
    w.addLight(&light);

    /* ----------------------------- */

    /* The floor / ceiling */
    Cube floor = Cube();
    floor.setTransform( scaling(20, 7, 20) * translation(0, 1, 0));
    floor.material.pattern = new CheckersPattern(Colour(0, 0, 0), Colour(0.25, 0.25, 0.25));
    floor.material.pattern->setTransform(scaling(0.07, 0.07, 0.07));
    floor.material.ambient = 0.25;
    floor.material.diffuse = 0.7;
    floor.material.specular = 0.9;
    floor.material.shininess = 300;
    floor.material.reflective = 0.1;
    w.addObject(&floor);

    /* Walls */
    Cube walls = Cube();
    walls.setTransform(scaling(10, 10, 10));
    walls.material.pattern = new CheckersPattern(Colour( 0.4863, 0.3765, 0.2941), Colour(0.3725, 0.2902, 0.2275 ));
    walls.material.pattern->setTransform(scaling(0.05, 20, 0.05));
    walls.material.ambient = 0.1;
    walls.material.diffuse = 0.7;
    walls.material.specular = 0.9;
    walls.material.shininess = 300;
    walls.material.reflective = 0.1;
    w.addObject(&walls);

    /* Table top */
    Cube tableTop = Cube();
    tableTop.setTransform(translation(0, 3.1, 0) * scaling(3, 0.1, 2));
    tableTop.material.pattern = new StripPattern(Colour(0.5529, 0.4235, 0.3255), Colour(0.6588, 0.5098, 0.4000 ));
    tableTop.material.pattern->setTransform(scaling(0.05, 0.05, 0.05) * rotationY(0.1));
    tableTop.material.ambient = 0.1;
    tableTop.material.diffuse = 0.7;
    tableTop.material.specular = 0.9;
    tableTop.material.shininess = 300;
    tableTop.material.reflective = 0.2;
    w.addObject(&tableTop);

    /* Leg 1 */
    Cube leg1 = Cube();
    leg1.setTransform(translation(2.7, 1.5, -1.7) * scaling(0.1, 1.5, 0.1));
    leg1.material.colour = Colour(0.5529, 0.4235, 0.3255);
    leg1.material.ambient = 0.2;
    leg1.material.diffuse = 0.7;
    w.addObject(&leg1);

    /* Leg 2 */
    Cube leg2 = Cube();
    leg2.setTransform(translation(2.7, 1.5, 1.7) * scaling(0.1, 1.5, 0.1));
    leg2.material.colour = Colour(0.5529, 0.4235, 0.3255);
    leg2.material.ambient = 0.2;
    leg2.material.diffuse = 0.7;
    w.addObject(&leg2);

    /* Leg 3 */
    Cube leg3 = Cube();
    leg3.setTransform(translation(-2.7, 1.5, -1.7) * scaling(0.1, 1.5, 0.1));
    leg3.material.colour = Colour(0.5529, 0.4235, 0.3255);
    leg3.material.ambient = 0.2;
    leg3.material.diffuse = 0.7;
    w.addObject(&leg3);

    /* Leg 4 */
    Cube leg4 = Cube();
    leg4.setTransform(translation(-2.7, 1.5, 1.7) * scaling(0.1, 1.5, 0.1));
    leg4.material.colour = Colour(0.5529, 0.4235, 0.3255);
    leg4.material.ambient = 0.2;
    leg4.material.diffuse = 0.7;
    w.addObject(&leg4);

    /* ----------------------------- */

    /* Glass cube */
    Cube glassCube = Cube();
    glassCube.setTransform(translation(0, 3.45001, 0) * rotationY(0.2) * scaling(0.25, 0.25, 0.25));
    glassCube.dropShadow = false;
    glassCube.material.colour = Colour(1, 1, 0.8);
    glassCube.material.ambient = 0;
    glassCube.material.diffuse = 0.3;
    glassCube.material.specular = 0.9;
    glassCube.material.shininess = 300;
    glassCube.material.reflective = 0.7;
    glassCube.material.transparency = 0.7;
    glassCube.material.refractiveIndex = 1.5;
    w.addObject(&glassCube);

    /* Little cube 1 */
    Cube lilCube1 = Cube();
    lilCube1.setTransform(translation(1, 3.35, -0.9) *
                           rotationY(-0.4) *
                           scaling(0.15, 0.15, 0.15));
    lilCube1.material.colour = Colour(1, 0.5, 0.5);
    lilCube1.material.reflective = 0.6;
    lilCube1.material.diffuse = 0.4;
    w.addObject(&lilCube1);

    /* Little cube 2 */
    Cube lilCube2 = Cube();
    lilCube2.setTransform(translation(-1.5, 3.27, 0.3) *
                          rotationY(0.4) *
                          scaling(0.15, 0.07, 0.15));
    lilCube2.material.colour = Colour(1, 1, 0.5);
    w.addObject(&lilCube2);

    /* Little cube 3 */
    Cube lilCube3 = Cube();
    lilCube3.setTransform(translation(0, 3.25, 1) *
                          rotationY(0.4) *
                          scaling(0.2, 0.05, 0.05));
    lilCube3.material.colour = Colour(0.5, 1, 0.5);
    w.addObject(&lilCube3);

    /* Little cube 4 */
    Cube lilCube4 = Cube();
    lilCube4.setTransform(translation(-0.6, 3.4, -1) *
                          rotationY(0.8) *
                          scaling(0.05, 0.2, 0.05));
    lilCube4.material.colour = Colour(0.5, 0.5, 1);
    w.addObject(&lilCube4);

    /* Little cube 5 */
    Cube lilCube5 = Cube();
    lilCube5.setTransform(translation(2, 3.4, 1) *
                          rotationY(0.8) *
                          scaling(0.05, 0.2, 0.05));
    lilCube5.material.colour = Colour(0.5, 1, 1);
    w.addObject(&lilCube5);

    /* ----------------------------- */

    /* Frame 1 */
    Cube frame1 = Cube();
    frame1.setTransform(translation(-10, 4, 1) * scaling(0.05, 1, 1));
    frame1.material.colour = Colour(0.7098, 0.2471, 0.2196);
    frame1.material.diffuse = 0.6;
    w.addObject(&frame1);

    /* Frame 2 */
    Cube frame2 = Cube();
    frame2.setTransform(translation(-10, 3.4, 2.7) * scaling(0.05, 0.4, 0.4));
    frame2.material.colour = Colour(0.2667, 0.2706, 0.6902);
    frame2.material.diffuse = 0.6;
    w.addObject(&frame2);

    /* Frame 3 */
    Cube frame3 = Cube();
    frame3.setTransform(translation(-10, 4.6, 2.7) * scaling(0.05, 0.4, 0.4));
    frame3.material.colour = Colour(0.3098, 0.5961, 0.3098);
    frame3.material.diffuse = 0.6;
    w.addObject(&frame3);

    /* ----------------------------- */

    /* Mirror */
    Cube mirror = Cube();
    mirror.setTransform(translation(-2, 3.5, 9.95) * scaling(4.8, 1.4, 0.06));
    mirror.material.colour = Colour(0, 0, 0);
    mirror.material.diffuse = 0;
    mirror.material.ambient = 0;
    mirror.material.specular = 1;
    mirror.material.shininess = 300;
    mirror.material.reflective = 1;
    w.addObject(&mirror);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(400, 200, 0.785);
    camera.setTransform(viewTransform(Point(8, 6, -8),
                                      Point(0, 3, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 4);

    image.SaveAsPNG("ch12_test.png");

    return 0;
}