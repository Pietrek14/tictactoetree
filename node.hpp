#pragma once

#include <stdlib.h>

class Node
{
	friend class Tree;

	Node **children;
	int childrenCount = 0;
	Node *parent = nullptr;

public:
	Node(void *data);
	~Node();

	void *data;

	void AddChild(Node *child);
	Node **GetChildren();
	int GetChildrenCount();
	Node* GetParent();
};