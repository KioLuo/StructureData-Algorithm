// BinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BinaryTree_H.h"
#include <iostream>
using namespace std;

int main()
{
	BinaryTree<int> binaryTree;
	binaryTree.SetEndFlag(-1);
	BinaryTreeNode<int>* root = binaryTree.Root();
	binaryTree.CreatTree(root);
	cout << "PreOrderRecusion" << endl;
	binaryTree.PreOrderRecusion(root);
	cout << "InOrderRecusion" << endl;
	binaryTree.InOrderRecusion(root);
	cout << "PostOrderRecusion" << endl;
	binaryTree.PostOrderRecusion(root);
	cout << "PreOrderWithoutRecusion" << endl;
	binaryTree.PreOrderWithoutRecusion(root);
	cout << "InOrderWithoutRecusion" << endl;
	binaryTree.InOrderWithoutRecusion(root);
	cout << "PostOrderWithoutRecusion" << endl;
	binaryTree.PostOrderWithoutRecusion(root);
    return 0;
}

