#include "../include/character.hpp"
#include "../include/map.hpp"
character::character()
{
	x = 9; y = 14;//这里实际上是10，15
	//纵为x,横为y
}
void character::setPosition(char key)
{
	map m;
	switch (key)
	{
	case 'w':
		if (x > 0 && m.getPin(x-1,y)!=1)x--;
		break;
	case 's':
		if (x < 9 && m.getPin(x+1, y) != 1)x++;
		break;
	case 'a':
		if (y > 0 && m.getPin(x, y-1) != 1)y--;
		break;
	case 'd':
		if (y < 14 && m.getPin(x, y+1) != 1)y++;
		break;

	default:
		break;
	}
}
char character::getpts_x()
{
	return x;
}
char character::getpts_y()
{
	return y;
}