#include "Node.h"

Node::Node() : Node(Point(DBL_MIN,DBL_MIN,DBL_MIN), Point(DBL_MAX,DBL_MAX,DBL_MAX)) {}
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
	if (trianglesCount() > MAX_SIZE) divade();
}
void Node::addTriangles(vector<Triangle> t) {
	this->trianglesList.insert(this->trianglesList.end(), t.begin(), t.end());
	if (trianglesCount() > MAX_SIZE) divade();
}
void Node::addTriangle(Triangle t) { this->trianglesList.push_back(t); 
	if (trianglesCount() > MAX_SIZE) divade();
}

Node* Node::right() { return this->rightN; }
Node* Node::left() { return this->leftN; }
Node* Node::parent() { return this->parentN; }
Point Node::start() { return this->startP; }
Point Node::end() { return this->endP; }
vector<Triangle> Node::triangles() { return this->trianglesList; }
int Node::trianglesCount() { return this->trianglesList.size(); }

Point Node::findMidle(Point* min, Point* max) {
	Point max_t = Point(DBL_MIN, DBL_MIN, DBL_MIN);
	Point min_t = Point(DBL_MAX, DBL_MAX, DBL_MAX);
	Point tmp = Point();
	for (auto& t : this->trianglesList) {
		tmp = t.center();
		if (tmp.x() > max_t.x()) max_t.setX(tmp.x());
		if (tmp.y() > max_t.y()) max_t.setY(tmp.y());
		if (tmp.z() > max_t.z()) max_t.setZ(tmp.z());
		if (tmp.x() < min_t.x()) min_t.setX(tmp.x());
		if (tmp.y() < min_t.y()) min_t.setY(tmp.y());
		if (tmp.z() < min_t.z()) min_t.setZ(tmp.z());
	}
	max->setCoordinates(max_t.x(), max_t.y(), max_t.z());
	min->setCoordinates(min_t.x(), min_t.y(), min_t.z());
	return (max_t + min_t) * 0.5;
}

void Node::fitBox() {
	Point m = findMidle(&start(), &end());
}

void Node::divade() {
	if (trianglesCount() < MAX_SIZE) return;

	Node l = Node(start(), end(), this);
	Node r = Node(start(), end(), this);

	Point tmp_r = Point(start());
	Point tmp_l = Point(end());
	vector<double> sizes = { end().x() - start().x(),end().y() - start().y(),end().z() - start().z()};
	double maxDif = *std::max_element(sizes.begin(), sizes.end());
	int indexDif = std::distance(sizes.begin(), std::find(sizes.begin(), sizes.end(), maxDif));
	Point change = (start()+end())*0.5;
	switch (indexDif)
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
	default:
		break;
	}
	for (auto& t : this->trianglesList) {
		bool ans = false;
		switch (indexDif)
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
		default:
			break;
		}
		if (ans) r.addTriangle(t);
		else l.addTriangle(t);
	}
	this->setLeft(&l);
	this->setRight(&r);

}

