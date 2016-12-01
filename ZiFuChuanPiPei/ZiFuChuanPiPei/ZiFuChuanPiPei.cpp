// ZiFuChuanPiPei.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//字符串模式匹配KMP算法
int* FindNext(string p)
{
	int j, k;
	int m = p.length();
	int* next = new int[m];
	next[0] = -1;
	j = 0;
	k = -1;
	while (j < m - 1)
	{
		while (k >= 0 && p[j] != p[k])
		{
			k = next[k];
		}
		j++;
		k++;
		if (p[j] == p[k])
			next[j] = next[k];
		else
			next[j] = k;
	}
	return next;
}

int KMPStrMatching(string T, string P, int* N, int start)
{
	int j = 0;
	int i = start;
	int pLen = P.length();
	int tLen = T.length();
	if (tLen - start < pLen)
	{
		return (-1);
	}
	while (i < tLen && j < pLen)
	{
		if (j == -1 || P[j] == T[i])
		{
			j++;
			i++;
		}
		else
		{
			j = N[j];
		}
	}
	if (j >= pLen)
		return (i - pLen);
	else
		return (-1);

}

//字符串模式匹配朴素算法
int BruteForceStrMatching(string T, string P, int startIndex)
{
	for (int g = startIndex; g <= (T.length() - P.length()); g++)
	{
		for (int i = 0; (i < P.length()) && (P[i] == T[i + g]); i++)
		{
			if (i == P.length() - 1)
				return g;
		}
	}
	return (-1);
}

int main()
{
    return 0;
}

