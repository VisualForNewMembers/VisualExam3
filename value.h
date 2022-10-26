#include<iostream>
#include<string>
#include<stdlib.h>
#include<windows.h>
using namespace std;
const int X = 12;//��ͼ���
const int Y = 12;
typedef struct MONSTER {
	int hp;//����Ѫ��
	int attack;//���﹥����
	int defensive;//���������
	int getexp;//��ɱ���õľ���
	int trueattack;//����̶��˺�
}*monsterset;

typedef struct PLAYER {
	int hp;//��ҳ�ʼѪ��
	int attack;//��ҳ�ʼ������
	int defensive;//��ҳ�ʼ������
	int level;//��ҵȼ�
	int exp;//����ܾ���
	int x;//�������
	int y;//�������
	int hplimit;//���Ѫ������
	int trueattack;//��ҹ̶��˺�
	int key;//���Կ��
	string playername;//�������
}*playerset;

typedef struct MAP {
	char arr[X][Y] = {
		{'#','#','#','#','#','#','#','#','#','#','#','#'},//�߽� 1
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
		{'#','#','#','#','#','#','#','#','#','#','#','#'}//�߽� 12
	};  //1,  2,  3,  4 , 5,  6,  7   8   9   10  11  12
	int row;
	int column;
}*mapset;

void printplayer(string, playerset player);//�����Ϣ
void printmap(mapset map);
void moves(playerset player,mapset map);//2,4,6,8��������
bool vsmonster1(playerset player);//��ͼ��ֶ�ս
bool vsmonster2(playerset player);//���м��ֶ�ս
bool vsmonster3(playerset player);//��߼��ֶ�ս
bool vsboss(playerset player);//��boss��ս;
void levelup(playerset player);//��������
void heal(playerset player);//��Ѫ����;
void getkey(playerset player);//�õ�Կ��
void lose(playerset player);//�жϽ�ɫѪ��
void initplayer(playerset player);
int attrule(playerset player, monsterset monster);//��ɫ�˺�����
void freememory(monsterset monster1, monsterset monster2, monsterset monster3, monsterset boss);//�Ż��ڴ�
int attrule1(playerset player, monsterset monster);//�����˺�����
//�ͼ���֩��
monsterset monster1;
//�м�������
monsterset monster2;
//�߼�������
monsterset monster3;
//ħ��
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