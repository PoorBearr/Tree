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

    void push(Node *p, Node* cur) {
        if (root == nullptr) {
            root = p;
            return;
        }
        while (cur != nullptr)  {
            if (cur->data < p->data) {
                if (cur->r != nullptr) cur = cur->r;
                else {
                    p->par = cur;
                    cur->r = p;
                    break;
                }
            } else if (cur->data == p->data) break;
            else if (cur->data > p->data) {
                if (cur->l != nullptr) cur = cur->l;
                else {
                    p->par = cur;
                    cur->l = p;
                }
            }
        }
    }

    Node *exist(Node* cur , int x) {
        if (cur == nullptr or x == cur->data) return cur;
        if (x < cur->data) return exist(cur->l, x);
        else return exist(cur->r, x);
    }

    Node *next(int x) {
        Node *cur = root;
        Node *ans = nullptr;
        while (cur != nullptr) {
            if (cur->data > x) {
                ans = cur;
                cur = cur->l;
            } else cur = cur->r;
        }
        return ans;
    }

    Node *prev(int x) {
        Node *cur = root;
        Node *ans = nullptr;
        while (cur != nullptr) {
            if (cur->data >= x) cur = cur->l;
            else {
                ans = cur;
                cur = cur->r;
            }
        }
        return ans;
    }

    void del(Node *p, int x) {
        if (p == nullptr) return;
        Node *node = p->par;
        if (p->l == nullptr && p->r == nullptr) {
            if (node == nullptr) {
                root = nullptr;
                return;
            }
            if (node->l == p) node->l = nullptr;
            if (node->r == p) node->r = nullptr;
        } else
            if (p->l == nullptr or p->r == nullptr) {
                if (p->l == nullptr) {
                    if (node == nullptr) {
                        root = p->r;
                        root->par = nullptr;
                        return;
                    }
                    if (node->l == p) node->l = p->r;
                    else node->r = p->r;
                    p->r->par = node;
                } else {
                    if (node == nullptr) {
                        root = p->l;
                        root->par = nullptr;
                        return;
                    }
                    if (node->l == p) node->l = p->l;
                    else node->r = p->l;
                    p->l->par = node;
                }
            } else {
            Node *cur = next(x);
            p->data = cur->data;
            if (cur->par->l == cur) {
                cur->par->l = cur->r;
                if (cur->r != nullptr) cur->r->par = cur->par;
            } else {
                cur->par->r = cur->r;
                if (cur->r != nullptr) cur->r->par = cur->par;
            }
        }
    }
};

int main() {
    int x, y;
    string  str, rst;
    tree t;
    while (cin >> str) {
        if (str == "insert") {
            cin >> x;
            Node* p = new Node(x);
            t.push(p, t.root);
        } else if (str == "exists") {
            cin >> x;
            if (t.exist(t.root, x) == nullptr) cout << "false" << '\n';
            else cout << "true" << '\n';
        } else if (str == "next") {
            cin >> x;
            if (t.next(x) != nullptr) cout << t.next(x)->data << '\n';
            else cout << "none" << '\n';
        } else if (str == "prev") {
            cin >> x;
            if (t.prev(x) != nullptr) cout << t.prev(x)->data << '\n';
            else cout << "none" << '\n';
        } else if (str == "delete") {
            cin >> x;
            t.del(t.exist(t.root, x), x);
        }
    }
    return 0;
}