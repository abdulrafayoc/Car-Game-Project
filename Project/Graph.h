#include <iostream>
#include <random>

#include "LinkedList.h"

using namespace std;


// Name            FG  BG
// Black           30  40
// Red             31  41
// Green           32  42
// Yellow          33  43
// Blue            34  44
// Magenta         35  45
// Cyan            36  46
// White           37  47
// Bright Black    90  100
// Bright Red      91  101
// Bright Green    92  102
// Bright Yellow   93  103
// Bright Blue     94  104
// Bright Magenta  95  105
// Bright Cyan     96  106
// Bright White    97  107

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

	bool ifLeftExists(int x, int y) {
		if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
			return false;
		}

		Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->x == x - 1 && temp->y == y) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	bool ifUpExists(int x, int y) {
		if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
			return false;
		}

		Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->x == x && temp->y == y - 1) {
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
		srand(static_cast<unsigned int>(time(nullptr)));

		for (int j = 0; j < gridSize; j++) {

			for (int i = 0; i < gridSize; ++i) {

				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<int> distribution(0, 4);


				int random;
				int random2;

				// populate random edges
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



				// populate random powerups and obstacles
				random = distribution(gen);
				random2 = distribution(gen);
				if (random == 1 && (random2 == 1 || random2 == 0)) {
					adjacencyList[i][j].powerup = true;

					Node* temp = adjacencyList[i][j].head;
					while (temp != nullptr) {
						random = distribution(gen);
						if (random == 0) {
							temp->weight = 1;
						}
						else if (random == 1) {
							temp->weight = 2;
						}
						else if (random == 2) {
							temp->weight = 3;
						}
						else if (random == 3) {
							temp->weight = 4;
						}
						temp = temp->next;
					}

				}
				random = distribution(gen);
				random2 = distribution(gen);
				if (random == 1 && (random2 == 1 || random2 == 0)) {
					adjacencyList[i][j].obstacle = true;

					Node* temp = adjacencyList[i][j].head;
					while (temp != nullptr) {
						random = distribution(gen);
						if (random == 0) {
							temp->weight = 9;
						}
						else if (random == 1) {
							temp->weight = 8;
						}
						else if (random == 2) {
							temp->weight = 7;
						}
						else if (random == 3) {
							temp->weight = 6;
						}

						temp = temp->next;
					}
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


		// update all the weights of the edges that are not powerups or obstacles but are adjacent to powerups or obstacles
		for (int j = 0; j < gridSize; j++) {

			for (int i = 0; i < gridSize; ++i) {

				if (adjacencyList[i][j].powerup == false && adjacencyList[i][j].obstacle == false) {
					// yeh woh node hai jis ky adjacent nodes powerups ya obstacles nai hain
					Node* temp = adjacencyList[i][j].head;
					while (temp != nullptr) {
						// yeh un nodes ky adjacent nodes hain jin ky adjacent nodes powerups ya obstacles hain
						if (adjacencyList[temp->x][temp->y].powerup == true) {
							Node* temp2 = adjacencyList[temp->x][temp->y].head;
							while (temp2 != nullptr) {
								if (temp2->x == i && temp2->y == j) {
									temp2->weight = temp->weight;
									break;
								}
								temp2 = temp2->next;
							}
						}
						else if (adjacencyList[temp->x][temp->y].obstacle == true) {
							Node* temp2 = adjacencyList[temp->x][temp->y].head;
							while (temp2 != nullptr) {
								if (temp2->x == i && temp2->y == j) {
									temp2->weight = temp->weight;
									break;
								}
								temp2 = temp2->next;
							}
						}
						temp = temp->next;
					}
				}
			}
		}



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
			else if (maze.adjacencyList[i][j].obstacle == true)
			{
				cout << "\033[40m";
				cout << "\033[31m";
				cout << "x";
				cout << "\033[42m";
				cout << "\033[37m";
			}
			else if (maze.adjacencyList[i][j].powerup == true)
			{
				cout << "\033[40m";
				cout << "\033[32m";
				cout << "+";
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
	string name;
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

	void showWin(Graph& maze) {
		if (checkWin(maze)) {
			cout << "You win!" << endl;
			exit(0);
		}
	}

	void updateScore(const Graph& maze) {
		if (maze.adjacencyList[x][y].powerup == true) {
			Node* temp = maze.adjacencyList[x][y].head;
			while (temp != nullptr) {
				score += 9 - temp->weight;
				temp = temp->next;
			}
			maze.adjacencyList[x][y].powerup = false;
		}
		else if (maze.adjacencyList[x][y].obstacle == true) {
			Node* temp = maze.adjacencyList[x][y].head;
			while (temp != nullptr) {
				score += temp->weight * -1;
				temp = temp->next;
			}
			maze.adjacencyList[x][y].obstacle = false;
		}
		else {

		}


	}

	void moveRight(Graph& maze) {
		if (maze.ifRightExists(x, y)) {
			maze.adjacencyList[x][y].car = false;
			x++;
			maze.adjacencyList[x][y].car = true;
			updateScore(maze);
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
			updateScore(maze);
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
			updateScore(maze);

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
			updateScore(maze);

		}
		else {

		}
		showWin(maze);
	}

	void cordinates(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void printPlayer() {
		cout << "Player: (" << x << ", " << y << ")" << endl;
	}
};


