// ChuZhanXuLieTongJi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Stack.h"
#include <iostream>
#include <vector>
using namespace std;

vector<int> inArray, outArray, reposArray;

bool PushStack(Stack<int> stack)
{
	if (inArray[0] == NULL)
		return false;
	else {
		stack.Push(inArray[0]);
		return true;
	}
}

bool PopStack(Stack<int> stack, int& buffer)
{
	if (stack.IsEmpty())
		return false;
	else {
		stack.Pop(buffer);
		return true;
	}
}

void StoreArray(vector<int> outArray)
{
	reposArray.push_back(0);
	int temp = 0;
	for (int i = 0; i < outArray.size(); i++) {
		temp 
	}
}

bool IfRepeat(vector<int> outArray)
{
	for (int i = 0; i < reposArray.size(); i++) {
		if (reposArray[i] == outArray)
	}
}

int main()
{

    return 0;
}

