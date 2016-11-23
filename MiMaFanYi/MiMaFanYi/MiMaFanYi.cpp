// MiMaFanYi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int nNum;
	cin >> nNum;
	cin.ignore(1);
	for (int i = 0; i < nNum; i++) {
		string szInput;
		getline(cin, szInput);
		for (int j = 0; j < szInput.size(); j++) {
			if ((szInput[j] >= 65 && szInput[j] <= 89) || (szInput[j] >= 97 && szInput[j] <= 121)) {
				szInput[j] = (char)((int)szInput[j] + 1);
			}
			else if (szInput[j] == 122 || szInput[j] == 90) {
				szInput[j] = (char)((int)szInput[j] - 25);
			}
		}
		cout << szInput << endl;
	}
    return 0;
}

