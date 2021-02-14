#pragma once
#include "Node.h"
using namespace System;
using namespace System::Collections::Generic;

#define TreeDepth 10

public ref class TreePainter {
public:
	int maxDepth;
	Node^ root;
	String^ leaf = "~";
	int branch = 46;
	int leftBranch = 47;
	int rightBranch = 92;
	int OriginalX;
	int OriginalY;
	int MaxX;
	int MaxY;
	Dictionary<int, List<Node^>^>^ associativeList;
	Dictionary<int, List<int>^>^ associativeLocations;
	TreePainter();
	~TreePainter();
	TreePainter(int maxDepth, Node^ root);
	void Paint(double compressionFactor);
	void Draw(int X, int Y, String^ character);
	void DrawLine(int X1, int Y1, int X2, int Y2, int character);
	void ParseAssociativeList();
	void StretchAssociativeLocations(double boostingFactor);
	void DrawXY(int x, int y, int character);
};