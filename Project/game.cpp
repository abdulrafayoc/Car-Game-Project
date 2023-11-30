#include <iostream>
#include "Graph.h"


using namespace std;


void printVertices(Graph& maze) {
	// Print the vertexes
	for (int i = 0; i < maze.gridSize; ++i) {
		for (int j = 0; j < maze.gridSize; ++j) {
			cout << "(" << i << ", " << j << ") : " << maze.adjacencyList[i][j] << endl;
		}
		cout << endl;
	}
}

void printGrid(Graph& maze) {

    // Print horizontal lines
    for (int i = 0; i < maze.gridSize; ++i) {
        for (int j = 0; j < maze.gridSize; ++j) {
			cout << "+";
			
			if (maze.ifRightExists(i, j)) {
				cout << " -- ";
			} else {
				cout << "    ";
			}
		}
		cout << endl;

		// Print vertical lines
		for (int j = 0; j < maze.gridSize; ++j) {
			if (maze.ifDownExists(i, j)) {
				cout << "|    ";
			} else {
				cout << "     ";
			}
		}
		cout << endl;
	}

}

int main() {
    // Set the size of the maze grid
    int gridSize = 5;

    // Create a maze graph
    Graph maze(gridSize);

	printVertices(maze);
    // Print the grid with lines representing adjacency
    printGrid(maze);

    return 0;
}
