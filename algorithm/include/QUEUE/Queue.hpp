#pragma once


class Queue {

public:

	int *queue;

	int MAX;
	int front;
	int rear;

	Queue();

	Queue(int MAX);

	virtual ~Queue();

	void init_queue();

	void clear_queue();

	int put(int k);

	int get();

	void print_queue();

};
