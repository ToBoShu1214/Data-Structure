#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

class BST {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* Insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = Insert(node->left, value);
        else
            node->right = Insert(node->right, value);
        return node;
    }

    int Height(Node* node) const {
        if (!node) return -1;
        return 1 + max(Height(node->left), Height(node->right));
    }

    void Clear(Node* node) {
        if (!node) return;
        Clear(node->left);
        Clear(node->right);
        delete node;
    }

    Node* FindMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* Delete(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->value) {
            node->left = Delete(node->left, key);
        }
        else if (key > node->value) {
            node->right = Delete(node->right, key);
        }
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* successor = FindMin(node->right);
            node->value = successor->value;
            node->right = Delete(node->right, successor->value);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        Clear(root);
    }

    void Insert(int value) {
        root = Insert(root, value);
    }

    int GetHeight() const {
        return Height(root);
    }

    void Delete(int key) {
        root = Delete(root, key);
    }
};

int main() {
    vector<int> n_values = { 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
    vector<double> ratios;

    mt19937 rng(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> dist(1, 1000000);

    for (int n : n_values) {
        BST bst;
        for (int i = 0; i < n; ++i) {
            bst.Insert(dist(rng));
        }
        int height = bst.GetHeight();
        double log2n = log2(n);
        double ratio = height / log2n;
        ratios.push_back(ratio);
        cout << "n = " << n << ", 高度 = " << height << ", log2(n) = " << log2n
            << ", 比率 = " << ratio << endl;
    }

    // 測試刪除功能
    BST bst;
    bst.Insert(5);
    bst.Insert(3);
    bst.Insert(7);
    cout << "初始高度: " << bst.GetHeight() << endl;
    bst.Delete(5);
    cout << "刪除5後高度: " << bst.GetHeight() << endl;

    return 0;
}
