#pragma once
#include <iostream>

namespace DoubleQueueStack2 {


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

		void print_stack();


	};

	void Main_DQS2();

}