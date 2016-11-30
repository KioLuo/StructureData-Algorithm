// NongFuGuoHe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "QueueArray.h"
#include <iostream>
using namespace std;

bool FarmerState(int state)
{
	return 0 != (state & 0x08);
}

bool WolfState(int state)
{
	return 0 != (state & 0x04);
}

bool GoatState(int state)
{
	return 0 != (state & 0x02);
}

bool CabbageState(int state)
{
	return 0 != (state & 0x01);
}

bool IsSafe(int state)
{
	if (WolfState(state) == GoatState(state) && WolfState(state) != FarmerState(state))
	{
		return false;
	}
	if (GoatState(state) == CabbageState(state) && GoatState(state) != FarmerState(state))
	{
		return false;
	}
	return true;
}

void Solution()
{
	QueueArray<int> arrayQueue(20);
	int state[16], mover, newMover;
	for (int i = 0; i < 16; i++)
		state[i] = -1;
	arrayQueue.EnQueue(0x00);
	state[0] = 0;
	while (!arrayQueue.IsEmpty() && state[15] == -1)
	{
		mover = arrayQueue.GetFront();
		arrayQueue.DeQueue();
		for (int i = 1; i <= 8; i <<= 1)
		{
			if ((0 != (mover & 0x08)) == (0 != (mover & i)))
			{
				newMover = mover ^ (i | 0x08);
				if (IsSafe(newMover) && state[newMover] == -1)
				{
					arrayQueue.EnQueue(newMover);
					state[newMover] = mover;
				}
			}
		}
	}
	if (state[15] != -1)
	{
		cout << "The reverse path is:" << endl;
		for (int i = 15; i >= 0; i = state[i])
		{
			cout <<  i << endl;
			if (i == 0)
				exit(0);
		}
	}
	else
		cout << "No solution." << endl;

}

int main()
{
	Solution();
    return 0;
}

