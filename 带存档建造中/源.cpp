#include"func.h"

int main() {
	cout << "----------»¶Ó­À´µ½Ä§Ëþ-----------" << endl;
	setplayer player;
	setmap1 map1;
	player.getplayername();
	while (1) {
		setmonster monster[4] = {
		setmonster("Ö©Öë",15,10,30,10,30),
		setmonster("÷¼÷Ã",20,15,50,15,50),
		setmonster("òùòð",30,20,70,20,70),
		setmonster("Ä§Íõ",35,25,150,30,100)
		};
		system("cls");
		printborad(player,map1);
		printmap(map1, player);
		moves(&player,&map1,monster);
		system("pause");
	}
}