#include "../include/map.hpp"




void map::MapUpdate(char x,char y)
{
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (x == i && y == j) { pin[i][j]=2; }
			else if(pin[i][j]!=1) pin[i][j]=0;
		}
	}
}
int map::getPin(int x, int y) { return pin[x][y]; }