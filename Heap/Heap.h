#pragma once

/*heap node index starts with 1*/

class Heap;
class HeapNode
{
	friend class Heap;
	private:
		HeapNode* next;
		HeapNode* previous;
		int key;

		HeapNode(int k);
		~HeapNode() {};
};

class Heap
{
	private:
		HeapNode* root;
		int size;
		bool isMaxHeap;//either max heap or min heap

		void heapify(int index);
		void demolish();

	public:
		Heap();
		~Heap();

		HeapNode* parent(int index);
		HeapNode* left(int index);
		HeapNode* right(int index);

		void build(int keys[], int s, bool isMax);
		bool getHeapType();
		int  getSize();
		int  getKey(int index);
		void setKey(int index, int k);
		void printKeys();
		int  extractRoot();
		void append(int k);
};
