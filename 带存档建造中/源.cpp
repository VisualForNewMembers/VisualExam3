#include"func.h"

int main() {
	cout << "----------��ӭ����ħ��-----------" << endl;
	setplayer player;
	setmap1 map1;
	player.getplayername();
	while (1) {
		setmonster monster[4] = {
		setmonster("֩��",15,10,30,10,30),
		setmonster("����",20,15,50,15,50),
		setmonster("����",30,20,70,20,70),
		setmonster("ħ��",35,25,150,30,100)
		};
		system("cls");
		printborad(player,map1);
		printmap(map1, player);
		moves(&player,&map1,monster);
		system("pause");
	}
}