// QianZhuiZhongDeZhouQi-2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int* FindNext(string str)
{
	int i, k;
	int strLen = str.length();
	int* next = new int[strLen];
	next[0] = -1;
	k = -1;
	i = 0;
	while (i < strLen)
	{
		while ((k >= 0) && (str[i] != str[k]))
		{
			k = next[k];
		}
		k++;
		i++;
		next[i] = k;
	}
}

int main()
{
    return 0;
}

