#pragma once
#include"RedBlackTree.h"
#include<string>

class BSTRenderInfo
{
    friend class BSTRenderer;
private:
    RedBlackTreeNode* targetTreeNode;
    //rendering coordinate
    int level;//level of the current target node on the tree, root is at level 0
    int rowPos;//starting with 1
};

class BSTRenderer
{
private:
    BSTRenderInfo* renderQueue;
    int head;
    int tail;
    int capacity;
    bool isEmpty;
    bool isFull;
    std::string levelBuffer;
    int currentLevel;

    void sendToBuffer(BSTRenderInfo& info);

public:
    BSTRenderer();
    ~BSTRenderer();
    void initiateRenderQueue(int cap);
    bool enqueue(RedBlackTreeNode* node, int lv, int rPos = 0);
    bool dequeue(BSTRenderInfo* info);
    int countLevel(RedBlackTree& bst);
    void render(RedBlackTree& bst);
};
