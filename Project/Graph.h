#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "LinkedList.h"

using namespace std;


//Name            FG  BG
//Black           30  40
//Red             31  41
//Green           32  42
//Yellow          33  43
//Blue            34  44
//Magenta         35  45
//Cyan            36  46
//White           37  47
//Bright Black    90  100
//Bright Red      91  101
//Bright Green    92  102
//Bright Yellow   93  103
//Bright Blue     94  104
//Bright Magenta  95  105
//Bright Cyan     96  106
//Bright White    97  107

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
			if (temp->x == x && temp->y == y + 1) {
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

		// alwats have a path from (0,0) to (gridSize - 1, gridSize - 1)
		addEdge(0, 0, 0, 1);
		addEdge(0, 1, 0, 0);

		addEdge(0, 0, 1, 0);
		addEdge(1, 0, 0, 0);

		addEdge(gridSize - 1, gridSize - 1, gridSize - 1, gridSize - 2);
		addEdge(gridSize - 1, gridSize - 2, gridSize - 1, gridSize - 1);

		addEdge(gridSize - 1, gridSize - 1, gridSize - 2, gridSize - 1);
		addEdge(gridSize - 2, gridSize - 1, gridSize - 1, gridSize - 1);



	}
};

void printGrid(Graph& maze) {
	for (int j = 0; j < maze.gridSize; ++j) {
		cout << "    ";
		for (int i = 0; i < maze.gridSize; ++i) {
			//cout << "(" << i << "," << j << ")";
			if (maze.adjacencyList[i][j].car == true)
			{
				cout << "\033[40m";
				cout << "\033[94m";
				cout << "#";
				cout << "\033[42m";
				cout << "\033[37m";
			}
			else if (maze.adjacencyList[i][j].finish == true)
			{
				cout << "\033[33m";
				cout << "\033[40m";
				cout << "*";
				cout << "\033[42m";
				cout << "\033[37m";
			}
			else {
				cout << "\033[40m";
				cout << " ";
				cout << "\033[42m";
			}
			if (maze.ifRightExists(i, j)) {
				cout << "\033[40m";
				cout << "    ";
				cout << "\033[42m";
			}
			else {
				cout << "    ";
			}
		}
		cout << endl;
		cout << "    ";
		for (int i = 0; i < maze.gridSize; ++i) {
			if (maze.ifDownExists(i, j)) {
				cout << "\033[40m";
				cout << " ";
				cout << "\033[42m";
				cout << "    ";
			}
			else {
				cout << "     ";
			}
		}

		cout << endl;
	}
}

class Car {
public:
	int x;
	int y;
	int score;

	Car() : x(0), y(0), score(0) {}
	Car(int x, int y) : x(x), y(y), score(0) {}


	bool checkWin(Graph& maze) {
		if (maze.adjacencyList[x][y].finish == true) {
			return true;
		}
		return false;
	}

	void showWin(Graph & maze) {
		if (checkWin(maze)) {
			cout << "You win!" << endl;
			exit(0);
		}
	}

	void moveRight(Graph& maze) {
		if (maze.ifRightExists(x, y)) {
			maze.adjacencyList[x][y].car = false;
			x++;
			maze.adjacencyList[x][y].car = true;
		}
		else {

		}
		showWin(maze);
	}

	void moveLeft(Graph& maze) {
		if (maze.ifRightExists(x - 1, y)) {
			maze.adjacencyList[x][y].car = false;
			x--;
			maze.adjacencyList[x][y].car = true;
		}
		else {

		}
		showWin(maze);
	}

	void moveUp(Graph& maze) {
		if (maze.ifDownExists(x, y - 1)) {
			maze.adjacencyList[x][y].car = false;
			y--;
			maze.adjacencyList[x][y].car = true;
		}
		else {

		}
		showWin(maze);
	}

	void moveDown(Graph& maze) {
		if (maze.ifDownExists(x, y)) {
			maze.adjacencyList[x][y].car = false;
			y++;
			maze.adjacencyList[x][y].car = true;

		}
		else {

		}
		showWin(maze);
	}

	void printPlayer() {
		cout << "Player: (" << x << ", " << y << ")" << endl;
	}
};