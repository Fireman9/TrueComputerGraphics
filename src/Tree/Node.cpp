#include "Node.h"
#include <iostream>

Node::Node() : Node(Point(-1000,-1000,-1000), Point(1000,1000,1000)) {}
Node::Node(Point start, Point end) : Node(start, end, {},NULL,NULL,NULL) {}
Node::Node(Point start, Point end, vector<Triangle> list) : Node(start, end, list,NULL,NULL,NULL) {}
Node::Node(Point start, Point end, Node* p) : Node(start, end, {}, NULL, NULL, p) {}
Node::Node(Node* l, Node* r, Node* p) : Node(p->start(), p->end(), {}, l, r, p) {}
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

void Node::setTriangles(vector<Triangle> t) { 
	this->trianglesList = t;
	if (trianglesCount() >= MAX_SIZE) divade();
}

void Node::addTriangles(vector<Triangle> t) {
	this->trianglesList.insert(this->trianglesList.end(), t.begin(), t.end());
	if (trianglesCount() >= MAX_SIZE) divade();
}

void Node::addTriangle(Triangle t) { 
	if (trianglesCount() >= MAX_SIZE) divade();
	if (left() == NULL && right() == NULL) {
		this->trianglesList.push_back(t);
	}
	else {
		this->setTriangleToSide(t);
	}
}

bool Node::isPointInBox(Point p, Point s, Point e) {
	bool ans1 = std::min(s.x(), e.x()) - EPSILON <= p.x() <= std::max(s.x(), e.x()) + EPSILON;
	bool ans2 = std::min(s.y(), e.y()) - EPSILON <= p.y() <= std::max(s.y(), e.y()) + EPSILON;
	bool ans3 = std::min(s.z(), e.z()) - EPSILON <= p.z() <= std::max(s.z(), e.z()) + EPSILON;
	return ans1 && ans2 && ans3;
}

void Node::setTriangleToSide(Triangle t) {
	bool ansLeft = true;
	Point m = (start() + end()) * 0.5;
	Point c = t.center();
	Point tmp_l = Point(end());
	Point tmp_r = Point(start());
	//findDivIndex();
	switch (divIndex)
	{
	case 0:
		tmp_l.setX(m.x());
		tmp_r.setX(m.x());
		break;
	case 1:
		tmp_l.setY(m.y());
		tmp_r.setY(m.y());
		break;
	case 2:
		tmp_l.setZ(m.z());
		tmp_r.setZ(m.z());
		break;
	}
	ansLeft = isPointInBox(c, start(), tmp_l);
	if (ansLeft) {
		if (left() != NULL) { left()->addTriangle(t); }
		else { 
			Node* l = new Node(start(), tmp_l, this);
			l->deep = deep + 1;
			setLeft(l);
			l->addTriangle(t);
		}
	}
	else {
		if (right() != NULL) { 
			right()->addTriangle(t);
		}
		else {
			Node* r = new Node(tmp_r, end(), this);
			r->deep = deep + 1;
			setRight(r);
			r->addTriangle(t);
		}
	}
}

Node* Node::right() { return this->rightN; }
Node* Node::left() { return this->leftN; }
Node* Node::parent() { return this->parentN; }
Point Node::start() { return this->startP; }
Point Node::end() { return this->endP; }
vector<Triangle> Node::triangles() { return this->trianglesList; }
int Node::trianglesCount() { return this->trianglesList.size(); }


void Node::fitBox() {
	Point max_t = Point(-1000, -1000, -1000);
	Point min_t = Point(1000, 1000, 1000);
	Point tmp = Point();
	for (auto& t : this->trianglesList) {
		tmp = t.center();
		vector<Point> allPoints = {t.v0(), t.v1(),t.v2()};
		for (auto& p : allPoints) {
			if (p.x() > max_t.x()) max_t.setX(p.x());
			if (p.y() > max_t.y()) max_t.setY(p.y());
			if (p.z() > max_t.z()) max_t.setZ(p.z());
			if (p.x() < min_t.x()) min_t.setX(p.x());
			if (p.y() < min_t.y()) min_t.setY(p.y());
			if (p.z() < min_t.z()) min_t.setZ(p.z());
		}
	}
	endP.setCoordinates(max_t.x()+EPSILON, max_t.y() + EPSILON, max_t.z() + EPSILON);
	startP.setCoordinates(min_t.x() - EPSILON, min_t.y() - EPSILON, min_t.z() - EPSILON);
}

void Node::findDivIndex() {
	vector<double> sizes = { end().x() - start().x(),end().y() - start().y(),end().z() - start().z() };
	double maxDif = *std::max_element(sizes.begin(), sizes.end());
	divIndex = std::distance(sizes.begin(), std::find(sizes.begin(), sizes.end(), maxDif));
}

void Node::divade() {
	if (trianglesCount() < MAX_SIZE) return;
	fitBox();

	Node* l = new Node(start(), end(), this);
	Node* r = new Node(start(), end(), this);
	l->deep = this->deep + 1;
	r->deep = this->deep + 1;
	findDivIndex();

	Point tmp_r = Point(start());
	Point tmp_l = Point(end());
	
	Point change = (start()+end())*0.5;
	switch (divIndex)
	{
	case 0:
		tmp_r.setX(change.x());
		tmp_l.setX(change.x());
		break;
	case 1:
		tmp_r.setY(change.y());
		tmp_l.setY(change.y());
		break;
	case 2:
		tmp_r.setZ(change.z());
		tmp_l.setZ(change.z());
		break;
	}
	l->setEnd(tmp_l);
	r->setStart(tmp_r);
	this->setLeft(l);
	this->setRight(r);
	for (auto& t : this->trianglesList) {
		bool ans = false;
		switch (divIndex)
		{
		case 0:
			ans = t.center().x() > change.x();
			break;
		case 1:
			ans = t.center().y() > change.y();
			break;
		case 2:
			ans = t.center().z() > change.z();
			break;
		}
		if (ans) { 
			r->addTriangle(t); }
		else {
			l->addTriangle(t); }
	}

	this->trianglesList = {};
}

void Node::findAllNodes(Ray r, vector<Node*>* n) {
	if (isRayInBox(r, this)) {
		if (left() == NULL && right() == NULL) {
			if (triangles().size() > 0) {
				n->push_back(this);
			}
		}
		else {
			if (left() != NULL) left()->findAllNodes(r, n);
			if (right() != NULL) right()->findAllNodes(r, n);
		}
	}

}

int Node::calcNodesSize(Node* n, int c) {
	if (n->right() == NULL && n->left() == NULL) c += n->trianglesCount();
	else {
		c = calcNodesSize(n->left(),c);
		c = calcNodesSize(n->right(),c);
	}
	return c;
}

bool Node::isRayInBox(Ray r, Node* n) {
	double dx = 1.0 / r.direction().x();
	double dy = 1.0 / r.direction().y();
	double dz = 1.0 / r.direction().z();

	double t1 = (n->start().x() - r.origin().x()) * dx;
	double t2 = (n->end().x() - r.origin().x()) * dx;
	double t3 = (n->start().y() - r.origin().y()) * dy;
	double t4 = (n->end().y() - r.origin().y()) * dy;
	double t5 = (n->start().z() - r.origin().z()) * dz;
	double t6 = (n->end().z() - r.origin().z()) * dz;

	double tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	double tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tmax < + EPSILON) return false; //box behind
	if (tmin > tmax - EPSILON) return false; //miss

	return true;
}

