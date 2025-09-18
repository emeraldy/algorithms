#include"Heap.h"
#include<iostream>
using namespace std;

/*Definition for HeapNode*/
HeapNode::HeapNode(int k)
{
    key = k;
    next = 0;
    previous = 0;
}

/*Definition for Heap*/
Heap::Heap()
{
    root = 0;
    size = 0;
    isMaxHeap = true;
}
Heap::~Heap()
{
    demolish();
}

void Heap::demolish()
{
    if (root != 0)
    {
        HeapNode* current = root;
        HeapNode* toDelete;

        //locate the last node
        while (current->next != 0)
            current = current->next;

        //delete from the last
        while (current->previous != 0)
        {
            toDelete = current;
            current = current->previous;

            delete toDelete;
        }

        delete current;//delete root
        current = 0;
        toDelete = 0;
        root = 0;
    }
}

void Heap::build(int keys[], int s, bool isMax)
{
    if (root != 0)
        demolish();

    size = s;
    isMaxHeap = isMax;
    HeapNode* current;
    //root node
    current = new HeapNode(keys[0]);
    root = current;

    //rest nodes
    for (int i = 1; i < s; i++)
    {
        current->next = new HeapNode(keys[i]);
        current->next->previous = current;
        current = current->next;
    }

    //maintain heap property
    for (int i = size / 2; i >= 1; i--)
        heapify(i);
}

bool Heap::getHeapType()
{
    return isMaxHeap;
}

int Heap::getSize()
{
    return size;
}

int Heap::getKey(int index)
{
    if (index < 1 || index > size)
    {
        cout << "index out of bound" << endl;
        return index;
    }
    else
    {
        HeapNode* current = root;
        for (int i = 1; i < index; i++)//heap index starting with 1
            current = current->next;

        return current->key;
    }
}

void Heap::setKey(int index, int k)
{
    if (index < 1 || index > size)
    {
        cout << "index out of bound" << endl;
    }
    else
    {
        HeapNode* current = root;
        int oldKey;
        for (int i = 1; i < index; i++)//heap index starting with 1
            current = current->next;
        oldKey = current->key;
        current->key = k;

        //check and maintain the heap property from this node's parent upward to root
        HeapNode* p;
        int pindex = index / 2, swapping;
        p = parent(index);
        if (isMaxHeap)
        {
            if (k > oldKey)//increasing key case
            {
                while (pindex >= 1)
                {
                    if (current->key > p->key)
                    {
                        swapping = p->key;
                        p->key = current->key;
                        current->key = swapping;

                        //save current index and node
                        swapping = pindex;
                        current = p;
                        //compute parent of an elder generation
                        pindex /= 2;
                        p = parent(swapping);
                    }
                    else
                        break;
                }
            }
            else if (k < oldKey)//decreasing key case
                heapify(index);
        }
        else//is a min heap
        {
            if (k < oldKey)//decreasing key case
            {
                while (pindex >= 1)
                {
                    if (current->key < p->key)
                    {
                        swapping = p->key;
                        p->key = current->key;
                        current->key = swapping;

                        //save current index and node
                        swapping = pindex;
                        current = p;
                        //compute parent of an elder generation
                        pindex /= 2;
                        p = parent(swapping);
                    }
                    else
                        break;
                }
            }
            else if (k > oldKey)//increasing key case
                heapify(index);
        }
    }
}

void Heap::printKeys()
{
    HeapNode* current = root;
    for (int i = 1; i < size; i++)
    {
        cout << current->key << ",";
        current = current->next;
    }
    cout << current->key << endl;
}

HeapNode* Heap::parent(int index)
{
    if (index < 1 || index > size)
    {
        cout << "index out of bound" << endl;
        return 0;
    }
    else if (index == 1)
    {
        cout << "root has no parent" << endl;
        return 0;
    }
    else
    {
        HeapNode* current = root;
        for (int i = 1; i < index / 2; i++)//heap index starting with 1
            current = current->next;

        return current;
    }
}

HeapNode* Heap::left(int index)
{
    if (index < 1 || index > size)
    {
        cout << "index out of bound" << endl;
        return 0;
    }
    else if (index > size / 2)
    {
        cout << "leaf has no child" << endl;
        return 0;
    }
    else
    {
        HeapNode* current = root;
        for (int i = 1; i < index * 2; i++)//heap index starting with 1
            current = current->next;

        return current;
    }
}

HeapNode* Heap::right(int index)
{
    if (index < 1 || index > size)
    {
        cout << "index out of bound" << endl;
        return 0;
    }
    else if (index > size / 2)
    {
        cout << "leaf has no child" << endl;
        return 0;
    }
    else
    {
        HeapNode* current = root;
        for (int i = 1; i < index * 2 + 1; i++)//heap index starting with 1
            current = current->next;

        return current;
    }
}

void Heap::heapify(int index)
{
    HeapNode* l, * r, * current;
    int lIndex, rIndex, largestIndex, swapping;

    lIndex = index * 2;
    rIndex = index * 2 + 1;
    largestIndex = index;
    if (index < 1 || index > size || (lIndex > size && rIndex > size))//invalid index or leaf
        return;
    //locate current node and its children
    l = left(index);
    r = right(index);//it is possible that right child doesn't exist!!!
    current = root;
    for (int i = 1; i < index; i++)//heap index starting with 1
        current = current->next;

    if (isMaxHeap)
    {
        if (l->key >= current->key)
        {
            if (r == 0 || (r != 0 && l->key >= r->key))//if right child doesn't exist or it exists but less than left
            {
                swapping = current->key;
                current->key = l->key;
                l->key = swapping;
                largestIndex = lIndex;
            }
            else
            {
                swapping = current->key;
                current->key = r->key;
                r->key = swapping;
                largestIndex = rIndex;
            }
        }
        else//left key < current key
        {
            if (r != 0 && current->key < r->key)
            {
                swapping = current->key;
                current->key = r->key;
                r->key = swapping;
                largestIndex = rIndex;
            }
        }
        if (largestIndex != index)//there was key swapping
            heapify(largestIndex);
    }
    else//is a min heap
    {
        if (l->key <= current->key)
        {
            if (r == 0 || (r != 0 && l->key <= r->key))
            {
                swapping = current->key;
                current->key = l->key;
                l->key = swapping;
                largestIndex = lIndex;//should've been named smallest but just borrow the variable here
            }
            else
            {
                swapping = current->key;
                current->key = r->key;
                r->key = swapping;
                largestIndex = rIndex;
            }
        }
        else//left key > current key
        {
            if (r != 0 && current->key > r->key)
            {
                swapping = current->key;
                current->key = r->key;
                r->key = swapping;
                largestIndex = rIndex;
            }
        }
        if (largestIndex != index)//there was key swapping
            heapify(largestIndex);
    }
}

int Heap::extractRoot()
{
    int rootKey = root->key;

    //locate the last node
    HeapNode* current = root;
    while (current->next != 0)
        current = current->next;

    //swap the last node's key with root key
    root->key = current->key;

    //delete the last node and maintain heap property
    if (size == 1)//only root node remaining
    {
        current = 0;
        delete root;
        root = 0;
        size--;
    }
    else
    {
        current->previous->next = 0;
        delete current;
        current = 0;
        size--;
        heapify(1);
    }

    return rootKey;
}

void Heap::append(int k)
{
    //locate the last node
    HeapNode* current = root;
    while (current->next != 0)
        current = current->next;

    //append a new node
    if (isMaxHeap)
        current->next = new HeapNode(-2147483648);//least number of an int
    else
        current->next = new HeapNode(2147483647);//greatest number of an int
    current->next->previous = current;
    size++;

    //update its key to the desired one
    setKey(size, k);
}