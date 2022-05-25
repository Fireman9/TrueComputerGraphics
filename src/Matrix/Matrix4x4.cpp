#include "Matrix4x4.h"

Matrix4x Matrix4x::rotateX(double a) {
	Matrix4x m({ 
		{1,0,0,0},
		{0,cos(a),-sin(a),0},
		{0,sin(a),cos(a),0},
		{0,0,0,1} });
	return m;
};
Matrix4x Matrix4x::rotateY(double a) {
	Matrix4x m({
		{cos(a),0,sin(a),0},
		{0,1,0,0},
		{-sin(a),0,cos(a),0},
		{0,0,0,1} });
	return m;
};
Matrix4x Matrix4x::rotateZ(double a) {
	Matrix4x m({
		{cos(a),-sin(a),0,0},
		{sin(a),cos(a),0,0},
		{0,0,1,0},
		{0,0,0,1} });
	return m;
};
Matrix4x Matrix4x::scale(double x, double y, double z) {
	Matrix4x m({
		{x,0,0,0},
		{0,y,0,0},
		{0,0,z,0},
		{0,0,0,1} });
	return m;
};
Matrix4x Matrix4x::shear(double xy, double xz, double yx, double yz, double zx, double zy) {
	Matrix4x m({
		{1,yx,zx,0},
		{xy,1,zy,0},
		{xz,yz,1,0},
		{0,0,0,1} });
	return m;
};
Matrix4x Matrix4x::transpose(double x, double y, double z) {
	Matrix4x m({
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{x,y,z,1} });
	return m;
};
	
Matrix4x::Matrix4x() { setMatrix({}); };
Matrix4x::Matrix4x(vector<vector<double>> m) { setMatrix(m); };
void Matrix4x::setMatrix(vector<vector<double>> m) {
	if (m.empty()) {
		m = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	}
	this->matrix = m;
};

Matrix4x Matrix4x::operator* (Matrix4x m) {
	vector<vector<double>> res = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int n = 0; n < 4; n++) {
				res[i][j] += this->matrix[i][n] * m.getMatrix()[n][j];
			}
		}
	}
	return Matrix4x(res);
};

vector<vector<double>> Matrix4x::getMatrix() {
	return this->matrix;
};