// QianZhuiZhongDeZhouQi-2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int strLen;
string str;

int* FindNext(string str)
{
	int i, k;
	int strLen = str.length();
	int* next = new int[strLen];
	next[0] = -1;
	k = -1;
	i = 0;
	while (i < strLen - 1)
	{
		while ((k >= 0) && (str[i] != str[k]))
		{
			k = next[k];
		}
		k++;
		i++;
		next[i] = k;
	}
	return next;
}

int main()
{
	int count = 0;
	while (cin >> strLen)
	{
		if (strLen == 0)
			break;
		cin >> str;
		count++;
		cout << "Test case #" << count << endl;
		str.push_back('x');
		int* next = FindNext(str);
		for (int i = 2; i <= strLen; i++)
		{
			if ((next[i] > 0) && (i % (i - next[i])) == 0)
			{
				cout << i << " " << i / (i - next[i]) << endl;
			}
		}
		cout << endl;
	}
    return 0;
}

