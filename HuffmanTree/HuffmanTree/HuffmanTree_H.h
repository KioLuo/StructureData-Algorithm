#pragma once
#include "MinHeap.h"
#include <iostream>
using namespace std;

template<class T> class HuffmanTree;

//HuffmanTreeNode类模板定义
template<class T>
class HuffmanTreeNode
{
	friend class HuffmanTree<T>;
private:
	T info;
	HuffmanTreeNode<T>* left;
	HuffmanTreeNode<T>* right;

public:
	HuffmanTreeNode()
	{
		left = NULL;
		right = NULL;
	};
	HuffmanTreeNode(T val)
	{
		info = val;
		left = NULL;
		right = NULL;
	};
	~HuffmanTreeNode() {};

public:
	T getInfo() const;
	HuffmanTreeNode<T>* getLeft();
	HuffmanTreeNode<T>* getRight();
	void setLeft(HuffmanTreeNode<T>* leftchild);
	void setRight(HuffmanTreeNode<T>* rightchild);
	void setInfo(const T& val);
	bool isLeaf() const;
	bool operator<(const HuffmanTreeNode<T>& node);
	bool operator>(const HuffmanTreeNode<T>& node);
	HuffmanTreeNode<T> operator=(const HuffmanTreeNode<T>& node);
	
};

//HuffmanTree类模板定义
template<class T>
class HuffmanTree
{
private:
	HuffmanTreeNode<T>* root;
	void mergeTree(HuffmanTreeNode<T>* ht1, HuffmanTreeNode<T>* ht2, HuffmanTreeNode<T>* parent);

public:
	HuffmanTree(T weight[], int n, int len);
	virtual ~HuffmanTree() { deleteTree(root); };
	void deleteTree(HuffmanTreeNode<T>* node);
	void preTravel(HuffmanTreeNode<T>* node);
	int getRouteLength(HuffmanTreeNode<T>* node, HuffmanTreeNode<T>* root, T& len);
	HuffmanTreeNode<T>* getRoot();
};


//HuffmanTree函数定义
template<class T>
inline void HuffmanTree<T>::mergeTree(HuffmanTreeNode<T>* ht1, HuffmanTreeNode<T>* ht2, HuffmanTreeNode<T>* parent)
{
	if (parent != NULL)
	{
		parent->setLeft(ht1);
		parent->setRight(ht2);
		parent->setInfo(ht1->getInfo() + ht2->getInfo());
	}
}

template<class T>
inline HuffmanTree<T>::HuffmanTree(T weight[], int n, int len)
{
	MinHeap<HuffmanTreeNode<T>> heap(n);
	HuffmanTreeNode<T>* nodeList = new HuffmanTreeNode<T>[len];
	for (int i = 0; i < len ; i++)
	{
		nodeList[i].setInfo(weight[i]);
		heap.insert(nodeList[i]);
	}

	HuffmanTreeNode<T> *parent, *leftChild, *rightChild;
	for (int i = 0; i < len - 1; i++)
	{
		parent = new HuffmanTreeNode<T>;
		leftChild = new HuffmanTreeNode<T>;
		rightChild = new HuffmanTreeNode<T>;
		*leftChild = heap.removeMin();
		*rightChild = heap.removeMin();
		mergeTree(leftChild, rightChild, parent);
		heap.insert(*parent);
		root = parent;
	}
	delete[] nodeList;
}

template<class T>
inline void HuffmanTree<T>::deleteTree(HuffmanTreeNode<T>* node)
{
	if (node != NULL)
	{
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
		delete node;
	}
}

template<class T>
inline void HuffmanTree<T>::preTravel(HuffmanTreeNode<T>* node)
{
	if (node != NULL)
	{
		cout << node->getInfo() << endl;
		preTravel(node->getLeft());
		preTravel(node->getRight());
	}
}

template<class T>
inline int HuffmanTree<T>::getRouteLength(HuffmanTreeNode<T>* node, HuffmanTreeNode<T>* root, T& len)
{
	int flag = 0;
	if (root != NULL)
	{
		if (node == root)
		{
			len += 0;
			flag = 1;
		}
		else
		{
			len++;
			if (flag = getRouteLength(node, root->getLeft(), len))
			{
			}
			else
			{
				if (!(flag = getRouteLength(node, root->getRight(), len)))
				{
					len--;
				}
			}
		}
	}
	return flag;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTree<T>::getRoot()
{
	return root;
}

//HuffmanTreeNode函数定义
template<class T>
inline T HuffmanTreeNode<T>::getInfo() const
{
	return info;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTreeNode<T>::getLeft()
{
	return left;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTreeNode<T>::getRight()
{
	return right;
}

template<class T>
inline void HuffmanTreeNode<T>::setLeft(HuffmanTreeNode<T>* leftchild)
{
	left = leftchild;
}

template<class T>
inline void HuffmanTreeNode<T>::setRight(HuffmanTreeNode<T>* rightchild)
{
	right = rightchild;
}

template<class T>
inline void HuffmanTreeNode<T>::setInfo(const T & val)
{
	info = val;
}

template<class T>
inline bool HuffmanTreeNode<T>::isLeaf() const
{
	if (left == NULL && right == NULL)
	{
		return true;
	}
	return false;
}

template<class T>
inline bool HuffmanTreeNode<T>::operator<(const HuffmanTreeNode<T>& node)
{
	if (this->getInfo() < node.getInfo())
	{
		return true;
	}
	else {
		return false;
	}
}

template<class T>
inline bool HuffmanTreeNode<T>::operator>(const HuffmanTreeNode<T>& node)
{
	if (this->getInfo() > node.getInfo())
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
inline HuffmanTreeNode<T> HuffmanTreeNode<T>::operator=(const HuffmanTreeNode<T>& node)
{
	info = node.info;
	left = node.left;
	right = node.right;
	return *this;
}
