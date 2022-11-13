#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<fstream>
using namespace std;
int key = 0;

//������Һ͹�������
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
СС�� = { 37,30,100,50,5,20,50 },
С�� = { 38,40,7,130,20,30,200 },
��� = { 126,80,20,200,40,70,400 };

//���õ�ͼ
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
void game_document_keep(char wor[]) {//��Ϸ�浵 
	ofstream ofs;
	ofs.open("��Ϸ�浵.text", ios::app);
	ofs << wor << endl;
	ofs.close();
}
void game_document_read() {//���� 
	char a[1024];
	ifstream ifs;
	ifs.open("��Ϸ�浵.text", ios::in);
	while (ifs >> a)
		cout << a << endl;
	ifs.close();
}

//��ʾ��������
void clear() {
	cout << "���Ѫ��" << Hero.boold_max << endl;
	cout << "Ѫ����" << Hero.hp << endl;
	cout << "������" << Hero.att << endl;
	cout << "������" << Hero.df << endl;
	cout << "����ֵ��" << Hero.exp << endl;
	cout << "�ȼ���" << Hero.lv << endl;
	cout << "Կ��������" << key << endl;
}
//�����ս���ĺ���
int PK(struct character M) {
	while (Hero.hp > 0 && M.hp > 0) {
		system("cls");
		cout << M.name << ":" << endl;
		cout << "Ѫ����" << M.hp << endl;
		cout << "�ȼ���" << M.lv << endl;
		system("pause");//ÿ�������غ���ʾ�����Ѫ���� 
		Hero.hp = Hero.hp - M.att + Hero.df;   //��������˺�=�˺�-�з�����
		M.hp = M.hp - Hero.att + M.df;
		if (Hero.hp <= 0) {
			cout << "�����ˣ���Ϸ����" << endl; //�����������Ϸ����
			char wor[] = "�����ˣ���Ϸ����";
			game_document_keep(wor);
			exit(1);
		}
		else if (M.hp <= 0) {//���ܹ���õ�����ľ��� 
			Hero.exp =Hero.exp+M.exp;
			if (Hero.exp >= 50) {
				Hero.lv += Hero.exp % 50;
				if (Hero.exp % 50 > 0) {//�������������� �����������Ѫ�� 
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
//��Ϸ�¼��ĺ���
int x_move(int x, int y, char map[10][20]) {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 19; j++) {
			if (map[i][j] == 72) {
				if (map[x][y] == 32) {
					map[x][y] = 72;
					map[i][j] = 32;
				}
				else if (map[x][y] == 33) {//Կ�� ������33 
					map[x][y] = 72;
					map[i][j] = 32;
					key++;
				}
				else if (map[x][y] == 68) {//�� ��D�� 68
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
					
						if (PK(СС��) == 2) {
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
				
						if (PK(С��) == 2) {
							map[x][y] = 72;
							map[i][j] = 32;
						}
					
				}
				else if (map[x][y] == 126) {
					
						if (PK(���) == 2) {
							map[x][y] = 72;
							map[i][j] = 32;
						}
					
				}
				else if (map[x][y] == 47) {//¥�� ��/��47 
					map[x][y] = 72;
					map[i][j] = 47;
					return 1;
				}
				else if (map[x][y] == 92) {//�ص���һ��ͼ��¥�� ��\'92 
					map[x][y] = 72;
					map[i][j] = 92;
					return 2;
				}
			}
		}
	}

}

//��ȡ�û�����
int move(char map[10][20])
{
	int i, j;
	char ch;
	while (1) {
		ch = _getch();
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 19; j++) {
				if (map[i][j] == Hero.name[0]) {
					switch (ch)//���̲���
					{
					case 'q': {//�˳���Ϸ 
						char wor[] = "�ֶ��˳���Ϸ";
						game_document_keep(wor);
						exit(1);
					}
					case 'r': {//���� 
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
					}//�� 

					case 's': {
						switch (x_move(++i, j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//�� 

					case 'a': {
						switch (x_move(i, --j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//�� 
					case 'd': {
						switch (x_move(i, ++j, map)) {
						case 1:return 1; break;
						case 2:return 2; break;
						}
						break;
					}//�� 
					}
					system("cls");
					for (i = 0; i < 10; i++) {//������ͼ 
						for (j = 0; j < 20; j++) {
							cout << map[i][j];
						}
						cout << endl;
					}
					clear();//���Ӣ�۵����Խ��м��		
				}
			}
		}
	}
}
int main() {
	cout << "��Ŭ�����������ֻ�е���һ���ȼ�����п��ܴ�Ӯboss" << endl;
	cout << "��ʹ��wsad����Ӣ��" << endl;
	cout << "��q �˳���Ϸ" << '\t' << "��r ��ȡ�浵" << endl;
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
		char wor[] = "˳��ͨ��";
		game_document_keep(wor);
		cout << "��ϲ��˳��ͨ��" << endl;
		cout << "���ߣ�������" << endl;
		system("pause");
		break;
	}
	}



}
return 0;
}