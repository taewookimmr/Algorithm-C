#include <iostream>

// rear가 큐의 끝을 가리키면 큐가 비어있는 상태를 표현하지 못한다.
// 만약 rear가 큐의 끝을 가리키면 어떤 문제가 있는지 확인해보자.
// 자료가 하나 있을 때, front = rear가 된다.
// 자료가 하나도 없다면? 그렇다 자료가 하나도 없는 empty state를 나타내지 못한다.

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
        front = rear = 0; // 비어있는 큐를 표현
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
        if (main_queue->put(k) == -1) { // main_queue가 꽉 차있다면
            std::cout << "stack overflow" << std::endl;
            return -1;
        }
        // 정상적으로 push 되었으면
        top++;
        return k;
    }

    int pop() {
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
    dqs.push(10); // 실질적으로 9개의 공간밖에 사용 못하는 거였지

    dqs.pop();
    dqs.print_stack();

    return 0;
}