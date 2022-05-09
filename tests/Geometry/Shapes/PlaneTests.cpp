#include "gtest/gtest.h"
#include "../../../src/Geometry/Point.h"
#include "../../../src/Geometry/Shapes/Plane.h"

TEST(PlaneIntersectionWithRay, NoIntersection) {
	Plane plane(-3, -2, 1, -4);
	Ray ray(Point(2, -3, 4), Vector(2, -4, -2));
	Point point;

	EXPECT_EQ(plane.getRayIntersection(ray, point), false);
	EXPECT_EQ(point.x(), 0);
	EXPECT_EQ(point.y(), 0);
	EXPECT_EQ(point.z(), 0);
}

TEST(PlaneIntersectionWithRay, Intersection) {
	Plane plane1(0, 0, 1, 0);
	Ray ray1(Point(1, 1, 1), Vector(0, 0, -1));
	Point point;

	EXPECT_EQ(plane1.getRayIntersection(ray1, point), true);
	EXPECT_EQ(point.x(), 1);
	EXPECT_EQ(point.y(), 1);
	EXPECT_EQ(point.z(), 0);

	Plane plane2(2, -1, 3, -15);
	Ray ray2(Point(4, -1, 4), Vector(1, 8, -2));
	EXPECT_EQ(plane2.getRayIntersection(ray2, point), true);
	EXPECT_EQ(point.x(), 4.5);
	EXPECT_EQ(point.y(), 3);
	EXPECT_EQ(point.z(), 3);
}
