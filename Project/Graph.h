#include <iostream>
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

		//update cordinates for each node
		for (int j = 0; j < gridSize; j++) {
			for (int i = 0; i < gridSize; ++i) {
				adjacencyList[i][j].x = i;
				adjacencyList[i][j].y = j;
			}
		}

		cout << "Building maze..." << endl;
		buildMaze();
		cout << "Maze built!" << endl;
	}

	~Graph() {
		delete[] adjacencyList;
	}



	void addEdge(int x1, int y1, int x2, int y2) {
		if (x1 < 0 || x1 >= gridSize || y1 < 0 || y1 >= gridSize || x2 < 0 || x2 >= gridSize || y2 < 0 || y2 >= gridSize) {
			return;
		}
		adjacencyList[x1][y1].addNeighbor(&adjacencyList[x2][y2], 5);
		adjacencyList[x2][y2].addNeighbor(&adjacencyList[x1][y1], 5);
	}

	bool ifRightExists(int x, int y) {
		if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
			return false;
		}


		LinkedList::Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->vertex == &adjacencyList[x + 1][y]) {
				//cout << temp->vertex << " == " << &adjacencyList[x + 1][y] << endl;
				//cout << "x: " << x << " y: " << y << ": " << adjacencyList[x + 1][y] << ", ";

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

		LinkedList::Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->vertex == &adjacencyList[x - 1][y]) {
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

		LinkedList::Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->vertex == &adjacencyList[x][y - 1]) {
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

		LinkedList::Node* temp = adjacencyList[x][y].head;
		while (temp != nullptr) {
			if (temp->vertex == &adjacencyList[x][y + 1]) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}



	void buildMaze() {
		srand(static_cast<unsigned int>(time(nullptr)));
		int random;
		int random2;

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distribution(0, 4);


		// populate the maze with random edges
		for (int j = 0; j < gridSize; j++) {

			for (int i = 0; i < gridSize; ++i) {

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


			}

		}


		for (int j = 0; j < gridSize; j++) {

			for (int i = 0; i < gridSize; ++i) {

				// populate random powerups and obstacles
				random = distribution(gen);
				random2 = distribution(gen);

				if (random == 1 && (random2 == 1 || random2 == 0)) {
					adjacencyList[i][j].powerup = true;

					LinkedList::Node* temp = adjacencyList[i][j].head;
					while (temp != nullptr) {
						random = distribution(gen);
						cout << random << "asdfsadf" << endl;
						if (random == 0) {
							temp->addWeight(1, &adjacencyList[i][j]);

						}
						else if (random == 1) {
							temp->addWeight(2, &adjacencyList[i][j]);
						}
						else if (random == 2) {
							temp->addWeight(3, &adjacencyList[i][j]);
						}
						else if (random == 3) {
							temp->addWeight(3, &adjacencyList[i][j]);
						}
						else if (random == 4) {
							temp->addWeight(4, &adjacencyList[i][j]);
						}
						temp = temp->next;
					}

				}
				else if (random == 2 && (random2 == 1 || random2 == 3)) {
					adjacencyList[i][j].obstacle = true;

					LinkedList::Node* temp = adjacencyList[i][j].head;
					while (temp != nullptr) {
						random = distribution(gen);
						cout << random << "/////////" << endl;
						if (random == 0) {
							temp->addWeight(9, &adjacencyList[i][j]);
						}
						else if (random == 1) {
							temp->addWeight(8, &adjacencyList[i][j]);
						}
						else if (random == 2) {
							temp->addWeight(7, &adjacencyList[i][j]);
						}
						else if (random == 3) {
							temp->addWeight(7, &adjacencyList[i][j]);
						}
						else if (random == 4) {
							temp->addWeight(6, &adjacencyList[i][j]);
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
	//bool timer

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
			LinkedList::Node* temp = maze.adjacencyList[x][y].head;
			while (temp != nullptr) {

				score += 9 - temp->weight;

				temp = temp->next;
			}
			maze.adjacencyList[x][y].powerup = false;
		}
		else if (maze.adjacencyList[x][y].obstacle == true) {
			LinkedList::Node* temp = maze.adjacencyList[x][y].head;
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
			cout << "You can't move right" << endl;

		}
		showWin(maze);
	}

	void moveLeft(Graph& maze) {
		if (maze.ifLeftExists(x, y)) {
			maze.adjacencyList[x][y].car = false;
			x--;
			maze.adjacencyList[x][y].car = true;
			updateScore(maze);
		}
		else {
			cout << "You can't move left" << endl;

		}
		showWin(maze);
	}

	void moveUp(Graph& maze) {
		if (maze.ifUpExists(x, y)) {
			maze.adjacencyList[x][y].car = false;
			y--;
			maze.adjacencyList[x][y].car = true;
			updateScore(maze);

		}
		else {
			cout << "You can't move up" << endl;
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
			cout << "You can't move down" << endl;

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


