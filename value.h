#include<iostream>
#include<string>
#include<stdlib.h>
#include<windows.h>
using namespace std;
const int X = 12;//地图规格
const int Y = 12;
typedef struct MONSTER {
	int hp;//怪物血量
	int attack;//怪物攻击力
	int defensive;//怪物防御力
	int getexp;//击杀后获得的经验
	int trueattack;//怪物固定伤害
}*monsterset;

typedef struct PLAYER {
	int hp;//玩家初始血量
	int attack;//玩家初始攻击力
	int defensive;//玩家初始防御力
	int level;//玩家等级
	int exp;//玩家总经验
	int x;//玩家坐标
	int y;//玩家坐标
	int hplimit;//玩家血量上限
	int trueattack;//玩家固定伤害
	int key;//玩家钥匙
	string playername;//玩家姓名
}*playerset;

typedef struct MAP {
	char arr[X][Y] = {
		{'#','#','#','#','#','#','#','#','#','#','#','#'},//边界 1
		{'#','*','*','%','*','*','%','*','*','*','*','#'},//10   2
		{'#',' ',' ',' ',' ','&','&',' ','B','B','/','#'},//9    3
		{'#','+',' ',' ','!','*','*','*','B','B','/','#'},//8    4
		{'#',' ',' ',' ',' ',' ','%','%',' ',' ','*','#'},//7    5
		{'#',' ','*','*','&','*','*','*','*','*','*','#'},//6    6
		{'#','%','*','*','*',' ',' ','&',' ',' ','D','#'},//5    7
		{'#',' ','*',' ',' ',' ',' ','*',' ','*','*','#'},//4    8
		{'#',' ','*','*','*',' ',' ','*','&','*','*','#'},//3    9
		{'#','%',' ',' ','%',' ',' ','*','+','*','*','#'},//2   10
		{'#','*','*','*','*',' ','o','*','*','*','*','#'},//1   11
		{'#','#','#','#','#','#','#','#','#','#','#','#'}//边界 12
	};  //1,  2,  3,  4 , 5,  6,  7   8   9   10  11  12
	int row;
	int column;
}*mapset;

void printplayer(string, playerset player);//玩家信息
void printmap(mapset map);
void moves(playerset player,mapset map);//2,4,6,8下左上右
bool vsmonster1(playerset player);//与低级怪对战
bool vsmonster2(playerset player);//与中级怪对战
bool vsmonster3(playerset player);//与高级怪对战
bool vsboss(playerset player);//与boss对战;
void levelup(playerset player);//升级机制
void heal(playerset player);//回血机制;
void getkey(playerset player);//得到钥匙
void lose(playerset player);//判断角色血量
void initplayer(playerset player);
int attrule(playerset player, monsterset monster);//角色伤害机制
void freememory(monsterset monster1, monsterset monster2, monsterset monster3, monsterset boss);//优化内存
int attrule1(playerset player, monsterset monster);//怪物伤害机制
//低级怪蜘蛛
monsterset monster1;
//中级怪骷髅
monsterset monster2;
//高级怪蝙蝠
monsterset monster3;
//魔王
monsterset boss;

int attrule(playerset player, monsterset monster) {
	int attack;
	attack = player->attack - monster->defensive;
	if (attack > 0) {
		attack = attack + player->trueattack;
	}
	else
		attack = player->trueattack;
	return attack;
}

int attrule1(playerset player, monsterset monster) {
	int attack;
	attack = monster->attack- player->defensive;
	if (attack > 0) {
		attack = monster->trueattack+attack;
	}
	else
		attack = monster->trueattack;
	return attack;
}
void freememory(monsterset monster1, monsterset monster2, monsterset monster3, monsterset boss) {
	free(monster1);
	free(monster2);
	free(monster3);
	free(boss);
}