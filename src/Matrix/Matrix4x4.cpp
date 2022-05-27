#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::rotateX(double a) {
	Matrix4x4 m({ 
		{1,0,0,0},
		{0,cos(a),-sin(a),0},
		{0,sin(a),cos(a),0},
		{0,0,0,1} });
	return m;
};
Matrix4x4 Matrix4x4::rotateY(double a) {
	Matrix4x4 m({
		{cos(a),0,sin(a),0},
		{0,1,0,0},
		{-sin(a),0,cos(a),0},
		{0,0,0,1} });
	return m;
};
Matrix4x4 Matrix4x4::rotateZ(double a) {
	Matrix4x4 m({
		{cos(a),-sin(a),0,0},
		{sin(a),cos(a),0,0},
		{0,0,1,0},
		{0,0,0,1} });
	return m;
};
Matrix4x4 Matrix4x4::scale(double x, double y, double z) {
	Matrix4x4 m({
		{x,0,0,0},
		{0,y,0,0},
		{0,0,z,0},
		{0,0,0,1} });
	return m;
};
Matrix4x4 Matrix4x4::shear(double xy, double xz, double yx, double yz, double zx, double zy) {
	Matrix4x4 m({
		{1,yx,zx,0},
		{xy,1,zy,0},
		{xz,yz,1,0},
		{0,0,0,1} });
	return m;
};
Matrix4x4 Matrix4x4::transpose(double x, double y, double z) {
	Matrix4x4 m({
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{x,y,z,1} });
	return m;
};
	
Matrix4x4::Matrix4x4() { setMatrix({}); };
Matrix4x4::Matrix4x4(vector<vector<double>> m) { setMatrix(m); };
void Matrix4x4::setMatrix(vector<vector<double>> m) {
	if (m.empty()) {
		m = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	}
	this->matrix = m;
};

Matrix4x4 Matrix4x4::operator* (Matrix4x4 m) const {
	vector<vector<double>> res = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int n = 0; n < 4; n++) {
				res[i][j] += this->matrix[i][n] * m.getMatrix()[n][j];
			}
		}
	}
	return Matrix4x4(res);
};

Point Matrix4x4::operator* (Point m) const {
	vector<double> res = { 0,0,0,0};
	vector<double> mH = {m.x(), m.y(), m.z(),1};
	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			res[i] += this->matrix[n][i] * mH[n];
		}
	}
	return Point(res[0],res[1],res[2]);
};

Vector Matrix4x4::operator* (Vector m) const {
	vector<double> res = { 0,0,0,0 };
	vector<double> mH = { m.x(), m.y(), m.z(),1 };
	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			res[i] += this->matrix[n][i] * mH[n];
		}
	}
	return Vector(res[0], res[1], res[2]);
};

vector<vector<double>> Matrix4x4::getMatrix() {
	return this->matrix;
};