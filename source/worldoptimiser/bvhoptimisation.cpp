/*
 *  DoRayMe - a quick and dirty Raytracer
 *  BVH world optimiser implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <worldoptimiser.h>
#include <cube.h>
#include <objfile.h>
#include <transformation.h>

void BVHOptimisation::makeTree(Group *leaf, int depth)
{
    /* Let's take the bounding box of the root */
    BoundingBox rootBB = leaf->getBounds();

    double dx = (rootBB.max.x - rootBB.min.x);
    double dy = (rootBB.max.y - rootBB.min.y);
    double dz = (rootBB.max.z - rootBB.min.z);
    /* Take the mid value for each axes */
    Tuple midMin = rootBB.min;
    Tuple midMax = rootBB.max;

    BoundingBox SlicesBB[2];
    int sliceIdx;
    Group *Slices[2];

    double largestSide = max3(dx, dy, dz);

    int i;

    if (largestSide == dx)
    {
        midMin.x = rootBB.min.x + dx / 2.0;
        midMax.x = rootBB.min.x + dx / 2.0;
    }
    else if (largestSide == dy)
    {
        midMin.y = rootBB.min.y + dy / 2.0;
        midMax.y = rootBB.min.y + dy / 2.0;
    }
    else
    {
        midMin.z = rootBB.min.z + dx / 2.0;
        midMax.z = rootBB.min.z + dx / 2.0;
    }


    /* Split the main bounding box into 8 boxes */
    SlicesBB[0] | rootBB.min;
    SlicesBB[0] | midMax;

    SlicesBB[1] | rootBB.max;
    SlicesBB[1] | midMin;


    for (sliceIdx = 0 ; sliceIdx < 2 ; sliceIdx++)
    {
        Slices[sliceIdx] = nullptr;
    }

    for (i = 0 ; i < leaf->getObjectCount(); i++)
    {
        Shape *shp = leaf->getObject(i);
        BoundingBox objBB = shp->getBounds();

        for (sliceIdx = 0 ; sliceIdx < 2 ; sliceIdx++)
        {
            if (SlicesBB[sliceIdx].fitsIn(objBB))
            {
                if (Slices[sliceIdx] == nullptr)
                {
                    char name[32];
                    snprintf(name, 32, "%d_Slice %d", depth, sliceIdx);
                    Slices[sliceIdx] = new Group(name);

                    Slices[sliceIdx]->setBounds(SlicesBB[sliceIdx]);
                }

                Slices[sliceIdx]->addObject(shp);
                leaf->removeObject(shp);

                i -= 1;
                break;
            }
        }
        if (shp->getType() == Shape::GROUP)
        {
            this->makeTree((Group *)shp, depth + 1);
        }
        else if (shp->getType() == Shape::OBJFILE)
        {
            this->makeTree((Group *)((OBJFile *)shp)->getBaseGroup(), depth + 1);
        }
    }

    /* Now add the quadrant to the root and recurse in it */
    for (sliceIdx = 0 ; sliceIdx < 2 ; sliceIdx++)
    {
        if (Slices[sliceIdx] != nullptr)
        {
            this->makeTree(Slices[sliceIdx], depth + 1);

            Slices[sliceIdx]->updateBoundingBox();

            leaf->addObject(Slices[sliceIdx]);
#if 0
            Cube *cb = new Cube();
            double sx = SlicesBB[sliceIdx].max.x - SlicesBB[sliceIdx].min.x;
            double sy = SlicesBB[sliceIdx].max.y - SlicesBB[sliceIdx].min.y;
            double sz = SlicesBB[sliceIdx].max.z - SlicesBB[sliceIdx].min.z;

            cb->setTransform(translation(SlicesBB[sliceIdx].min.x, SlicesBB[sliceIdx].min.y,
                                         SlicesBB[sliceIdx].min.z) * scaling(sx, sy, sz));
            cb->material.colour = Colour(0.01, 0.01, 0);
            cb->materialSet = true;
            cb->dropShadow = false;
            cb->material.ambient = 0.1;
            cb->material.reflective = 0;
            cb->material.transparency = 0.95;
            cb->material.refractiveIndex = 1;
            cb->material.specular = 0;
            leaf->addObject(cb);

            printf("%s: %d objs\n", Slices[sliceIdx]->getName(),
                   Slices[sliceIdx]->getObjectCount());
#endif
        }
    }
}

void BVHOptimisation::run()
{
    /* First let's clear our hands */
    this->moveInfiniteObjects();

    /* Then let's have some fun! */
    //this->moveAllObjects();

    /* Now.. The fun start ! */
    makeTree(this->root, 0);
}