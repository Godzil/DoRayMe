/*
 *  DoRayMe - a quick and dirty Raytracer
 *  CSG unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <intersection.h>
#include <sphere.h>
#include <cube.h>
#include <csg.h>
#include <transformation.h>
#include <gtest/gtest.h>

/* Proxy class to get access to protected functions / members */
class CSGTest : public CSG
{
public:
    Intersect doLocalIntersect(Ray r) {
        return this->localIntersect(r);
    };
    Tuple doLocalNormalAt(Tuple point, Intersection *hit = nullptr) {
        return this->localNormalAt(point, hit);
    };
    BoundingBox doGetLocalBounds() {
        return this->getLocalBounds();
    };
    bool doIntersectionAllowed(bool leftHit, bool inLeft, bool inRight) {
        return this->intersectionAllowed(leftHit, inLeft, inRight);
    };

    void doFilterIntersections(Intersect &xs, Intersect &ret) {
        this->filterIntersections(xs, ret);
    }

    CSGTest(OperationType operation, Shape *left, Shape *right) : CSG(operation, left, right) {};


    Shape *getLeft() { return this->left; };
    Shape *getRight() { return this->right; };
    OperationType getOperation() { return this->operation; };
    void setOperation(OperationType operation) { this->operation = operation; };
};

TEST(CSGTest, Csg_is_created_with_an_operation_and_two_shape)
{
    Sphere s1 = Sphere();
    Cube s2 = Cube();

    CSGTest c = CSGTest(CSG::UNION, &s1, &s2);

    ASSERT_EQ(c.getOperation(), CSG::UNION);
    ASSERT_EQ(*c.getLeft(), s1);
    ASSERT_EQ(*c.getRight(), s2);

    ASSERT_EQ(*s1.parent, c);
    ASSERT_EQ(*s2.parent, c);
}

TEST(CSGTest, Evaluating_the_rules_for_a_csg_operation)
{
    Sphere s1 = Sphere();
    Cube s2 = Cube();
    CSGTest c = CSGTest(CSG::UNION, &s1, &s2);

    CSG::OperationType testList2[] = {
            CSG::UNION, CSG::UNION,
            CSG::UNION, CSG::UNION,
            CSG::UNION, CSG::UNION,
            CSG::UNION, CSG::UNION,

            CSG::INTERSECTION, CSG::INTERSECTION,
            CSG::INTERSECTION, CSG::INTERSECTION,
            CSG::INTERSECTION, CSG::INTERSECTION,
            CSG::INTERSECTION, CSG::INTERSECTION,

            CSG::DIFFERENCE, CSG::DIFFERENCE,
            CSG::DIFFERENCE, CSG::DIFFERENCE,
            CSG::DIFFERENCE, CSG::DIFFERENCE,
            CSG::DIFFERENCE, CSG::DIFFERENCE,
    };

    bool testList[][3] = {
            /* lhit, inl,   inr */
/* UNION */ { true,  true,  true  },
            { true,  true,  false },
            { true,  false, true  },
            { true,  false, false },
            { false, true,  true  },
            { false, true,  false },
            { false, false, true  },
            { false, false, false },

/* INTER */ { true,  true,  true  },
            { true,  true,  false },
            { true,  false, true  },
            { true,  false, false },
            { false, true,  true  },
            { false, true,  false },
            { false, false, true  },
            { false, false, false },

/* DIFFE */ { true,  true,  true  },
            { true,  true,  false },
            { true,  false, true  },
            { true,  false, false },
            { false, true,  true  },
            { false, true,  false },
            { false, false, true  },
            { false, false, false },
    };

    bool testResults[] {
        /* Unions */
            false,
            true,
            false,
            true,
            false,
            false,
            true,
            true,
        /* Intersection */
            true,
            false,
            true,
            false,
            true,
            true,
            false,
            false,
        /* difference */
            false,
            true,
            false,
            true,
            true,
            true,
            false,
            false
    };

    int testCount = sizeof(testList)/sizeof((testList)[0]);
    int i;

    for(i = 0; i < testCount; i++)
    {
        c.setOperation(testList2[i]);
        ASSERT_EQ(c.doIntersectionAllowed(testList[i][0], testList[i][1], testList[i][2]), testResults[i]);
    }
}

TEST(CSGTest, Filtering_a_list_of_intersections)
{
    Sphere s1 = Sphere();
    Cube s2 = Cube();
    CSGTest c = CSGTest(CSG::UNION, &s1, &s2);

    CSG::OperationType testList[] = {
            CSG::UNION,
            CSG::INTERSECTION,
            CSG::DIFFERENCE,
    };

    uint32_t testResults[][2] = {
            {0, 3},
            {1, 2},
            {0, 1},
    };

    int testCount = sizeof(testList)/sizeof((testList)[0]);
    int i;

    Intersect xs = Intersect();
    Intersection i1 = Intersection(1, &s1);
    Intersection i2 = Intersection(2, &s2);
    Intersection i3 = Intersection(3, &s1);
    Intersection i4 = Intersection(4, &s2);
    xs.add(i1);
    xs.add(i2);
    xs.add(i3);
    xs.add(i4);

    for(i = 0; i < testCount; i++)
    {
        c.setOperation(testList[i]);
        Intersect result = Intersect();
        c.doFilterIntersections(xs, result);

        ASSERT_EQ(result.count(), 2);
        ASSERT_EQ(result[0], xs[testResults[i][0]]);
        ASSERT_EQ(result[1], xs[testResults[i][1]]);
    }
}

TEST(CSGTest, A_ray_misses_a_csg_object)
{
    Sphere s1 = Sphere();
    Cube s2 = Cube();
    CSGTest c = CSGTest(CSG::UNION, &s1, &s2);

    Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    Intersect xs = c.doLocalIntersect(r);

    ASSERT_EQ(xs.count(), 0);
}

TEST(CSGTest, A_ray_hits_a_csg_object)
{
    Sphere s1 = Sphere();
    Sphere s2 = Sphere();

    s2.setTransform(translation(0, 0, 0.5));

    CSGTest c = CSGTest(CSG::UNION, &s1, &s2);

    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersect xs = c.doLocalIntersect(r);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_TRUE(double_equal(xs[0].t, 4));
    ASSERT_EQ(xs[0].object, &s1);
    ASSERT_TRUE(double_equal(xs[1].t, 6.5));
    ASSERT_EQ(xs[1].object, &s2);
}