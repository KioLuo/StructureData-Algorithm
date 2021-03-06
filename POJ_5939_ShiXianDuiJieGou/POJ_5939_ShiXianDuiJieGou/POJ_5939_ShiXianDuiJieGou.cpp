// POJ_5939_ShiXianDuiJieGou.cpp : 定义控制台应用程序的入口点。
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
	heapArray[j] = temp;
}

template<class T>
inline void MinHeap<T>::buildHeap()
{
	for (int i = currentSize / 2 - 1; i >= 0; i--)
	{
		siftDown(i);
	}
}



int main()
{
	int nGroup;
	cin >> nGroup;
	for (int i = 0; i < nGroup; i++)
	{
		MinHeap<int> minHeap(100010);
		int nActions;
		cin >> nActions;
		int choice[2];
		for (int j = 0; j < nActions; j++)
		{
			cin >> choice[0];
			if (choice[0] == 1)
			{
				cin >> choice[1];
				minHeap.insert(choice[1]);
			}
			else if (choice[0] == 2)
			{
				cout << minHeap.removeMin() << endl;
			}
		}
	}
    return 0;
}

