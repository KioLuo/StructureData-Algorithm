// ChuZhanXuLieTongJi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//��������ģ��
template <class T>
class Node
{
public:
	Node() {}
	Node(T d) :data(d), next(NULL) {}
	~Node() {}
	T data;
	Node<T>* next;
};

//���嵥������ģ��
template <class T>
class SLinkList
{
public:
	SLinkList();
	SLinkList(T initData);
	~SLinkList();
public:
	void Insert(T aData, T bData);		//�����½ڵ�
	void AddHead(T data);		//�����½ڵ���Ϊ����ͷ
	T GetHead();		//�������ͷ����
	void DeleteHead();		//ɾ������ͷ�ڵ����ݣ���һ�����Ϊ�±�ͷ
	void Delete(T data);		//ɾ���ض����ݵĽ��
	Node<T>* Search(T data);		//�����������ض����ݵĽ��
	void Destroy();		//�����������
	void OutPutList();		//�����������
	bool IsEmpty();		//�Ƿ�Ϊ������
	int GetCount();		//���ؽ����Ŀ
private:
	Node<T>* Head;

};

//��������
template <class T>
inline SLinkList<T>::SLinkList()
{
	Head = NULL;
}

template<class T>
inline SLinkList<T>::SLinkList(T initData)
{
	Head = new Node<T>(initData);
}

template <class T>
inline SLinkList<T>::~SLinkList()
{
}

template<class T>
inline void SLinkList<T>::Insert(T aData, T bData)
{
	Node<T> *newNode, *curNode, *preNode;
	newNode = new Node<T>(bData);
	curNode = Head;
	if (Head == NULL) {
		newNode->next = NULL;
		Head = newNode;
	}
	else {
		if (curNode->data == aData) {
			newNode->next = curNode;
			Head = newNode;
		}
		else {
			while (curNode->data != aData && curNode->next != NULL) {
				preNode = curNode;
				curNode = curNode->next;
			}
			if (curNode->data == aData) {
				preNode->next = newNode;
				newNode->next = curNode;
			}
			else {
				curNode->next = newNode;
				newNode->next = NULL;
			}
		}
	}
}

template<class T>
inline void SLinkList<T>::AddHead(T data)
{
	Node<T>* newNode;
	newNode = new Node<T>(data);
	newNode->next = Head;
	Head = newNode;
}

template<class T>
inline T SLinkList<T>::GetHead()
{
	return Head->data;
}

template<class T>
inline void SLinkList<T>::DeleteHead()
{
	Node<T>* deleteNode = Head;
	Head = Head->next;
	delete deleteNode;
}

template<class T>
inline void SLinkList<T>::Delete(T data)
{
	Node<T> *curNode, *preNode;
	curNode = Head;
	if (Head == NULL) {
		return;
	}
	else {
		if (curNode->data == data) {
			Head = curNode->next;
			delete curNode;
		}
		else {
			while (curNode->data != data && curNode->next != NULL) {
				preNode = curNode;
				curNode = curNode->next;
			}
			if (curNode->data == data) {
				preNode->next = curNode->next;
				delete curNode;
			}
			else {
				return;
			}
		}
	}
}

template<class T>
inline Node<T>* SLinkList<T>::Search(T data)
{
	Node<T>*curNode;
	curNode = Head;
	while (curNode->data != data && curNode->next != NULL) {
		curNode = curNode->next;
	}
	if (curNode->data == data) {
		return curNode;
	}
	else {
		return NULL;
	}
}

template<class T>
inline void SLinkList<T>::Destroy()
{
	Node<T>* curNode, tempNode;
	curNode = Head;
	while (curNode != NULL) {
		tempNode = curNode;
		curNode = curNode->next;
		delete tempNode;
	}
}

template<class T>
inline void SLinkList<T>::OutPutList()
{
	Node<T>* curNode;
	while (curNode != NULL) {
		cout << curNode->data << endl;
		curNode = curNode->next;
	}
}

template<class T>
inline bool SLinkList<T>::IsEmpty()
{
	if (Head == NULL)
		return true;
	else
		return false;
}

template<class T>
inline int SLinkList<T>::GetCount()
{
	int count = 0;
	if (Head == NULL)
		return count = 0;
	Node<T>* curNode;
	curNode = Head;
	while (curNode != NULL) {
		count++;
		curNode = curNode->next;
	}
	return count;
}



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
inline Stack<T>::Stack(T initData) :m_linkList(initData)
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



//��ջ����ͳ��
vector<int> inArray, outArray, reposArray;
int n;
long totalCount = 0;

bool PushStack(Stack<int>& stack)
{
	if (inArray.size() == 0)
		return false;
	else {
		stack.Push(inArray[inArray.size() - 1]);
		inArray.pop_back();
		return true;
	}
}

void CancelPushStack(Stack<int>& stack)
{
	int buffer;
	stack.Pop(buffer);
	inArray.push_back(buffer);
}

bool PopStack(Stack<int>& stack)
{
	int buffer;
	if (stack.IsEmpty())
		return false;
	else {
		stack.Pop(buffer);
		outArray.push_back(buffer);
		return true;
	}
}

void CancelPopStack(Stack<int>& stack)
{
	int buffer;
	buffer = outArray[outArray.size() - 1];
	outArray.pop_back();
	stack.Push(buffer);
}

void StoreArray(vector<int>& outArray)
{
	int temp = 0;
	for (int i = 0; i < outArray.size(); i++) {
		temp = temp + outArray[i] * pow(10, outArray.size() - i - 1);
	}
	reposArray.push_back(temp);
}

bool IfRepeat(vector<int>& outArray)
{
	int temp = 0;
	for (int i = 0; i < outArray.size(); i++) {
		temp = temp + outArray[i] * pow(10, outArray.size() - i - 1);
	}
	for (int i = 0; i < reposArray.size(); i++) {
		if (temp == reposArray[i])
			return true;
	}
	return false;
}

void Action(Stack<int>& stack)
{
	if (outArray.size() == n) {
		totalCount++;
	}
	else {
		if (PushStack(stack)) {
			Action(stack);
			CancelPushStack(stack);
		}
		if (PopStack(stack)) {
			Action(stack);
			CancelPopStack(stack);
		}
	}
}

int main()
{
	cin >> n;
	for (int i = n; i > 0; i--) {
		inArray.push_back(i);
	}
	Stack<int> stack;
	Action(stack);
	cout << totalCount << endl;
    return 0;
}

