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

#ifdef RENDER_STATS
#include <stdio.h>

class RenderStats
{
private:
    uint64_t coneCount;                  /* Total number of cones    */
    uint64_t cylinderCount;              /* Total number of cylinder    */
    uint64_t cubeCount;                  /* Total number of cubes    */
    uint64_t groupCount;                 /* Total number of groups   */
    uint64_t lightCount;                 /* Total number of light    */
    uint64_t planeCount;                 /* Total number of plane    */
    uint64_t sphereCount;                /* Total number of sphere   */
    uint64_t triangleCount;               /* Total number of triangle */

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
                    intersectCount(0), intersectionCount(0), reallocCallCount(0), mallocCallCount(0),
                    discardedIntersectCount(0), maxDepthAttained(UINT64_MAX), maxIntersectOnARay(0) {};

    void addCone() { this->coneCount++; };
    void addCylinder() { this->cylinderCount++; };
    void addCube() { this->cubeCount++; };
    void addGroup() { this->groupCount++; };
    void addLight() { this->lightCount++; };
    void addPlane() { this->planeCount++; };
    void addSphere() { this->sphereCount++; };
    void addTriangle() { this->triangleCount++; };

    void addPixel() { this->pixelCount++; };
    void addRay() { this->rayCount++; };
    void addLightRay() { this->lightRayEmitedCount++; };
    void addReflectRay() { this->reflectionRayCount++; };
    void addRefractRay() { this->refractedRayCount++; };
    void addIntersect() { this->intersectCount++; };
    void addIntersection() { this->intersectionCount++; };
    void addMalloc() { this->mallocCallCount++; };
    void addRealloc() { this->reallocCallCount++; };
    void addDiscardedIntersect() {  this->discardedIntersectCount++; };
    void setMaxDepth(uint32_t depth) { if (this->maxDepthAttained>depth) { this->maxDepthAttained = depth; } };
    void setMaxIntersect(uint32_t count) { if (this->maxIntersectOnARay<count) { this->maxIntersectOnARay = count; } };
    void printStats() {
        printf("Rendering statistics:\n");
        printf("Cones                   : %lld\n", this->coneCount);
        printf("Cubes                   : %lld\n", this->cubeCount);
        printf("Cylinders               : %lld\n", this->cylinderCount);
        printf("Groups                  : %lld\n", this->groupCount);
        printf("Lights                  : %lld\n", this->lightCount);
        printf("Planes                  : %lld\n", this->planeCount);
        printf("Spheres                 : %lld\n", this->sphereCount);
        printf("Triangles               : %lld\n", this->triangleCount);
        printf("==================================================\n");
        printf("Pixel rendered          : %lld\n", this->pixelCount);
        printf("Ray casted              : %lld\n", this->rayCount);
        printf("Light Ray casted        : %lld\n", this->lightRayEmitedCount);
        printf("Reflection ray casted   : %lld\n", this->reflectionRayCount);
        printf("Refraction ray casted   : %lld\n", this->refractedRayCount);
        printf("Intersect object created: %lld\n", this->intersectCount);
        printf("Intersection created    : %lld\n", this->intersectionCount);
        printf("Malloc called           : %lld\n", this->mallocCallCount);
        printf("Realloc called          : %lld\n", this->reallocCallCount);
        printf("Bounding box missed     : %lld\n", this->discardedIntersectCount);
        printf("Min depth atteined      : %lld\n", this->maxDepthAttained);
        printf("Max intersect count     : %lld\n", this->maxIntersectOnARay);
        printf("==================================================\n");
    };
};
#else
class RenderStats
{
public:
    static void addCone() {};
    static void addCylinder() {};
    static void addCube() {};
    static void addGroup() {};
    static void addLight() {};
    static void addPlane() {};
    static void addSphere() {};
    static void addTriangle() {};
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
};
#endif

extern RenderStats stats;

#endif /* DORAYME_RENDERSTAT_H */
