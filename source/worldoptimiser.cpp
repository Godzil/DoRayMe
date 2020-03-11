/*
 *  DoRayMe - a quick and dirty Raytracer
 *  WorldOptimiser implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <shape.h>
#include <group.h>
#include <objfile.h>
#include <world.h>
#include <worldoptimiser.h>

/* This function is meant to move all infinite object to the root group */
void WorldOptimiser::moveInfiniteObjects(Shape *s)
{
    if (s == nullptr)
    {
        s = this->root;
    }

    if (s->getType() == Shape::OBJFILE)
    {
        /* Special case */
        OBJFile *obj = (OBJFile *)s;
        s = obj->getBaseGroup();
    }


    if (s->getType() == Shape::GROUP)
    {
        int i;
        Group *grp = (Group *)s;

        if (grp->getUnboxableCount() > 0)
        {
            for(i = 0; i < grp->getUnboxableCount(); i++)
            {
                Shape *shp = grp->getUnboxable(i);

                if (this->root != s)
                {
                    if (shp->getType() == Shape::GROUP)
                    {
                        /* Issue a warning if it is a group */
                        printf("WARNING: The group '%s' in '%s' have infinite bounds, all items part of it will not be optimised."
                               "That may affect performances!",
                               ((Group *)shp)->getName(),
                               grp->getName());
                    }

                    this->root->addObject(shp);
                    grp->removeObject(shp);

                    /* We remove an object from that list, so need to do some stuffs. */
                    i -= 1;
                }
            }
        }

        /* Now let's traverse the rest of that group */
        if (grp->getObjectCount() > 0)
        {
            for(i = 0; i < grp->getObjectCount(); i++)
            {
                Shape *shp = grp->getObject(i);
                this->moveInfiniteObjects(shp);
            }
        }
    }
    /* If it is not a group, there is nothing to be done there. */
}

void WorldOptimiser::moveAllObjects(Shape *s)
{
    if (s == nullptr)
    {
        s = this->root;
    }

    if (s->getType() == Shape::OBJFILE)
    {
        /* Special case */
        OBJFile *obj = (OBJFile *)s;
        s = obj->getBaseGroup();
    }

    /* We should be here only when it is a group, but better being safe. */
    if (s->getType() == Shape::GROUP)
    {
        int i;
        Group *grp = (Group *)s;

        /* Now let's traverse the rest of that group */
        if (grp->getObjectCount() > 0)
        {
            for(i = 0; i < grp->getObjectCount(); i++)
            {
                Shape *shp = grp->getObject(i);
                switch(shp->getType())
                {
                default:
                    /* Don't move if we are on the same leaf */
                    if (this->root != s)
                    {
                        /* It is not a group type object so, move it! */
                        this->root->addObject(shp);
                        grp->removeObject(shp);

                        /* We remove an object from that list, so need to do some stuffs. */
                        i -= 1;
                    }
                    break;

                case Shape::GROUP:
                case Shape::OBJFILE:
                    this->moveAllObjects(shp);
                }
            }
        }
    }
    /* If it is not a group, there is nothing to be done there. */
}