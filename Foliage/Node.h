#pragma once

public ref class Node {
public:
	Node(Node^ node, int value);
	Node();
	~Node();
	int value;
	int depth;
	Node^ left;
	Node^ right;
	Node^ parent;
};