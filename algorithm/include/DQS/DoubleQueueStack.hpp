#pragma once
#include <iostream>

#define MAX 10

namespace DoubleQueueStack {

class Queue {

public:

	int queue[MAX];
	int front;
	int rear;

	Queue();
	virtual ~Queue();

	void init_queue();

	void clear_queue();

	int put(int k);

	int get();

	void print_queue();

};

class DQS {

public:
	int top;
	Queue main_queue, temp_queue;

	DQS();
	virtual ~DQS();

	void init_stack();

	void clear_stack();

	int push(int k);

	int pop();

	void print_stack();
};

void Main_DQS();

}