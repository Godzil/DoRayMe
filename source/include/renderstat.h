/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render statistics header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_RENDERSTAT_H
#define DORAYME_RENDERSTAT_H

#include <stdint.h>

class RenderStats
{
private:
    uint64_t coneCount;                  /* Total number of cones           */
    uint64_t cylinderCount;              /* Total number of cylinder        */
    uint64_t cubeCount;                  /* Total number of cubes           */
    uint64_t groupCount;                 /* Total number of groups          */
    uint64_t lightCount;                 /* Total number of light           */
    uint64_t planeCount;                 /* Total number of plane           */
    uint64_t sphereCount;                /* Total number of sphere          */
    uint64_t triangleCount;              /* Total number of triangle        */
    uint64_t smoothTriangleCount;        /* Total number of smooth triangle */
    uint64_t objfileCount;               /* Total number of OBJ File        */
    uint64_t csgCount;                   /* Total number of CSG             */

    uint64_t pixelCount;                 /* Total number of rendered pixels */
    uint64_t rayCount;                   /* Total number of rays */
    uint64_t lightRayEmitedCount;        /* Total number of ray launched for light tests */
    uint64_t reflectionRayCount;         /* Total number of reflection ray launched */
    uint64_t refractedRayCount;          /* Total number of refracted ray launched */
    uint64_t intersectCount;             /* Total number of intersect object created */
    uint64_t intersectionCount;          /* Total number of intersection for all casted rays, including light and reflections */
    uint64_t reallocCallCount;           /* Total number of time realloc being called */
    uint64_t mallocCallCount;            /* Total number of time malloc/calloc being called */
    uint64_t discardedIntersectCount;    /* Number of time a bounding box check said "no need to test me" */
    uint64_t maxDepthAttained;           /* Report the lowest depth attained during ray recursion */
    uint64_t maxIntersectOnARay;         /* Biggest intersect done */

public:
    RenderStats() : coneCount(0), cylinderCount(0), cubeCount(0), groupCount(0), lightCount(0), planeCount(0), sphereCount(0), triangleCount(0),
                    pixelCount(0), rayCount(0), lightRayEmitedCount(0), reflectionRayCount(0), refractedRayCount(0),
                    intersectCount(0), intersectionCount(0), reallocCallCount(0), mallocCallCount(0), smoothTriangleCount(0),
                    discardedIntersectCount(0), maxDepthAttained(UINT64_MAX), maxIntersectOnARay(0), objfileCount(0), csgCount(0) {};
#ifdef RENDER_STATS
    void addCone();
    void addCylinder();
    void addCube();
    void addGroup();
    void addLight();
    void addPlane();
    void addSphere();
    void addCsg();
    void addOBJFile();
    void addTriangle();
    void addSmoothTriangle();
    void printStats();
    void addPixel();
    void addRay();
    void addLightRay();
    void addReflectRay();
    void addRefractRay();
    void addIntersection();
    void addDiscardedIntersect();
    void setMaxDepth(uint32_t depth);
    void addIntersect();
    void addMalloc();
    void addRealloc();
    void setMaxIntersect(uint32_t count);
#else
    static void addCone() {};
    static void addCylinder() {};
    static void addCube() {};
    static void addGroup() {};
    static void addLight() {};
    static void addPlane() {};
    static void addSphere() {};
    static void addTriangle() {};
    static void addSmoothTriangle() {};
    static void printStats() {};
    static void addPixel() {};
    static void addRay() {};
    static void addLightRay() {};
    static void addReflectRay() {};
    static void addRefractRay() {};
    static void addIntersection() {};
    static void addDiscardedIntersect() {};
    static void setMaxDepth(uint32_t depth) {};
    static void addIntersect() {};
    static void addMalloc() {};
    static void addRealloc() {};
    static void setMaxIntersect(uint32_t count) {};
    static void addOBJFile() {};
    static void addCsg() {};
#endif
};


extern RenderStats stats;

#endif /* DORAYME_RENDERSTAT_H */
