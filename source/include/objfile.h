/*
 *  DoRayMe - a quick and dirty Raytracer
 *  OBJ File header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_OBJFILE_H
#define DORAYME_OBJFILE_H

#include <shape.h>
#include <renderstat.h>

class OBJFile : public Shape
{
private:
    uint32_t allocatedFaceGroupCount;
    Shape* *faceGroupList;
    uint32_t faceGroupCount;

    uint32_t allocatedVertexCount;
    Tuple* *vertexList;
    uint32_t vertexCount;


private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    /* Some stats */
    uint32_t ignoredLines;

protected:
    void addGroup(Shape *group);
    void addVertex(Tuple *vertex);

    BoundingBox bounds;

public:
    OBJFile();
    OBJFile(const char *filepath);

    int parseOBJFile(const char *content);

    BoundingBox getLocalBounds();
    bool haveFiniteBounds() { return true; };
};

#endif /* DORAYME_OBJFILE_H */
