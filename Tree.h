
#ifndef TREE_H
#define TREE_H
class Tree {
public:
	Tree(const Tree *parent, const int value) : parent(parent), value(value) {}
	const Tree *parent;
	const int value;
};
#endif
