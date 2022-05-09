#include "gtest/gtest.h"
#include "../../../src/Geometry/Shapes/Sphere.h"

TEST(SphereIntersectionWithRay, NoIntersection) {

	Sphere sphere(1, {2, 0, 0});
	Ray ray({0, 0, 3}, {0, 0, 2});
	Point point;
	EXPECT_EQ(sphere.isRayIntersection(ray), sphere.NoIntersection);
	EXPECT_ANY_THROW(sphere.getOnePointRayIntersection(ray));
	EXPECT_ANY_THROW(sphere.getTwoPointRayIntersection(ray));
	EXPECT_EQ(point.x(), 0);
	EXPECT_EQ(point.y(), 0);
	EXPECT_EQ(point.z(), 0);
}

TEST(SphereIntersectionWithRay, OnePointIntersection) {
	Sphere sphere1(2, {2, 0, 0});
	Ray ray1({0, 0, 3}, {0, 0, 1});

	EXPECT_EQ(sphere1.isRayIntersection(ray1), sphere1.OnePointIntersection);
	EXPECT_ANY_THROW(sphere1.getTwoPointRayIntersection(ray1));

	Point point1 = sphere1.getOnePointRayIntersection(ray1);

	EXPECT_EQ(point1.x(), 0);
	EXPECT_EQ(point1.y(), 0);
	EXPECT_EQ(point1.z(), 0);


	Sphere sphere2(2, {3, 0, 0});
	Ray ray2({1, 0, 3}, {0, 0, 1});

	EXPECT_EQ(sphere2.isRayIntersection(ray2), sphere2.OnePointIntersection);
	EXPECT_ANY_THROW(sphere2.getTwoPointRayIntersection(ray2));

	Point point2 = sphere2.getOnePointRayIntersection(ray2);

	EXPECT_EQ(point2.x(), 1);
	EXPECT_EQ(point2.y(), 0);
	EXPECT_EQ(point2.z(), 0);
}

TEST(SphereIntersectionWithRay, TwoPointIntersection) {
	Sphere sphere(1, {0, 0, 0});
	Ray ray({0, 0, 2}, {0, 0, 1});

	EXPECT_EQ(sphere.isRayIntersection(ray), sphere.TwoPointIntersection);
	EXPECT_ANY_THROW(sphere.getOnePointRayIntersection(ray));

	std::pair<Point, Point> points = sphere.getTwoPointRayIntersection(ray);

	EXPECT_EQ(points.first.x(), 0);
	EXPECT_EQ(points.first.y(), 0);
	EXPECT_EQ(points.first.z(), -1);

	EXPECT_EQ(points.second.x(), 0);
	EXPECT_EQ(points.second.y(), 0);
	EXPECT_EQ(points.second.z(), 1);
}
