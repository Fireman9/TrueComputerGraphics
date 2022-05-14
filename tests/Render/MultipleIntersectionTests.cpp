#include "gtest/gtest.h"
#include "../../../src/Geometry/Point.h"
#include "../../../src/Geometry/Shapes/Plane.h"
#include "../../../src/Geometry/Shapes/Sphere.h"
#include "../../../src/Geometry/Shapes/Triangle.h"
#include "../../../src/Render/Scene.h"
#include ".../../../src/Render/Screen.h"

TEST(MultipleIntersections, With3Plane) {
	Point inter;
	Plane p1(1, 1, 1, -1);
	Plane p2(1, 1, 1, -2);
	Plane p3(1, 1, 1, 3);

	Scene sc;
	Screen scr;
	scr.SetStartPoint(Point(0, 0, 1));
	sc.SetScreen(scr);
	sc.AddNewPlane({ p1,p2,p3 });
	sc.Intersections(0, 0, inter);
	EXPECT_TRUE(inter.isEqual(Point(0, 0, 1)));
}
TEST(MultipleIntersections, With3Shpere) {
	Point inter;
	Sphere s1(20, 0, 0, 50);
	Sphere s2(20, 0, 0, 60);
	Sphere s3(15, 0, 0, 47);

	Scene sc;
	Screen scr;
	scr.SetStartPoint(Point(0, 0, 1));
	sc.SetScreen(scr);
	sc.AddNewSphere({ s1,s2, s3 });
	sc.Intersections(0, 0, inter);
	EXPECT_TRUE(inter.isEqual(Point(0, 0, 30)));
}
TEST(MultipleIntersections, With2Triangle) {
	Point inter;
	Triangle t1(Point(-1, -1, 5), Point(-1, 4, 5), Point(3, -1, 5));
	Triangle t2(Point(-1, -1, 5), Point(-1, 4, 8), Point(3, 2, 9));

	Scene sc;
	Screen scr;
	scr.SetStartPoint(Point(0, 0, 1));
	sc.SetScreen(scr);
	sc.AddNewTriangle({ t1,t2 });
	sc.Intersections(0, 0, inter);
	EXPECT_TRUE(inter.isEqual(Point(0, 0, 5)));
}
TEST(MultipleIntersections, WithAll) {
	Point inter;
	Sphere s1(20, 0, 0, 50);
	Plane p1(1, 1, 1, 60);
	Triangle t1(Point(-10, -5, 20), Point(10, -5, 20), Point(0, 5, 40));

	Scene sc;
	Screen scr;
	scr.SetStartPoint(Point(0, 0, 1));
	sc.SetScreen(scr);
	sc.AddNewSphere({ s1 });
	sc.AddNewPlane({ p1 });
	sc.AddNewTriangle({ t1 });
	sc.Intersections(0, 0, inter);
	EXPECT_TRUE(inter.isEqual(Point(0, 0, 30)));
}
TEST(MultipleIntersections, WithNothing) {
	Point inter(NULL, NULL, NULL);
	Point inter_f = inter;
	Sphere s1(1, 0, 0, 50);
	Plane p1(1, 1, 1, 60);
	Triangle t1(Point(-10, -5, 20), Point(-5, -5, 20), Point(-10, 5, 40));

	Scene sc;
	Screen scr;
	scr.SetStartPoint(Point(0, 0, 1));
	sc.SetScreen(scr);
	sc.AddNewSphere({ s1 });
	sc.AddNewPlane({ p1 });
	sc.AddNewTriangle({ t1 });
	sc.Intersections(0, 0, inter);
	EXPECT_EQ(inter.x(), NULL);
}