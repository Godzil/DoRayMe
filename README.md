[![codecov](https://codecov.io/gh/Godzil/DoRayMe/branch/master/graph/badge.svg)](https://codecov.io/gh/Godzil/DoRayMe) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/66339747e4a843719cba29cf5e31ff90)](https://www.codacy.com/manual/Godzil/DoRayMe?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Godzil/DoRayMe&amp;utm_campaign=Badge_Grade) [![Coverage Status](https://coveralls.io/repos/github/Godzil/DoRayMe/badge.svg?branch=master)](https://coveralls.io/github/Godzil/DoRayMe?branch=master) [![Build Status](https://travis-ci.org/Godzil/DoRayMe.svg?branch=master)](https://travis-ci.org/Godzil/DoRayMe)

DoRayMe
=======

A Quick and dirty raytracer.


This raytracer is made following the book "[The Ray Tracer Challenge](https://pragprog.com/book/jbtracer/the-ray-tracer-challenge)" by Jamis Buck.

It is writen in C++ with no STL and use [LodePNG](https://github.com/lvandeve/lodepng) to output PNG file.


Examples outputs
----------------

**From chapter 05 - Sphere intersections:**

![Chapter 5 rendering test](output/ch5_test.png)

**From Chapter 06 - Phong shading:**

![Chapter 6 rendering test](output/ch6_test.png)

**From Chapter 07 - World / Camera / Scenes:**

![Chapter 7 rendering test](output/ch7_test.png)

**From Chapter 08 - Shadows:**

![Chapter 8 rendering test](output/ch8_test.png)

**From Chapter 09 - Planes:**

![Chapter 9 rendering test](output/ch9_test.png)

**From Chapter 10 - Patterns:**

![Chapter 10 rendering test](output/ch10_test.png)

**From Chapter 11 - Reflections, Transparency & Refractions:**

![Chapter 11 reflections rendering test](output/ch11_reflection.png)

Bonus: Zooming on a reflective ball:
![Chapter 11 zooming on a ball](output/ch11_zooming_on_reflective_ball.png)

Zooming on a reflection on that ball:
![Chapter 11 zooming on a reflection](output/ch11_reflection_on_ball.png)

![Chapter 11 refraction rendering test](output/ch11_refraction.png | width=1000)

![Chapter 11 rendering test](output/ch11_test.png | width=1000)

**From Chapter 12 - Cubes:**

![Chapter 12 rendering test](output/ch12_test.png)

**From Chapter 13 - Cylinders:**

![Chapter 13 rendering test](output/ch13_test.png)
Bonus:
![Chapter 13 cone test](output/ch13_cone.png)

**From Chapter 14 - Groups & Bounding boxes:**
![Chapter 14 rendering test](output/ch14_test.png)


**Bonus (from the forum):**

[Merry Christmas](https://forum.raytracerchallenge.com/thread/16/merry-christmas-scene-description)
![Merry Christmas](output/christmasball.png)

(about 1min render time using OpenMP on a 2.6Ghz Core i7 3720QM)

**Bonus chapter - Soft shadow / Area light**

Without jitter:
![Area light without jitter](output/arealight_test_nojitter.png)

With jitter:
![Area light witht jitter](output/arealight_test.png)