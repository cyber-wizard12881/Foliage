#include "Bfs.h"

void Bfs::bfs(Node^ root, int depth, Queue^ queue, Dictionary<int, List<Node^>^>^ associativeDict)
{
	if (depth == 0) {
		root->depth = depth;
		queue->Enqueue(root);
	}
	if (queue->Count > 0) {
		Node^ node = (Node^)queue->Dequeue();
		if (node != nullptr) {
			if (associativeDict->ContainsKey(node->depth)) {
				associativeDict[node->depth]->Add(node);
			}
			else {
				List<Node^>^ nodes = gcnew List<Node^>();
				nodes->Add(node);
				associativeDict->Add(node->depth, nodes);
			}
			if ((node->left != nullptr || node->right != nullptr || node->left == nullptr || node->right == nullptr) ) { //&& depth <= this->maxDepth) {
				depth++;
				if (node->left != nullptr) {
					node->left->depth = node->left->parent->depth + 1;
					queue->Enqueue(node->left);
				}
				
				if (node->right != nullptr) {
					node->right->depth = node->right->parent->depth + 1;
					queue->Enqueue(node->right);
				}
			}
		}
		bfs(root, depth, queue, associativeDict);
	}
}

void Bfs::bfsPostProcessing(Node^ root, int depth, Queue^ queue, Dictionary<int, List<Node^>^>^ associativeDict)
{
	bfs(root, 0, queue, associativeDict);
	this->associativeDict = associativeDict;
}
