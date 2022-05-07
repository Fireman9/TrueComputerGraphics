#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point();

	Point(double x, double y, double z);

	void setCoordinates(double x, double y, double z);

	double distanceTo(Point &p) const;

	double distanceTo(double x, double y, double z) const;

	bool isEqual(Point &p, double epsilon = 0.01) const;

	Point operator+(Point &p) const;

	Point operator-(Point &p) const;

	double x() const;

	double y() const;

	double z() const;

	void setX(double x);

	void setY(double y);

	void setZ(double z);

private:
	double mX, mY, mZ;

};

#endif //POINT_H
