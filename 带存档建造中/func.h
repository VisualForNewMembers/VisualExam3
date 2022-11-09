#include<Windows.h>
#include "player.h"
#include<iostream>
#include"monster.h"
#include"map.h"
#include<fstream>
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); //��ɫ
#define nop SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);   //ԭɫ
#define blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);			//��ɫ
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);  //��ɫ
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  //��ɫ
#define pink SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_BLUE);//��ɫ
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE);  //��ɫ

void printborad(setplayer p,setmap1 map);
void printmonster(int i,setmonster *monster);
void moves(setplayer* player, setmap1* map,setmonster *monster);
bool vs(setplayer* player, int i,setmonster *monster);
void levelup(setplayer* player);
bool kill(setplayer *player);
int damage(int i,setmonster *monster);
int getdamage(int i,setmonster *monster);
void printmap(setmap1 map, setplayer player);
void savemap();
void loadmap();

void levelup(setplayer* player) {
	if (player->exp >= 100) {
		cout << "��������" << endl;
		player->attack+=10;
		player->defensive+=5;
		player->hplimit+=20;
		player->hp = player->hplimit;
		player->exp =player->exp-100;
		player->leavl += 1;
		system("pause");
	}
}

bool kill(setplayer* player) {
	if (player->hp <= 0) {
		cout << "���������Ϸ����" << endl;
		return true;
	}
	else return false;
}
int damage(int i,setmonster *monster) {
	setplayer player;
	int flag;
	int attack;
	flag = player.attack+player.rattack - monster[i].defensive;
	if (flag > 0) {
		attack = flag;
	}
	else attack = player.rattack;
	return attack;
}
int getdamage(int i,setmonster *monster) {
	setplayer player;
	int flag;
	int getattack;
	flag = monster[i].attack+monster[i].rattack - player.defensive;
	if (flag > 0) {
		getattack = flag;
	}
	else getattack = monster[i].rattack;
	return getattack;
}

bool vs(setplayer* player,int i,setmonster *monster) {
	char tmp;
	cout << "--------�Ƿ���" << monster[i].monstername << "��ս(y/n)---------" << endl;
	printmonster(i,monster);
	cin >> tmp;
	switch (tmp)
	{
	case 'Y':case 'y':
		while (monster[i].hp >= 0) {
			player->hp -= getdamage(i, monster);
			cout << "���ܵ����˺�:" << getdamage(i, monster);
			monster[i].hp -= damage(i, monster);
			cout << "���" << monster[i].monstername << "�����" << damage(i, monster) << "�˺�" << endl;
			if (kill(player)) {
				cout << "�㱻" << monster[i].monstername << "ɱ����" << endl;
				exit(1);
			}
		}
		player->exp += monster[i].getexp;
		levelup(player);
		return true;
			break;
	case 'n':case 'N':
		return false;
		break;
	}
}




void setplayer::getplayername() {
	cout << "����������û���" << endl;
	cin >> playername;
}
void printborad(setplayer p,setmap1 map) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "�����:" << p.playername << endl;
	cout << "��ǰ���ڲ���:" << map.ceng << endl;
	cout << "��ǰѪ��:" << p.hp << endl;
	cout << "��ǰ����:" << p.exp << endl;
	cout << "��ǰ������:" << p.attack << endl;
	cout << "��ǰ������:" << p.defensive << endl;
	cout << "�̶��˺�:" << p.rattack << endl;
	cout << "��ǰ�ȼ�" << p.leavl << endl;
	cout << "��ǰ����Կ��" << p.key << endl;
	cout << "��ǰ����" << p.x << "," << p.y<<endl;
	cout << "----------------------------------------------------------------" << endl;
}

void printmonster(int i,setmonster *monster) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "������:" << monster[i].monstername << endl;
	cout << "��ǰѪ��" << monster[i].hp << endl;
	cout << "������" << monster[i].attack << endl;
	cout << "������" << monster[i].defensive << endl;
	cout << "�̶��˺�" << monster[i].rattack << endl;
	cout << "�ɻ�ȡ�ľ���" << monster[i].getexp << endl;
	cout << "----------------------------------------------------------------" << endl;
}

void moves(setplayer* player, setmap1* map, setmonster* monster) {
	char dir;
	cin >> dir;
	int px = player->x, py = player->y, tr = map->row, tl = map->column, ceng = 1;
	switch (dir) {
	case 'w':case'W':map->row -= 1; player->y += 1; break;
	case 's':case'S':map->row += 1; player->y -= 1; break;
	case 'a':case'A':map->column -= 1; player->x -= 1; break;
	case 'd':case'D':map->column += 1; player->x += 1; break;
	}
	if (map->map1[map->ceng - 1][map->row][map->column] == 10) {
		map->map1[map->ceng - 1][tr][tl] = 10;
		map->map1[map->ceng - 1][map->row][map->column] = 12;

	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 0 || map->map1[map->ceng - 1][map->row][map->column] == 1) {
		cout << "�޷�Խ���߽���ϰ�" << endl;
		player->y = py; player->x = px;
		map->row = tr; map->column = tl;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 5) {
		map->map1[map->ceng - 1][map->row][map->column] = 12;
		map->map1[map->ceng - 1][tr][tl] = 10;
		cout << "���һ��Կ��" << endl;
		player->key += 1;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 8) {
		cout << "����ֵ�Ѿ��ظ�" << endl;
		map->map1[map->ceng - 1][map->row][map->column] = 12;
		map->map1[map->ceng - 1][tr][tl] = 10;
		player->hp = player->hplimit;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 6) {
		player->y = py; player->x = px;

		if (player->key > 0) {
			cout << "�Ƿ�ʹ��һ��Կ�׿���" << endl;
			char tmp;
			cin >> tmp;
			switch (tmp) {
			case 'y':
				map->map1[map->ceng - 1][map->row][map->column] = 10;
				map->row = tr; map->column = tl;
				player->key -= 1;
				break;
			case 'n':
				break;
			}
		}
		else {
			cout << "��ȥ��һ��Կ�װ�" << endl;
			player->y = py; player->x = px;
			map->row = tr; map->column = tl;
		}
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 2) {
		if (vs(player, 0, monster)) {
			map->map1[map->ceng - 1][map->row][map->column] = 12;
			map->map1[map->ceng - 1][tr][tl] = 10;
		}
		else {
			player->y = py; player->x = px;
			map->row = tr; map->column = tl;
		}
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 3) {
		if (vs(player, 1, monster)) {
			map->map1[map->ceng - 1][map->row][map->column] = 12;
			map->map1[map->ceng - 1][tr][tl] = 10;
		}
		else {
			player->y = py; player->x = px;
			map->row = tr; map->column = tl;
		}
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 4) {
		if (vs(player, 2, monster)) {
			map->map1[map->ceng - 1][map->row][map->column] = 12;
			map->map1[map->ceng - 1][tr][tl] = 10;
		}
		else {
			player->y = py; player->x = px;
			map->row = tr; map->column = tl;
		}
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 7) {
		if (vs(player, 3, monster)) {
			map->map1[map->ceng - 1][map->row][map->column] = 12;
			map->map1[map->ceng - 1][tr][tl] = 10;
		}
		else {
			player->y = py; player->x = px;
			map->row = tr; map->column = tl;
		}
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 9) {
		map->map1[map->ceng - 1][tr][tl] = 10;
		map->ceng += 1;
		player->x = 0;
		player->y = 0;
		map->row =11 ;
		map->column =1;
		map->map1[map->ceng - 1][map->row][map->column] = 12;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 11) {
		map->map1[map->ceng - 1][tr][tl] = 10;
		map->ceng -= 1;
		player->x = 10;
		player->y = 8;
		map->row =4 ;
		map->column = 10;
		map->map1[map->ceng - 1][map->row][map->column] = 12;
	}
}

void printmap(setmap1 map, setplayer player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			switch (map.map1[map.ceng-1][i][j]) {
			case 0:red;
				cout << "#";//��ͼ�߽�
				break;
			case 1:red;
				cout << "*";//ǽ��
				break;
			case 2:blue;
				cout << "%";//֩��ͼ���
				break;
			case 3:blue;
				cout << "&";//�����м���
				break;
			case 4:blue;
				cout << "~";//����߼���
				break;
			case 5:ching;
				cout << "!";//Կ��
				break;
			case 6:pink;
				cout << "D";//���ϵ���
				break;
			case 7:white;
				cout << "B";//ħ��
				break;
			case 8:
				green;
				cout << "+";//��Ѫ
				break;
			case 9:nop;
				cout << "/";//��¥��
				break;
			case 10:cout << " ";//ͨ��
				break;
			case 11:nop;
				cout << "\\";//��¥��
				break;
			case 12:cout << "o";//��ɫλ��
				break;
			}
		}
		cout << endl;
	}
}