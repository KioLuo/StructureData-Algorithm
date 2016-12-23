#pragma once
#include "MinHeap.h"

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
	HuffmanTreeNode<T>* getLeft() const;
	HuffmanTreeNode<T>* getRight() const;
	void setLeft(HuffmanTreeNode<T>* leftchild);
	void setRight(HuffmanTreeNode<T>* rightchild);
	void setInfo(const T& val);
	
};

//HuffmanTree类模板定义
template<class T>
class HuffmanTree
{
private:
	HuffmanTreeNode<T>* root;
	void mergeTree(HuffmanTreeNode<T>& ht1, HuffmanTreeNode<T>& ht2, HuffmanTreeNode* parent);

public:
	HuffmanTree(T weight[], int n);
	virtual ~HuffmanTree() { deleteTree(root); };

};


//HuffmanTreeNode函数定义
template<class T>
inline T HuffmanTreeNode<T>::getInfo() const
{
	return info;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTreeNode<T>::getLeft() const
{
	return left;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTreeNode<T>::getRight() const
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

//HuffmanTree函数定义
template<class T>
inline void HuffmanTree<T>::mergeTree(HuffmanTreeNode<T>& ht1, HuffmanTreeNode<T>& ht2, HuffmanTreeNode<T>* parent)
{
	if (parent != NULL)
	{
		parent->setLeft(&ht1);
		parent->setRight(&ht2);
		parent->setInfo(ht1.getInfo() + ht2.getInfo());
	}
}

template<class T>
inline HuffmanTree<T>::HuffmanTree(T weight[], int n)
{
	MinHeap<HuffmanTreeNode<T>> heap(n);
	HuffmanTreeNode<T>* nodeList = new HuffmanTreeNode<T>[n];
	for (int i = 0; i < n; i++)
	{
		nodeList[i].setInfo(weight[i]);
		heap.insert(nodeList[i]);
	}
	
	HuffmanTreeNode<T> *parent, leftChild, rightChild;
	for (int i = 0; i < n - 1; i++)
	{
		parent = new HuffmanTreeNode<T>;
		leftChild = heap.removeMin();
		rightChild = heap.removeMin();
		mergeTree(leftChild, rightChild, parent);
		heap.insert(*parent);
		root = parent;
	}
	delete[] nodeList;
}
