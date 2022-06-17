#ifndef NODE_H
#define NODE_H

#include "../Geometry/Point.h"
#include "../Geometry/Shapes/Triangle.h"
#include <vector>
#include <algorithm>

using std::vector;

class Node {
public:
	Node();
	Node(Point start, Point end);
	Node(Point start, Point end, vector<Triangle> list);
	Node(Point start, Point end, Node* p);
	Node(Node* l, Node* r, Node* p);
	Node(Point start, Point end, vector<Triangle> list, Node* l, Node* r, Node* p);
	void setStart(Point start);
	void setEnd(Point end);
	void setLeft(Node* l);
	void setRight(Node* r);
	void setParent(Node* p);
	void setTriangles(vector<Triangle> t);
	void addTriangles(vector<Triangle> t);
	void addTriangle(Triangle t);

	Node* right();
	Node* left();
	Node* parent();
	Point start();
	Point end();
	vector<Triangle> triangles();
	int trianglesCount();
	
private:
	Point startP;
	Point endP;
	vector<Triangle> trianglesList;
	static int const MAX_SIZE = 50;
	Node* leftN;
	Node* rightN;
	Node* parentN;

	Point findMidle(Point* min, Point* max);
	void fitBox();
	void divade();
};

#endif //NODE_H