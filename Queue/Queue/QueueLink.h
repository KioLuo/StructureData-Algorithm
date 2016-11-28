#pragma once
#include "SLinkList.h"
using namespace std;

//单链表实现的队列
template<class T>
class Queue
{
public:
	Queue();
	Queue(const T& initData);
	~Queue();
public:
	bool EnQueue(const T& data);
	T DeQueue();
	T GetFront();
	T GetRear();
	void MakeEmpty();
	bool IsEmpty();
	int GetCount();
private:
	SLinkList<T> slist;
};

//单链表队列函数定义
template<class T>
inline Queue<T>::Queue() :slist()
{
}

template<class T>
inline Queue<T>::Queue(const T & initData) : slist(initData)
{
}

template<class T>
inline Queue<T>::~Queue()
{
}

template<class T>
bool Queue<T>::EnQueue(const T & data)
{
	slist.AddTail(data);
	return true;
}

template<class T>
T Queue<T>::DeQueue()
{
	T data = slist.GetHead();
	slist.DeleteHead();
	return data;
}

template<class T>
T Queue<T>::GetFront()
{
	T data = slist.GetHead();
	return data;
}

template<class T>
T Queue<T>::GetRear()
{
	T data;
	data = slist.GetTail();
	return data;
}

template<class T>
void Queue<T>::MakeEmpty()
{
	slist.Destroy();
}

template<class T>
bool Queue<T>::IsEmpty()
{
	return slist.IsEmpty();
}

template<class T>
int Queue<T>::GetCount()
{
	int count;
	count = slist.GetCount();
	return count;
}
