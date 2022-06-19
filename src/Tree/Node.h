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
	static Node* createNode(vector<Triangle> list);
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
	void findAllNodes(Ray r, vector<Node*>* n);
	int calcNodesSize(Node* n, int c);
	void static fitBox(Node* n, vector<Triangle> v);

private:
	Point startP;
	Point endP;
	vector<Triangle> trianglesList;
	static int const MAX_SIZE = 500;
	double const EPSILON = 0.01;
	Node* leftN;
	Node* rightN;
	Node* parentN;
	int divIndex = 0;
	int deep = 0;

	void divade();
	void setTriangleToSide(Triangle t);
	bool isPointInBox(Point p, Point s, Point e);
	void findDivIndex();
	bool isRayInBox(Ray r, Node* n);
	void fitBox();
};

#endif //NODE_H