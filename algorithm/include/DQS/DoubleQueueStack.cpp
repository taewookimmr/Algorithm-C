#include <iostream>
#include "DoubleQueueStack.hpp"


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
	if (main_queue->put(k) == -1) { // main_queue�� �� ���ִٸ�
		std::cout << "stack overflow" << std::endl;
		return -1;
	}
	// ���������� push �Ǿ�����
	top++;
	return k;
}

int DQS::pop() {


	if (getSize() == 0) {
		std::cout << "stack underflow" << std::endl;
		return -1;
	}

	temp_queue->init_queue();

	int transfer = 0; 
	int condition = main_queue->rear == (main_queue->front + 1) % main_queue->MAX;
	while (!condition) {
		transfer = main_queue->get();
		temp_queue->put(transfer);
		condition = main_queue->rear == (main_queue->front + 1) % main_queue->MAX;
	}

	int result = main_queue->get(); // pop�� ��Ҹ� �����Ѵ�.

	condition = temp_queue->front == temp_queue->rear;
	while (!condition) {
		transfer = temp_queue->get();
		main_queue->put(transfer);
		condition = temp_queue->front == temp_queue->rear;
	}

	top--;
	return result;
}

int DQS::pop_swap_version() {


	if (getSize() == 0) {
		std::cout << "stack underflow" << std::endl;
		return -1;
	}

	temp_queue->init_queue();

	int transfer = 0;
	int condition = main_queue->rear == (main_queue->front + 1) % main_queue->MAX;
	while (!condition) {
		transfer = main_queue->get();
		temp_queue->put(transfer);
		condition = main_queue->rear == (main_queue->front + 1) % main_queue->MAX;
	}

	int result = main_queue->get(); // pop�� ��Ҹ� �����Ѵ�.

	Queue *temp = main_queue;
	main_queue = temp_queue;
	temp_queue = temp;
	temp_queue->init_queue();

	top--;
	return result;
}

// ��������� 0, ä���������� ä���� ����� ������ ��ȯ�Ѵ�.
int DQS::getSize() {
	return top+1;
}

void DQS::print_stack() {
	std::cout << "bottom --> top" << std::endl;
	for (int i = main_queue->front; i != main_queue->rear; i = (++i) % main_queue->MAX) {
		std::cout << main_queue->queue[i] << " ";
	}
	std::cout << std::endl;
}


void Main_DQS() {

	DQS dqs(10);
	dqs.init_stack();


	dqs.push(1);

	dqs.pop();
	dqs.pop();
	dqs.pop();

	dqs.push(2);
	dqs.push(3);
	dqs.push(4);
	dqs.push(5);
	dqs.push(6);
	dqs.push(7);
	dqs.push(8);
	dqs.push(9);

	
	dqs.print_stack();

}

