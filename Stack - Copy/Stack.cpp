#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(const T& item) {
        Node* newNode = new Node(item);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty. Unable to pop item.\n";
            return T();
        }

        Node* poppedNode = topNode;
        T poppedData = poppedNode->data;
        topNode = topNode->next;
        delete poppedNode;

        return poppedData;
    }

    T top() const {
        if (isEmpty()) {
            std::cout << "Stack is empty. No top item.\n";
            return T();
        }

        return topNode->data;
    }
};

int main() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top item: " << stack.top() << std::endl;

    stack.pop();
    stack.pop();

    std::cout << "Top item after popping twice: " << stack.top() << std::endl;

    stack.push(40);
    stack.push(50);
    stack.push(60);

    return 0;
}
