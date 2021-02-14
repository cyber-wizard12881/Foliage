#pragma once
#include "Node.h"

#define Depth 10

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

ref class Bfs {
public:
	int maxDepth;
	Queue queue;
	Dictionary<int, List<Node^>^>^ associativeDict;
	void bfs(Node^ root, int depth, Queue^ queue, Dictionary<int, List<Node^>^>^ associativeDict);
	void bfsPostProcessing(Node^ root, int depth, Queue^ queue, Dictionary<int, List<Node^>^>^ associativeDict);
};
