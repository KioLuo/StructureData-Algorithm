// BlahShuJi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;


void Work(int a, long n)
{
	long long*buffer, temp2, temp3;
	buffer = new long long[n];
	long head2 = 0;
	long head3 = 0;
	long tail = 0;
	buffer[0] = a;
	while (++tail < n)
	{
		temp2 = 2 * buffer[head2] + 1;
		temp3 = 3 * buffer[head3] + 1;
		if (temp2 < temp3)
		{
			buffer[tail] = temp2;
			head2++;
		}
		else if (temp2 > temp3)
		{
			buffer[tail] = temp3;
			head3++;
		}
		else {
			buffer[tail] = temp2;
			head2++;
			head3++;
		}
	}
	cout << buffer[n - 1] << endl;
	delete[]buffer;
}


int main()
{
	int a;
	long n;
	while (cin >> a >> n) {
		Work(a, n);
	}
    return 0;
}

