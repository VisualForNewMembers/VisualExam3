#include<Windows.h>
#include "player.h"
#include<iostream>
#include"monster.h"
#include"map.h"
#include<fstream>
#include<io.h>
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); //红色
#define nop SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);   //原色
#define blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);			//蓝色
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);  //绿色
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  //白色
#define pink SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_BLUE);//粉色
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE);  //青色

void printborad(setplayer p,setmap1 map);
void printmonster(int i,setmonster *monster);
void moves(setplayer* player, setmap1* map,setmonster *monster);
bool vs(setplayer* player, int i,setmonster *monster);
void levelup(setplayer* player);
bool kill(setplayer *player);
int damage(int i,setmonster *monster,setplayer);
int getdamage(int i,setmonster *monster,setplayer );
void printmap(setmap1 map, setplayer player);
void save(setmap1 map,setplayer player);
void load(setmap1 *map, setplayer *player);
bool menu(setmap1 *map,setplayer *player);
void gamehelp();
void gamehelp() {
	white{
	cout << "-------------------------------------这是一个游戏帮助------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "输入w a s d并进行回车来进行移动" << endl;
	cout << "输入数字0进行游戏存档" << endl;
	cout << "下面是玩法介绍" << endl;
	cout << "%(蜘蛛)(level:1)  &(骷髅)(level:2)  ~(蝙蝠)(level 3)  B(魔王)(level 4)" << endl;
	cout << "+(回血包)回满血  !(钥匙)  D(锁上的门)  *(墙壁)  #(地图边界)  o(主角)" << endl;
	cout << "                 升级将会回满血                             " << endl;
	cout << "作者能力有限颜色随机变化，请见谅" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	}
}

void load(setmap1 *map,setplayer *player) {
	ifstream cundang;
	if (_access("version.txt", 0) == -1) {
		cout << "你还没有创建存档" << endl;
		system("pause");
		system("cls");
		menu(map, player);
	}
	else {
		cundang.open("version.txt", ios::in);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					cundang >> map->map1[i][j][k];
				}
			}
		}
		cundang >> player->attack;
		cundang >> player->rattack;
		cundang >> player->defensive;
		cundang >> player->hp;
		cundang >> player->hplimit;
		cundang >> player->exp;
		cundang >> player->key;
		cundang >> player->leavl;
		cundang >> player->x;
		cundang >> player->y;
		cundang >> player->playername;
		cundang >> map->ceng;
		cundang >> map->row;
		cundang >> map->column;
		cundang.close();
		system("cls");
		cout << "读档成功" << endl;
		system("pause");
	}
}
bool menu(setmap1 *map, setplayer *player) {
	white{
	cout << "欢迎来到魔塔     制作人:123456dfg " << endl;
	cout << "           请输入数字来进行操作     " << endl;
	cout << "  1.新建存档        2.读取存档        " << endl;
	}
	int select;
	cin >> select;
	switch (select) {
	case 1: 
		player->getplayername();
		return true;
		break;
	case 2:load(map,player);
		return false;
		break;
	}

}
void save(setmap1 map, setplayer player) {
	ofstream cundang;
	cundang.open("version.txt", ios::out);
	for(int k=0;k<2;k++){
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cundang <<map.map1[k][i][j] << ' ';
			}
			cundang << '\n';
		}
	}
	cundang << player.attack << '\n';
	cundang << player.rattack << '\n';
	cundang << player.defensive << '\n';
	cundang << player.hp << '\n';
	cundang << player.hplimit << '\n';
	cundang << player.exp << '\n';
	cundang << player.key << '\n';
	cundang << player.leavl << '\n';
	cundang << player.x << '\n';
	cundang << player.y << '\n';
	cundang << player.playername << '\n';
	cundang << map.ceng << '\n';
	cundang << map.row << '\n';
	cundang << map.column << '\n';
	system("cls");
	cout << "存档成功" << endl;
	cundang.close();
}

void levelup(setplayer* player) {
	if (player->exp >= 100) {
		cout << "你升级了" << endl;
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
		cout << "玩家死亡游戏结束" << endl;
		system("pause");
		return true;
	}
	else return false;
}
int damage(int i,setmonster *monster,setplayer player) {
	int flag;
	int attack;
	flag = player.attack+player.rattack - monster[i].defensive;
	if (flag > 0) {
		attack = flag;
	}
	else attack = player.rattack;
	return attack;
}
int getdamage(int i,setmonster *monster,setplayer player) {
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
	cout << "--------是否与" << monster[i].monstername << "对战(y/n)---------" << endl;
	printmonster(i,monster);
	cin >> tmp;
	switch (tmp)
	{
	case 'Y':case 'y':
		while (monster[i].hp >= 0) {
			player->hp -= getdamage(i, monster,*player);
			cout << "你受到了伤害:" << getdamage(i, monster,*player);
			monster[i].hp -= damage(i, monster,*player);
			cout << "你对" << monster[i].monstername << "造成了" << damage(i, monster,*player) << "伤害" << endl;
			if (kill(player)) {
				cout << "你被" << monster[i].monstername << "杀死了" << endl;
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
	cout << "请输入你的用户名" << endl;
	cin >> playername;
}
void printborad(setplayer p,setmap1 map) {
	white{
	cout << "----------------------------------------------------------------" << endl;
	cout << "玩家名:" << p.playername << endl;
	cout << "当前所在层数:" << map.ceng << endl;
	cout << "当前血量:" << p.hp << endl;
	cout << "当前经验:" << p.exp << endl;
	cout << "当前攻击力:" << p.attack << endl;
	cout << "当前防御力:" << p.defensive << endl;
	cout << "固定伤害:" << p.rattack << endl;
	cout << "当前等级" << p.leavl << endl;
	cout << "当前持有钥匙" << p.key << endl;
	cout << "当前坐标" << p.x << "," << p.y << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "按t键打开游戏帮助" << endl;
	}
}

void printmonster(int i,setmonster *monster) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "怪物名:" << monster[i].monstername << endl;
	cout << "当前血量" << monster[i].hp << endl;
	cout << "攻击力" << monster[i].attack << endl;
	cout << "防御力" << monster[i].defensive << endl;
	cout << "固定伤害" << monster[i].rattack << endl;
	cout << "可获取的经验" << monster[i].getexp << endl;
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
	case '0':save(*map, *player); break;
	case't':case'T':gamehelp(); break;
	}
	if (map->map1[map->ceng - 1][map->row][map->column] == 10) {
		map->map1[map->ceng - 1][tr][tl] = 10;
		map->map1[map->ceng - 1][map->row][map->column] = 12;

	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 0 || map->map1[map->ceng - 1][map->row][map->column] == 1) {
		cout << "无法越过边界和障碍" << endl;
		player->y = py; player->x = px;
		map->row = tr; map->column = tl;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 5) {
		map->map1[map->ceng - 1][map->row][map->column] = 12;
		map->map1[map->ceng - 1][tr][tl] = 10;
		cout << "获得一条钥匙" << endl;
		player->key += 1;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 8) {
		cout << "生命值已经回复" << endl;
		map->map1[map->ceng - 1][map->row][map->column] = 12;
		map->map1[map->ceng - 1][tr][tl] = 10;
		player->hp = player->hplimit;
	}
	else if (map->map1[map->ceng - 1][map->row][map->column] == 6) {
		player->y = py; player->x = px;

		if (player->key > 0) {
			cout << "是否使用一把钥匙开门" << endl;
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
			cout << "先去找一把钥匙吧" << endl;
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
				cout << "#";//地图边界
				break;
			case 1:red;
				cout << "*";//墙壁
				break;
			case 2:blue;
				cout << "%";//蜘蛛低级怪
				break;
			case 3:blue;
				cout << "&";//骷髅中级怪
				break;
			case 4:blue;
				cout << "~";//蝙蝠高级怪
				break;
			case 5:ching;
				cout << "!";//钥匙
				break;
			case 6:pink;
				cout << "D";//锁上的门
				break;
			case 7:white;
				cout << "B";//魔王
				break;
			case 8:
				green;
				cout << "+";//回血
				break;
			case 9:nop;
				cout << "/";//上楼梯
				break;
			case 10:cout << " ";//通道
				break;
			case 11:nop;
				cout << "\\";//下楼梯
				break;
			case 12:cout << "o";//角色位置
				break;
			}
		}
		cout << endl;
	}
}