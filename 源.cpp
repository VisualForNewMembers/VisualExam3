#include"func.h"

int main() {
	setmap1 map1;
	setplayer player;
	if (menu(&map1,&player)) {
		player.getplayername();
	}
	system("cls");
	gamehelp();
	system("pause");
	while (1) {
		setmonster monster[4] = {
		setmonster("Ö©Öë",15,10,30,10,30),
		setmonster("÷¼÷Ã",20,15,50,15,50),
		setmonster("òùòğ",30,20,70,20,70),
		setmonster("Ä§Íõ",35,25,150,30,100)
		};
		system("cls");
		printborad(player,map1);
		printmap(map1, player);
		moves(&player,&map1,monster);
		system("pause");
	}
	return 0;
}