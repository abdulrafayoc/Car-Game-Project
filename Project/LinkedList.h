#pragma once

#include <iostream>

using namespace std;

// Node class for representing vertices in the graph
class Node {
public:
	int x;
	int y;
	/*bool car;
	bool finish;
	bool obstacle;
	bool powerup;*/
	Node* next;

	Node(int xx, int yy) : x(xx), y(yy), next(nullptr) { 
		//car = false;
		//finish = false;
		//obstacle = false;
		//powerup = false;
	}
};

// LinkedList class for representing adjacency lists
class LinkedList {
public:
	Node* head;
	bool car;
	bool finish;

	LinkedList() : head(nullptr) { 
		car = false;
	}

	void addNode(int x, int y) {
		// if the node already exists
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->x == x && temp->y == y) {
				return;
			}
			temp = temp->next;
		}

		Node* newNode = new Node(x, y);
		newNode->next = head;
		head = newNode;
	}


	friend ostream& operator<<(ostream& os, const LinkedList& ll) {
		Node* temp = ll.head;
		while (temp != nullptr) {
			os << "(" << temp->x << ", " << temp->y << ") ";
			temp = temp->next;
		}
		return os;
	}

};


class Queue {
	public:
	int* x;
	int* y;
	int front;
	int rear;
	int size;

	Queue(int s = 100) : size(s), front(-1), rear(-1) {
		x = new int[size];
		y = new int[size];
	}

	~Queue() {
		delete[] x;
		delete[] y;
	}

	void push(int xx, int yy) {
		if (front == -1) {
			front = 0;
		}
		rear++;
		x[rear] = xx;
		y[rear] = yy;
	}

	void pop() {
		if (front == -1 || front > rear) {
			return;
		}
		front++;
	}

	int frontX() {
		return x[front];
	}

	int frontY() {
		return y[front];
	}

	bool isEmpty() {
		return front == -1 || front > rear;
	}
};
