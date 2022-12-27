#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* l;
    Node* r;
    Node* par;

    Node(int data) {
        this->data = data;
        this->l = nullptr;
        this->r = nullptr;
        this->par = nullptr;
    }
};

struct tree {
    Node *root = nullptr;
};

int main() {
    int x, y;
    string  str, rst;
    tree t;
    return 0;
}