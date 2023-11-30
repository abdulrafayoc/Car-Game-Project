#include <iostream>
#include "Graph.h"


using namespace std;

int main() {
	int gridSize = 6;

	Graph maze(gridSize);

	maze.printVertices();
	maze.printGrid();

	return 0;
}
