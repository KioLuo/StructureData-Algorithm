// DengJiaBiaoDaShi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#define MAX_NUM 100
using namespace std;

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
	T top()
	{
		T topData = a[curSize];
		return topData;
	}
	bool empty()
	{
		if (curSize < 0)
			return true;
		return false;
	}
};

vector<string> preString(char* str)
{
	vector<string> tokens;
	int len = strlen(str);
	char* p = (char*)malloc((len + 1)*sizeof(char));
	int i = 0, j = 0;
	while (i < len) {
		if (str[i] == ' ' || str[i] == '\t') {
			i++;
			continue;
		}
		p[j++] = str[i++];
	}
	p[j] = '\0';

	len = strlen(p);
	j = 0;
	char temp[2];
	string token;
	while (j < len) {
		switch (p[j]) {
		case '+':
		case '*':
		case '/':
		case '(':
		case ')':
		{
			temp[0] = p[j];
			temp[1] = '\0';
			token = temp;
			tokens.push_back(token);
			break;
		}
		case '-':
		{
			if (j == 0) {
				temp[0] = '#';
				temp[1] = '\0';
			}
			else if (p[j - 1] == ')' || isdigit(p[j - 1])) {
				temp[0] = p[j];
				temp[1] = '\0';
			}
			else {
				temp[0] = '#';
				temp[1] = '\0';
			}
			token = temp;
			tokens.push_back(token);
			break;
		}
		default:
		{
			i = j;
			while (isdigit(p[i]) && i < len) {
				i++;
			}
			char* opd = (char*)malloc(i - j + 1);
			strncpy(opd, p + j, i - j);
			opd[i - j] = '\0';
			token = opd;
			tokens.push_back(token);
			j = i - 1;
			free(opd);
			break;
		}
		}
		j++;
	}
	free(p);
	return tokens;
}

int getPriority(string opt)
{
	int priority;
	if (opt == "#") {
		priority = 3;
	}
	else if (opt == "*" || opt == "/") {
		priority = 2;
	}
	else if (opt == "+" || opt == "-") {
		priority = 1;
	}
	else if (opt == "(") {
		priority = 0;
	}
	return priority;
}

void calculate(Stack<int>& stack, string opt)
{
	if (opt == "#") {
		int opd = stack.top();
		stack.pop();
		int result = 0 - opd;
		stack.push(result);
	}
	else if (opt == "*") {
		int rOpd = stack.top();
		stack.pop();
		int lOpd = stack.top();
		stack.pop();
		int result = lOpd * rOpd;
		stack.push(result);
	}
	else if (opt == "/") {
		int rOpd = stack.top();
		stack.pop();
		int lOpd = stack.top();
		stack.pop();
		int result = lOpd / rOpd;
		stack.push(result);
	}
	else if (opt == "+") {
		int rOpd = stack.top();
		stack.pop();
		int lOpd = stack.top();
		stack.pop();
		int result = lOpd + rOpd;
		stack.push(result);
	}
	else if (opt == "-") {
		int rOpd = stack.top();
		stack.pop();
		int lOpd = stack.top();
		stack.pop();
		int result = lOpd - rOpd;
		stack.push(result);
	}
}

int evaMidExpression(char* str)
{
	vector<string> tokens = preString(str);
	Stack<int> opdStack;
	Stack<string> optStack;
	int i = 0;
	int size = tokens.size();
	for (i = 0; i < size; i++) {
		string token = tokens[i];
		if (token == "#" || token == "+" || token == "-" || token == "*" || token == "/") {
			if (optStack.empty()) {
				optStack.push(token);
			}
			else {
				int tokenPriority = getPriority(token);
				string topOpt = optStack.top();
				int topOptPriority = getPriority(topOpt);
				if (tokenPriority > topOptPriority) {
					optStack.push(token);
				}
				else {
					while (tokenPriority <= topOptPriority) {
						calculate(opdStack, topOpt);
						optStack.pop();
						if (!optStack.empty()) {
							topOpt = optStack.top();
							topOptPriority = getPriority(topOpt);
						}
						else
							break;
					}
					optStack.push(token);
				}
			}
		}
		else if (token == "(")
			optStack.push(token);
		else if (token == ")") {
			string topOpt = optStack.top();
			while (topOpt != "(") {
				calculate(opdStack, topOpt);
				optStack.pop();
				topOpt = optStack.top();
			}
			optStack.pop();
		}
		else {
			opdStack.push(atoi(token.c_str()));
		}
	}
	while (!optStack.empty()) {
		string topOpt = optStack.top();
		calculate(opdStack, topOpt);
		optStack.pop();
	}
	return opdStack.top();
}

char* VarAssign(char* str, int n)
{
	int len = strlen(str);
	char* tempStr;
	tempStr = new char[len + 1];
	for (int i = 0; i < len; i++) {
		tempStr[i] = str[i];
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) {
			tempStr[i] = (((int)str[i])*n) % 10 + 48;
		}
	}
	tempStr[len] = '\0';
	return tempStr;
}


bool ExpressionIsEqual(char* str1, char* str2)
{
	for (int i = 1; i < 2; i++) {
		int result1 = evaMidExpression(VarAssign(str1, i));
		int result2 = evaMidExpression(VarAssign(str2, i));
		if (result1 != result2)
			return false;
	}
	return true;
}


int main()
{
	int n;
	cin >> n;
	cin.ignore(1);
	for (int i = 0; i < n; i++) {
		char *str1, *str2;
		str1 = new char[81];
		str2 = new char[81];
		cin.getline(str1, 81, '\n');
		cin.getline(str2, 81, '\n');
		if (ExpressionIsEqual(str1, str2))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
    return 0;
}

