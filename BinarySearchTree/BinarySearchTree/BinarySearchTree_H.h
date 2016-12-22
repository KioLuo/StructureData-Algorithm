#pragma once

#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template <class T> class BinaryTree;
template <class T> class BinarySearchTree;

//�����������
template <class T>
class BinaryTreeNode
{
	friend class BinaryTree<T>;		//����������Ϊ��Ԫ��
	friend class BinarySearchTree<T>;		//��������������Ϊ��Ԫ��
protected:
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
	BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r)		//�������ݺ����������Ĺ��캯��
	{
		info = ele;
		left = l;
		right = r;
	};
	~BinaryTreeNode() {};		//��������
public:
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
enum Tags { Left, Right };
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
protected:
	BinaryTreeNode<T>* root;
	T endflag_value;
public:
	BinaryTree() { root = NULL; };
	~BinaryTree() { DeleteBinaryTree(root); };
	bool isEmpty() const;		//�ж��Ƿ�Ϊ��
	BinaryTreeNode<T>* Root() { return root; };		//���ظ����
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);		//����ĳ���ĸ����
	BinaryTreeNode<T>* LeftSiBling(BinaryTreeNode<T>* current);		//����ĳ�������ֵܽ��
	BinaryTreeNode<T>* RightSiBling(BinaryTreeNode<T>* current);		//����ĳ�������ֵܽ��
	BinaryTreeNode<T>* Find(const T& data, BinaryTreeNode<T>* Node) const;		//����
	int Height(BinaryTreeNode<T>* root);		//��������߶�
	int Size(BinaryTreeNode<T>* root);		//������������
	void CreatTree(BinaryTreeNode<T>*& Node);		//��������
	void Visit(BinaryTreeNode<T>*);		//���ʽ��
	void PreOrderRecusion(BinaryTreeNode<T>* root);		//������ȵݹ�ǰ�����������
	void InOrderRecusion(BinaryTreeNode<T>* root);		//������ȵݹ��������������
	void PostOrderRecusion(BinaryTreeNode<T>* root);		//������ȵݹ�������������
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);		//�ǵݹ�ǰ�����������
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);		//�ǵݹ��������������
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);		//�ǵݹ�������������
	void LevelOrder(BinaryTreeNode<T>* root);		//�������������
	void DeleteBinaryTree(BinaryTreeNode<T>* Node);			//ɾ��������
	void SetEndFlag(const T& val);		//���ý�����־
	void SetRoot(BinaryTreeNode<T>* Node);		//���ø����
};


//��������������
template<class T>
class BinarySearchTree : public BinaryTree<T>
{
public:

	BinarySearchTree()
	{
	}

	~BinarySearchTree()
	{
	}

public:
	void insert(const T& val, BinaryTreeNode<T>* & node);
	void removeNode(BinaryTreeNode<T>*& node, const T& val);
	BinaryTreeNode<T>* deletemin(BinaryTreeNode<T>*& node);

};

//BinaryTree��ģ�庯������
//�ж��Ƿ�Ϊ��
template<class T>
inline bool BinaryTree<T>::isEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	return false;
}

//����ĳ���ĸ����
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

//����ĳ�������ֵܽ��
template<class T>
inline BinaryTreeNode<T>* BinaryTree<T>::LeftSiBling(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* parent = Parent(current);
	return parent->leftchild();
}

//����ĳ�������ֵܽ��
template<class T>
inline BinaryTreeNode<T>* BinaryTree<T>::RightSiBling(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* parent = Parent(current);
	return parent->rightchild();
}

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

//��������߶�
template<class T>
inline int BinaryTree<T>::Height(BinaryTreeNode<T>* Node)
{
	if (Node == NULL)
	{
		return 0;
	}
	int lHeight = Height(Node->leftchild()) + 1;
	int rHeight = Height(Node->rightchild()) + 1;
	return lHeight>rHeight ? lHeight : rHeight;
}

//������������
template<class T>
inline int BinaryTree<T>::Size(BinaryTreeNode<T>* Node)
{
	if (Node == NULL)
	{
		return 0;
	}
	return (1 + Size(Node->leftchild()) + Size(Node->rightchild()));
}

//��������
template<class T>
inline void BinaryTree<T>::CreatTree(BinaryTreeNode<T>* & Node)
{
	T item;
	cin >> item;
	if (item != endflag_value)
	{
		Node = new BinaryTreeNode<T>(item);
		CreatTree(Node->left);
		CreatTree(Node->right);
	}
	else
	{
		Node = NULL;
	}
}

//���ʽ��
template<class T>
inline void BinaryTree<T>::Visit(BinaryTreeNode<T>* current)
{
	cout << current->info << endl;
}

//������ȵݹ�ǰ�����������
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

//������ȵݹ��������������
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

//������ȵݹ�������������
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

//�ǵݹ�ǰ�����������
template<class T>
inline void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	using std::stack;
	stack<BinaryTreeNode<T>*> aStack;
	BinaryTreeNode<T>* pointer = root;
	aStack.push(NULL);
	while (pointer)
	{
		Visit(pointer);
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

//�ǵݹ��������������
template<class T>
inline void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	using std::stack;
	stack<BinaryTreeNode<T>*> aStack;
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

//�ǵݹ�������������
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

//�������������
template<class T>
inline void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root)
{
	using std::queue;
	queue<BinaryTreeNode<T>*> aQueue;
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

//���ý�����־
template<class T>
inline void BinaryTree<T>::SetEndFlag(const T & val)
{
	endflag_value = val;
}

template<class T>
inline void BinaryTree<T>::SetRoot(BinaryTreeNode<T>* Node)
{
	root = Node;
}

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

//����������
template<class T>
inline void BinaryTreeNode<T>::setLeftChild(BinaryTreeNode<T>* leftchild)
{
	left = leftchild;
}

//����������
template<class T>
inline void BinaryTreeNode<T>::setRightChild(BinaryTreeNode<T>* rightchild)
{
	right = rightchild;
}

//���õ�ǰ�������
template<class T>
inline void BinaryTreeNode<T>::setValue(const T & val)
{
	info = val;
}

//�ж��Ƿ�ΪҶ���
template<class T>
inline bool BinaryTreeNode<T>::isLeaf() const
{
	if (left == NULL && right == NULL)
	{
		return true;
	}
	return false;
}

//���ظ�ֵ������
template<class T>
inline BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode<T>& Node)
{
	info = Node.info;
	if (left != NULL)
	{
		delete left;
	}
	if (right != NULL)
	{
		delete right;
	}
	left = Node.left;
	right = Node.right;
	return *this;
}


//������������������
//������
template<class T>
inline void BinarySearchTree<T>::insert(const T& val, BinaryTreeNode<T>*& node)
{
	if (node == NULL)
	{
		node = new BinaryTreeNode<T>(val);
	}
	else
	{
		if (val < node->info)
		{
			insert(val, node->left);
		}
		else if (val > node->info)
		{
			insert(val, node->right);
		}

	}
}

//ɾ�����
template<class T>
inline void BinarySearchTree<T>::removeNode(BinaryTreeNode<T>*& node, const T & val)
{
	if (node == NULL)
	{
		cout << val << " is not in the tree." << endl;
	}
	else if (val < node->info)
	{
		removeNode(node->left, val);
	}
	else if (val > node->info)
	{
		removeNode(node->right, val);
	}
	else
	{
		BinaryTreeNode<T>* temp = node;
		if (node->left == NULL) { node = node->right; }
		else if (node->right == NULL) { node = node->left; }
		else
		{
			temp = deletemin(node->right);
			node->setValue(temp->info);
		}
		delete temp;
	}
}

//ɾ����������С���
template<class T>
inline BinaryTreeNode<T>* BinarySearchTree<T>::deletemin(BinaryTreeNode<T>*& node)
{
	if (node->left != NULL)
	{
		return deletemin(node->left);
	}
	else
	{
		BinaryTreeNode<T>* temp = node;
		node = node->right;
		return temp;
	}
}
