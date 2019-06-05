#include "DoubleQueueStack.hpp"

namespace DoubleQueueStack {


	Queue::Queue() {
			front = rear = 0;
		}

	Queue:: ~Queue() {}

	void Queue::init_queue() {
		front = rear = 0; // ����ִ� ť�� ǥ��
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

	void Queue::print_queue() {
		int i = 0;
		std::cout << "queue contents : front --> rear" << std::endl;
		for (int i = front; i != rear; i = (++i) % MAX) {
			std::cout << queue[i] << " ";
		}
		std::cout << std::endl;
	}


	DQS::DQS() {}
	DQS::~DQS() {}

	void DQS::init_stack() {
		top = -1;
		main_queue.init_queue();
		temp_queue.init_queue();
	}

	void DQS::clear_stack() {
		top = -1;
		main_queue.clear_queue();
		temp_queue.clear_queue();
	}

	int DQS::push(int k) {
		if (main_queue.put(k) == -1) { // main_queue�� �� ���ִٸ�
			std::cout << "stack overflow" << std::endl;
			return -1;
		}
		// ���������� push �Ǿ�����
		top++;
		return k;
	}

	int DQS::pop() {
		// �ϴ� main_queue�� ��� ��Ұ� ����ִ��� �˾ƾ���

		int transfer = 0; // �ӽ� ����

		while (true) {
			transfer = main_queue.get();
			temp_queue.put(transfer);

			if (main_queue.rear == (main_queue.front + 1) % MAX) {
				// �� main_queue�� �ϳ��� ��Ҹ� ���� �����
				// (�� �༮�� main_queue�� �� ���������� ���� �༮)
				// �ݺ����� ���´�.
				break;
			}
		}


		int result = main_queue.get(); // pop�� ��Ҹ� �����Ѵ�.

		while (true) {
			transfer = temp_queue.get();
			main_queue.put(transfer);
			if (temp_queue.front == temp_queue.rear) {
				// temp_queue�� ��������� �ݺ��� �ߴ��Ѵ�.
				break;
			}
		}

		top--;
		return result;
	}

	void DQS::print_stack() {
		std::cout << "bottom --> top" << std::endl;
		for (int i = main_queue.front; i != main_queue.rear; i = (++i) % MAX) {
			std::cout << main_queue.queue[i] << " ";
		}
		std::cout << std::endl;
	}

	void Main_DQS() {

		DQS dqs;
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
		dqs.push(10); // ���������� 9���� �����ۿ� ��� ���ϴ� �ſ���

		dqs.pop();
		dqs.print_stack();
	}
};



