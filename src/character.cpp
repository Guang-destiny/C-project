#include "../include/character.hpp"
#include "../include/map.hpp"
character::character()
{
	x = 14; y = 14;
}
void character::setPTs1(char key)
{
	map m;
	switch (key)
	{
	case 'w':
		if (x > 0 && m.getPTs1(x-1,y)!=1)x--;
		break;
	case 's':
		if (x < 14 && m.getPTs1(x+1, y) != 1)x++;
		break;
	case 'a':
		if (y > 0 && m.getPTs1(x, y-1) != 1)y--;
		break;
	case 'd':
		if (y < 14 && m.getPTs1(x, y+1) != 1)y++;
		break;

	default:
		break;
	}
}
void character::setPTs2(char key)
{
	map m;
	switch (key)
	{
	case 'w':
		if (x > 0 && m.getPTs2(x-1,y)!=1)x--;
		break;
	case 's':
		if (x < 14 && m.getPTs2(x+1, y) != 1)x++;
		break;
	case 'a':
		if (y > 0 && m.getPTs2(x, y-1) != 1)y--;
		break;
	case 'd':
		if (y < 14 && m.getPTs2(x, y+1) != 1)y++;
		break;

	default:
		break;
	}
}
int character::getpts_x()
{
	return x;
}
int character::getpts_y()
{
	return y;
}
void character::setHP(int map_pin)
{
	map m;
	if(danger_trag==false&&map_pin==2)
	{
		HP--;
		danger_trag=true;
	}
	else if(map_pin!=2) danger_trag=false;
}
int character::getHP()
{
	return HP;
}

void character::RST()
{
	HP=3;
	x=14;
	y=14;

}