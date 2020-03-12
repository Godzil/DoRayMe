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
#include <transformation.h>

void OctreeOptimisation::makeTree(Group *leaf, int depth)
{
    /* Let's take the bounding box of the root */
    BoundingBox rootBB = leaf->getBounds();

    /* Take the mid value for each axes */
    double midX = (rootBB.max.x - rootBB.min.x) / 2.0 + rootBB.min.x;
    double midY = (rootBB.max.y - rootBB.min.y) / 2.0 + rootBB.min.y;
    double midZ = (rootBB.max.z - rootBB.min.z) / 2.0 + rootBB.min.z;
    BoundingBox QuadrantBB[8];
    int quadrantIdx;
    Group *Quadrants[8];

    int i;

    if (leaf->getObjectCount() > 2)
    {
        /* Split the main bounding box into 8 boxes */
        QuadrantBB[0] | Point(rootBB.min.x, rootBB.min.y, rootBB.min.z);
        QuadrantBB[0] | Point(midX, midY, midZ);

        QuadrantBB[1] | Point(midX, rootBB.min.y, rootBB.min.z);
        QuadrantBB[1] | Point(rootBB.max.x, midY, midZ);

        QuadrantBB[2] | Point(rootBB.min.x, midY, rootBB.min.z);
        QuadrantBB[2] | Point(midX, rootBB.max.y, midZ);

        QuadrantBB[3] | Point(midX, midY, rootBB.min.z);
        QuadrantBB[3] | Point(rootBB.max.x, rootBB.max.y, midZ);

        QuadrantBB[4] | Point(rootBB.min.x, midY, midZ);
        QuadrantBB[4] | Point(midX, rootBB.max.y, rootBB.max.z);

        QuadrantBB[5] | Point(midX, midY, midZ);
        QuadrantBB[5] | Point(rootBB.max.x, rootBB.max.y, rootBB.max.z);

        QuadrantBB[6] | Point(rootBB.min.x, rootBB.min.y, midZ);
        QuadrantBB[6] | Point(midX, midY, rootBB.max.z);

        QuadrantBB[7] | Point(midX, rootBB.min.y, midZ);
        QuadrantBB[7] | Point(rootBB.max.x, midY, rootBB.max.z);

        for (quadrantIdx = 0 ; quadrantIdx < 8 ; quadrantIdx++)
        {
            Quadrants[quadrantIdx] = nullptr;
        }

        for (i = 0 ; i < leaf->getObjectCount(); i++)
        {
            Shape *shp = leaf->getObject(i);
            if ((shp->getType() != Shape::GROUP) && (shp->getType() != Shape::OBJFILE))
            {
                BoundingBox objBB = shp->getBounds();

                for (quadrantIdx = 0 ; quadrantIdx < 8 ; quadrantIdx++)
                {
                    if (QuadrantBB[quadrantIdx].fitsIn(objBB))
                    {
                        if (Quadrants[quadrantIdx] == nullptr)
                        {
                            char name[32];
                            snprintf(name, 32, "%d_Quadrant %d", depth, quadrantIdx);
                            //for(int j=0; j < depth; j++) { printf(" "); }
                            //printf("%s\n", name);
                            Quadrants[quadrantIdx] = new Group(name);

                            Quadrants[quadrantIdx]->setBounds(QuadrantBB[quadrantIdx]);
                        }

                        Quadrants[quadrantIdx]->addObject(shp);
                        leaf->removeObject(shp);

                        i -= 1;
                        break;
                    }
                }
            }
            else
            {
                leaf->removeObject(shp);
                /* No cleanup for now, it's bad, I know */
                //delete shp;
                i -= 1;
            }
        }

        //if (depth < 1)
        {
            /* Now add the quadrant to the root and recurse in it */
            for (quadrantIdx = 0 ; quadrantIdx < 8 ; quadrantIdx++)
            {
                if (Quadrants[quadrantIdx] != nullptr)
                {
                    this->makeTree(Quadrants[quadrantIdx], depth + 1);

                    Quadrants[quadrantIdx]->updateBoundingBox();

                    leaf->addObject(Quadrants[quadrantIdx]);
#if 0
                    Cube *cb = new Cube();
                    double sx = QuadrantBB[quadrantIdx].max.x - QuadrantBB[quadrantIdx].min.x;
                    double sy = QuadrantBB[quadrantIdx].max.y - QuadrantBB[quadrantIdx].min.y;
                    double sz = QuadrantBB[quadrantIdx].max.z - QuadrantBB[quadrantIdx].min.z;

                    cb->setTransform(translation(QuadrantBB[quadrantIdx].min.x, QuadrantBB[quadrantIdx].min.y,
                                                 QuadrantBB[quadrantIdx].min.z) * scaling(sx, sy, sz));
                    cb->material.colour = Colour(0.01, 0.01, 0);
                    cb->materialSet = true;
                    cb->dropShadow = false;
                    cb->material.ambient = 0.1;
                    cb->material.reflective = 0;
                    cb->material.transparency = 0.95;
                    cb->material.refractiveIndex = 1;
                    cb->material.specular = 0;
                    leaf->addObject(cb);

                    printf("%s: %d objs\n", Quadrants[quadrantIdx]->getName(),
                           Quadrants[quadrantIdx]->getObjectCount());
#endif
                }
            }
        }
    }
}

void OctreeOptimisation::run()
{
    /* First let's clear our hands */
    this->moveInfiniteObjects();

    /* Then let's have some fun! */
    this->moveAllObjects();

    /* Now.. The fun start ! */
    makeTree(this->root, 0);
}