/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render statistics implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <renderstat.h>
#include <stdio.h>

RenderStats stats;

#ifdef RENDER_STATS

void RenderStats::addCone()
{
#pragma omp atomic
    this->coneCount++;
};

void RenderStats::addCylinder()
{
#pragma omp atomic
    this->cylinderCount++;
};

void RenderStats::addCube()
{
#pragma omp atomic
    this->cubeCount++;
};

void RenderStats::addGroup()
{
#pragma omp atomic
    this->groupCount++;
};

void RenderStats::addLight()
{
#pragma omp atomic
    this->lightCount++;
};

void RenderStats::addPlane()
{
#pragma omp atomic
    this->planeCount++;
};

void RenderStats::addSphere()
{
#pragma omp atomic
    this->sphereCount++;
};

void RenderStats::addTriangle()
{
#pragma omp atomic
    this->triangleCount++;
};

void RenderStats::addSmoothTriangle()
{
#pragma omp atomic
    this->smoothTriangleCount++;
};

void RenderStats::addOBJFile()
{
#pragma omp atomic
    this->objfileCount++;
};

void RenderStats::addPixel()
{
#pragma omp atomic
    this->pixelCount++;
};

void RenderStats::addRay()
{
#pragma omp atomic
    this->rayCount++;
};

void RenderStats::addCastedRay()
{
#pragma omp atomic
    this->rayCasted++;
};

void RenderStats::addLightRay()
{
    this->addCastedRay();

#pragma omp atomic
    this->lightRayEmitedCount++;
};

void RenderStats::addReflectRay()
{
    this->addCastedRay();

#pragma omp atomic
    this->reflectionRayCount++;
};

void RenderStats::addRefractRay()
{
    this->addCastedRay();

#pragma omp atomic
    this->refractedRayCount++;
};

void RenderStats::addIntersect()
{
#pragma omp atomic
    this->intersectCount++;
};

void RenderStats::addIntersection()
{
#pragma omp atomic
    this->intersectionCount++;
};

void RenderStats::addMalloc()
{
#pragma omp atomic
    this->mallocCallCount++;
};

void RenderStats::addRealloc()
{
#pragma omp atomic
    this->reallocCallCount++;
};

void RenderStats::addDiscardedIntersect()
{
#pragma omp atomic
    this->discardedIntersectCount++;
};

void RenderStats::addCsg()
{
#pragma omp atomic
    this->csgCount++;
};


void RenderStats::setMaxDepth(uint32_t depth)
{
    if (this->maxDepthAttained > depth)
    {
        this->maxDepthAttained = depth;
    }
};

void RenderStats::setMaxIntersect(uint32_t count)
{
    if (this->maxIntersectOnARay < count)
    {
        this->maxIntersectOnARay = count;
    }
};

void RenderStats::printStats()
{
    printf("Rendering statistics:\n");
    printf("Cones                   : %lld\n", this->coneCount);
    printf("Cubes                   : %lld\n", this->cubeCount);
    printf("Cylinders               : %lld\n", this->cylinderCount);
    printf("Groups                  : %lld\n", this->groupCount);
    printf("Lights                  : %lld\n", this->lightCount);
    printf("Planes                  : %lld\n", this->planeCount);
    printf("Spheres                 : %lld\n", this->sphereCount);
    printf("Triangles               : %lld\n", this->triangleCount);
    printf("Smooth Triangles        : %lld\n", this->smoothTriangleCount);
    printf("OBJ File                : %lld\n", this->objfileCount);
    printf("CSG                     : %lld\n", this->csgCount);
    printf("==================================================\n");
    printf("Pixel rendered          : %lld\n", this->pixelCount);
    printf("Ray created             : %lld\n", this->rayCount);
    printf("Ray casted              : %lld\n", this->rayCasted);
    printf("Light Ray casted        : %lld\n", this->lightRayEmitedCount);
    printf("Reflection ray casted   : %lld\n", this->reflectionRayCount);
    printf("Refraction ray casted   : %lld\n", this->refractedRayCount);
    printf("Intersect object created: %lld\n", this->intersectCount);
    printf("Intersection created    : %lld\n", this->intersectionCount);
    printf("Malloc called           : %lld\n", this->mallocCallCount);
    printf("Realloc called          : %lld\n", this->reallocCallCount);
    printf("Bounding box missed     : %lld\n", this->discardedIntersectCount);
    printf("Min depth attained      : %lld\n", this->maxDepthAttained);
    printf("Max intersect count     : %lld\n", this->maxIntersectOnARay);
    printf("==================================================\n");
};

#endif