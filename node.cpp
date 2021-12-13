#include "node.hpp"

Node::Node(void *data = nullptr)
{
	this->children = new Node *[0];
	this->data = data;
}

Node::~Node()
{
	delete[] this->children;
}

void Node::AddChild(Node *child)
{
	this->children = (Node **)realloc(this->children, (this->childrenCount + 1) * sizeof(Node));
	this->children[this->childrenCount] = child;
	child->parent = this;
	this->childrenCount++;
}

Node **Node::GetChildren()
{
	return this->children;
}

int Node::GetChildrenCount()
{
	return this->childrenCount;
}

Node *Node::GetParent()
{
	return this->parent;
}