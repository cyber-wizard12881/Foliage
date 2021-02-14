#include "Foliage.h"
#include <iostream>
#include "Bfs.h"
#include "Dfs.h"

using namespace std;

int main() {
	Node^ root = gcnew Node(nullptr, 7);
	root->left = gcnew Node(root, 4);
	root->right = gcnew Node(root, 9);

	root->left->left = gcnew Node(root->left, 2);
	root->left->right = gcnew Node(root->left, 5);

	root->right->left = gcnew Node(root->right, 8);
	root->right->right = gcnew Node(root->right, 10);

	root->right->left->right = gcnew Node(root->right->left, 11);
	root->right->left->right->right = gcnew Node(root->right->left->right, 13);


	Dfs^ dfs = gcnew Dfs();
	dfs->dfs(root, 0);
	dfs->dfsPostProcessing(root, 0);

	Bfs^ bfs = gcnew Bfs();
	bfs->maxDepth = dfs->maxDepth;
	Queue^ queue = gcnew Queue();
	Dictionary<int, List<Node^>^>^ associativeDict = gcnew Dictionary<int, List<Node^>^>();
	bfs->bfsPostProcessing(root, 0, queue, associativeDict);
	

	TreePainter^ treePainter = gcnew TreePainter();
	treePainter->maxDepth = bfs->maxDepth;
	treePainter->associativeList = bfs->associativeDict;
	treePainter->ParseAssociativeList();
	treePainter->StretchAssociativeLocations(2);
	treePainter->Paint(1.3);
	return getchar();
}