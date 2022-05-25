#include <vector>
using namespace std;


class Matrix4x {
public:
	static Matrix4x rotateX(double a);
	static Matrix4x rotateY(double a);
	static Matrix4x rotateZ(double a);
	static Matrix4x scale(double x, double y, double z);
	static Matrix4x shear(double xy, double xz, double yx, double yz, double zx, double zy);
	static Matrix4x transpose(double x, double y, double z);

	Matrix4x operator* (Matrix4x m);
	vector<vector<double>> getMatrix();
private:
	Matrix4x();
	Matrix4x(vector<vector<double>> m);
	vector<vector<double>> matrix;
	void setMatrix(vector<vector<double>> m);
};