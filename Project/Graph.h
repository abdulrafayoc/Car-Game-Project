#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "LinkedList.h"

using namespace std;

// Graph class for representing the maze
class Graph {
public:
	int gridSize;
	LinkedList** adjacencyList;

	Graph(int size) : gridSize(size) {
		adjacencyList = new LinkedList * [size];
		for (int i = 0; i < gridSize; i++) {
			adjacencyList[i] = new LinkedList[size];
		}

		buildMaze();
	}

	~Graph() {
		delete[] adjacencyList;
	}

	void addEdge(int x1, int y1, int x2, int y2) {
		if (x1 < 0 || x1 >= gridSize || y1 < 0 || y1 >= gridSize || x2 < 0 || x2 >= gridSize || y2 < 0 || y2 >= gridSize) {
			return;
		}
		adjacencyList[x1][y1].addNode(x2, y2);
		adjacencyList[x2][y2].addNode(x1, y1);
	}

	bool ifRightExists(int x, int y) {
		if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
			return false;
		}

		Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->x == x + 1 && temp->y == y) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	bool ifDownExists(int x, int y) {
		if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
			return false;
		}

		Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->x == x  && temp->y == y + 1) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void printVertices() {
		// Print the vertexes
		for (int i = 0; i < gridSize; ++i) {
			for (int j = 0; j < gridSize; ++j) {
				cout << "(" << i << ", " << j << ") : " << adjacencyList[i][j] << endl;
			}
			cout << endl;
		}
	}

	void printGrid() {
		for (int j = 0; j < gridSize; ++j) {
			for (int i = 0; i < gridSize; ++i) {
				//cout << "(" << i << "," << j << ")";
				cout << "0";
				if (ifRightExists(i, j)) {
					cout << " -- ";
				}
				else {
					cout << "    ";
				}
			}
			cout << endl;

			for (int i = 0; i < gridSize; ++i) {
				if (ifDownExists(i, j)) {
					cout << "|    ";
				}
				else {
					cout << "     ";
				}
			}

			cout << endl;
		}
	}

	void buildMaze() {
		// Implement logic to generate random maze with roads, obstacles, and power-ups
		// You can use srand() and rand() functions to generate random elements in the maze
		// Populate the adjacency list based on the generated maze
		srand(static_cast<unsigned int>(time(nullptr)));

		for (int j = 0; j < gridSize; j++)
			for (int i = 0; i < gridSize; ++i) {
				{
					// Seed for the random number generator
					//srand(static_cast<unsigned int>(time(nullptr)));
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> distribution(0, 3);

					// Generate a random number between 0 and 3
					// probability of getting a conecting two adjecent vertieces (x +- 1 and y +- 1) should be 3/4
					// use <random> library

					int random;

					//addEdge(i, j, i + 1, j);


					random = distribution(gen);
					if (random == 0 || random == 1) {
						addEdge(i, j, i + 1, j);
					}

					random = distribution(gen);
					if (random == 0 || random == 1) {
						addEdge(i, j, i - 1, j);
					}

					random = distribution(gen);
					if (random == 0 || random == 1) {
						addEdge(i, j, i, j + 1);
					}

					random = distribution(gen);
					if (random == 0 || random == 1) {
						addEdge(i, j, i, j - 1);
					}


				}
			}
	}
};