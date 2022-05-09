#include "gtest/gtest.h"
#include "../../../src/Geometry/Point.h"
#include "../../../src/Geometry/Shapes/Triangle.h"

TEST(TriangleIntersectionWithRay, Parallel) {
	Triangle triangle({0, 0, 0}, {3, 0, 0}, {0, 3, 0});
	Ray ray({3, 0, 1}, {-1, 0, 0});
	Point point;

	EXPECT_EQ(triangle.getRayIntersection(ray, point), false);
}

TEST(TriangleIntersectionWithRay, Behind) {
	Triangle triangle({0, 0, 0}, {3, 0, 0}, {0, 3, 0});
	Ray ray({1, 1, 3}, {0, 0, 1});
	Point point;

	EXPECT_EQ(triangle.getRayIntersection(ray, point), false);
}

TEST(TriangleIntersectionWithRay, NoIntersection) {
	Triangle triangle({0, 0, 0}, {3, 0, 0}, {0, 3, 0});
	Ray ray({-1, -1, 3}, {0, 0, -1});
	Point point;

	EXPECT_EQ(triangle.getRayIntersection(ray, point), false);
}

TEST(TriangleIntersectionWithRay, Intersection) {
	Triangle triangle({0, 0, 0}, {3, 0, 0}, {0, 3, 0});
	Ray ray({1, 1, 3}, {0, 0, -1});
	Point point;

	EXPECT_EQ(triangle.getRayIntersection(ray, point), true);
	EXPECT_EQ(point.x(), 1);
	EXPECT_EQ(point.y(), 1);
	EXPECT_EQ(point.z(), 0);
}
