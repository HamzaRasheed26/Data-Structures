#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    void enqueue(const T& item) {
        Node* newNode = new Node(item);

        if (isEmpty()) {
            frontNode = newNode;
            rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty. Unable to dequeue item.\n";
            return T();
        }

        Node* dequeuedNode = frontNode;
        T dequeuedData = dequeuedNode->data;

        if (frontNode == rearNode) {
            frontNode = nullptr;
            rearNode = nullptr;
        } else {
            frontNode = frontNode->next;
        }

        delete dequeuedNode;

        return dequeuedData;
    }

    T front() const {
        if (isEmpty()) {
            std::cout << "Queue is empty. No front item.\n";
            return T();
        }

        return frontNode->data;
    }
};

int main() {
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Front item: " << queue.front() << std::endl;

    queue.dequeue();
    queue.dequeue();

    std::cout << "Front item after dequeuing twice: " << queue.front() << std::endl;

    queue.enqueue(40);
    queue.enqueue(50);
    queue.enqueue(60);

    return 0;
}
