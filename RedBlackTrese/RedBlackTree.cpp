#include"RedBlackTree.h"
#include<iostream>
using namespace std;

/*Definitions for RedBlackTreeNode*/
RedBlackTreeNode::RedBlackTreeNode(int k)
{
	key = k;

	parent = 0;
	left = 0;
	right = 0;
	identical = 0;
	identicalSize = 0;
	isRed = true;
}

/*Definitions for RedBlackTree*/
RedBlackTree::RedBlackTree()
{
	keyNumber = 0;
	nodeNumber = 0;
	root = 0;
}

RedBlackTree::~RedBlackTree()
{
	demolish(root);
}

void RedBlackTree::insert(int k)
{
	if (root == 0)
	{
		root = new RedBlackTreeNode(k);
		nodeNumber++;
	}
	else
	{
		RedBlackTreeNode * current =  root;
		RedBlackTreeNode * previous = current->parent;
		RedBlackTreeNode * identityPointer = 0;
		int branch = -1;//0:left, 1:right, 2:identical

		while (current != 0)
		{
			if (k < current->key)//left
			{
				previous = current;
				branch = 0;
				current = current->left;
			}
			else if (k > current->key)//right
			{
				previous = current;
				branch = 1;
				current = current->right;
			}
			else//identical
			{
				branch = 2;
				break;//while (current != 0)
			}
		}

		//insert the new key
		switch (branch)
		{
			case 0://left
				previous->left = new RedBlackTreeNode(k);
				previous->left->parent = previous;
				nodeNumber++;
				break;
			case 1://right
				previous->right = new RedBlackTreeNode(k);
				previous->right->parent = previous;
				nodeNumber++;
				break;
			case 2:
				//attach the new key to the identical list
				identityPointer = current;
				(current->identicalSize)++;
				while (identityPointer->identical != 0)//loop till the end
					identityPointer = identityPointer->identical;

				//append the new identical node
				identityPointer->identical = new RedBlackTreeNode(k);
				identityPointer->identical->parent = identityPointer;
				break;
		}
	}
	keyNumber++;//don't forget to increase the total key number
}

void RedBlackTree::insertFix(RedBlackTreeNode* target)
{

}

/*cases for deletion are based on the children of the node to be delete (hereby denoted z):
  1. no children -> just delete it
  2. one child -> replace z with that child
  3. two children -> the gist is to use z's successor (hereby denoted s) to replace z. some
     facts first in this case: a). s must be in the right subtree; b). s does not have left
	 subtree. now, if s is z's right child, replace z with s directly. if s is somewhere in
	 the right subtree, we need to extract s and then replace it with z.
*/
void RedBlackTree::deleteKey(RedBlackTreeNode* z)
{
	if (z == 0)
		return;

	//case 2 left
	if (z->left != 0 && z->right == 0)
	{
	    z->left->parent = z->parent;
		if (z == root)
			root = z->left;
		else
		{
			if (z->parent->left == z)
			{
				z->parent->left = z->left;
			}
			else
			{
				z->parent->right = z->left;
			}
		}
	}

	//case 2 right
	if (z->left == 0 && z->right != 0)
	{
	    z->right->parent = z->parent;
		if (z == root)
			root = z->right;
		else
		{
			if (z->parent->left == z)
			{
				z->parent->left = z->right;
			}
			else
			{
				z->parent->right = z->right;
			}
		}
	}

	//case 3
	if (z->left != 0 && z->right != 0)
	{
		RedBlackTreeNode* s = const_cast<RedBlackTreeNode*>(getSuccessor(z));
		if (s == z->right)
		{
			//build a new subtree whose root is s
			s->left = z->left;
			z->left->parent = s;
			s->parent = z->parent;
			
			//attach the new subtree to z's parent
			if (z == root)
				root = s;
			else
			{
				if (z->parent->left == z)
				{
					z->parent->left = s;
				}
				else
				{
					z->parent->right = s;
				}
			}
		}
		else //s is not z's immediate right child
		{
			//extract s from the subtree it belongs to
			if (s->right != 0)
				s->right->parent = s->parent;
			
			s->parent->left = s->right;

			//build a new subtree whose root is s
			s->left = z->left;
			z->left->parent = s;
			s->right = z->right;
			z->right->parent = s;
			s->parent = z->parent;
			
			//attach the new subtree to z's parent
			if (z == root)
				root = s;
			else
			{
				if (z->parent->left == z)
				{
					z->parent->left = s;
				}
				else
				{
					z->parent->right = s;
				}
			}
		}
	}

	//first, delete identical list in z, if any
	RedBlackTreeNode* idenDel;
	if (z->identicalSize != 0)
	{
	    idenDel = z->identical;
		while (z->identical != 0)
		{
			z->identical = z->identical->identical;
			delete idenDel;
			idenDel = z->identical;
		}
		keyNumber = keyNumber - z->identicalSize - 1;//subtract all identical and z itself
	}
	else
		keyNumber--;
	nodeNumber--;//but either case, node number less 1
	idenDel = 0;

	delete z;
	z = 0;
	if (keyNumber == 0)
		root = 0;
}

const RedBlackTreeNode* RedBlackTree::findKey(int k)
{
	RedBlackTreeNode * current =  root;
	while (current != 0)
	{
		if (k < current->key)
			current = current->left;
		else if (k > current->key)
			current = current->right;
		else
			return current;
	}

	//not found
	return 0;
}

//print left -> root -> right
void RedBlackTree::inOrderWalk(RedBlackTreeNode const* rootNode)
{
	if (rootNode != 0)
	{
		inOrderWalk(rootNode->left);
		if (rootNode->identicalSize != 0)
		{
			cout << rootNode->key;
			cout << " (" << rootNode->identicalSize << " more)" << endl;
		}
		else
			cout << rootNode->key << endl;
		inOrderWalk(rootNode->right);
	}
}

const RedBlackTreeNode* RedBlackTree::getMax(const RedBlackTreeNode* rootNode)
{
	const RedBlackTreeNode* current = rootNode;
	if (current == 0)
		return 0;

	while (current->right != 0)
	{
		current = current->right;
	}
	return current;
}

const RedBlackTreeNode* RedBlackTree::getMin(const RedBlackTreeNode* rootNode)
{
	const RedBlackTreeNode* current = rootNode;
	if (current == 0)
		return 0;

	while (current->left != 0)
	{
		current = current->left;
	}
	return current;
}

const RedBlackTreeNode* RedBlackTree::getSuccessor(const RedBlackTreeNode* node)
{
	if (node->right != 0)
		return getMin(node->right);

	const RedBlackTreeNode* current = node;
	while (current->parent != 0)
	{
		if (current->parent->left == current)
			return current->parent;
		current = current->parent;
	}

	return 0;
}

const RedBlackTreeNode* RedBlackTree::getPredecessor(const RedBlackTreeNode* node)
{
	if (node->left != 0)
		return getMax(node->left);

	const RedBlackTreeNode* current = node;
	while (current->parent != 0)
	{
		if (current->parent->right == current)
			return current->parent;
		current = current->parent;
	}

	return 0;
}

void RedBlackTree::demolish(RedBlackTreeNode* rootNode)
{
	if (rootNode != 0)
	{
		demolish(rootNode->getLeft());
		demolish(rootNode->getRight());

		//delete current node
		//identical chain first, if any
		RedBlackTreeNode* delPointer;
		while (rootNode->identical != 0)
		{
			delPointer = rootNode->identical;
			//all are going to be deleted so no need to update parents here
			/*if (delPointer->identical != 0)
				delPointer->identical->parent = rootNode;
			*/
			rootNode->identical = delPointer->identical;
			delete delPointer;
		}
		//now current node
		delete rootNode;
	}
}

bool RedBlackTree::leftRotateOn(RedBlackTreeNode* pivot)
{
	RedBlackTreeNode* rightChild = pivot->right;
	if (rightChild != 0)
	{
		if (pivot->parent != 0)
		{
			if (pivot->parent->left == pivot)//pivot is left child
			{
				pivot->parent->left = rightChild;
			}
			else//pivot is right child
			{
				pivot->parent->right = rightChild;
			}
			pivot->right = rightChild->left;
			rightChild->left = pivot;
			
			rightChild->parent = pivot->parent;
			pivot->parent = rightChild;
		}
		else//pivot is root
		{
			root = rightChild;
			pivot->right = rightChild->left;
			rightChild->left = pivot;

			rightChild->parent = 0;
			pivot->parent = rightChild;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool RedBlackTree::rightRotateOn(RedBlackTreeNode* pivot)
{
	RedBlackTreeNode* leftChild = pivot->left;
	if (leftChild != 0)
	{
		if (pivot->parent != 0)
		{
			if (pivot->parent->left == pivot)//pivot is left child
			{
				pivot->parent->left = leftChild;
			}
			else//pivot is right child
			{
				pivot->parent->right = leftChild;
			}
			pivot->left = leftChild->right;
			leftChild->right = pivot;
			
			leftChild->parent = pivot->parent;
			pivot->parent = leftChild;
		}
		else//pivot is root
		{
			root = leftChild;
			pivot->left = leftChild->right;
			leftChild->right = pivot;

			leftChild->parent = 0;
			pivot->parent = leftChild;
		}
		return true;
	}
	else
	{
		return false;
	}
}