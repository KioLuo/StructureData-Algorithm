// POJ_5941_HuffmanBianMaShu.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//最小堆类模板定义
template<class T>
class MinHeap
{

private:

	T* heapArray;		//存放堆数据的数组
	int maxSize;		//堆所能容纳的最大元素数目
	int currentSize;		//堆中当前元素数目
	void buildHeap();		//建堆

public:

	MinHeap(int n);			//构造最大容纳数目为n的堆
	virtual ~MinHeap() { delete[] heapArray; };		//虚析构函数
	void createHeap();		//创建最小堆
	bool isLeaf(int pos) const;		//判断是否为叶结点
	int leftChild(int pos) const;		//返回左孩子位置
	int rightChild(int pos) const;		//返回右孩子位置
	int parent(int pos) const;		//返回父节点位置
	bool remove(int pos, T& node);		//删除给定下标的元素
	bool insert(const T& newNode);		//插入新元素
	T removeMin();		//删除最小元素
	void siftUp(int pos);		//从pos位置开始向上调整，使序列成为堆
	void siftDown(int pos);		//从pos位置开始向下调整，是序列成为堆
	void printHeap();		//打印堆元素
};

template<class T>
inline MinHeap<T>::MinHeap(int n)
{
	heapArray = new T[n];
	maxSize = n;
	currentSize = 0;
}

template<class T>
inline void MinHeap<T>::createHeap()
{
	T temp;
	while (cin >> temp && currentSize < maxSize)
	{
		heapArray[currentSize++] = temp;
	}
	buildHeap();
}

template<class T>
inline bool MinHeap<T>::isLeaf(int pos) const
{
	if (pos > currentSize / 2 - 1)
	{
		return true;
	}
	return false;
}

template<class T>
inline int MinHeap<T>::leftChild(int pos) const
{
	int leftchild = -1;
	if (pos > currentSize / 2 - 1)
	{
		cout << "No left child" << endl;
	}
	else
	{
		leftchild = 2 * pos + 1;
	}
	return leftchild;
}

template<class T>
inline int MinHeap<T>::rightChild(int pos) const
{
	int rightchild = -1;
	if (pos < (currentSize - 1) / 2)
	{
		rightchild = 2 * pos + 2;
	}
	else
	{
		cout << "No right child" << endl;
	}
	return rightchild;
}

template<class T>
inline int MinHeap<T>::parent(int pos) const
{
	int parent;
	if (pos == 0)
	{
		cout << "No parent" << endl;
		parent = -1;
	}
	else if (pos % 2 == 0)
	{
		parent = pos / 2 - 1;
	}
	else if (pos % 2 != 0)
	{
		parent = (pos + 1) / 2 - 1;
	}
	return parent;
}

template<class T>
inline bool MinHeap<T>::remove(int pos, T & node)
{
	if (pos < 0 || pos >= currentSize)
	{
		return false;
	}
	T temp = heapArray[pos];
	heapArray[pos] = heapArray[--currentSize];
	if (pos == 0)
	{
		siftDown(pos);
	}
	else if (heapArray[pos] < heapArray[parent(pos)])
	{
		siftUp(pos);
	}
	else
	{
		siftDown(pos);
	}
	node = temp;
	return true;
}

template<class T>
inline bool MinHeap<T>::insert(const T & newNode)
{
	if (currentSize == maxSize)
	{
		return false;
	}
	heapArray[currentSize] = newNode;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template<class T>
inline T MinHeap<T>::removeMin()
{
	T ret;
	if (currentSize != 0)
	{
		remove(0, ret);
	}
	return ret;
}

template<class T>
inline void MinHeap<T>::siftUp(int pos)
{
	int tempPos = pos;
	T temp = heapArray[tempPos];
	while (tempPos > 0 && temp < heapArray[parent(tempPos)])
	{
		heapArray[tempPos] = heapArray[parent(tempPos)];
		tempPos = parent(tempPos);
	}
	heapArray[tempPos] = temp;
}

template<class T>
inline void MinHeap<T>::siftDown(int pos)
{
	int i = pos;
	int j = 2 * i + 1;
	T temp = heapArray[i];

	while (j < currentSize)
	{
		if (j < currentSize - 1 && heapArray[j] > heapArray[j + 1])
		{
			j++;
		}
		if (temp > heapArray[j])
		{
			heapArray[i] = heapArray[j];
			i = j;
			j = 2 * i + 1;
		}
		else break;
	}
	heapArray[i] = temp;
}

template<class T>
inline void MinHeap<T>::printHeap()
{
	for (int i = 0; i < currentSize; i++)
	{
		cout << heapArray[i] << endl;
	}
}

template<class T>
inline void MinHeap<T>::buildHeap()
{
	for (int i = currentSize / 2 - 1; i >= 0; i--)
	{
		siftDown(i);
	}
}



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
	void outRouteLength(HuffmanTreeNode<T>* node, int& len);
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
	for (int i = 0; i < len; i++)
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
inline void HuffmanTree<T>::outRouteLength(HuffmanTreeNode<T>* node, int& len)
{
	if (node != NULL)
	{
		if (node->isLeaf())
		{
			int nodeLen = 0;
			getRouteLength(node, root, nodeLen);
			len += (node->getInfo() * nodeLen);
		}
		outRouteLength(node->getLeft(), len);
		outRouteLength(node->getRight(), len);
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


//主函数
int main()
{
	int nGroup;
	cin >> nGroup;
	for (int i = 0; i < nGroup; i++)
	{
		int weight[110], weightLen, outRouteLen = 0;
		cin >> weightLen;
		for (int i = 0; i < weightLen; i++)
		{
			cin >> weight[i];
		}
		HuffmanTree<int> huffTree(weight, 1000, weightLen);
		huffTree.outRouteLength(huffTree.getRoot(), outRouteLen);
		cout << outRouteLen << endl;
	}
    return 0;
}

