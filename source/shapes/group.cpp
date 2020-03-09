/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Group implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <ray.h>
#include <group.h>
#include <math_helper.h>
#include <renderstat.h>
#include <string.h>

#define MIN_ALLOC (2)

Group::Group(const char *name) : Shape(Shape::GROUP)
{
    stats.addGroup();
    this->allocatedObjectCount = MIN_ALLOC;
    this->objectList = (Shape **)calloc(sizeof(Shape **), MIN_ALLOC);
    this->objectCount = 0;

    this->allocatedUnboxableObjectCount = MIN_ALLOC;
    this->unboxableObjectList = (Shape **)calloc(sizeof(Shape **), MIN_ALLOC);
    this->unboxableObjectCount = 0;

    if (name != nullptr)
    {
        strncpy(this->name, name, 32);
    }
    else
    {
        strncpy(this->name, "untitled", 32);
    }
}

Intersect Group::intersect(Ray r)
{
    Intersect ret;
    int i, j;
    if (this->objectCount > 0)
    {
        if (this->bounds.intesectMe(r))
        {
            for (i = 0 ; i < this->objectCount ; i++)
            {
                Intersect xs = this->objectList[i]->intersect(r);
                if (xs.count() > 0)
                {
                    for (j = 0 ; j < xs.count() ; j++)
                    {
                        ret.add(xs[j]);
                    }
                }
            }
        }
    }

    /* We are force to do them all the time */
    if (this->unboxableObjectCount > 0)
    {
        for(i = 0; i < this->unboxableObjectCount; i++)
        {
            Intersect xs = this->unboxableObjectList[i]->intersect(r);
            if (xs.count() > 0)
            {
                for(j = 0; j < xs.count(); j++)
                {
                    ret.add(xs[j]);
                }
            }
        }
    }
    return ret;
}

bool Group::includes(Shape *b)
{
    if (this->objectCount > 0)
    {
        int i;
        for (i = 0 ; i < this->objectCount ; i++)
        {
            if (this->objectList[i] == b)
            {
                return true;
            }
        }
    }

    /* We are force to do them all the time */
    if (this->unboxableObjectCount > 0)
    {
        int i;
        for(i = 0; i < this->unboxableObjectCount; i++)
        {
            if (this->unboxableObjectList[i] == b)
            {
                return true;
            }
        }
    }
    return false;
}

Intersect Group::localIntersect(Ray r)
{
    return Intersect();
}

Tuple Group::localNormalAt(Tuple point, Intersection *hit)
{
    return Vector(1, 0, 0);
}

/* ONLY INSERT SHAPES THAT ARE NOT GOING TO CHANGE ELSE..! */
void Group::addObject(Shape *s)
{
    if (s->haveFiniteBounds())
    {
        if ((this->objectCount + 1) > this->allocatedObjectCount)
        {
            this->allocatedObjectCount *= 2;
            this->objectList = (Shape **)realloc(this->objectList, sizeof(Shape **) * this->allocatedObjectCount);
        }

        s->parent = this;
        s->updateTransform();

        this->objectList[this->objectCount++] = s;

        this->bounds | s->getBounds();

    }
    else
    {
        if ((this->unboxableObjectCount + 1) > this->allocatedUnboxableObjectCount)
        {
            this->allocatedUnboxableObjectCount *= 2;
            this->unboxableObjectList = (Shape **)realloc(this->unboxableObjectList, sizeof(Shape **) * this->allocatedUnboxableObjectCount);
        }

        s->parent = this;
        s->updateTransform();

        this->unboxableObjectList[this->unboxableObjectCount++] = s;
    }
}

bool Group::isEmpty()
{
    return (this->objectCount == 0) && (this->unboxableObjectCount == 0);
}

BoundingBox Group::getLocalBounds()
{
    return this->bounds;
}

BoundingBox Group::getBounds()
{
    if (this->bounds.isEmpty()) { this->updateBoundingBox(); }
    return this->bounds;
}

void Group::updateBoundingBox()
{
    this->bounds.reset();
    if (this->objectCount > 0)
    {
        int i;
        for(i = 0; i < this->objectCount; i++)
        {
            if (this->objectList[i]->haveFiniteBounds())
            {
                BoundingBox objB = this->objectList[i]->getBounds();
                this->bounds | objB;
            }
        }
    }
}

void Group::updateTransform()
{
    int i;

    Shape::updateTransform();
    if (this->objectCount > 0)
    {
        for (i = 0 ; i < this->objectCount ; i++)
        {
            this->objectList[i]->updateTransform();
        }
    }

    if (this->unboxableObjectCount > 0)
    {
        for(i = 0; i < this->unboxableObjectCount; i++)
        {
            this->unboxableObjectList[i]->updateTransform();
        }
    }

    /* Once the full stack being notified of the changes, let's update the
     * bounding box
     */
    this->updateBoundingBox();
}

void Group::dumpMe(FILE *fp)
{
    int i;
    fprintf(fp, "\"Type\": \"Group\",\n");
    fprintf(fp, "\"Name\": \"%s\",\n", this->name);
    if (this->objectCount > 0)
    {
        fprintf(fp, "\"Objects\": {\n");
        for(i = 0; i < this->objectCount; i++)
        {
            fprintf(fp, "\"%d\": {\n", i);
            this->objectList[i]->dumpMe(fp);
            fprintf(fp, "},\n");
        }
        fprintf(fp, "},\n");
    }

    if (this->unboxableObjectCount > 0)
    {
        fprintf(fp, "\"UnboxableObjects\": {\n");
        for(i = 0; i < this->objectCount; i++)
        {
            fprintf(fp, "\"%d\": {\n", i);
            this->objectList[i]->dumpMe(fp);
            fprintf(fp, "},\n");
        }
        fprintf(fp, "},\n");
    }
    Shape::dumpMe(fp);
}