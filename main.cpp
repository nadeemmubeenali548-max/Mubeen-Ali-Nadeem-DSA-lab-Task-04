#include <iostream>
#include <string>
using namespace std;

struct Node {
    int id;
    string title;
    Node* next;
};

class Stack {
    Node* top = nullptr;

public:
    void Push(int id, string title) {
        top = new Node{id, title, top};
    }

    void Pop() {
        if (!top) {
            cout << "No book requests!\n";
            return;
        }
        Node* t = top;
        cout << "Processed: " << t->title << endl;
        top = top->next;
        delete t;
    }

    void Peek() {
        if (top) cout << "Top: " << top->title << endl;
        else cout << "No requests!\n";
    }

    void Print() {
        for (Node* p = top; p; p = p->next)
            cout << p->id << " - " << p->title << endl;
    }

    ~Stack() {
        while (top) {
            Node* t = top;
            top = top->next;
            delete t;
        }
    }
};

int main() {
    Stack s;
    s.Push(1, "Data Structures");
    s.Push(2, "Programming");
    s.Push(3, "Algorithms");

    cout << "Book Requests:\n";
    s.Print();

    s.Peek();
    s.Pop();

    cout << "Remaining Requests:\n";
    s.Print();
}