// BinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template <class T> class BinaryTree;


//�����������
template <class T>
class BinaryTreeNode
{
	friend class BinaryTree<T>;		//����������Ϊ��Ԫ��
private:
	T info;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;
public:
	BinaryTreeNode()      //Ĭ�Ϲ��캯��
	{
		left = NULL;
		right = NULL;
	};
	BinaryTreeNode(const T& ele)       //�������ݵĹ��캯��
	{
		info = ele;
		left = NULL;
		right = NULL;
	};
	~BinaryTreeNode() {};		//��������
public:
	T value() const;		//���ص�ǰ�������
	BinaryTreeNode<T>* leftchild() const;		//����������
	BinaryTreeNode<T>* rightchild() const;		//����������
};

//��������
template <class T>
class BinaryTree
{
private:
	BinaryTreeNode<T>* root;
	T endflag_value;
public:
	BinaryTree() { root = NULL; };
	~BinaryTree() { DeleteBinaryTree(root); };
public:
	void setRoot(BinaryTreeNode<T>* node);		//���ø����
	BinaryTreeNode<T>* Find(const T& data, BinaryTreeNode<T>* Node) const;		//����
	void CreatTree(BinaryTreeNode<T>*& Node);		//��������
	void SetEndFlag(const T& val);		//���ý�����־
	BinaryTreeNode<T>*& Parent(const T& val);		//����ĳ���ĸ����
	void exchangeNode(const T& val1, const T& val2);		//�������
	BinaryTreeNode<T>* findLeft(const T& val);		//Ѱ������ߵĽ��
	void DeleteBinaryTree(BinaryTreeNode<T>* Node);			//ɾ��������
};


//BinaryTreeNode��ģ�庯������
//���ص�ǰ�������
template<class T>
inline T BinaryTreeNode<T>::value() const
{
	return info;
}

//����������
template<class T>
inline BinaryTreeNode<T>* BinaryTreeNode<T>::leftchild() const
{
	return left;
}

//����������
template<class T>
inline BinaryTreeNode<T>* BinaryTreeNode<T>::rightchild() const
{
	return right;
}


//BinaryTree��ģ�庯������
//����
template<class T>
inline BinaryTreeNode<T>* BinaryTree<T>::Find(const T & data, BinaryTreeNode<T>* Node) const
{
	if (Node == NULL)
	{
		return NULL;
	}
	if (Node->info == data)
	{
		return Node;
	}
	if (BinaryTreeNode<T>* temp = Find(data, Node->leftchild()))
	{
		return temp;
	}
	else
		return Find(data, Node->rightchild());
}

//���ý�����־
template<class T>
inline void BinaryTree<T>::SetEndFlag(const T & val)
{
	endflag_value = val;
}

//��������
template<class T>
inline void BinaryTree<T>::CreatTree(BinaryTreeNode<T>* & Node)
{
	T item[3];

	using std::queue;
	queue<BinaryTreeNode<T>**> aQueue;
	BinaryTreeNode<T>** pointer = &Node;
	aQueue.push(pointer);

	while (!aQueue.empty())
	{
		cin >> item[0] >> item[1] >> item[2];
		pointer = aQueue.front();
		aQueue.pop();
		if (item[0] != endflag_value)
		{
			*pointer = new BinaryTreeNode<T>(item[0]);
		}
		if (item[1] != endflag_value)
		{
			aQueue.push(&((*pointer)->left));
		}
		if (item[2] != endflag_value)
		{
			aQueue.push(&((*pointer)->right));
		}
	}
}

//�������
template<class T>
void BinaryTree<T>::exchangeNode(const T & val1, const T & val2)
{
	BinaryTreeNode<T>*& node1Parent = Parent(val1);
	BinaryTreeNode<T>*& node2Parent = Parent(val2);
	if (node1Parent != NULL && node2Parent != NULL)
	{
		BinaryTreeNode<T>* temp = node1Parent;
		node1Parent = node2Parent;
		node2Parent = temp;
	}
}

//Ѱ������ߵĽ��
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::findLeft(const T & val)
{
	BinaryTreeNode<T>* pointer= Find(val, root);
	while (pointer->leftchild() != NULL)
	{
		pointer = pointer->leftchild();
	}
	return pointer;
}

//���ø����
template<class T>
void BinaryTree<T>::setRoot(BinaryTreeNode<T>* node)
{
	root = node;
}

//���Ҹ����
template<class T>
inline BinaryTreeNode<T>*& BinaryTree<T>::Parent(const T& val)
{
	using std::stack;
	stack<BinaryTreeNode<T>*> aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);
	while (pointer)
	{
		if (val == pointer->leftchild()->info)
			return pointer->left;
		if (val == pointer->rightchild()->info)
			return pointer->right;
		if (pointer->rightchild())
			aStack.push(pointer->rightchild());
		if (pointer->leftchild())
			pointer = pointer->leftchild();
		else
		{
			pointer = aStack.top();
			aStack.pop();
		}
	}
	return pointer;
}

//ɾ��������
template<class T>
inline void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* Node)
{
	if (Node != NULL)
	{
		DeleteBinaryTree(Node->leftchild());
		DeleteBinaryTree(Node->rightchild());
		delete Node;
	}
}

int main()
{
	int nGroup;
	cin >> nGroup;

	for (int i = 0; i < nGroup; i++)
	{
		int nNodes, nActions;
		cin >> nNodes >> nActions;
		BinaryTree<int> binaryTree;
		binaryTree.SetEndFlag(-1);
		BinaryTreeNode<int>* root;
		binaryTree.CreatTree(root);
		binaryTree.setRoot(root);

		int input[3];
		for (int j = 0; j < nActions; j++)
		{
			cin >> input[0];
			if (input[0] == 1)
			{
				cin >> input[1] >> input[2];
				binaryTree.exchangeNode(input[1], input[2]);
			}
			else if (input[0] == 2)
			{
				cin >> input[1];
				cout << binaryTree.findLeft(input[1])->value() << endl;
			}
		}
	}

    return 0;
}


