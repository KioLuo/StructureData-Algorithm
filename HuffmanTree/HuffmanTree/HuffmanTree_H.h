#pragma once

template<class T> class HuffmanTree;

//HuffmanTreeNode��ģ�嶨��
template<class T>
class HuffmanTreeNode
{
	friend class HuffmanTree<T>;
private:
	T info;
	HuffmanTreeNode<T>* left;
	HuffmanTreeNode<T>* right;

public:
	HuffmanTreeNode()
	{
		left = NULL;
		right = NULL;
	};
	HuffmanTreeNode(T val)
	{
		info = val;
		left = NULL;
		right = NULL;
	};
	~HuffmanTreeNode() {};

public:
	T getInfo() const;
	HuffmanTreeNode<T>* getLeft() const;
	HuffmanTreeNode<T>* getRight() const;
	
};

//HuffmanTree��ģ�嶨��
template<class T>
class HuffmanTree
{
private:
	HuffmanTreeNode<T>* root;

public:
	HuffmanTree(T weight[], int n);
	virtual ~HuffmanTree() { deleteTree(root); };

public:

};


//HuffmanTreeNode��������
template<class T>
inline T HuffmanTreeNode<T>::getInfo() const
{
	return info;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTreeNode<T>::getLeft() const
{
	return left;
}

template<class T>
inline HuffmanTreeNode<T>* HuffmanTreeNode<T>::getRight() const
{
	return right;
}

//HuffmanTree��������
template<class T>
inline HuffmanTree<T>::HuffmanTree(T weight[], int n)
{

}
