#pragma once

class BinarySearchTreeNode
{
    friend class BinarySearchTree;
private:
    BinarySearchTreeNode* left;
    BinarySearchTreeNode* right;
    BinarySearchTreeNode* parent;
    BinarySearchTreeNode* identical;
    int identicalSize;//number of elements on the identical list
    int key;

public:
    BinarySearchTreeNode(int k);
    ~BinarySearchTreeNode() {}
    BinarySearchTreeNode* getLeft() { return left; }
    BinarySearchTreeNode* getRight() { return right; }
    int getIdenticalSize() const { return identicalSize; }
    int getKey() const { return key; }
};

class BinarySearchTree
{
private:
    BinarySearchTreeNode* root;
    int nodeNumber;
    int keyNumber;//nodeNumber + duplicates

    void demolish(BinarySearchTreeNode* rootNode);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    int getNodeNumber() { return nodeNumber; }
    int getKeyNumber() { return keyNumber; }
    BinarySearchTreeNode* getRoot() { return root; }

    const BinarySearchTreeNode* findKey(int k);
    void deleteKey(BinarySearchTreeNode* z);
    const BinarySearchTreeNode* getMax(const BinarySearchTreeNode* rootNode);
    const BinarySearchTreeNode* getMin(const BinarySearchTreeNode* rootNode);
    const BinarySearchTreeNode* getSuccessor(const BinarySearchTreeNode* node);
    const BinarySearchTreeNode* getPredecessor(const BinarySearchTreeNode* node);
    void insert(int k);
    void inOrderWalk(BinarySearchTreeNode const* rootNode);
};