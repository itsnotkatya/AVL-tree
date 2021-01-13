#include <iostream>
using namespace std;
#define COUNT 3

class AVLTree {

    struct Node {
        int data;
        int height;
        Node* left;
        Node* right;
        Node(int k) { data = k; left = right = 0; height = 1; }
    };
    Node* root;

    int height(Node* p) {
        return p ? p -> height : 0;
    }

    int bfactor(Node* p) {
        return height(p -> right) - height(p -> left);
    }

    void fixheight(Node* p) {
        int hl = height(p->left);
        int hr = height(p->right);
        p -> height = (hl > hr ? hl : hr) + 1;
    }

    Node* rotateRight(Node* p) {
        cout << "поворот вправо" << endl;
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    Node* rotateLeft(Node* q) {
        cout << "поворот влево" << endl;
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    Node* balance(Node* p) {
        fixheight(p);
        if (bfactor(p) == 2) {
//             cout << "большой поворот";
            if (bfactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (bfactor(p) == -2) {
//            cout << "большой поворот";
            if (bfactor(p->left) > 0)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p; // балансировка не нужна
    }

    Node* insert(Node* p, int k) {
        if( !p ) return new Node(k);
        if (k < p->data)
            p->left = insert(p->left,k);
        if (k > p->data)
            p->right = insert(p->right,k);
        return balance(p);
    }

    Node* findmin(Node* p) { // поиск узла с минимальным ключом в дереве p
        return p->left ? findmin(p->left) : p;
    }

    Node* removemin(Node* p) {// удаление узла с минимальным ключом из дерева p
        if (p->left == 0)
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    Node* remove(Node* p, int k) {// удаление ключа k из дерева p
        if (!p) return 0;
        if (k < p->data)
            p->left = remove(p->left,k);
        else if( k > p->data )
            p->right = remove(p->right,k);
        else {                        //  k == p->key
            Node* q = p->left;
            Node* r = p->right;
            delete p;
            if( !r ) return q;
            Node* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

    Node* removeall(Node* p) {
        if (!p) return 0;
        while (p->left != 0 && p->right != 0) {
            p->left = remove(p->left,p->left->data);
            p->right = remove(p->right,p->right->data);
        }
        remove(p, p->data);
        return nullptr;
    }

    Node* search (int x, Node* t) {
        if (t == nullptr) {
            cout << x << " wasn't found";
            return nullptr;
        }
         if (x < t->data) {
            t->left = search (x, t->left);
            if (x == t->data) {
                cout << x << " was found" << endl;
            }
        }
        else if (x > t->data) {
            t->right = search (x, t->right);
            if (x == t->data) {
                cout << x << " was found" << endl;
            }
        }
        else if (x == t->data) {
            cout << x << " was found" << endl;
        }
        return t;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void Insert(int x) {
        root = insert(root, x);
    }

    void Remove(int x) {
        root = remove(root, x);
    }

    void Search (int x) {
        root = search(x,root);
    }
    void RemoveAll() {
        root = removeall(root);
    }

    void print(Node* root, int space) {
        if (root != nullptr) {

            space += COUNT;               // Increase distance between levels
            print(root->right, space);  // Process right child first
            cout << endl;                 // Print current node after space
            // count
            for (int i = COUNT; i < space; i++)
                cout << " ";
            cout << root->data << "\n";

            // Process left child
            print(root->left, space);
        }
    }

    void print2D() {
        print(root, 0);
    }


};


int main() {
    AVLTree t;
    t.Insert(18);
    t.Insert(13);
    t.Insert(22);
    t.Insert(8);
    t.Insert(20);
    t.Insert(30);
    t.Insert(19);
    t.Insert(21);
    t.Insert(29);
    t.Insert(31);



    cout << "<---------------- Исходное дерево ----------->"<< endl;

    t.print2D();

    cout << "<---------------- Исходное дерево ----------->"<< endl;
    cout << endl;

    cout << "<---------------- Удаление 13 ----------->"<< endl;

    t.Remove(13);
    t.print2D();
    cout << "<---------------- Удаление 13 ----------->"<< endl;

    cout << endl;

    cout << "<---------------- Удаление 22 ----------->"<< endl;
    t.Remove(22);
    t.print2D();
    cout << "<---------------- Удаление 22 ----------->"<< endl;

    cout << endl;

    cout << "<---------------- Удаление 29 ----------->"<< endl;
    t.Remove(29);
    t.print2D();
    cout << "<---------------- Удаление 29 ----------->"<< endl;

    cout << endl;

//    cout << "<---------------- Удаление 20 ----------->"<< endl;
//    t.Remove(20);
//    t.print2D();
//    cout << "<---------------- Удаление 20 ----------->"<< endl;
//
//    cout << endl;

    cout << "<---------------- Удаление 21 ----------->"<< endl;
    t.Remove(21);
    t.print2D();
    cout << "<---------------- Удаление 21 ----------->"<< endl;

    cout << "<---------------- Удаление 31 ----------->"<< endl;
    t.Remove(31);
    t.print2D();
    cout << "<---------------- Удаление 31 ----------->"<< endl;

    cout << "<---------------- Удаление 30 ----------->"<< endl;
    t.Remove(30);
    t.print2D();
    cout << "<---------------- Удаление 30 ----------->"<< endl;

    cout << "<---------------- Удаление 8 ----------->"<< endl;
    t.Remove(8);
    t.print2D();
    cout << "<---------------- Удаление 8 ----------->"<< endl;
    return 0;
}