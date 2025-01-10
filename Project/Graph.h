#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

#include "LinkedList.h"

using namespace std;
using namespace chrono;


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

auto startTimer() {
	return high_resolution_clock::now();
}

int stopTimer(const decltype(high_resolution_clock::now())& start_time) {
	auto stop_time = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop_time - start_time);
	cout << "Time elapsed: " << duration.count() << " seconds" << endl;
	return duration.count();
}

class Player {
public:
	string name;
	int score;

	Player()
	{
		name = "";
		score = 0;
	}

	// Constructor to initialize name and score
	Player(const string& playerName, int playerScore) : name(playerName), score(playerScore) {}

	bool operator<(const Player& p) const {
		return (score < score);
	}

	// Add more comparison operators as needed

	// Example: Overloading greater than operator (>)
	bool operator>(const Player& p) const {
		return (score > p.score);
	}
};

class MaxHeap {
private:
	Player* heapArray;
	int capacity;
	int size;

	int parent(int i) { return (i - 1) / 2; }
	int leftChild(int i) { return 2 * i + 1; }
	int rightChild(int i) { return 2 * i + 2; }

	void heapifyUp(int index) {
		while (index > 0 && heapArray[parent(index)].score < heapArray[index].score) {
			swap(heapArray[parent(index)], heapArray[index]);
			index = parent(index);
		}
	}

	void heapifyDown(int index) {
		int maxIndex = index;
		int left = leftChild(index);
		int right = rightChild(index);

		if (left < size && heapArray[left].score > heapArray[maxIndex].score) {
			maxIndex = left;
		}

		if (right < size && heapArray[right].score > heapArray[maxIndex].score) {
			maxIndex = right;
		}

		if (index != maxIndex) {
			swap(heapArray[index], heapArray[maxIndex]);
			heapifyDown(maxIndex);
		}
	}

public:
	MaxHeap(int capacity) : capacity(capacity), size(0) {
		heapArray = new Player[capacity];
	}

	~MaxHeap() {
		delete[] heapArray;
	}

	void insert(const Player& player) {
		if (size == capacity) {
			cout << "Heap is full, cannot insert more elements." << endl;
			return;
		}

		size++;
		int index = size - 1;
		heapArray[index] = player;
		heapifyUp(index);
	}

	Player extractMax() {
		if (size <= 0) {
			cout << "Heap is empty." << endl;
			return Player("", 0); // Return a default player if the heap is empty
		}

		if (size == 1) {
			size--;
			return heapArray[0];
		}

		Player root = heapArray[0];
		heapArray[0] = heapArray[size - 1];
		size--;
		heapifyDown(0);

		return root;
	}

	void display() {
		for (int i = 0; i < size; ++i) {
			cout << "Player: " << heapArray[i].name << ", Score: " << heapArray[i].score << endl;
		}
	}
};

void readDataFromFile() {
	ifstream inputFile("scores.txt");

	if (!inputFile.is_open()) {
		cout << "Error opening the file." << endl;
		return;
	}

	int numPlayers = 0;
	string line;
	while (getline(inputFile, line)) {
		++numPlayers;
	}
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	Player* players = new Player[numPlayers];

	for (int i = 0; i < numPlayers; ++i) {
		getline(inputFile, line, ',');
		players[i].name = line;

		inputFile >> players[i].score;
		inputFile.ignore();

	}

	inputFile.close();

	MaxHeap h(numPlayers);
	for (int i = 0; i < numPlayers; i++)
	{
		h.insert(players[i]);
	}

	Player highscorer = h.extractMax();
	cout << "Name: " << highscorer.name << endl << "Score: " << highscorer.score;
}

void ViewScoreBoard()
{
	ifstream inputFile("scores.txt");

	if (!inputFile.is_open()) {
		cout << "Error opening the file." << endl;
		return;
	}

	int numPlayers = 0;
	string line;
	while (getline(inputFile, line)) {
		++numPlayers;
	}
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	Player* players = new Player[numPlayers];

	for (int i = 0; i < numPlayers; ++i) {
		getline(inputFile, line, ',');
		players[i].name = line;

		inputFile >> players[i].score;
		inputFile.ignore();
	}
	cout << "Player\tScore\n";
	for (int i = 0; i < numPlayers; i++)
	{
		cout << players[i].name << "\t" << players[i].score << endl;
	}
}


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

				if ((random == 1 || random == 0) && (random2 == 1 || random2 == 0 || random2 == 2)) {
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
				else if ((random == 3 || random == 2) && (random2 == 1 || random2 == 3)) {
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
				if (maze.adjacencyList[i][j].weight == 9)
				{

				cout << "\033[40m";
				cout << "\033[31m";
				cout << "X";
				cout << "\033[42m";
				cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 9)
				{

					cout << "\033[40m";
					cout << "\033[31m";
					cout << "X";
					cout << "\033[42m";
					cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 8)
				{
					cout << "\033[40m";
					cout << "\033[31m";
					cout << "%";
					cout << "\033[42m";
					cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 7)
				{
					cout << "\033[40m";
					cout << "\033[31m";
					cout << "%";
					cout << "\033[42m";
					cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 6)
				{
					cout << "\033[40m";
					cout << "\033[31m";
					cout << "x";
					cout << "\033[42m";
					cout << "\033[37m";
				}
			}
			else if (maze.adjacencyList[i][j].powerup == true)
			{
				if (maze.adjacencyList[i][j].weight == 1)
				{
					cout << "\033[40m";
					cout << "\033[32m";
					cout << "+";
					cout << "\033[42m";
					cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 2)
				{
					cout << "\033[40m";
					cout << "\033[32m";
					cout << "0";
					cout << "\033[42m";
					cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 3)
				{
					cout << "\033[40m";
					cout << "\033[32m";
					cout << "o";
					cout << "\033[42m";
					cout << "\033[37m";
				}
				else if (maze.adjacencyList[i][j].weight == 4)
				{
					cout << "\033[40m";
					cout << "\033[32m";
					cout << ">";
					cout << "\033[42m";
					cout << "\033[37m";
				}
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

	bool SearchName(const string& name, fstream& inputFile) {
		string line;
		while (getline(inputFile, line)) {
			size_t commaPos = line.find(',');
			if (commaPos != string::npos) {
				string nameInFile = line.substr(0, commaPos);
				if (nameInFile == name) {
					return true;  // Name found
				}
			}
		}
		return false;  // Name not found
	}

	void RecordScore()
	{
		//cout << "Enetered the record scores func";
		fstream inputFile("scores.txt");
		if (!inputFile.is_open()) {
			cout << "Error opening the file" << endl;
		}

		inputFile.close();
		ofstream outputFile("scores.txt", ios::app);
		outputFile << name << "," << score << endl;
		outputFile.close();
	}

	bool checkWin(Graph& maze) {
		if (maze.adjacencyList[x][y].finish == true) {
			return true;
		}
		return false;
	}

	void showWin(Graph& maze) {
		if (checkWin(maze)) {
			RecordScore();
			cout << "You win!" << endl;
			cout << "\n\n\nHighScorer:\n";
			readDataFromFile();
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

