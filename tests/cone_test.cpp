/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cone unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <intersection.h>
#include <cone.h>
#include <transformation.h>
#include <gtest/gtest.h>

class ConeTest : public Cone
{
public:
    Tuple doLocalNormalAt(Tuple point)
    {
        return localNormalAt(point);
    }
};

TEST(ConeTest, Intersecting_a_cone_with_a_ray)
{
    Cone cone = Cone();

    Point Origins[] = {
            Point(0, 0, -5),
            Point(0, 0, -5),
            Point(1, 1, -5),
    };

    Vector Directions[] = {
            Vector(0, 0, 1),
            Vector(1, 1, 1),
            Vector(-0.5, -1, 1),
    };

    double t0s[] = { 5, 8.66025, 4.55006 };
    double t1s[] = { 5, 8.66025, 49.44994 };

    int i;
    for(i = 0; i < 3; i++)
    {
        Tuple direction = Directions[i].normalise();
        Ray r = Ray(Origins[i], direction);

        Intersect xs; cone.intersect(r, xs);

        /* Temporary lower the precision */
        set_equal_precision(0.00001);

        ASSERT_EQ(xs.count(), 2);
        EXPECT_TRUE(double_equal(xs[0].t, t0s[i]));
        EXPECT_TRUE(double_equal(xs[1].t, t1s[i]));

        set_equal_precision(FLT_EPSILON);
    }
}

TEST(ConeTest, Intersecting_a_cone_with_a_ray_parall_to_one_of_its_halves)
{
    Cone cone = Cone();
    Tuple direction = Vector(0, 1, 1).normalise();
    Ray r = Ray(Point(0, 0, -1), direction);
    Intersect xs; cone.intersect(r, xs);
    ASSERT_EQ(xs.count(), 1);

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_TRUE(double_equal(xs[0].t, 0.35355));

    set_equal_precision(FLT_EPSILON);

}
TEST(ConeTest, Intersecting_a_cone_end_cap)
{
    Point Origins[] = {
            Point(0, 0, -5),
            Point(0, 0, -0.25),
            Point(0, 0, -0.25),
    };
    
    Vector Directions[] = {
            Vector(0, 1, 0),
            Vector(0, 1, 1),
            Vector(0, 1, 0),
    };
    
    uint32_t Counts[] = { 0, 2, 4 };
    
    Cone cone = Cone();
    cone.minCap = -0.5;
    cone.maxCap = 0.5;
    cone.isClosed = true;
    
    int i;
    for(i = 0; i < 3; i++)
    {
        Tuple direction = Directions[i].normalise();
        Ray r = Ray(Origins[i], direction);

        Intersect xs;
        cone.intersect(r, xs);

        ASSERT_EQ(xs.count(), Counts[i]);
    }
}

TEST(ConeTest, Computing_the_normal_vector_on_a_cone)
{
    ConeTest cone = ConeTest();

    Point HitPointss[] = {
            Point(0, 0, 0),
            Point(1, 1, 1),
            Point(-1, -1, 0),
    };

    Vector Normals[] = {
            Vector(0, 0, 0),
            Vector(1, -sqrt(2), 1),
            Vector(-1, 1, 0),
    };

    int i;
    for(i = 0; i < 3; i++)
    {
        ASSERT_EQ(cone.doLocalNormalAt(HitPointss[i]), Normals[i]);
    }
}

TEST(ConeTest, The_bounding_box_of_a_cut_cone)
{
    Cone t = Cone();
    BoundingBox b = BoundingBox(Point(-8, -5, -8), Point(8, 8, 8));
    t.minCap = -5;
    t.maxCap = 8;
    BoundingBox res = t.getBounds();

    ASSERT_EQ(res.min, b.min);
    ASSERT_EQ(res.max, b.max);
}

TEST(ConeTest, The_bounding_box_of_a_uncut_cone)
{
    /* This one is tricky. Infinite size don't cope well with transformations */
    Cone t = Cone();
    BoundingBox res = t.getBounds();

    ASSERT_FALSE(res.min.isRepresentable());
    ASSERT_FALSE(res.max.isRepresentable());
}

TEST(ConeTest, An_uncut_cone_have_infinite_bounds)
{
    Cone t = Cone();

    ASSERT_FALSE(t.haveFiniteBounds());
}

TEST(ConeTest, A_cut_cone_have_finite_bounds)
{
    Cone t = Cone();
    t.minCap = -5;
    t.maxCap = 3;
    BoundingBox res = t.getBounds();

    ASSERT_TRUE(t.haveFiniteBounds());
    ASSERT_EQ(res.min, Point(-5, -5, -5));
    ASSERT_EQ(res.max, Point(5, 3, 5));
}