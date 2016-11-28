#pragma once
#include <cassert>

const int MinQueueSize = 5;
const int MaxQueueSize = 500;

//利用数组实现的循环队列
template<class T>
class QueueArray
{
public:
	QueueArray(int maxSize = MaxQueueSize);
	QueueArray(const QueueArray<T>& other);
	QueueArray<T>& operator=(const QueueArray<T>& other);
	~QueueArray();
public:
	bool IsEmpty();
	bool IsFull();
	int GetCount();
	T GetFront();
	T GetRear();
	void MakeEmpty();
	bool EnQueue(const T& data);
	T DeQueue();
private:
	int capacity;
	int front;
	int rear;
	int size;
	T* m_array;
};

template<class T>
inline QueueArray<T>::QueueArray(int maxSize) :capacity(maxSize), front(1), rear(0), size(0), m_array(NULL)
{
	assert(capacity >= MinQueueSize);
	try
	{
		m_array = new T[capacity];
	}
	catch (std::bad_alloc&)
	{
	}
}

template<class T>
inline QueueArray<T>::QueueArray(const QueueArray<T>& other) :
{

}
