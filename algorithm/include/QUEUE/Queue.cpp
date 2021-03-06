#include "Queue.hpp"
#include <iostream>


Queue::Queue() {
	Queue(10);
}

Queue::Queue(int MAX) {
	this->MAX = MAX;
	this->queue = new int[MAX];
}

Queue:: ~Queue() {
	delete queue;
}

void Queue::init_queue() {
	front = rear = 0; // 비어있는 큐를 표현
}

void Queue::clear_queue() {
	front = rear;
}

int Queue::put(int k) {
	if ((rear + 1) % MAX == front) {
		std::cout << "queue overflow" << std::endl;
		return -1;
	}
	queue[rear] = k;
	rear = ++rear % MAX;
	return k;
}

int Queue::get() {
	if (front == rear) {
		std::cout << "queue underflow" << std::endl;
		return -1;
	}
	int result = queue[front];
	front = ++front % MAX;
	return result;
}


int Queue::getSize() {
	if (front == rear) {
		return 0; // 비어 있는 큐
	}
	if (rear - front > 0) {
		return rear - front;
	}

	// rear < front인 경우
	return rear + MAX - front;
	
}
void Queue::print_queue() {
	int i = 0;
	std::cout << "queue contents : front --> rear" << std::endl;
	for (int i = front; i != rear; i = (++i) % MAX) {
		std::cout << queue[i] << " ";
	}
	std::cout << std::endl;
}
