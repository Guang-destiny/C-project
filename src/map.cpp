#include "../include/map.hpp"
#include <iostream>	
using namespace std;



void map::printMap(char x,char y)
{
	//x,y不可能为10，15；需要减一
	for (int i = 0; i < 10; i++)
	{
		cout << "|";
		for (int j = 0; j < 15; j++)
		{
			if (x == i && y == j) { cout << "A"; }
			else 
			{
				if (pin[i][j] == 0)cout << " ";
				else cout << "#";
			}
		}
		cout << "|";
		cout << endl;
	}
}
char map::getPin(int x, int y) { return pin[x][y]; }