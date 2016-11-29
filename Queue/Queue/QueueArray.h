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
	bool IsEmpty() const;
	bool IsFull() const;
	int GetCount() const;
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
inline QueueArray<T>::QueueArray(const QueueArray<T>& other) :capacity(other.capacity), front(other.front), rear(other.rear), size(otehr.size), m_array(NULL)
{
	if (capacity > 0)
	{
		try
		{
			m_array = new T[capacity];
		}
		catch (std::bad_alloc&)
		{
		}
		for (int i = 0; i < capacity; i++)
		{
			m_array[i] = other.m_array[i];
		}
	}

}

template<class T>
inline QueueArray<T>& QueueArray<T>::operator=(const QueueArray<T>& other)
{
	if (this == &other)
	{
		return *this;
	}
	if (m_array != NULL)
	{
		delete[]m_array;
		m_array = NULL;
	}
	capacity = other.capacity;
	front = other.front;
	rear = other.rear;
	size = other.size;
	if (capacity > 0)
	{
		try
		{
			m_array = new T[capacity];
		}
		catch (std::bad_alloc&)
		{
		}
		for (int i = 0; i < capacity; i++)
		{
			m_array[i] = other.m_array[i];
		}
	}
	return *this;
}

template<class T>
inline QueueArray<T>::~QueueArray()
{
	if (m_array)
	{
		delete[]m_array;
	}
}

template<class T>
inline bool QueueArray<T>::IsEmpty() const
{
	return 0 == size;
}

template<class T>
inline bool QueueArray<T>::IsFull() const
{
	return capacity == size;
}

template<class T>
inline int QueueArray<T>::GetCount() const
{
	return size;
}

template<class T>
inline T QueueArray<T>::GetFront()
{
	assert(0 != size);
	return m_array[front];
}

template<class T>
inline T QueueArray<T>::GetRear()
{
	assert(0 != size);
	return m_array[rear];
}

template<class T>
inline void QueueArray<T>::MakeEmpty()
{
	rear = 0;
	front = 1;
	size = 0;
}

template<class T>
inline bool QueueArray<T>::EnQueue(const T & data)
{
	if (size < capacity)
	{
		rear = (rear + 1) % capacity;
		m_array[rear] = data;
		size++;
		return true;
	}
	else
	{
		return false;
	}

}

template<class T>
inline T QueueArray<T>::DeQueue()
{
	assert(!IsEmpty());
	T data;
	data = m_array[front];
	front = (front + 1) % capacity;
	size--;
	return data;
}
