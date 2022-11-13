#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<fstream>
using namespace std;
int key = 0;

//设置玩家和怪物属性
struct character {
	char name[1];
	int exp;
	int lv;
	int hp;
	int df;
	int att;
	int boold_max;
}Hero = { 72,0,0,200,30,80,300 },
BOSS = { 66,100,50,2500,150,160,3000 },
小小怪 = { 37,30,100,50,5,20,50 },
小怪 = { 38,40,7,130,20,30,200 },
大怪 = { 126,80,20,200,40,70,400 };

//设置地图
char map1[10][20] = { {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35},
					 {35,32,32,32,42,32,32,32,32,32,32,32,32,32,32,37,32,32,126,35},
					 {35,37,43,37,42,32,32,32,32,32,32,32,32,32,32,42,32,42,33,35},
					 {35,32,37,32,42,32,32,42,38,32,42,42,42,32,42,32,42,32,33,35},
					 {35,32,32,32,42,32,32,42,32,38,32,32,42,32,42,32,32,68,32,35},
					 {35,32,32,72,42,32,37,32,32,32,126,32,42,32,32,32,42,42,32,35},
					 {35,32,32,32,32,32,32,32,37,32,32,32,42,32,32,68,47,42,32,35},
					 {35,32,32,32,32,32,32,32,32,32,32,32,68,32,32,32,42,32,42,35},
					 {35,32,32,32,32,32,32,32,32,32,32,32,42,32,32,32,32,32,32,35},
					 {35,35,35,35,35,35,35,35,35,35,35,35,42,35,35,35,35,35,35,35} };

char map2[10][20] = { {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35},
					 {35,92,32,72,32,32,32,32,32,42,32,32,32,42,32,126,32,32,33,35},
					 {35,38,32,32,32,32,32,32,68,32,32,32,32,68,32,32,32,126,32,35},
					 {35,32,37,32,32,32,32,42,32,32,32,32,42,42,32,42,42,68,42,35},
					 {35,32,126,32,32,32,42,32,32,32,33,32,42,35,42,32,32,32,32,35},
					 {35,37,32,32,38,42,42,35,35,68,35,35,42,35,43,38,32,32,66,35},
					 {35,32,38,126,33,42,42,32,32,32,32,32,43,35,35,35,35,66,47,35},
					 {35,32,126,32,42,42,36,36,38,42,42,38,36,35,32,32,32,32,32,35},
					 {35,42,42,42,42,42,33,32,32,32,32,42,42,42,42,42,42,42,42,35},
					 {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35} };
void game_document_keep(char wor[]) {//游戏存档 
	ofstream ofs;
	ofs.open("游戏存档.text", ios::app);
	ofs << wor << endl;
	ofs.close();
}
void game_document_read() {//读档 
	char a[1024];
	ifstream ifs;
	ifs.open("游戏存档.text", ios::in);
	while (ifs >> a)
		cout << a << endl;
	ifs.close();
}

//显示勇者属性
void clear() {
	cout << "最大血量" << Hero.boold_max << endl;
	cout << "血量：" << Hero.hp << endl;
	cout << "攻击力" << Hero.att << endl;
	cout << "防御力" << Hero.df << endl;
	cout << "经验值：" << Hero.exp << endl;
	cout << "等级：" << Hero.lv << endl;
	cout << "钥匙数量：" << key << endl;
}
//与怪物战斗的函数
int PK(struct character M) {
	while (Hero.hp > 0 && M.hp > 0) {
		system("cls");
		cout << M.name << ":" << endl;
		cout << "血量：" << M.hp << endl;
		cout << "等级：" << M.lv << endl;
		system("pause");//每个攻击回合显示怪物的血量等 
		Hero.hp = Hero.hp - M.att + Hero.df;   //最终造成伤害=伤害-敌方防御
		M.hp = M.hp - Hero.att + M.df;
		if (Hero.hp <= 0) {
			cout << "你死了，游戏结束" << endl; //玩家死亡后游戏结束
			char wor[] = "你死了，游戏结束";
			game_document_keep(wor);
			exit(1);
		}
		else if (M.hp <= 0) {//击败怪物得到怪物的经验 
			Hero.exp =Hero.exp+M.exp;
			if (Hero.exp >= 50) {
				Hero.lv += Hero.exp % 50;
				if (Hero.exp % 50 > 0) {//升级后提升攻击 防御力和最大血量 
					Hero.att += 20;
					Hero.boold_max += 30;
					Hero.df += 20;
					Hero.hp = Hero.boold_max;
				}
				Hero.exp = Hero.exp / 50;
			}
			return 2;
		}
	}
}
//游戏事件的函数
int x_move(int x, int y, char map[10][20]) {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 19; j++) {
			if (map[i][j] == 72) {
				if (map[x][y] == 32) {
					map[x][y] = 72;
					map[i][j] = 32;
				}
				else if (map[x][y] == 33) {//钥匙 ‘！’33 
					map[x][y] = 72;
					map[i][j] = 32;
					key++;
				}
				else if (map[x][y] == 68) {//门 ‘D’ 68
					if (key > 0) {
						map[x][y] = 72;
						map[i][j] = 32;
						key--;
					}
				}
				else if (map[x][y] == 43) {
					map[x][y] = 72;
					map[i][j] = 32;
					Hero.hp += 100;
				}
				else if (map[x][y] == 37) {
					
						if (PK(小小怪) == 2) {
							map[x][y] = 72;
							map[i][j] = 32;
						}
				}
				else if (map[x][y] == 66) {
					
						if (PK(BOSS) == 2) {
							map[x][y] = 72;
							map[i][j] = 32;
						}
					
				}
				else if (map[x][y] == 38) {
				
						if (PK(小怪) == 2) {
							map[x][y] = 72;
							map[i][j] = 32;
						}
					
				}
				else if (map[x][y] == 126) {
					
						if (PK(大怪) == 2) {
							map[x][y] = 72;
							map[i][j] = 32;
						}
					
				}
				else if (map[x][y] == 47) {//楼梯 ‘/’47 
					map[x][y] = 72;
					map[i][j] = 47;
					return 1;
				}
				else if (map[x][y] == 92) {//回到上一张图的楼梯 ‘\'92 
					map[x][y] = 72;
					map[i][j] = 92;
					return 2;
				}
			}
		}
	}

}

//获取用户操作
int move(char map[10][20])
{
	int i, j;
	char ch;
	while (1) {
		ch = _getch();
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 19; j++) {
				if (map[i][j] == Hero.name[0]) {
					switch (ch)//键盘操作
					{
					case 'q': {//退出游戏 
						char wor[] = "手动退出游戏";
						game_document_keep(wor);
						exit(1);
					}
					case 'r': {//读档 
						game_document_read();
						system("pause");
						break;
					}
					case 'w': {
						switch (x_move(--i, j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//上 

					case 's': {
						switch (x_move(++i, j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//下 

					case 'a': {
						switch (x_move(i, --j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//左 
					case 'd': {
						switch (x_move(i, ++j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//右 
					}
					system("cls");
					for (i = 0; i < 10; i++) {//画出地图 
						for (j = 0; j < 20; j++) {
							cout << map[i][j];
						}
						cout << endl;
					}
					clear();//输出英雄的属性进行监控		
				}
			}
		}
	}
}
int main() {
	cout << "请努力打怪升级，只有到达一定等级后才有可能打赢boss" << endl;
	cout << "请使用wsad控制英雄" << endl;
	cout << "按q 退出游戏" << '\t' << "按r 读取存档" << endl;
	system("pause");
	system("cls");
	int i, j;
c:	for (i = 0; i < 10; i++) {
	for (j = 0; j < 20; j++) {
		cout << map1[i][j];
	}
	cout << endl;
}

if (move(map1) == 1) {
	switch (move(map2)) {
	case 2: {
		system("cls");
		goto c;
		break;
	}
	case 1: {
		char wor[] = "顺利通关";
		game_document_keep(wor);
		cout << "恭喜你顺利通关" << endl;
		cout << "作者：李永浩" << endl;
		system("pause");
		break;
	}
	}



}
return 0;
}