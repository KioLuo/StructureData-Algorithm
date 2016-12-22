// MinHeap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MinHeap_H.h"
#include <iostream>
using namespace std;

int main()
{
	MinHeap<int> minHeap(20);
	minHeap.createHeap();
	cout << minHeap.removeMin() << endl;
    return 0;
}

