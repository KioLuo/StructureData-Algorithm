#pragma once
#include "SLinkList.h"

//����ջ����ģ�嶨��
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
	bool IsEmpty();		//�ж��Ƿ�Ϊ��ջ
	void MakeEmpty();		//���ջ
	int GetCount();		//����������Ŀ
	void Push(T data);		//��ջ
	int Pop(T& data);		//��ջ
	int Top(T& data);		//ȡջ��


private:
	SLinkList<T> m_linkList;
};

//��������
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
