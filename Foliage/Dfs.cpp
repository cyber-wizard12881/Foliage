#include "Dfs.h"

using namespace System;

void Dfs::dfs(Node^ root, int depth)
{
    if (root != nullptr) {
        int currentDepth = depth;
        this->maxDepth = Math::Max(currentDepth, this->maxDepth);
        root->depth = depth;
        if (root->value == -1 && depth < this->maxDepth) {
            Node^ lnode = gcnew Node(root, -1);
            root->left = lnode;
            root->left->depth = root->parent->depth + 1;
            Node^ rnode = gcnew Node(root, -1);
            root->right = rnode;
            root->right->depth = root->parent->depth + 1;
        }
    }
    if (root!= nullptr && (root->left != nullptr || root->right != nullptr)) {
        ++depth;
        if (root != nullptr && root->left != nullptr) {
            dfs(root->left, depth);
        }
        else if(root != nullptr && root->left == nullptr) {
            Node^ node = gcnew Node(root, -1);
            root->left = node;
            root->left->depth = root->depth + 1;
        }
        if (root != nullptr && root->right != nullptr) {
            dfs(root->right, depth);
        }
        else if (root != nullptr && root->right == nullptr) {
            Node^ node = gcnew Node(root, -1);
            root->right = node;
            root->right->depth = root->depth + 1;
        }
    }
    if (root != nullptr && root->left == nullptr && root->right == nullptr) {
        int currentDepth = depth;
        this->maxDepth = Math::Max(currentDepth, this->maxDepth);
        root->depth = depth;
        if (depth < this->maxDepth) {
            Node^ lnode = gcnew Node(root, -1);
            root->left = lnode;
            root->left->depth = root->parent->depth + 1;
            Node^ rnode = gcnew Node(root, -1);
            root->right = rnode;
            root->right->depth = root->parent->depth + 1;
        }
    }
    return;
}

void Dfs::dfsPostProcessing(Node^ root, int depth)
{
    if (root!=nullptr && root->left == nullptr && root->right == nullptr) {
        if (depth < this->maxDepth) {
            Node^ lnode = gcnew Node(root, -1);
            root->left = lnode;
            Node^ rnode = gcnew Node(root, -1);
            root->right = rnode;
        }
    }
    if (root != nullptr && (root->left != nullptr || root->right != nullptr)) {
        depth++;
        if (root != nullptr && root->left != nullptr) {
            dfsPostProcessing(root->left, depth);
        }
        if (root != nullptr && root->right != nullptr) {
            dfsPostProcessing(root->right, depth);
        }
    }
    return;
}
