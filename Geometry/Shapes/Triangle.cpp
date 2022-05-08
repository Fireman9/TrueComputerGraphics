#include "Triangle.h"

Triangle::Triangle(Point &first, Point &second, Point &third) : mFirst(first),
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

void Triangle::setFirst(Point &m_first) {
	mFirst = m_first;
}

void Triangle::setSecond(Point &m_second) {
	mSecond = m_second;
}

void Triangle::setThird(Point &m_third) {
	mThird = m_third;
}
