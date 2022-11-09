#pragma once
#include<string>
using namespace std;
class setmonster {
public:
	int hp;
	string monstername;
	int attack;
	int rattack;
	int defensive;
	int getexp;
	setmonster(string mm, int att, int ratt, int hp, int defensive, int getexp) {
		monstername = mm;
		attack = att;
		rattack = ratt;
		this->hp = hp;
		this->defensive = defensive;
		this->getexp = getexp;
	}
};
