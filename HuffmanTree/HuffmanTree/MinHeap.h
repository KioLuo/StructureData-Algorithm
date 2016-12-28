#pragma once
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
