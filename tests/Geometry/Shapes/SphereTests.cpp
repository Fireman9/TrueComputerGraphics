#include "gtest/gtest.h"
#include "../../../src/Geometry/Shapes/Sphere.h"

TEST(SphereIntersectionWithRay, NoIntersection) {
	Sphere sphere(1, {2, 0, 0});
	Ray ray({0, 0, 3}, {0, 0, 2});
	EXPECT_EQ(sphere.getRayIntersection(ray).size(), 0);
}

TEST(SphereIntersectionWithRay, OnePointIntersection) {
	Sphere sphere1(2, {2, 0, 0});
	Ray ray1({0, 0, 3}, {0, 0, -1});

	auto intersectionPoints1 = sphere1.getRayIntersection(ray1);

	EXPECT_EQ(intersectionPoints1.size(), 1);

	EXPECT_EQ(intersectionPoints1[0].x(), 0);
	EXPECT_EQ(intersectionPoints1[0].y(), 0);
	EXPECT_EQ(intersectionPoints1[0].z(), 0);

	Sphere sphere2(2, {3, 0, 0});
	Ray ray2({1, 0, 3}, {0, 0, -1});

	auto intersectionPoints2 = sphere2.getRayIntersection(ray2);

	EXPECT_EQ(intersectionPoints2.size(), 1);

	EXPECT_EQ(intersectionPoints2[0].x(), 1);
	EXPECT_EQ(intersectionPoints2[0].y(), 0);
	EXPECT_EQ(intersectionPoints2[0].z(), 0);
}

TEST(SphereIntersectionWithRay, TwoPointIntersection) {
	Sphere sphere(1, {0, 0, 0});
	Ray ray({0, 0, 2}, {0, 0, -1});

	auto intersectionPoints = sphere.getRayIntersection(ray);

	EXPECT_EQ(intersectionPoints.size(), 2);

	EXPECT_EQ(intersectionPoints[0].x(), 0);
	EXPECT_EQ(intersectionPoints[0].y(), 0);
	EXPECT_EQ(intersectionPoints[0].z(), 1);

	EXPECT_EQ(intersectionPoints[1].x(), 0);
	EXPECT_EQ(intersectionPoints[1].y(), 0);
	EXPECT_EQ(intersectionPoints[1].z(), -1);
}
