// ChuZhanXuLieTongJi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
	int a;
	Stack<int> stack(1);
	stack.Push(2);
	stack.Push(3);
	stack.Top(a);
	cout << a << endl;
	a = stack.GetCount();
	cout << a << endl;
	stack.Pop(a);
	int b = stack.GetCount();
	cout << a << b << endl;
    return 0;
}

