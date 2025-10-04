#include "../include/map.hpp"



int map::getPTs1(int x, int y) 
{ 
	return map1[x][y]; 
}

int map::getPTs2(int x, int y) 
{ 
	return map2[x][y]; 
}

int map::getrow()
{
	return row;
}
int map::getcol()
{
	return col;
}
void map::setPTs1(int x,int y,int value)
{
	map1[x][y]=value;
}
void map::setPTs2(int x,int y,int value)
{
	map2[x][y]=value;
}
