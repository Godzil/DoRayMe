/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sphere unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <sphere.h>
#include <material.h>
#include <transformation.h>
#include <gtest/gtest.h>


TEST(SphereTest, A_ray_intersect_a_sphere_at_two_points)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].t, 4.0);
    ASSERT_EQ(xs[1].t, 6.0);
}

TEST(SphereTest, A_ray_intersect_a_sphere_at_a_tangent)
{
    Ray r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].t, 5.0);
    ASSERT_EQ(xs[1].t, 5.0);
}

TEST(SphereTest, A_ray_miss_a_sphere)
{
    Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 0);
}

TEST(SphereTest, A_ray_originate_inside_a_sphere)
{
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].t, -1.0);
    ASSERT_EQ(xs[1].t, 1.0);
}

TEST(SphereTest, A_sphere_is_behind_a_ray)
{
    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].t, -6.0);
    ASSERT_EQ(xs[1].t, -4.0);
}

TEST(SphereTest, A_sphere_default_transformation)
{
    Sphere s = Sphere();
    ASSERT_EQ(s.transformMatrix, Matrix4().identity());
}

TEST(SphereTest, Changing_a_sphere_transformation)
{
    Sphere s = Sphere();
    Matrix t = translation(2, 3, 4);

    s.setTransform(t);

    ASSERT_EQ(s.transformMatrix, t);
}

TEST(SphereTest, Intersecting_a_scaled_sphere_with_a_ray)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();

    s.setTransform(scaling(2, 2, 2));

    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].t, 3.0);
    ASSERT_EQ(xs[1].t, 7.0);
}

TEST(SphereTest, Intersecting_a_translated_sphere_with_a_ray)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();

    s.setTransform(translation(5, 0, 0));

    Intersect xs; s.intersect(r, xs);

    ASSERT_EQ(xs.count(), 0);
}

TEST(SphereTest, The_normal_on_a_sphere_at_a_point_on_the_X_axis)
{
    Sphere s = Sphere();
    Tuple n = s.normalAt(Point(1, 0, 0));

    ASSERT_EQ(n, Vector(1, 0, 0));
}

TEST(SphereTest, The_normal_on_a_sphere_at_a_point_on_the_Y_axis)
{
    Sphere s = Sphere();
    Tuple n = s.normalAt(Point(0, 1, 0));

    ASSERT_EQ(n, Vector(0, 1, 0));
}

TEST(SphereTest, The_normal_on_a_sphere_at_a_point_on_the_Z_axis)
{
    Sphere s = Sphere();
    Tuple n = s.normalAt(Point(0, 0, 1));

    ASSERT_EQ(n, Vector(0, 0, 1));
}

TEST(SphereTest, The_normal_on_a_sphere_at_a_nonaxial_point)
{
    Sphere s = Sphere();
    Tuple n = s.normalAt(Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));

    ASSERT_EQ(n, Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
}

TEST(SphereTest, The_normal_is_a_normalise_vector)
{
    Sphere s = Sphere();
    Tuple n = s.normalAt(Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));

    ASSERT_EQ(n, n.normalise());
}

TEST(SphereTest, Computing_the_normal_on_a_translated_sphere)
{
    Sphere s = Sphere();

    s.setTransform(translation(0, 1, 0));

    Tuple n = s.normalAt(Point(0, 1.70711, -0.70711));

    set_equal_precision(0.0001);

    ASSERT_EQ(n, Vector(0, 0.70711, -0.70711));

    /* Revert to default */
    set_equal_precision(FLT_EPSILON);
}

TEST(SphereTest, Computing_the_normal_on_a_tranformed_sphere)
{
    Sphere s = Sphere();

    s.setTransform(scaling(1, 0.5, 1) * rotationZ(M_PI / 5));

    Tuple n = s.normalAt(Point(0, sqrt(2)/2, -sqrt(2)/2));

    set_equal_precision(0.0001);

    ASSERT_EQ(n, Vector(0, 0.97014, -0.24254));

    /* Revert to default */
    set_equal_precision(FLT_EPSILON);
}

TEST(SphereTest, A_sphere_have_a_default_material)
{
    Sphere s = Sphere();
    Material m = Material();

    ASSERT_EQ(s.material, m);
}

TEST(SphereTest, A_sphere_may_be_assigned_a_material)
{
    Sphere s = Sphere();

    Material m = Material();
    m.ambient = 1;

    s.setMaterial(m);

    ASSERT_EQ(s.material, m);
}

TEST(SphereTest, A_helper_for_producing_a_sphere_with_a_glassy_material)
{
    GlassSphere s = GlassSphere();

    ASSERT_EQ(s.transformMatrix, Matrix4().identity());
    ASSERT_EQ(s.material.transparency, 1.0);
    ASSERT_EQ(s.material.refractiveIndex, 1.5);
}

TEST(SphereTest, The_bounding_box_of_a_sphere)
{
    Sphere t = Sphere();
    Tuple sphereMin = Point(-1, -1, -1);
    Tuple sphereMax = Point(1, 1, 1);

    BoundingBox res = t.getBounds();

    ASSERT_EQ(res.min, sphereMin);
    ASSERT_EQ(res.max, sphereMax);
}

TEST(SphereTest, A_sphere_have_finite_bounds)
{
    Sphere t = Sphere();

    ASSERT_TRUE(t.haveFiniteBounds());
}