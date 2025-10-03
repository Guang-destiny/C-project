#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class character
{
private:
	int x=9;
	int y=14;
public:
	character();
	void setPosition(char key);
	int getpts_x();
	int getpts_y();
};

#endif 