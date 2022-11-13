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
#define SIZE 25//字体大小



int k=0,x=11, y=6;//勇者的位置

int HP = 100, LV = 1, DEF = 20, ATK = 30, EXP = 0;//勇者状态
int key = 0;//持有钥匙数量

enum {空,勇,墙,门,愈,匙,魔,妖,怪,鬼,界,上,下};//枚举所用的符号


int map[3][ROW][COL] = {{
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,},
{墙,上,空,匙,空,妖,妖,空,空,空,空,空,墙,},
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,空,墙,},
{墙,愈,空,鬼,门,空,墙,愈,匙,空,墙,空,墙,},
{墙,匙,空,空,墙,空,墙,愈,空,空,墙,空,墙,},
{墙,墙,门,墙,墙,空,墙,墙,墙,空,墙,空,墙,},
{墙,匙,怪,空,墙,空,门,妖,怪,鬼,墙,空,墙,},
{墙,空,空,空,墙,空,墙,墙,墙,墙,墙,空,墙,},
{墙,墙,门,墙,墙,空,空,空,空,空,空,空,墙,},
{墙,空,怪,空,墙,墙,门,墙,墙,墙,门,墙,墙,},
{墙,愈,空,愈,墙,匙,空,空,墙,愈,妖,愈,墙,},
{墙,空,匙,空,墙,空,勇,空,墙,空,空,匙,墙,},
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,},
},{
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,},
{墙,下,空,匙,妖,鬼,妖,空,空,空,空,空,墙,},
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,空,墙,},
{墙,愈,空,鬼,门,空,墙,空,匙,愈,墙,空,墙,},
{墙,匙,空,空,墙,空,墙,空,空,空,墙,空,墙,},
{墙,墙,门,墙,墙,空,墙,墙,墙,空,墙,空,墙,},
{墙,匙,怪,空,墙,空,门,妖,怪,鬼,墙,空,墙,},
{墙,空,空,空,墙,空,墙,墙,墙,墙,墙,空,墙,},
{墙,墙,门,墙,墙,空,空,空,空,空,空,空,墙,},
{墙,空,怪,空,墙,鬼,妖,怪,墙,墙,门,墙,墙,},
{墙,愈,空,愈,墙,妖,怪,空,墙,愈,怪,愈,墙,},
{墙,空,匙,空,墙,愈,上,愈,墙,空,空,匙,墙,},
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,},
},{
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,魔,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,空,空,空,空,空,空,墙,},
{墙,空,空,空,空,空,下,空,空,空,空,空,墙,},
{墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,墙,},
} };





const char* text[]= {"  ","勇","墙","门","愈","匙","魔","妖","怪","鬼","界","上","下"};
//定义字符数组便于输出地图


//输出二维数组

void mapDraw()
{
	BeginBatchDraw();//双缓冲防止画面闪烁卡顿
	cleardevice();//清屏刷新
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < COL; j++)
			outtextxy(j * SIZE, i * SIZE, text[map[k][i][j]]);//输出在界面，x-行，y-列
	char a[8]; char b[8]; char c[8]; char d[8]; char e[8]; char f[8];
	sprintf_s(a, "%d", HP); outtextxy(0, 325,"血量："); outtextxy(60, 325, a);//显示血量
	sprintf_s(b, "%d", DEF); outtextxy(110, 325, "防御："); outtextxy(160, 325, b);
	sprintf_s(c, "%d", ATK); outtextxy(210, 325, "攻击："); outtextxy(260, 325, c);
	sprintf_s(d, "%d", LV); outtextxy(0, 350, "等级："); outtextxy(60, 350, d);
	sprintf_s(e, "%d", EXP); outtextxy(110, 350, "经验："); outtextxy(160, 350, e);
	sprintf_s(f, "%d", key); outtextxy(210, 350, "钥匙："); outtextxy(260, 350, f);
	EndBatchDraw();

}






//战斗流程
int fightyao()//与妖斗
{
	int MHP = 100, MDEF = 20, MATK = 20;//妖的状态
	for (1; HP > 0 && MHP > 0;)
	{
		printf("勇者使用挥砍\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("勇者胜利了\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("勇者等级上升了\n");
			}
			return 1;
		}
		printf("怪物发起了攻击\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
			if (HP <= 0)
			{
				printf("勇者倒下了\n");
				return 0;
			}
	}
}


int fightguai()
{
	int MHP = 200, MDEF = 20, MATK = 10;//怪的状态
	for (1; HP > 0 && MHP > 0;)
	{
		printf("勇者使用挥砍\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("勇者胜利了\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("勇者等级上升了\n");
			}
			return 1;
		}
		printf("怪物发起了攻击\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
		if (HP <= 0)
		{
			printf("勇者倒下了\n");
			return 0;
		}
	}
}


int fightgui()
{
	int MHP = 150, MDEF = 10, MATK = 30;//鬼的状态
	for (1; HP > 0 && MHP > 0;)
	{
		printf("勇者使用挥砍\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("勇者胜利了\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("勇者等级上升了\n");
			}
			return 1;
		}
		printf("怪物发起了攻击\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
		if (HP <= 0)
		{
			printf("勇者倒下了\n");
			return 0;
		}
	}
}


int fightmo()
{
	int MHP = 1000, MDEF = 50, MATK = 100;//魔王的状态
	for (1; HP > 0 && MHP > 0;)
	{

		printf("勇者使用挥砍\n");
		if (ATK - MDEF <= 0)
			MHP -= 20;
		else MHP -= 20 + ATK - MDEF;
		if (MHP <= 0)
		{
			printf("魔王被打败了，勇者获得了最后的胜利\n");
			EXP += 20;
			if (EXP >= 50)
			{
				LV += 1; EXP -= 50; HP += 20; DEF += 5; ATK += 10;
				printf("勇者等级上升了\n");
			}
			return 1;
		}
		printf("魔王发起了攻击\n");
		if (MATK - DEF <= 0)
			HP -= 10;
		else HP -= 10 + (MATK - DEF);
		if (HP <= 0)
		{
			printf("勇者倒下了\n");
			return 0;
		}
	}
}
//移动
void move(int vx, int vy)
{
	if (map[k][x + vx][y + vy] == 空)
	{
		map[k][x + vx][y + vy] += 1;
		map[k][x][y] -= 1;
		x = x + vx;
		y = y + vy;
	}
	else if (map[k][x + vx][y + vy] == 门)
	{
		if (key > 0)
		{
			printf("======================================\n");
			printf("消耗一把钥匙来打开门\n");
			map[k][x + vx][y + vy] -= 3;
			key -= 1;
		}
		else if (key <= 0)
		{
			printf("======================================\n");
			printf("缺少钥匙，无法打开门\n");
		}
	}
	else if (map[k][x + vx][y + vy] == 愈)
	{
		printf("======================================\n");
		HP += 50;
		printf("HP回复50\n");
		map[k][x + vx][y + vy] -= 4;
	}
	else if (map[k][x + vx][y + vy] == 妖)
	{
		printf("======================================\n");
		printf("勇者遭遇妖\n");
		if (fightyao() == 0)
		{
			map[k][x][y] -= 1;
			printf("游戏结束\n");
		}
		else
			map[k][x + vx][y + vy] -= 7;
	}
	else if (map[k][x + vx][y + vy] == 怪)
	{
		printf("======================================\n");
		printf("勇者遭遇怪\n");
		if (fightguai() == 0)
		{
			map[k][x][y] -= 1;
			printf("游戏结束\n");
		}
		else
			map[k][x + vx][y + vy] -= 8;
	}
	else if (map[k][x + vx][y + vy] == 鬼)
	{
		printf("======================================\n");
		printf("勇者遭遇鬼\n");
		if (fightgui() == 0)
		{
			map[k][x][y] -= 1;
			printf("游戏结束\n");
		}
		else
			map[k][x + vx][y + vy] -= 9;
	}
	else if (map[k][x + vx][y + vy] ==魔 )
	{
		printf("======================================\n");
		printf("勇者与魔王正面交锋\n");
		if (fightmo() == 0)
		{
			map[k][x][y] -= 1;
			printf("游戏结束\n");
		}
		else
			map[k][x + vx][y + vy] -= 6;
	}
	else if (map[k][x + vx][y + vy] == 匙)
	{
		printf("======================================\n");
		printf("获得一把钥匙，可以打开一扇门\n");
		key += 1;
		map[k][x + vx][y + vy] -= 5;
	}
	else if (map[k][x + vx][y + vy] == 上)
	{
		k++;
		map[k][x][y] += 1;
		map[k - 1][x][y] -= 1;
		printf("======================================\n");
		printf("上了一层楼\n");
	}
	else if (map[k][x + vx][y + vy] == 下)
	{
		k--;
		map[k+1][x][y] -= 1;
		map[k][x][y] += 1;
		printf("======================================\n");
		printf("下了一层楼");
	}

}








int player()//控制勇者的行为
{
	ExMessage m = { 0 };//窗口消息
	m = getmessage(EM_KEY);//只获取键盘消息
	
	switch (m.message)
	{
	case WM_KEYDOWN:
		switch (m.vkcode)
		{
		case VK_UP: //上
		{
			move(-1, 0);
			break;
		}
		case VK_DOWN://下
		{
			move(1, 0);
		}break;
		case VK_LEFT://左
		{
			move(0, -1);
		}break;
		case VK_RIGHT://右
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
	mciSendString("open bgm.mp3 alias bgm", 0, 0, 0);//打开背景音乐
	mciSendString("setaudio bgm to 175", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
	initgraph(COL * SIZE, ROW * SIZE,1);//创建图形界面
	settextstyle(SIZE, 0, "微软雅黑");//设置字体大小和样式

	while (1)
	{
	mapDraw();
	player();
	};
	while (1);
	return 0;
}