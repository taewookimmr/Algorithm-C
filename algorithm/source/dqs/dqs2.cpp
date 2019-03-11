#include <iostream>

// rear�� ť�� ���� ����Ű�� ť�� ����ִ� ���¸� ǥ������ ���Ѵ�.
// ���� rear�� ť�� ���� ����Ű�� � ������ �ִ��� Ȯ���غ���.
// �ڷᰡ �ϳ� ���� ��, front = rear�� �ȴ�.
// �ڷᰡ �ϳ��� ���ٸ�? �׷��� �ڷᰡ �ϳ��� ���� empty state�� ��Ÿ���� ���Ѵ�.

class Queue {
public:

    int *queue;

    int MAX;
    int front;
    int rear;

    Queue() {
        Queue(10);
    }

    Queue(int MAX){
        this->MAX = MAX;
        queue = new int[MAX];
    }

    virtual ~Queue() {
        free(queue);
    }

    void init_queue() {
        front = rear = 0; // ����ִ� ť�� ǥ��
    }

    void clear_queue() {
        front = rear;
    }

    int put(int k) {
        if ((rear + 1) % MAX == front) {
            std::cout << "queue overflow" << std::endl;
            return -1;
        }
        queue[rear] = k;
        rear = ++rear % MAX;
        return k;
    }

    int get() {
        if (front == rear) {
            std::cout << "queue underflow" << std::endl;
            return -1;
        }
        int result = queue[front];
        front = ++front % MAX;
        return result;
    }

    void print_queue() {
        int i = 0;
        std::cout << "queue contents : front --> rear" << std::endl;
        for (int i = front; i != rear; i = (++i) % MAX) {
            std::cout << queue[i] << " ";
        }
        std::cout << std::endl;
    }

};

class Stack {

public:
    int top;
    int MAX;
    Queue *main_queue, *temp_queue;

    Stack() {
        Stack(10);
    }

    Stack(int MAX) {
        main_queue = new Queue(MAX);
        temp_queue = new Queue(MAX);
    }

    ~Stack() {
        free(main_queue);
        free(temp_queue);
    }

   
    void init_stack() {
        top = -1;
        main_queue->init_queue();
        temp_queue->init_queue();
    }

    void clear_stack() {
        top = -1;
        main_queue->clear_queue();
        temp_queue->clear_queue();
    }

    int push(int k) {
        if (main_queue->put(k) == -1) { // main_queue�� �� ���ִٸ�
            std::cout << "stack overflow" << std::endl;
            return -1;
        }
        // ���������� push �Ǿ�����
        top++;
        return k;
    }

    int pop() {
        // �ϴ� main_queue�� ��� ��Ұ� ����ִ��� �˾ƾ���

        int transfer = 0; // �ӽ� ����

        while (true) {
            transfer = main_queue->get();
            temp_queue->put(transfer);

            if (main_queue->rear == (main_queue->front + 1) % main_queue->MAX) {
                // �� main_queue�� �ϳ��� ��Ҹ� ���� �����
                // (�� �༮�� main_queue�� �� ���������� ���� �༮)
                // �ݺ����� ���´�.
                break;
            }
        }


        int result = main_queue->get(); // pop�� ��Ҹ� �����Ѵ�.

        while (true) {
            transfer = temp_queue->get();
            main_queue->put(transfer);
            if (temp_queue->front == temp_queue->rear) {
                // temp_queue�� ��������� �ݺ��� �ߴ��Ѵ�.
                break;
            }
        }

        top--;
        return result;
    }

    void print_stack() {
        std::cout << "bottom --> top" << std::endl;
        for (int i = main_queue->front; i != main_queue->rear; i = (++i) % main_queue->MAX) {
            std::cout << main_queue->queue[i] << " ";
        }
        std::cout << std::endl;
    }


};

int main() {

    Stack dqs(10);
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

    return 0;
}