#pragma once
#include "../QUEUE/Queue.hpp"


class DQS {

public:
	int top;
	int MAX;
	Queue *main_queue, *temp_queue;

	DQS();

	DQS(int MAX);

	~DQS();

	void init_stack();

	void clear_stack();

	int push(int k);

	int pop();

	int pop_swap_version();

	int getSize();

	void print_stack();


};

void Main_DQS();
