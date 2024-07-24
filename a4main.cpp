// Basic test program for AVL Tree

#include <vector>
#include <iostream>
#include "AVLTree.h"
using std::cout;
using std::endl;
using std::vector;

void a4marking();
template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree);

int main()
{
    a4marking();

    cout << endl;
}

void a4marking()
{
    AVLTree<int, int> aspen;
    //checkAVLTree<int, int>(aspen);

    // Method return values
    bool success = aspen.insert(1, 2);
    success = aspen.insert(2,3);
    cout << aspen.insert(2, 0) << endl;
    bool yes;
    int count = 0;
    int j = 25;
    for (int i = 0; i < 10; i++) {
        yes = aspen.insert(i+1, i+11);
        count++;
        if (yes != 1) {
            break;
        }
    }
    cout << yes << " " << count << endl;

    cout << aspen.size();  
    cout << endl;

    cout << "Found: " << aspen.search(10) << endl;
    aspen.remove(2);
    aspen.remove(3);
    cout << aspen.remove(1) << endl;
    cout << aspen.size() << endl;
    aspen.insert(11, 11);
    aspen.insert(1, 10);
    cout << aspen.size();

    success = aspen.remove(1);
    int result = aspen.search(1);
    vector<int> v2 = aspen.values();
    vector<int> k1 = aspen.keys();
    AVLTree<int, int> larch(aspen);
    aspen = larch;

    cout << endl << "end a4 test" << endl;
}


template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree)
{
    AVLTreeNode<int, int>* nd = (AVLTreeNode<int, int>*)tree.getRoot();
    cout << "height = " << nd->depth << endl;

    return false;
}