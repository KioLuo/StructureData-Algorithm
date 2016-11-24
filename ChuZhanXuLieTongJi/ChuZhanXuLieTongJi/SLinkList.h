#pragma once
//定义结点类模板
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

//定义单链表类模板
template <class T>
class SLinkList
{
public:
	SLinkList();
	SLinkList(T initData);
	~SLinkList();
public:
	void Insert(T aData, T bData);		//插入新节点
	void AddHead(T data);		//插入新节点作为链表头
	Node<T>* GetHead();		//输出链表头数据
	void DeleteHead();		//删除链表头节点内容，下一结点作为新表头
	void Delete(T data);		//删除特定数据的结点
	Node<T>* Search(T data);		//搜索并返回特定数据的结点
	void Destroy();		//清空整个链表
	void OutPutList();		//输出整个链表
	bool IsEmpty();		//是否为空链表
	int GetCount();		//返回结点数目
private:
	Node<T>* Head;

};

//函数定义
template <class T>
inline SLinkList<T>::SLinkList()
{
	Head = NULL;
}

template<class T>
inline SLinkList<T>::SLinkList(T initData)
{
	Head = new Node<T>;
	Head->data = initData;
	Head->next = NULL;
}

template <class T>
inline SLinkList<T>::~SLinkList()
{
}

template<class T>
inline void SLinkList<T>::Insert(T aData, T bData)
{
	Node<T> *newNode(bData), *curNode, *preNode;
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
	Node<T>* newNode(data);
	newNode->next = Head;
	Head = newNode;
}

template<class T>
inline Node<T>* SLinkList<T>::GetHead()
{
	return Head;
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
	int count;
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
