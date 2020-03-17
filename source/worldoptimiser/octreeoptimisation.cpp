/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Octree world optimiser implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <worldoptimiser.h>
#include <cube.h>
#include <objfile.h>
#include <transformation.h>

void OctreeOptimisation::makeTree(Group *leaf, int depth)
{
    /* Let's take the bounding box of the root */
    BoundingBox rootBB = leaf->getBounds();

    /* Take the mid value for each axes */
    double midX = (rootBB.max.x - rootBB.min.x) / 2.0 + rootBB.min.x;
    double midY = (rootBB.max.y - rootBB.min.y) / 2.0 + rootBB.min.y;
    double midZ = (rootBB.max.z - rootBB.min.z) / 2.0 + rootBB.min.z;
    BoundingBox octantBB[8];
    int octantIdx;
    Group *octants[8];

    int i;


    /* Split the main bounding box into 8 boxes */
    octantBB[0] | Point(rootBB.min.x, rootBB.min.y, rootBB.min.z);
    octantBB[0] | Point(midX, midY, midZ);

    octantBB[1] | Point(midX, rootBB.min.y, rootBB.min.z);
    octantBB[1] | Point(rootBB.max.x, midY, midZ);

    octantBB[2] | Point(rootBB.min.x, midY, rootBB.min.z);
    octantBB[2] | Point(midX, rootBB.max.y, midZ);

    octantBB[3] | Point(midX, midY, rootBB.min.z);
    octantBB[3] | Point(rootBB.max.x, rootBB.max.y, midZ);

    octantBB[4] | Point(rootBB.min.x, midY, midZ);
    octantBB[4] | Point(midX, rootBB.max.y, rootBB.max.z);

    octantBB[5] | Point(midX, midY, midZ);
    octantBB[5] | Point(rootBB.max.x, rootBB.max.y, rootBB.max.z);

    octantBB[6] | Point(rootBB.min.x, rootBB.min.y, midZ);
    octantBB[6] | Point(midX, midY, rootBB.max.z);

    octantBB[7] | Point(midX, rootBB.min.y, midZ);
    octantBB[7] | Point(rootBB.max.x, midY, rootBB.max.z);

    for (octantIdx = 0 ; octantIdx < 8 ; octantIdx++)
    {
        octants[octantIdx] = nullptr;
    }

    for (i = 0 ; i < leaf->getObjectCount(); i++)
    {
        Shape *shp = leaf->getObject(i);

        BoundingBox objBB = shp->getBounds();
        //if ((shp->getType() != Shape::GROUP) && (shp->getType() != Shape::OBJFILE))
        for (octantIdx = 0 ; octantIdx < 8 ; octantIdx++)
        {
            if (octantBB[octantIdx].fitsIn(objBB))
            {
                if (octants[octantIdx] == nullptr)
                {
                    char name[32];
                    snprintf(name, 32, "%d_Quadrant %d", depth, octantIdx);
                    octants[octantIdx] = new Group(name);

                    octants[octantIdx]->setBounds(octantBB[octantIdx]);
                }

                octants[octantIdx]->addObject(shp);
                leaf->removeObject(shp);

                i -= 1;
                break;
            }
        }
        if (shp->getType() == Shape::GROUP)
        {
            this->makeTree((Group *)shp, depth + 1);
        }
        if (shp->getType() == Shape::OBJFILE)
        {
            this->makeTree((Group *)((OBJFile *)shp)->getBaseGroup(), depth + 1);
        }
    }

    /* Now add the quadrant to the root and recurse in it */
    for (octantIdx = 0 ; octantIdx < 8 ; octantIdx++)
    {
        if (octants[octantIdx] != nullptr)
        {
            this->makeTree(octants[octantIdx], depth + 1);

            octants[octantIdx]->updateBoundingBox();

            leaf->addObject(octants[octantIdx]);
#if 0
            Cube *cb = new Cube();
            double sx = octantBB[octantIdx].max.x - octantBB[octantIdx].min.x;
            double sy = octantBB[octantIdx].max.y - octantBB[octantIdx].min.y;
            double sz = octantBB[octantIdx].max.z - octantBB[octantIdx].min.z;

            cb->setTransform(translation(octantBB[octantIdx].min.x, octantBB[octantIdx].min.y,
                                         octantBB[octantIdx].min.z) * scaling(sx, sy, sz));
            cb->material.colour = Colour(0.01, 0.01, 0);
            cb->materialSet = true;
            cb->dropShadow = false;
            cb->material.ambient = 0.1;
            cb->material.reflective = 0;
            cb->material.transparency = 0.95;
            cb->material.refractiveIndex = 1;
            cb->material.specular = 0;
            leaf->addObject(cb);

            printf("%s: %d objs\n", octants[octantIdx]->getName(),
                   octants[octantIdx]->getObjectCount());
#endif
        }
    }
}

void OctreeOptimisation::run()
{
    /* First let's clear our hands */
    this->moveInfiniteObjects();

    /* Then let's have some fun! */
    //this->moveAllObjects();

    /* Now.. The fun start ! */
    makeTree(this->root, 0);
}