#ifdef UNICODE
#undef UNICODE
#endif 
#include<graphics.h>
#include <iostream>
#include <easyx.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#include <conio.h> 
#include <fstream>


using namespace std;
#define ROW 20
#define COL 20
#define SIZE 25//�����С



int k=0,x=11, y=6;//���ߵ�λ��

int HP = 100, LV = 1, DEF = 20, ATK = 30, EXP = 0;//����״̬
int key = 0;//����Կ������

enum {��,��,ǽ,��,��,��,ħ,��,��,��,��,��,��};//ö�����õķ���


int map[3][ROW][COL] = {{
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,��,ǽ,},
{ǽ,��,��,��,��,��,ǽ,��,��,��,ǽ,��,ǽ,},
{ǽ,��,��,��,ǽ,��,ǽ,��,��,��,ǽ,��,ǽ,},
{ǽ,ǽ,��,ǽ,ǽ,��,ǽ,ǽ,ǽ,��,ǽ,��,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,��,��,ǽ,��,ǽ,},
{ǽ,��,��,��,ǽ,��,ǽ,ǽ,ǽ,ǽ,ǽ,��,ǽ,},
{ǽ,ǽ,��,ǽ,ǽ,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,ǽ,ǽ,��,ǽ,ǽ,ǽ,��,ǽ,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,ǽ,��,��,��,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,ǽ,��,��,��,ǽ,},
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,},
},{
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,��,ǽ,},
{ǽ,��,��,��,��,��,ǽ,��,��,��,ǽ,��,ǽ,},
{ǽ,��,��,��,ǽ,��,ǽ,��,��,��,ǽ,��,ǽ,},
{ǽ,ǽ,��,ǽ,ǽ,��,ǽ,ǽ,ǽ,��,ǽ,��,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,��,��,ǽ,��,ǽ,},
{ǽ,��,��,��,ǽ,��,ǽ,ǽ,ǽ,ǽ,ǽ,��,ǽ,},
{ǽ,ǽ,��,ǽ,ǽ,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,ǽ,ǽ,��,ǽ,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,ǽ,��,��,��,ǽ,},
{ǽ,��,��,��,ǽ,��,��,��,ǽ,��,��,��,ǽ,},
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,},
},{
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,ħ,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,��,��,��,��,��,��,��,��,��,��,��,ǽ,},
{ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,ǽ,},
} };





const char* text[]= {"  ","��","ǽ","��","��","��","ħ","��","��","��","��","��","��"};
//�����ַ�������������ͼ


//�����ά����

void mapDraw()
{
	BeginBatchDraw();//˫�����ֹ������˸����
	cleardevice();//����ˢ��
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < COL; j++)
			outtextxy(j * SIZE, i * SIZE, text[map[k][i][j]]);//����ڽ��棬x-�У�y-��
	char a[8]; char b[8]; char c[8]; char d[8]; char e[8]; char f[8];
	sprintf_s(a, "%d", HP); outtextxy(0, 325,"Ѫ����"); outtextxy(60, 325, a);//��ʾѪ��
	sprintf_s(b, "%d", DEF); outtextxy(110, 325, "������"); outtextxy(160, 325, b);
	sprintf_s(c, "%d", ATK); outtextxy(210, 325, "������"); outtextxy(260, 325, c);
	sprintf_s(d, "%d", LV); outtextxy(0, 350, "�ȼ���"); outtextxy(60, 350, d);
	sprintf_s(e, "%d", EXP); outtextxy(110, 350, "���飺"); outtextxy(160, 350, e);
	sprintf_s(f, "%d", key); outtextxy(210, 350, "Կ�ף�"); outtextxy(260, 350, f);
	EndBatchDraw();

}






//ս������
int fightyao()//������
{
	int MHP = 100, MDEF = 20, MATK = 20;//����״̬
	for (1; HP > 0 && MHP > 0;)
	{
		printf("����ʹ�ûӿ�\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("����ʤ����\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("���ߵȼ�������\n");
			}
			return 1;
		}
		printf("���﷢���˹���\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
			if (HP <= 0)
			{
				printf("���ߵ�����\n");
				return 0;
			}
	}
}


int fightguai()
{
	int MHP = 200, MDEF = 20, MATK = 10;//�ֵ�״̬
	for (1; HP > 0 && MHP > 0;)
	{
		printf("����ʹ�ûӿ�\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("����ʤ����\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("���ߵȼ�������\n");
			}
			return 1;
		}
		printf("���﷢���˹���\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
		if (HP <= 0)
		{
			printf("���ߵ�����\n");
			return 0;
		}
	}
}


int fightgui()
{
	int MHP = 150, MDEF = 10, MATK = 30;//���״̬
	for (1; HP > 0 && MHP > 0;)
	{
		printf("����ʹ�ûӿ�\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("����ʤ����\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("���ߵȼ�������\n");
			}
			return 1;
		}
		printf("���﷢���˹���\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
		if (HP <= 0)
		{
			printf("���ߵ�����\n");
			return 0;
		}
	}
}


int fightmo()
{
	int MHP = 1000, MDEF = 50, MATK = 100;//ħ����״̬
	for (1; HP > 0 && MHP > 0;)
	{

		printf("����ʹ�ûӿ�\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("ħ��������ˣ����߻��������ʤ��\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("���ߵȼ�������\n");
			}
			return 1;
		}
		printf("ħ�������˹���\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
		if (HP <= 0)
		{
			printf("���ߵ�����\n");
			return 0;
		}
	}
}
//�ƶ�
void move(int vx, int vy)
{
	if (map[k][x + vx][y + vy] == ��)
	{
		map[k][x + vx][y + vy] += 1;
		map[k][x][y] -= 1;
		x = x + vx;
		y = y + vy;
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		if (key > 0)
		{
			printf("======================================\n");
			printf("����һ��Կ��������\n");
			map[k][x + vx][y + vy] -= 3;
			key -= 1;
		}
		else if (key <= 0)
		{
			printf("======================================\n");
			printf("ȱ��Կ�ף��޷�����\n");
		}
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		printf("======================================\n");
		HP += 50;
		printf("HP�ظ�50\n");
		map[k][x + vx][y + vy] -= 4;
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		printf("======================================\n");
		printf("����������\n");
		if (fightyao() == 0)
		{
			map[k][x][y] -= 1;
			printf("��Ϸ����\n");
		}
		else
			map[k][x + vx][y + vy] -= 7;
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		printf("======================================\n");
		printf("����������\n");
		if (fightguai() == 0)
		{
			map[k][x][y] -= 1;
			printf("��Ϸ����\n");
		}
		else
			map[k][x + vx][y + vy] -= 8;
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		printf("======================================\n");
		printf("����������\n");
		if (fightgui() == 0)
		{
			map[k][x][y] -= 1;
			printf("��Ϸ����\n");
		}
		else
			map[k][x + vx][y + vy] -= 9;
	}
	else if (map[k][x + vx][y + vy] ==ħ )
	{
		printf("======================================\n");
		printf("������ħ�����潻��\n");
		if (fightmo() == 0)
		{
			map[k][x][y] -= 1;
			printf("��Ϸ����\n");
		}
		else
			map[k][x + vx][y + vy] -= 6;
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		printf("======================================\n");
		printf("���һ��Կ�ף����Դ�һ����\n");
		key += 1;
		map[k][x + vx][y + vy] -= 5;
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		k++;
		map[k][x][y] += 1;
		map[k - 1][x][y] -= 1;
		printf("======================================\n");
		printf("����һ��¥\n");
	}
	else if (map[k][x + vx][y + vy] == ��)
	{
		k--;
		map[k+1][x][y] -= 1;
		map[k][x][y] += 1;
		printf("======================================\n");
		printf("����һ��¥");
	}

}








int player()//�������ߵ���Ϊ
{
	ExMessage m = { 0 };//������Ϣ
	m = getmessage(EM_KEY);//ֻ��ȡ������Ϣ
	
	switch (m.message)
	{
	case WM_KEYDOWN:
		switch (m.vkcode)
		{
		case VK_UP: //��
		{
			move(-1, 0);
			break;
		}
		case VK_DOWN://��
		{
			move(1, 0);
		}break;
		case VK_LEFT://��
		{
			move(0, -1);
		}break;
		case VK_RIGHT://��
		{
			move(0, 1);
		}break;
		case '1':
		{cout << "save the game" << endl;
		ofstream outfile;
		outfile.open("save.txt");
		/*for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				outfile << map[k][i][j];
			}outfile << endl;
		}*/
		//outfile << k << endl;
		//outfile << x << endl;
		//outfile << y << endl;
		outfile << HP << endl;
		outfile << ATK << endl;
		outfile << DEF << endl;
		outfile << EXP << endl;
		outfile << LV << endl;
		outfile << key << endl;
		outfile.close();//key '1'save the game;
		}break;
		case'2'://key'2'loading game;
		{int i = 0, j = 0;
		int map2[2][20][20] = {};
			ifstream infile;
			infile.open("save.txt");
		/*	for (i = 0; i < 20; i++)
				for (j = 0; j < 20; j++)
				{
					infile >> map[k][i][j];
				}*/
			/*for (i = 0; i < 20; i++)
			{
				for (j = 0; j < 20; j++)
					map2[k][i][j] = map[k][i][j];
			}*/
			int HPs, ATKs, DEFs, EXPs, LVs,keys/*, ks, xs, ys*/;
			/*infile >> k; ks = k;
			infile >> x; xs = x;
			infile >> y; ys = y;*/
			infile >> HP; HPs = HP;
			infile >> ATK; ATKs = ATK;
			infile >> DEF; DEFs = DEF;
			infile >> EXP; EXPs = EXP;
			infile >> LV; LVs = LV;
			infile >> key; keys = key;
				infile.close(); 
				/*for (i = 0; i < 20; i++)
				{
					for (j = 0; j < 20; j++)
					{
						map[k][i][j] = map2[k][i][j];
					}
				}*/
				/*k = ks; x = xs; y = ys; */HP = HPs; ATK = ATKs; DEF = DEFs; EXP = EXPs; LV = LVs; key = keys;
				//for (i = 0; i < 20; i++)
				//{
				//	for (j = 0; j < 20; j++)
				//	{
				//		cout << map2[k][i][j];
				//	}cout << endl;
				//}
				break;
		}
		}
		return 0;
	}
}




int main()
{
	mciSendString("open bgm.mp3 alias bgm", 0, 0, 0);//�򿪱�������
	mciSendString("setaudio bgm to 175", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
	initgraph(COL * SIZE, ROW * SIZE,1);//����ͼ�ν���
	settextstyle(SIZE, 0, "΢���ź�");//���������С����ʽ

	while (1)
	{
	mapDraw();
	player();
	};
	while (1);
	return 0;
}