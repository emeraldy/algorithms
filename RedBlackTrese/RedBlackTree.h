#pragma once

class RedBlackTreeNode
{
    friend class RedBlackTree;
private:
    RedBlackTreeNode* left;
    RedBlackTreeNode* right;
    RedBlackTreeNode* parent;
    RedBlackTreeNode* identical;
    int identicalSize;//number of elements on the identical list
    int key;
    bool isRed;

public:
    RedBlackTreeNode(int k);
    ~RedBlackTreeNode() {}
    RedBlackTreeNode* getLeft() { return left; }
    RedBlackTreeNode* getRight() { return right; }
    int getIdenticalSize() const { return identicalSize; }
    int getKey() const { return key; }
};

class RedBlackTree
{
private:
    RedBlackTreeNode* root;
    int nodeNumber;
    int keyNumber;//nodeNumber + duplicates

    void demolish(RedBlackTreeNode* rootNode);
    void insertFix(RedBlackTreeNode* target);
    void deleteFix(RedBlackTreeNode* target);
    bool leftRotateOn(RedBlackTreeNode* pivot);
    bool rightRotateOn(RedBlackTreeNode* pivot);

public:
    RedBlackTree();
    ~RedBlackTree();

    int getNodeNumber() { return nodeNumber; }
    int getKeyNumber() { return keyNumber; }
    RedBlackTreeNode* getRoot() { return root; }

    const RedBlackTreeNode* findKey(int k);
    void deleteKey(RedBlackTreeNode* z);
    const RedBlackTreeNode* getMax(const RedBlackTreeNode* rootNode);
    const RedBlackTreeNode* getMin(const RedBlackTreeNode* rootNode);
    const RedBlackTreeNode* getSuccessor(const RedBlackTreeNode* node);
    const RedBlackTreeNode* getPredecessor(const RedBlackTreeNode* node);
    void insert(int k);
    void inOrderWalk(RedBlackTreeNode const* rootNode);
};