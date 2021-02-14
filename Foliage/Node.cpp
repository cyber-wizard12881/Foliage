#include "Node.h"

Node::Node(Node^ node, int value)
{
    this->parent = node;
    this->value = value;
}

Node::Node()
{
    this->value = 0;
}

Node::~Node()
{
    this->value = 0;
}
