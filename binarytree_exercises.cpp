/*******************************************************************************
 * Name          : binarytree.cpp
 * Author        : Eric Stazzone
 * Version       : 1.0
 * Date          : November 5th, 2020
 * Last modified : March 30, 2020
 * Description   : Implementation of common interview questions on binary trees.
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

struct Node {
    Node *parent, *left, *right;
    int level, data;

    Node(int level, int data) :
            parent{nullptr}, left{nullptr}, right{nullptr},
            level{level}, data(data) { }

    Node(Node *parent, int level, int data) :
            parent{parent}, left{nullptr}, right{nullptr},
            level{level}, data{data} { }
};

Node* lowest_common_ancestor(Node *p, Node *q) {
    if (p == nullptr || q == nullptr) {
        return nullptr;
    }
    if (p == q) {
        return p;
    }
    if (p->level > q->level) {
        return lowest_common_ancestor(p->parent, q);
    }
    if (p->level < q->level) {
        return lowest_common_ancestor(p, q->parent);
    }
    return lowest_common_ancestor(p->parent, q->parent);
}

Node* create_bst_helper(int data[], int low, int high, int level) {
    if (low > high) {
        return nullptr;
    }
    int mid = low + (high - low) / 2;
    Node *parent = new Node(level, data[mid]);
    parent->left = create_bst_helper(data, low, mid - 1, level + 1);
    if (parent->left != nullptr) {
        parent->left->parent = parent;
    }
    parent->right = create_bst_helper(data, mid + 1, high, level + 1);
    if (parent->right != nullptr) {
        parent->right->parent = parent;
    }
    return parent;
}

Node* create_bst(int data[], int length) {
    return create_bst_helper(data, 0, length - 1, 0);
}

bool is_bst(Node *n, int *min, int *max) {
    if (n == nullptr) {
        return true;
    }
    if ((min != nullptr && n->data <= *min) ||
        (max != nullptr && n->data >= *max)) {
        return false;
    }
    return is_bst(n->left, min, &n->data) &&
           is_bst(n->right, &n->data, max);
}

bool is_bst(Node *tree) {
    return is_bst(tree, nullptr, nullptr);
}

void display_sideways(Node *node) {
    if (node != nullptr) {
        display_sideways(node->right);
        if (node->level == 0) {
            cout << "root ";
        } else {
            cout << "     ";
        }
        for (int i = 0; i < node->level; ++i) {
            cout << "    ";
        }
        cout << node->data << endl;
        display_sideways(node->left);
    }
}

void delete_bst(Node *n) {
    if (n != nullptr) {
        delete_bst(n->left);
        delete_bst(n->right);
        delete n;
    }
}

bool do_trees_match(Node *t1, Node *t2) {
    if (t1 == nullptr && t2 == nullptr) {
        // Both trees being NULL constitutes a match.
        return true;
    }
    if (t1 == nullptr || t2 == nullptr || t1->data != t2->data) {
        // One tree being NULL or unequal data indicates no match.
        return false;
    }
    // Continue checking both trees for equality.
    return do_trees_match(t1->left, t2->left) &&
           do_trees_match(t1->right, t2->right);
}

bool is_subtree(Node *t1, Node *t2) {
    if (t1 == nullptr) {
        // The supposed larger tree is NULL, so t2 cannot be a subtree.
        return false;
    }
    if (t1->data == t2->data && do_trees_match(t1, t2)) {
        // The data fields and tree substructures match.
        return true;
    }
    // Continue looking for t2 in the left and right subtrees of t1.
    return is_subtree(t1->left, t2) || is_subtree(t1->right, t2);
}

bool contains_tree(Node *t1, Node *t2) {
    // The NULL tree is always a subtree of a non-NULL tree.
    return t2 == nullptr ? true : is_subtree(t1, t2);
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <node 1> <node 2>" << endl;
        return 1;
    }
    int node1, node2;
    istringstream iss(argv[1]);
    if (!(iss >> node1) || node1 <= 0 || node1 >= 7) {
        cerr << "Error: Bad value for node 1." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[2]);
    if (!(iss >> node2) || node2 <= 0 || node2 >= 7) {
        cerr << "Error: Bad value for node 2." << endl;
        return 1;
    }

    Node* nodes[7];
    nodes[0] = nullptr;
    nodes[1] = new Node(1, 1);
    nodes[2] = new Node(nodes[1], 2, 2);
    nodes[3] = new Node(nodes[1], 2, 3);
    nodes[4] = new Node(nodes[2], 3, 4);
    nodes[5] = new Node(nodes[2], 3, 5);
    nodes[6] = new Node(nodes[5], 4, 6);

    Node *common_ancestor = lowest_common_ancestor(nodes[node1], nodes[node2]);
    cout << "Lowest common ancestor: " << common_ancestor->data << endl << endl;

    for (int i = 1; i <= 6; ++i) {
        delete nodes[i];
    }

    int data[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Node *bst = create_bst(data, 15);
    display_sideways(bst);
    cout << endl << endl;

    int data2[7] = {1, 2, 3, 4, 5, 6, 7};
    Node *bst2 = create_bst(data2, 7);
    display_sideways(bst2);

    cout << "Is BST? " << (is_bst(bst) ? "yes" : "no") << endl;
    cout << "Is t2 in t1? " << (contains_tree(bst, bst2) ? "yes" : "no")
         << endl;

    delete_bst(bst);
    delete_bst(bst2);
    return 0;
}
