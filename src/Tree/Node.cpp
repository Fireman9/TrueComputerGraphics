#include "Node.h"

Node::Node() : Node(Point(INT_MIN,INT_MIN,INT_MIN), Point(INT_MAX,INT_MAX,INT_MAX)) {}
Node::Node(Point start, Point end) : Node(start, end, {},NULL,NULL,NULL) {}
Node::Node(Point start, Point end, vector<Triangle> list) : Node(start, end, list,NULL,NULL,NULL) {}
Node::Node(Node* l, Node* r, Node* p) : Node(Point(INT_MIN, INT_MIN, INT_MIN), Point(INT_MAX, INT_MAX, INT_MAX), {},l,r,p) {}
Node::Node(Point start_p, Point end_p, vector<Triangle> list, Node* l, Node* r, Node* p) {
	setStart(start_p);
	setEnd(end_p);
	setTriangles(list);
	setLeft(l);
	setRight(r);
	setParent(p);
}

void Node::setStart(Point start) { this->startP = start; }
void Node::setEnd(Point end) { this->endP = end; }
void Node::setLeft(Node* l) { this->leftN = l; }
void Node::setRight(Node* r) { this->rightN = r; }
void Node::setParent(Node* p) { this->parentN = p; }
void Node::setTriangles(vector<Triangle> t) { this->trianglesList = t; }
void Node::addTriangles(vector<Triangle> t) {
	this->trianglesList.insert(this->trianglesList.end(), t.begin(), t.end());
}
void Node::addTriangle(Triangle t) { this->trianglesList.push_back(t); }

Node* Node::right() { return this->rightN; }
Node* Node::left() { return this->leftN; }
Node* Node::parent() { return this->parentN; }
Point Node::start() { return this->startP; }
Point Node::end() { return this->endP; }
vector<Triangle> Node::triangles() { return this->trianglesList; }
int Node::trianglesCount() { return this->trianglesList.size(); }
