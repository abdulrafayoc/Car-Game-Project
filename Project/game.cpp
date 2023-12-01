#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

#include "Graph.h"

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

using namespace std;

void dijkstra(Graph& maze, Car& ai) {
	
}

void play(Graph& maze, Car& player) {
	while (1)
	{
		cout << "\033[42m";
		cout << "\n	Use arrow keys to move the car";
		cout << "\n	Press `esc` to Quit";

		cout << endl << endl << endl;

		printGrid(maze);
		int c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			player.moveUp(maze);


			break;
		case KEY_DOWN:
			player.moveDown(maze);


			break;
		case KEY_LEFT:
			player.moveLeft(maze);


			break;
		case KEY_RIGHT:
			player.moveRight(maze);

			break;
		case 27:
			exit(0);

			break;
		default:



			break;

		}
		system("cls");

	}
}


int main() {
	int gridSize = 10;

	Graph maze(gridSize);

	//maze.printVertices();


	maze.adjacencyList[0][0].car = true;
	maze.adjacencyList[gridSize - 1][gridSize - 1].finish = true;

	Car player;
	Car AI;


	// menu
	cout << "1. Play" << endl;
	cout << "2. AI" << endl;

	cout << "Enter your choice: ";
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		play(maze, player);
		break;
	case 2:
		dijkstra(maze, player);
	default:
		break;
	}





	return 0;
}
