#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class character
{
private:
	int x=14;
	int y=14;
	int HP=3;
	bool danger_trag=false;
public:
	character();
	void setPTs1(char key);
	void setPTs2(char key);
	int getpts_x();
	int getpts_y();
	int getHP();
	void setHP(int map_pin);
	void RST();
	
};

#endif 