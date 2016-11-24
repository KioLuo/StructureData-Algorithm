#pragma once
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
	Node<T>* GetHead();		//�������ͷ����
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
