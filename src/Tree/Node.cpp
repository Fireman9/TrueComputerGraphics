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
