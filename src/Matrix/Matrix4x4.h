#include <vector>

#include "../Geometry/Point.h"

#include "../Geometry/Vector.h"

#include "../Geometry/Shapes/Triangle.h"
using namespace std;


class Matrix4x4 {
public:
	static Matrix4x4 rotateX(double a);
	static Matrix4x4 rotateY(double a);
	static Matrix4x4 rotateZ(double a);
	static Matrix4x4 scale(double x, double y, double z);
	static Matrix4x4 shear(double xy, double xz, double yx, double yz, double zx, double zy);
	static Matrix4x4 transpose(double x, double y, double z);

	Matrix4x4 operator* (Matrix4x4 m) const;
	Point operator* (Point m) const;
	Vector operator* (Vector m) const;
	Triangle operator* (Triangle m) const;
	vector<vector<double>> getMatrix();
private:
	Matrix4x4();
	Matrix4x4(vector<vector<double>> m);
	vector<vector<double>> matrix;
	void setMatrix(vector<vector<double>> m);
};