#include"BSTRenderer.h"
#include<iostream>
#include<math.h>
using namespace std;

BSTRenderer::BSTRenderer()
{
    renderQueue = 0;
    head = 0;
    tail = 0;
    capacity = 0;
    isEmpty = true;
    isFull = false;
    currentLevel = 0;
}

BSTRenderer::~BSTRenderer()
{
    delete[] renderQueue;
    renderQueue = 0;
    head = 0;
    tail = 0;
}

void BSTRenderer::initiateRenderQueue(int cap)
{
    if (renderQueue != 0)
    {
        delete[] renderQueue;
        renderQueue = 0;
        head = 0;
        tail = 0;
        isEmpty = true;
        isFull = false;
    }

    capacity = cap;
    renderQueue = new BSTRenderInfo[capacity];
    head = tail = 0;
}

bool BSTRenderer::enqueue(RedBlackTreeNode* node, int lv, int rPos)
{
    if (!isFull)
    {
        renderQueue[tail].targetTreeNode = node;
        renderQueue[tail].level = lv;
        renderQueue[tail].rowPos = rPos;
        if (++tail == capacity)
            tail = 0;
        if (tail == head)
            isFull = true;
        if (isEmpty)
            isEmpty = false;
        return true;
    }
    else
        return false;
}

bool BSTRenderer::dequeue(BSTRenderInfo* info)
{
    if (!isEmpty)
    {
        info->targetTreeNode = renderQueue[head].targetTreeNode;
        info->level = renderQueue[head].level;
        info->rowPos = renderQueue[head].rowPos;
        if (++head == capacity)
            head = 0;
        if (head == tail)
            isEmpty = true;
        if (isFull)
            isFull = false;
        return true;
    }
    else
        return false;
}

int BSTRenderer::countLevel(RedBlackTree& bst)
{
    int level = 0;
    int stopCount = 0;
    BSTRenderInfo current;

    if (bst.getRoot() == 0)
        return -1;

    initiateRenderQueue(bst.getNodeNumber() + 5);
    enqueue(bst.getRoot(), 0);
    stopCount++;
    while (!isEmpty)
    {
        if (dequeue(&current))
        {
            if (current.targetTreeNode == 0)//is it empty node?
            {
                //yes, enqueue empty left and right child
                enqueue(0, current.level);
                enqueue(0, current.level);
            }
            else
            {
                //enqueue left
                if (current.targetTreeNode->getLeft() != 0)
                {
                    enqueue(current.targetTreeNode->getLeft(), current.level + 1);
                    stopCount++;
                    if (current.level + 1 > level)
                        level = current.level + 1;
                }
                else
                    enqueue(0, current.level);

                //enqueue right
                if (current.targetTreeNode->getRight() != 0)
                {
                    enqueue(current.targetTreeNode->getRight(), current.level + 1);
                    stopCount++;
                    if (current.level + 1 > level)
                        level = current.level + 1;
                }
                else
                    enqueue(0, current.level);
            }
        }
        else
        {
            cout << "BST renderer dequeue error!" << endl;
            cin.get();
            exit(0);
        }

        if (stopCount == bst.getNodeNumber())//need to get the actual number of nodes in the bst here
            break;
    }

    return level;
}

void BSTRenderer::sendToBuffer(BSTRenderInfo& info)
{
    if (info.level != currentLevel)
    {
        //new level now, print the last level
        cout << levelBuffer << endl;
        levelBuffer.clear();
        currentLevel = info.level;
    }

    string workingBuffer;
    for (int i = 1; i < info.rowPos; i++)
        workingBuffer.append(" ");
    if (info.targetTreeNode != 0)
    {
        workingBuffer.append(to_string(info.targetTreeNode->getKey()));
        if (info.targetTreeNode->getIdenticalSize() != 0)
        {
            workingBuffer.append("(");
            workingBuffer.append(to_string(info.targetTreeNode->getIdenticalSize()));
            workingBuffer.append(")");
        }
    }
    else
        workingBuffer.append(" ");

    size_t effectiveSize = workingBuffer.length() - levelBuffer.length();
    levelBuffer.append(workingBuffer.substr(levelBuffer.length(), effectiveSize));
}

void BSTRenderer::render(RedBlackTree& bst)
{
    int treeLevel = countLevel(bst);
    int childLevel = 1;//the current child level
    int pos = (1 + 2 * pow(2, treeLevel) - 1) / 2;// (first + last) / 2 for root level
    int posStep = 0;
    int stopCount = 0;
    BSTRenderInfo currentNode;

    if (treeLevel == -1)
    {
        cout << "empty tree" << endl;
        return;
    }
    initiateRenderQueue(pow(2, treeLevel + 1));
    enqueue(bst.getRoot(), 0, pos);
    stopCount++;
    //compute level 1 starting indent and step
    pos = pow(2, treeLevel - childLevel);
    posStep = pow(2, treeLevel - (childLevel - 1)) * 2 - pos - pos;

    while (!isEmpty)
    {
        if (dequeue(&currentNode))
        {
            //compute new indent if processing a new level
            if (currentNode.level + 1 != childLevel)
            {
                childLevel++;
                pos = pow(2, treeLevel - childLevel);
                posStep = pow(2, treeLevel - (childLevel - 1)) * 2 - pos - pos;
            }

            if (currentNode.targetTreeNode == 0)//is it empty node?
            {
                //yes, enqueue empty left and right child
                enqueue(0, childLevel, pos);
                pos += posStep;
                enqueue(0, childLevel, pos);
                pos += posStep;
            }
            else
            {
                //enqueue left
                if (currentNode.targetTreeNode->getLeft() != 0)
                {
                    enqueue(currentNode.targetTreeNode->getLeft(), childLevel, pos);
                    stopCount++;
                }
                else
                    enqueue(0, childLevel, pos);
                pos += posStep;

                //enqueue right
                if (currentNode.targetTreeNode->getRight() != 0)
                {
                    enqueue(currentNode.targetTreeNode->getRight(), childLevel, pos);
                    stopCount++;
                }
                else
                    enqueue(0, childLevel, pos);
                pos += posStep;
            }

            //render currentNode
            sendToBuffer(currentNode);

            if (currentNode.level > treeLevel)
                break;
        }
        else
        {
            cout << "BST renderer dequeue error!" << endl;
            cin.get();
            exit(0);
        }
    }
}