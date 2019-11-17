#include <iostream>
#include <stack>

class BST {
public:
    class Node {
    public:
        Node(int value, Node *left, Node *right) :
                value(value), left(left), right(right) {}

        explicit Node(int value) :
                value(value), left(nullptr), right(nullptr) {}

    public:
        int value;
        Node *left;
        Node *right;
    };

    static Node *MakeNode(int value) {
        return new Node(value);
    }

    static Node *MakeNode(int value, Node *left, Node *right) {
        return new Node(value, left, right);
    }

    BST() : root_(nullptr) {}

    void add(int value) {
        root_ = AddValue(root_, value);
    }

    static Node *AddValue(Node *node, int value) {
        if (!node) {
            return MakeNode(value);
        }

        if (value < node->value) {
            node->left = AddValue(node->left, value);
        } else {
            node->right = AddValue(node->right, value);
        }

        return node;
    }

    typedef void (*NodeHandler)(Node *);

    static void print(Node *node) {
        std::cout << node->value << std::endl;
    }

    void preOrderPrint(bool recursive = true) {
        std::cout << "pre order:" << std::endl;
        if (recursive) {
            PreOrder(root_, print);
        } else {
            PreOrderWithoutRecursive(root_, print);
        }
        std::cout << std::endl;
    }

    static void PreOrder(Node *node, NodeHandler func) {
        if (node != nullptr) {
            func(node);
            PreOrder(node->left, func);
            PreOrder(node->right, func);
        }
    }

    static void PreOrderWithoutRecursive(Node *node, NodeHandler func) {
        std::stack<Node*> stack;
        if (node != nullptr) {
            stack.push(node);
        }

        while (!stack.empty()) {
            Node *n = stack.top();
            stack.pop();

            func(n);
            if (n->right) {
                stack.push(n->right);
            }
            if (n->left) {
                stack.push(n->left);
            }
        }
    }

    void inOrderPrint(bool recursive = true) {
        std::cout << "in order:" << std::endl;
        if (recursive) {
            InOrder(root_, print);
        } else {
            InOrderWithoutRecursive(root_, print);
        }
        std::cout << std::endl;
    }

    static void InOrder(Node *node, NodeHandler func) {
        if (node != nullptr) {
            InOrder(node->left, func);
            func(node);
            InOrder(node->right, func);
        }
    }

    static void InOrderWithoutRecursive(Node *node, NodeHandler func) {
        std::stack<Node*> stack;

        while (!stack.empty() || node) {
            if (node) {
                stack.push(node);
                node = node->left;
            } else {
                node = stack.top();
                stack.pop();
                func(node);
                node = node->right;
            }
        }
    }

    void postOrderPrint(bool recursive = true) {
        std::cout << "post order" << std::endl;
        if (recursive) {
            PostOrder(root_, print);
        } else {
            PostOrderWithoutRecursive(root_, print);
        }
        std::cout << std::endl;
    }

    static void PostOrder(Node *node, NodeHandler func) {
        if (node != nullptr) {
            PostOrder(node->left, func);
            PostOrder(node->right, func);
            func(node);
        }
    }

    static void PostOrderWithoutRecursive(Node *node, NodeHandler func) {
        std::stack<Node*> stack;
        Node *last_handled = nullptr;

        while (node) {
            stack.push(node);
            node = node->left;
        }

        while (!stack.empty()) {
            node = stack.top();
            stack.pop();

            if (node->right == nullptr || node->right == last_handled) {
                func(node);
                last_handled = node;
            } else {
                stack.push(node);
                node = node->right;

                while (node) {
                    stack.push(node);
                    node = node->left;
                }
            }
        }

    }

private:
    Node *root_;
};

int main() {
    BST tree;

    tree.add(10);
    tree.add(7);
    tree.add(12);
    tree.add(6);
    tree.add(8);

    tree.preOrderPrint(false);
    tree.inOrderPrint(false);
    tree.postOrderPrint(false);
    return 0;
}