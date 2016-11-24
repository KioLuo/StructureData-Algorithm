#pragma once
#include "SLinkList.h"

//链表栈的类模板定义
template<class T>
class Stack
{
public:

	Stack()
	{
	}

	Stack(T initData);

	~Stack()
	{
	}
public:
	bool IsEmpty();		//判断是否为空栈
	void MakeEmpty();		//清空栈
	int GetCount();		//返回数据数目
	void Push(T data);		//入栈
	int Pop(T& data);		//出栈
	int Top(T& data);		//取栈顶


private:
	SLinkList<T> m_linkList;
};

//函数定义
template<class T>
inline Stack<T>::Stack(T initData):m_linkList(initData)
{
}

template<class T>
inline bool Stack<T>::IsEmpty()
{
	if (m_linkList.IsEmpty())
		return true;
	else
		return false;
}

template<class T>
inline void Stack<T>::MakeEmpty()
{
	m_linkList.Destroy();
}

template<class T>
inline int Stack<T>::GetCount()
{
	return m_linkList.GetCount();
}

template<class T>
inline void Stack<T>::Push(T data)
{
	m_linkList.AddHead(data);
}

template<class T>
inline int Stack<T>::Pop(T & data)
{
	if (IsEmpty())
		return 0;
	Top(data);
	m_linkList.DeleteHead();
	return 1;
}

template<class T>
inline int Stack<T>::Top(T & data)
{
	if (IsEmpty())
		return 0;
	data = m_linkList.GetHead();
	return 1;
}
