#include <iostream>
#include "DoubleQueueStack2.hpp"


DQS::DQS() {
	DQS(10);
}

DQS::DQS(int MAX) {
	main_queue = new Queue(MAX);
	temp_queue = new Queue(MAX);
}

DQS::~DQS() {
	delete main_queue;
	delete temp_queue;
}


void DQS::init_stack() {
	top = -1;
	main_queue->init_queue();
	temp_queue->init_queue();
}

void DQS::clear_stack() {
	top = -1;
	main_queue->clear_queue();
	temp_queue->clear_queue();
}

int DQS::push(int k) {
	if (main_queue->put(k) == -1) { // main_queue가 꽉 차있다면
		std::cout << "stack overflow" << std::endl;
		return -1;
	}
	// 정상적으로 push 되었으면
	top++;
	return k;
}

int DQS::pop() {
	// 일단 main_queue에 몇개의 요소가 들어있는지 알아야해

	int transfer = 0; // 임시 전달

	while (true) {
		transfer = main_queue->get();
		temp_queue->put(transfer);

		if (main_queue->rear == (main_queue->front + 1) % main_queue->MAX) {
			// 즉 main_queue에 하나의 요소만 남은 경우라면
			// (그 녀석은 main_queue에 맨 마지막으로 들어온 녀석)
			// 반복문을 나온다.
			break;
		}
	}


	int result = main_queue->get(); // pop할 요소를 저장한다.

	while (true) {
		transfer = temp_queue->get();
		main_queue->put(transfer);
		if (temp_queue->front == temp_queue->rear) {
			// temp_queue가 비워졌으면 반복을 중단한다.
			break;
		}
	}

	top--;
	return result;
}

void DQS::print_stack() {
	std::cout << "bottom --> top" << std::endl;
	for (int i = main_queue->front; i != main_queue->rear; i = (++i) % main_queue->MAX) {
		std::cout << main_queue->queue[i] << " ";
	}
	std::cout << std::endl;
}


void Main_DQS2() {

	DQS dqs(10);
	dqs.init_stack();

	dqs.push(1);
	dqs.push(2);
	dqs.push(3);
	dqs.push(4);
	dqs.push(5);
	dqs.push(6);
	dqs.push(7);
	dqs.push(8);
	dqs.push(9);

	dqs.pop();
	dqs.print_stack();

}

