// ChuZhanXuLieTongJi_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#define MAX_NUM 20
using namespace std;

int n;

template <class T>
class Stack
{
	T a[MAX_NUM];
	int curSize;
public:
	Stack() :curSize(-1)
	{
	}
	~Stack()
	{
	}
	void push(T data)
	{
		a[++curSize] = data;
	}
	void pop()
	{
		curSize--;
	}
	bool full()
	{
		if (curSize >= n)
			return true;
		return false;
	}
	bool empty()
	{
		if (curSize < 0)
			return true;
		return false;
	}
};

int totalCount = 0;

void Action(Stack<int> stack, int s)
{
	if (stack.empty() && s == 0) {
		totalCount++;
	}
	else if (stack.empty()) {
		stack.push(s--);
		Action(stack, s);
	}
	else if (s == 0) {
		stack.pop();
		Action(stack, s);
	}
	else {
		stack.push(s--);
		Action(stack, s);
		stack.pop();
		s++;
		stack.pop();
		Action(stack, s);
	}
}



int main()
{
	cin >> n;
	Stack<int> stack;
	Action(stack, n);
	cout << totalCount << endl;
    return 0;
}

