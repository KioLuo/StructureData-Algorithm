#pragma once
#include <stack>
#include <queue>

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
	BinaryTreeNode();		//Ĭ�Ϲ��캯��
	BinaryTreeNode(const T& ele);		//�������ݵĹ��캯��
	BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r);		//�������ݺ����������Ĺ��캯��
	T value() const;		//���ص�ǰ�������
	BinaryTreeNode<T>* leftchild() const;		//����������
	BinaryTreeNode<T>* rightchild() const;		//����������
	void setLeftChild(BinaryTreeNode<T>*);		//����������
	void setRightChild(BinaryTreeNode<T>*);		//����������
	void setValue(const T& val);		//���õ�ǰ�������
	bool isLeaf() const;		//�ж��Ƿ�ΪҶ���
	BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& Node);		//���ظ�ֵ������
};

//���ұ�ǩ,���ں���ǵݹ����
enum Tags{Left, Right};
template <class T>
class StackElement
{
public:
	BinaryTreeNode<T>* pointer;
	Tags tag;
};

//��������
template <class T>
class BinaryTree
{
private:
	BinaryTreeNode<T>* root;
public:
	BinaryTree() { root = NULL; };
	~BinaryTree() { DeleteBinaryTree(root); };
	bool isEmpty() const;
	BinaryTreeNode<T>* Root() { return root; };		//���ظ����
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);		//����ĳ���ĸ����
	BinaryTreeNode<T>* LeftSiBling(BinaryTreeNode<T>* current);		//����ĳ�������ֵܽ��
	BinaryTreeNode<T>* RightSiBling(BinaryTreeNode<T>* current);		//����ĳ�������ֵܽ��
	void CreatTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& RightTree);		//��������
	void Visit(BinaryTreeNode<T>*);		//���ʽ��
	void PreOrderRecusion(BinaryTreeNode<T>* root);		//������ȵݹ�ǰ�����������
	void InOrderRecusion(BinaryTreeNode<T>* root);		//������ȵݹ��������������
	void PostOrderRecusion(BinaryTreeNode<T>* root);		//������ȵݹ�������������
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);		//�ǵݹ�ǰ�����������
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);		//�ǵݹ��������������
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);		//�ǵݹ�������������
	void LevelOrder(BinaryTreeNode<T>* root);		//�������������
	void DeleteBinaryTree(BinaryTreeNode<T>* root);			//ɾ��������
};

template<class T>
inline BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current)
{
	using std::stack;
	stack<BinaryTreeNode<T>> aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);
	while (pointer)
	{
		if (current == pointer->leftchild() || current == pointer->rightchild())
			return pointer;
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
	return NULL;
}

template<class T>
inline void BinaryTree<T>::PreOrderRecusion(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		Visit(root);
		PreOrderRecusion(root->leftchild());
		PreOrderRecusion(root->rightchild());
	}
}

template<class T>
inline void BinaryTree<T>::InOrderRecusion(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		InOrderRecusion(root->leftchild());
		Visit(root);
		InOrderRecusion(root->rightchild());
	}
}

template<class T>
inline void BinaryTree<T>::PostOrderRecusion(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		PostOrderRecusion(root->leftchild());
		PostOrderRecusion(root->rightchild());
		Visit(root);
	}
}

template<class T>
inline void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	using std::stack;
	stack<BinaryTreeNode<T>> aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);
	while (pointer)
	{
		Visit(root);
		if (pointer->rightchild() != NULL)
		{
			aStack.push(pointer->rightchild());
		}
		if (pointer->leftchild() != NULL)
		{
			pointer = pointer->leftchild();
		}
		else
		{
			pointer = aStack.top();
			aStack.pop();
		}
	}
}

template<class T>
inline void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	using std::stack;
	stack<BinaryTreeNode<T>> aStack;
	BinaryTreeNode<T>* pointer = root;
	while (!aStack.empty() || pointer)
	{
		if (pointer)
		{
			aStack.push(pointer);
			pointer = pointer->leftchild();
		}
		else
		{
			pointer = aStack.top();
			aStack.pop();
			Visit(pointer);
			pointer = pointer->rightchild();
		}
		
	}
}

template<class T>
inline void BinaryTree<T>::PostOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	using std::stack;
	StackElement<T> element;
	stack<StackElement<T>> aStack;
	BinaryTreeNode<T>* pointer = root;
	while (!aStack.empty() || pointer)
	{
		while (pointer)
		{
			element.pointer = pointer;
			element.tag = Left;
			aStack.push(element);
			pointer = pointer->leftchild();
		}
		element = aStack.top();
		aStack.pop();
		pointer = element.pointer;
		if (element.tag == Left)
		{
			element.tag = Right;
			aStack.push(element);
			pointer = pointer->rightchild();
		}
		else
		{
			Visit(pointer);
			pointer = NULL;
		}
	}
}

template<class T>
inline void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root)
{
	using std::queue;
	queue<T> aQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer)
		aQueue.push(pointer);
	while (!aQueue.empty())
	{
		pointer = aQueue.front();
		aQueue.pop();
		Visit(pointer);
		if (pointer->leftchild())
			aQueue.push(pointer->leftchild());
		if (pointer->rightchild())
			aQueue.push(pointer->rightchild());
	}
}
