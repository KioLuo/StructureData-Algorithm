
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

int main()
{

	string szInput1, szInput2;
	int aResult[400] = { 0 };
	cin >> szInput1 >> szInput2;
	vector<int> vctNum1, vctNum2;
	for (int i = 0; i < szInput1.size(); i++) {
		vctNum1.push_back((int)szInput1[i] - 48);
	}
	for (int j = 0; j < szInput2.size(); j++) {
		vctNum2.push_back((int)szInput2[j] - 48);
	}


	for (int i = vctNum2.size() - 1, m = 0; i >= 0; i--, m++) {
		int temp = 0;
		for (int j = vctNum1.size() - 1, n = m; j >= 0; j--, n++) {
			int tempInt1 = vctNum1[j] * vctNum2[i] / 10;
			int tempRes1 = vctNum1[j] * vctNum2[i] % 10;
			aResult[n] = (aResult[n] + tempRes1) % 10;
			aResult[n + 1] = (aResult[n + 1] + tempInt1 + temp + (aResult[n] + tempRes1) / 10) % 10;
			temp = (aResult[n + 1] + tempInt1 + temp + (aResult[n] + tempRes1) / 10) / 10;
		}
	}


	for (int i = 0; i < 400; i++) {
		cout << aResult[i];
	}
	cout << endl;
	return 0;
}

