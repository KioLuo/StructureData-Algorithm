#pragma once
#include <iostream>
using namespace std;

//��С����ģ�嶨��
template<class T>
class MinHeap
{

private:

	T* heapArray;		//��Ŷ����ݵ�����
	int maxSize;		//���������ɵ����Ԫ����Ŀ
	int currentSize;		//���е�ǰԪ����Ŀ
	void buildHeap();		//����

public:

	MinHeap(int n);			//�������������ĿΪn�Ķ�
	virtual ~MinHeap() { delete[] heapArray; };		//����������
	void createHeap();		//������С��
	bool isLeaf(int pos) const;		//�ж��Ƿ�ΪҶ���
	int leftChild(int pos) const;		//��������λ��
	int rightChild(int pos) const;		//�����Һ���λ��
	int parent(int pos) const;		//���ظ��ڵ�λ��
	bool remove(int pos, T& node);		//ɾ�������±��Ԫ��
	bool insert(const T& newNode);		//������Ԫ��
	T removeMin();		//ɾ����СԪ��
	void siftUp(int pos);		//��posλ�ÿ�ʼ���ϵ�����ʹ���г�Ϊ��
	void siftDown(int pos);		//��posλ�ÿ�ʼ���µ����������г�Ϊ��
	void printHeap();		//��ӡ��Ԫ��
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
