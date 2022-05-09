#include "Triangle.h"

Triangle::Triangle(Point first, Point second, Point third) : mFirst(first),
																mSecond(second),
																mThird(third) {}

Point Triangle::first() {
	return mFirst;
}

Point Triangle::second() {
	return mSecond;
}

Point Triangle::third() {
	return mThird;
}

void Triangle::setFirst(Point first) {
	mFirst = first;
}

void Triangle::setSecond(Point second) {
	mSecond = second;
}

void Triangle::setThird(Point third) {
	mThird = third;
}
