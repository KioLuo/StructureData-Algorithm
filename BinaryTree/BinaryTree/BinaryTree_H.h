#pragma once
#include <stack>
#include <queue>

//二叉树结点类
template <class T>
class BinaryTreeNode
{
	friend class BinaryTree<T>;		//声明二叉树为友元类
private:
	T info;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;
public:
	BinaryTreeNode();		//默认构造函数
	BinaryTreeNode(const T& ele);		//给定数据的构造函数
	BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r);		//给定数据和左右子树的构造函数
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
enum Tags{Left, Right};
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
private:
	BinaryTreeNode<T>* root;
public:
	BinaryTree() { root = NULL; };
	~BinaryTree() { DeleteBinaryTree(root); };
	bool isEmpty() const;
	BinaryTreeNode<T>* Root() { return root; };		//返回根结点
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);		//返回某结点的父结点
	BinaryTreeNode<T>* LeftSiBling(BinaryTreeNode<T>* current);		//返回某结点的左兄弟结点
	BinaryTreeNode<T>* RightSiBling(BinaryTreeNode<T>* current);		//返回某结点的右兄弟结点
	void CreatTree(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& RightTree);		//构造新树
	void Visit(BinaryTreeNode<T>*);		//访问结点
	void PreOrderRecusion(BinaryTreeNode<T>* root);		//深度优先递归前序遍历二叉树
	void InOrderRecusion(BinaryTreeNode<T>* root);		//深度优先递归中序遍历二叉树
	void PostOrderRecusion(BinaryTreeNode<T>* root);		//深度优先递归后序遍历二叉树
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);		//非递归前序遍历二叉树
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);		//非递归中序遍历二叉树
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);		//非递归后序遍历二叉树
	void LevelOrder(BinaryTreeNode<T>* root);		//层序遍历二叉树
	void DeleteBinaryTree(BinaryTreeNode<T>* root);			//删除二叉树
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
