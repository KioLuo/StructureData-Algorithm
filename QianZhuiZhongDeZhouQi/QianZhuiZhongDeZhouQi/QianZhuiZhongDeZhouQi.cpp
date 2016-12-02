// QianZhuiZhongDeZhouQi.cpp : 定义控制台应用程序的入口点。
//优化的BF算法，结果超时

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int strLen, count = 0;
	string str;
	while (1)
	{
		cin >> strLen;
		if (strLen == 0)
			break;
		cin >> str;
		count++;
		cout << "Test case #" << count << endl;
		int checkPoint = 1, preLen = 1, K = 1;
		for (; checkPoint < strLen; checkPoint++)
		{
			int i = 0;
			for (i = 0; (((i + checkPoint) < strLen) && str[i] == str[checkPoint + i]) && (i < checkPoint);i++)
			{
				if ((checkPoint == preLen) && (i >= (preLen / K - 1)))
				{
					preLen = preLen / K * (K + 1);
					K++;
					cout << preLen << " " << K << endl;
					break;
				}
			}
			if (i == checkPoint)
			{
				preLen = checkPoint * 2;
				K = 2;
				cout << preLen << " " << K << endl;
			}
			if ((i + checkPoint) >= strLen)
				break;
		}
		cout << endl;
	}
    return 0;
}

