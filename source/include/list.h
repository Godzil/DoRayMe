/*
 *  DoRayMe - a quick and dirty Raytracer
 *  List header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_LIST_H
#define DORAYME_LIST_H

#include <shape.h>

struct ChainList
{
    Shape *shape;
    ChainList *next;
};

class List
{
private:
    ChainList *head;
    ChainList *tail;
    uint32_t count;
public:
    List() : head(nullptr), tail(nullptr), count(0) { };
    ~List()
    {
        ChainList *p = this->head;
        if (p == nullptr) { return; }

        /* clear up the list */
    }

    Shape *last()
    {
        ChainList *p = this->tail;
        if (p == nullptr) { return nullptr; }
        return p->shape;
    }

    void remove(Shape *s)
    {
        ChainList *p = this->head;
        if (p == nullptr) { return; }
        while(p->next != nullptr)
        {
            if (p->next->shape == s)
            {
                this->count --;
                p->next = p->next->next;
                free(p->next);
                return;
            }
            p = p->next;
        }
    }

    void append(Shape *s)
    {
        ChainList *theNew = (ChainList *)calloc(1, sizeof(ChainList));

        theNew->shape = s;

        ChainList *p = this->tail;
        tail = theNew;

        if (p != nullptr) { p->next = theNew; }
        else { head = theNew; } /* If the tail is empty, it mean the list IS empty. */

        this->count ++;
    }

    bool isEmpty()
    {
        return (this->count == 0);
    }

    bool doesInclude(Shape *s)
    {
        ChainList *p = this->head;

        while(p != nullptr)
        {
            if (p->shape == s) { return true; }
            p = p->next;
        }

        return false;
    }
};

#endif //DORAYME_LIST_H
