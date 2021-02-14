#pragma once
#include "Node.h"

ref class Dfs {
public:
	int maxDepth;
	void dfs(Node^ root, int depth);
	void dfsPostProcessing(Node^ root, int depth);
};