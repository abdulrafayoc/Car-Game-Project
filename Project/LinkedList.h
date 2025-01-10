#pragma once

#include <iostream>

using namespace std;

// Node class for representing vertices in the graph


// LinkedList class for representing adjacency lists
class LinkedList {
public:

	int x;
	int y;

	int numNeb;

	bool car;
	bool finish;
	bool obstacle;
	bool powerup;

	int weight;

	class Node {
	public:
		LinkedList* vertex;
		int weight;
		Node* next;

		Node(LinkedList* v, int w) : vertex(v), weight(w), next(nullptr) {}

		void addWeight(int w, LinkedList* thiss) {
			thiss->weight = w;
			LinkedList::Node* temp = vertex->head;
			while (temp != nullptr) {
				// compare the address of this LinkedList object pointed by temp
				if (temp->vertex == thiss) {
					temp->weight = w;
					//cout << *vertex << endl;
					//cout << temp->weight << endl;
					return;
				}
				temp = temp->next;
			}
					cout << "Vertex not found in the linked list." << endl;
		}
	};

	Node* head;



	LinkedList() : head(nullptr) {
		car = false;
		finish = false;
		obstacle = false;
		powerup = false;
		numNeb = 0;
	}

	LinkedList(int xx, int yy) : head(nullptr), x(xx), y(yy) {
		car = false;
		finish = false;
		obstacle = false;
		powerup = false;
		numNeb = 0;
	}

	// << operator overloading
	friend ostream& operator<<(ostream& os, const LinkedList& list) {
		Node* temp = list.head;
		while (temp != nullptr) {
			os << "(" << temp->vertex->x << " " << temp->vertex->y << " " << temp->weight << ")";
			temp = temp->next;
		}
		return os;
	}

	void addNeighbor(LinkedList* v, int w) {
		// if the node already exists
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->vertex == v) {
				return;
			}
			temp = temp->next;
		}

		// if the node does not exist
		Node* newNode = new Node(v, w);
		newNode->next = head;
		head = newNode;
		numNeb++;


	}



	// [] operator overloading
	Node* operator[](int index) {
		if (index < 0 || index >= numNeb) {
			return nullptr;
		}
		Node* temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp;
	}
};


class Queue {
public:
	int* x;
	int* y;
	int front;
	int rear;
	int size;

	Queue(int s = 10000) : size(s), front(-1), rear(-1) {
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

	PriorityQueue(int s = 10000) : size(s), front(-1), rear(-1) {
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

