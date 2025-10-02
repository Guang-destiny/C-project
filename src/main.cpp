#include <iostream>
#include "../include/map.hpp"
#include "../include/character.hpp"
using namespace std;

int main() {

	map myMap;
	character myCharacter;
	myMap.printMap(myCharacter.getpts_x(), myCharacter.getpts_y());
	cout << endl;
	char a;
	while (1)
	{
		cin >> a;
		cout << endl;
		if (a == 'q')break;
		myCharacter.setPosition(a);
		myMap.printMap(myCharacter.getpts_x(), myCharacter.getpts_y());
		cout<< endl;
	}

	return 0;
	
}
