#pragma once

#include <iostream>

using namespace std;

// Node class for representing vertices in the graph
class Node {
public:
	int x;
	int y;
	int weight;
	Node* next;

	Node(int xx, int yy) : x(xx), y(yy), next(nullptr) {
		weight = 5;

	}
};

// LinkedList class for representing adjacency lists
class LinkedList {
public:
	Node* head;

	int size;

	bool car;
	bool finish;
	bool obstacle;
	bool powerup;


	LinkedList() : head(nullptr) {
		car = false;
		finish = false;
		obstacle = false;
		powerup = false;
		size = 0;
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
		size++;
	}

	// [] operator overloading
	Node* operator[](int index) {
		if (index < 0 || index >= size) {
			return nullptr;
		}
		Node* temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp;
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


class Stack {
private:
	class Node {
	public:
		int x;
		int y;
		Node* next;

		Node(int xx, int yy) : x(xx), y(yy), next(nullptr) {}
	};
	Node* top;

public:
	Stack() : top(nullptr) {}

	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}

	void push(int xx, int yy) {
		Node* newNode = new Node(xx, yy);
		newNode->next = top;
		top = newNode;
	}

	void pop() {
		if (isEmpty()) {
			return;
		}
		Node* temp = top;
		top = top->next;
		delete temp;
	}

	int topX() {
		if (isEmpty()) {
			return -1;
		}
		return top->x;
	}

	int topY() {
		if (isEmpty()) {
			return -1;
		}
		return top->y;
	}

	bool isEmpty() {
		return top == nullptr;
	}
};

class PriorityQueue {

public:
	int* x;
	int* y;
	int* distance;
	int front;
	int rear;
	int size;

	PriorityQueue(int s = 100) : size(s), front(-1), rear(-1) {
		x = new int[size];
		y = new int[size];
		distance = new int[size];
	}

	~PriorityQueue() {
		delete[] x;
		delete[] y;
		delete[] distance;
	}

	void enqueue(int xx, int yy, int dist) {
		if (front == -1) {
			front = 0;
		}
		int i;
		for (i = rear; i >= front && distance[i] > dist; i--) {
			x[i + 1] = x[i];
			y[i + 1] = y[i];
			distance[i + 1] = distance[i];
		}
		x[i + 1] = xx;
		y[i + 1] = yy;
		distance[i + 1] = dist;
		rear++;
	}

	void dequeue() {
		if (front == -1 || front > rear) {
			return;
		}
		front++;
	}

	int frontX() {
		if (front == -1 || front > rear) {
			return -1;
		}
		return x[front];
	}

	int frontY() {
		if (front == -1 || front > rear) {
			return -1;
		}
		return y[front];
	}

	int frontD() {
		return distance[front];
	}

	bool isEmpty() {
		return front == -1 || front > rear;
	}
};