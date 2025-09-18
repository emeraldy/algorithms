#include"RedBlackTree.h"
#include"BSTRenderer.h"
#include<iostream>
using namespace std;

void main()
{
    RedBlackTree bst;
    bst.insert(15);
    bst.insert(15);
    bst.insert(15);
    bst.insert(15);
    bst.insert(6);
    bst.insert(18);
    bst.insert(3);
    bst.insert(3);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(13);
    bst.insert(9);
    bst.insert(17);
    bst.insert(20);


    BSTRenderer bstRenderer;
    bstRenderer.render(bst);

    const RedBlackTreeNode* searchResult = bst.findKey(15);
    if (searchResult == 0)
        cout << "key not found" << endl;
    else
        cout << "key found: " << searchResult->getKey() << endl;

    bst.deleteKey(const_cast<RedBlackTreeNode*>(searchResult));
    searchResult = 0;

    bstRenderer.render(bst);
}
