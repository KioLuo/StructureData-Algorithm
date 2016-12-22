#pragma once

#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template <class T> class BinaryTree;
template <class T> class BinarySearchTree;

//二叉树结点类
template <class T>
class BinaryTreeNode
{
	friend class BinaryTree<T>;		//声明二叉树为友元类
	friend class BinarySearchTree<T>;		//声明二叉搜索树为友元类
protected:
	T info;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;
public:
	BinaryTreeNode()      //默认构造函数
	{
		left = NULL;
		right = NULL;
	};
	BinaryTreeNode(const T& ele)       //给定数据的构造函数
	{
		info = ele;
		left = NULL;
		right = NULL;
	};
	BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r)		//给定数据和左右子树的构造函数
	{
		info = ele;
		left = l;
		right = r;
	};
	~BinaryTreeNode() {};		//析构函数
public:
	T value() const;		//返回当前结点数据
	BinaryTreeNode<T>* leftchild() const;		//返回左子树
	BinaryTreeNode<T>* rightchild() const;		//返回右子树
	void setLeftChild(BinaryTreeNode<T>*);		//设置左子树
	void setRightChild(BinaryTreeNode<T>*);		//设置右子树
	void setValue(const T& val);		//设置当前结点数据
	bool isLeaf() const;		//判断是否为叶结点
	BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& Node);		//重载赋值操作符
};


//左右标签,用于后序非递归遍历
enum Tags { Left, Right };
template <class T>
class StackElement
{
public:
	BinaryTreeNode<T>* pointer;
	Tags tag;
};


//二叉树类
template <class T>
class BinaryTree
{
protected:
	BinaryTreeNode<T>* root;
	T endflag_value;
public:
	BinaryTree() { root = NULL; };
	~BinaryTree() { DeleteBinaryTree(root); };
	bool isEmpty() const;		//判断是否为空
	BinaryTreeNode<T>* Root() { return root; };		//返回根结点
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);		//返回某结点的父结点
	BinaryTreeNode<T>* LeftSiBling(BinaryTreeNode<T>* current);		//返回某结点的左兄弟结点
	BinaryTreeNode<T>* RightSiBling(BinaryTreeNode<T>* current);		//返回某结点的右兄弟结点
	BinaryTreeNode<T>* Find(const T& data, BinaryTreeNode<T>* Node) const;		//查找
	int Height(BinaryTreeNode<T>* root);		//求二叉树高度
	int Size(BinaryTreeNode<T>* root);		//求二叉树结点数
	void CreatTree(BinaryTreeNode<T>*& Node);		//创建新树
	void Visit(BinaryTreeNode<T>*);		//访问结点
	void PreOrderRecusion(BinaryTreeNode<T>* root);		//深度优先递归前序遍历二叉树
	void InOrderRecusion(BinaryTreeNode<T>* root);		//深度优先递归中序遍历二叉树
	void PostOrderRecusion(BinaryTreeNode<T>* root);		//深度优先递归后序遍历二叉树
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);		//非递归前序遍历二叉树
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);		//非递归中序遍历二叉树
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);		//非递归后序遍历二叉树
	void LevelOrder(BinaryTreeNode<T>* root);		//层序遍历二叉树
	void DeleteBinaryTree(BinaryTreeNode<T>* Node);			//删除二叉树
	void SetEndFlag(const T& val);		//设置结束标志
	void SetRoot(BinaryTreeNode<T>* Node);		//设置根结点
};


//二叉搜索树定义
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

//BinaryTree类模板函数定义
//判断是否为空
template<class T>
inline bool BinaryTree<T>::isEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	return false;
}

//返回某结点的父结点
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

//返回某结点的左兄弟结点
template<class T>
inline BinaryTreeNode<T>* BinaryTree<T>::LeftSiBling(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* parent = Parent(current);
	return parent->leftchild();
}

//返回某结点的右兄弟结点
template<class T>
inline BinaryTreeNode<T>* BinaryTree<T>::RightSiBling(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* parent = Parent(current);
	return parent->rightchild();
}

//查找
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

//求二叉树高度
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

//求二叉树结点数
template<class T>
inline int BinaryTree<T>::Size(BinaryTreeNode<T>* Node)
{
	if (Node == NULL)
	{
		return 0;
	}
	return (1 + Size(Node->leftchild()) + Size(Node->rightchild()));
}

//创建新树
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

//访问结点
template<class T>
inline void BinaryTree<T>::Visit(BinaryTreeNode<T>* current)
{
	cout << current->info << endl;
}

//深度优先递归前序遍历二叉树
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

//深度优先递归中序遍历二叉树
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

//深度优先递归后序遍历二叉树
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

//非递归前序遍历二叉树
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

//非递归中序遍历二叉树
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

//非递归后序遍历二叉树
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

//层序遍历二叉树
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

//删除二叉树
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

//设置结束标志
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

//BinaryTreeNode类模板函数定义
//返回当前结点数据
template<class T>
inline T BinaryTreeNode<T>::value() const
{
	return info;
}

//返回左子树
template<class T>
inline BinaryTreeNode<T>* BinaryTreeNode<T>::leftchild() const
{
	return left;
}

//返回右子树
template<class T>
inline BinaryTreeNode<T>* BinaryTreeNode<T>::rightchild() const
{
	return right;
}

//设置左子树
template<class T>
inline void BinaryTreeNode<T>::setLeftChild(BinaryTreeNode<T>* leftchild)
{
	left = leftchild;
}

//设置右子树
template<class T>
inline void BinaryTreeNode<T>::setRightChild(BinaryTreeNode<T>* rightchild)
{
	right = rightchild;
}

//设置当前结点数据
template<class T>
inline void BinaryTreeNode<T>::setValue(const T & val)
{
	info = val;
}

//判断是否为叶结点
template<class T>
inline bool BinaryTreeNode<T>::isLeaf() const
{
	if (left == NULL && right == NULL)
	{
		return true;
	}
	return false;
}

//重载赋值操作符
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


//二叉搜索树函数定义
//插入结点
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

//删除结点
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

//删除右子树最小结点
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
