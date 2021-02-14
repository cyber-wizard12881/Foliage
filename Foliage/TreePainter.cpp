#include "TreePainter.h"
#include <iostream>

using namespace System::Drawing;

using namespace std;

TreePainter::TreePainter()
{
	this->maxDepth = 0;
	this->root = gcnew Node();
	this->MaxX = Console::WindowWidth - 1;
	this->MaxY = Console::WindowHeight - 1;
	Console::SetWindowSize(this->MaxX, this->MaxY);
}

TreePainter::~TreePainter()
{
	this->maxDepth = 0;
	delete this->root;
	this->MaxX = 0;
	this->MaxY = 0;
	Console::SetWindowSize(this->MaxX, this->MaxY);
}

TreePainter::TreePainter(int maxDepth, Node^ root)
{
	this->maxDepth = maxDepth;
	this->root = root;
	this->MaxX = Console::WindowWidth - 1;
	this->MaxY = Console::WindowHeight - 1;
	Console::SetWindowSize(this->MaxX, this->MaxY);
}

void TreePainter::Paint(double compressionFactor)
{
	int Y = 0;
	List<int>^ prevLocations = gcnew List<int>();
	List<Node^>^ prevNodes = gcnew List<Node^>();
	double deltaY = this->maxDepth;
	for (int depth = 0; depth < this->associativeLocations->Count; depth++) {
		List<Node^>^ nodes = gcnew List<Node^>();
		this->associativeList->TryGetValue(depth, nodes);
		List<int>^ locations = gcnew List<int>();
		this->associativeLocations->TryGetValue(depth, locations);
		if (depth > 0) {
			deltaY = Math::Ceiling((deltaY * 1.0) / compressionFactor);
			Y += deltaY;
		}
		for (int breadth = 0; breadth < nodes->Count; breadth++) {
			if (nodes[breadth]->value != -1) {
				this->Draw(locations[breadth], Y, Convert::ToString(nodes[breadth]->value));
				if (depth > 0) {
					for (int index = 0; index < prevLocations->Count; index++) {
						if (nodes[breadth]->parent == prevNodes[index] && nodes[breadth]->parent->left == nodes[breadth]) {
							this->DrawLine(prevLocations[index], Y - deltaY, locations[breadth], Y - 1, this->branch);
						}
						if (nodes[breadth]->parent == prevNodes[index] && nodes[breadth]->parent->right == nodes[breadth]) {
							this->DrawLine(prevLocations[index], Y - deltaY, locations[breadth], Y - 1, this->branch);
						}
					}
				}
			}
		}
		prevLocations = locations;
		prevNodes = nodes;
	}
}

void TreePainter::Draw(int X, int Y, String^ character)
{
	Console::SetCursorPosition(X, Y);
	Console::Write(character);
}

void TreePainter::DrawXY(int x, int y, int character) {
	Console::SetCursorPosition(x, y);
	Console::Write(wchar_t(character));
}

void TreePainter::DrawLine(int X1, int Y1, int X2, int Y2, int character)
{
	double dx = X2 - X1;
	double dy = Y2 - Y1;
	double m = Math::Abs(dx / dy);

	if (X1 < X2) {
		for (int x = X2 - 1, y = Y2; x > X1; y--) {
			this->DrawXY(x, y, character);
			x = Math::Round(x - m);
		}
	}
	else {
		for (int x = X1 - 1, y = Y1 + 1; x > X2; y++) {
			this->DrawXY(x, y, character);
			x = Math::Round(x - m);
		}
	}
}

void TreePainter::ParseAssociativeList()
{
	Dictionary<int, List<int>^>^ associativeLocations = gcnew Dictionary<int, List<int>^>();
	for (int depth = 0; depth < this->associativeList->Count; depth++) {
		List<Node^>^ nodes = gcnew List<Node^>();
		this->associativeList->TryGetValue(depth, nodes);
		List<int>^ locations = gcnew List<int>();
		if (depth == 0) {
			locations->Add(Convert::ToInt32(Math::Pow(2.0, this->maxDepth + 1)
				/ (Math::Pow(2.0, depth + 1))));
		}
		else {
			List<int>^ locs = gcnew List<int>();
			associativeLocations->TryGetValue(depth - 1, locs);
			for (int loc = 0; loc < locs->Count; loc++) {
				locations->Add((locs[loc] - Convert::ToInt32(Math::Pow(2.0, this->maxDepth + 1))
					/ (Math::Pow(2.0, depth + 1))));
				locations->Add((locs[loc] + Convert::ToInt32(Math::Pow(2.0, this->maxDepth + 1))
					/ (Math::Pow(2.0, depth + 1))));
			}
		}
		associativeLocations->Add(depth, locations);
	}
	this->associativeLocations = associativeLocations;
}

void TreePainter::StretchAssociativeLocations(double boostingFactor)
{
	for (int index = 0; index < this->associativeLocations->Count; index++) {
		List<int>^ locations = gcnew List<int>();
		this->associativeLocations->TryGetValue(index, locations);
		for (int idx = 0; idx < locations->Count; idx++) {
			locations[idx] = Math::Round(locations[idx] * boostingFactor);
		}
	}
}


