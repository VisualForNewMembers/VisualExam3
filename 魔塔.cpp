
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
void Input_Name()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                           魔王横空出世，威将人间，无恶不作，生灵涂炭，横尸遍野\n");
	Sleep(1000);
	printf("                           天将启明,勇者，现如今你寻得宝剑，带着全村人的祝愿,踏上了魔塔，与魔王决一死战\n");
	Sleep(1000);
	printf("                           请问勇者，你的名字是>:");
	char input = 0;
	scanf_s("%c", &input);

}

typedef struct humanrole
{
	int blood;
	int power;
	int defense;
	int level;
	float exp;
	int key;
	int x;
	int y;

}humanrole;
typedef struct monsterrole
{
	char name;
	int blood;
	int power;
	int defense;
}monsterrole;
void UI(int blood, int power, int defense, int level, float exp, int i, int j, int a, int g)
{
	humanrole h = { blood,power,defense,level,exp,a,i,j };
	printf("血量: %d\n", h.blood);
	printf("攻击力: %d\n", h.power);
	printf("防御力: %d\n", h.defense);
	printf("等级: %d\n", h.level);
	printf("经验值: %.2lf\n", (float)h.exp);
	printf("秒杀红药水:%d\n", g);
	printf("钥匙数量: %d\n", h.key);
	printf("位置x: %d \n", h.y);
	printf("位置y: %d\n", h.x);
	printf("------------------\n");
	printf("你是o勇者  !是钥匙 D是大门 G是秒杀红药水  ~ & %% 是从弱到强的怪物  +是回血点\n通过wasd进行操作\n按2进入攻略，再按一次退出攻略\n\n\n");
}
void UI1()
{
	monsterrole b = { 'RNG',90,70,0 };
}
void UI2()
{
	monsterrole c = { 'JDG', 100, 80, 10 };
}
void UI3()
{
	monsterrole d = { 'T1',110,90,20 };
}
void UI4()
{
	monsterrole f = { 'DRX',150,110,30 };
}
void SS(char map[2][13][13],int z,int i,int j,struct humanrole* 人物 )      //与死神交易 二分之一的概率升2级 或者扣100血
{
	srand((unsigned int)time(NULL));
	int time = rand() % 100 ;
	if (time < 50)
	{
		人物->level = 人物->level + 2;

	}
	else {
		人物->blood = 人物->blood - 100;
	}
	
}
void PK(char map[2][13][13], int z, int i, int j, struct humanrole* 人物, struct monsterrole* 怪物, int t)                   //对局过程
{
	int p = 20;//人物和怪物的基础攻击力

	怪物->blood = 怪物->blood - 人物->power + 怪物->defense - p;
	if (怪物->blood > 0)
	{
		人物->blood = 人物->blood - 怪物->power + 人物->defense - p;
		if (人物->blood <= 0)
		{
			printf("你已死亡");
		}
		else
		{
			怪物->blood = 怪物->blood - 人物->power + 怪物->defense - p;
			if (怪物->blood <= 0)
			{
				map[z][i][j] = ' ';
			}
			else if (怪物->blood > 0)
			{
				人物->blood = 人物->blood - 怪物->power + 人物->defense - p;
				if (人物->blood <= 0)
				{

					printf("你已死亡");
				}
				else
				{
					怪物->blood = 怪物->blood - 人物->power + 怪物->defense - p;
					if (怪物->blood <= 0);
					{

						map[z][i][j] = ' ';
					}
				}
			}
		}
	}
	if (怪物->blood <= 0);
	{

		map[z][i][j] = ' ';
	}
}
void AddBlood(struct humanrole* 人物)     //回血功能
{
	if (人物->level == 1)
	{
		if (人物->blood > 20 && 人物->blood < 100)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 100)
					break;
			}
		}
		if (人物->blood <= 20 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;

		}
	}
	if (人物->level == 2)
	{
		if (人物->blood <= 40 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 40 && 人物->blood < 120)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 120)
					break;
			}
		}
	}
	if (人物->level == 3)
	{
		if (人物->blood <= 60 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 60 && 人物->blood < 140)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 140)
					break;
			}
		}

	}
	if (人物->level == 4)
	{
		if (人物->blood <= 60 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 60 && 人物->blood < 160)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 160)
					break;
			}
		}

	}
	if (人物->level == 5)
	{
		if (人物->blood <= 60 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 60 && 人物->blood < 180)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 180)
					break;
			}
		}

	}
	if (人物->level == 6)
	{
		if (人物->blood <= 60 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 60 && 人物->blood < 200)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 200)
					break;
			}
		}

	}
	if (人物->level == 7)
	{
		if (人物->blood <= 60 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 60 && 人物->blood < 220)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 220)
					break;
			}
		}

	}
	if (人物->level == 8)
	{
		if (人物->blood <= 60 && 人物->blood > 0)
		{
			人物->blood = 人物->blood + 80;
		}
		if (人物->blood > 60 && 人物->blood < 240)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				人物->blood++;
				if (人物->blood >= 240)
					break;
			}
		}

	}
}

void EXPup(struct humanrole* 人物, int z, int i, int j, char map[2][13][13])   //打怪得经验 （随着等级而经验衰减
{
	if (map[z][i][j] == '~')
	{
		if (人物->level == 1 )
		{
			人物->exp = 人物->exp + 25.0;
		}
		if (人物->level == 2 )
		{
			人物->exp = 人物->exp + 12.5;
		}
		if (人物->level == 3|| 人物->level==4|| 人物->level==5|| 人物->level==6 || 人物->level == 7)
		{
			人物->exp = 人物->exp + 12.5 / 2;
		}
	}
	if (map[z][i][j] == '&')
	{
		if (人物->level == 1)
		{
			人物->exp = 人物->exp + 25.0;
		}
		if (人物->level == 2)
		{
			人物->exp = 人物->exp + 25.0;
		}
		if (人物->level == 3 || 人物->level == 4 || 人物->level == 5 || 人物->level == 6 || 人物->level == 7)
		{
			人物->exp = 人物->exp + 25.0 / 2;
		}
	}
	if (map[z][i][j] == '%')
	{
		if (人物->level == 2)
		{
			人物->exp = 人物->exp + 50.0;
		}
		if (人物->level == 3 || 人物->level == 4 || 人物->level == 5 || 人物->level == 6||人物->level==7)
		{
			人物->exp = 人物->exp + 25.0;
		}
	}
}
void Levelup(struct humanrole* 人物)        //升级功能
{
	if (人物->exp >= 50)
	{
		人物->exp = 人物->exp - 50;
		人物->level = 人物->level + 1;
		人物->blood = 人物->blood + 20;
		人物->power = 人物->power + 10;
		人物->defense = 人物->defense + 5;
	}
}
void MadeMap(char map[2][13][13], int z)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			printf(" %c ", map[z][i][j]);
		}
		printf("\n");
	}
}
void KeyDown(char map[2][13][13])
{
put:
	int z = 0;	int x = 0; int y = 0; char usekey = 0;
	int i = 0; int j = 0; int  g = 0;
	int  t = 0; t = t + 1;//人物死亡时i=0，跳出while循环 
	int a = 0;//用于记录钥匙  
	int p = 0;//为了跳地图
	int u = 0;//为了打开攻略
	
	humanrole h = { 100,30,20,1,0,a,i,j };//人物属性
	while (t) {
		monsterrole b = { 'RNG',100,50,0 }; monsterrole c = { 'JDG', 110, 60, 5 };	monsterrole d = { 'T1',120,70,10 };//3只小怪的属性
		monsterrole f = { 'DRX', 150, 110, 30 };


		UI(h.blood, h.power, h.defense, h.level, h.exp, i + 1, j + 1, a, g);

		MadeMap(map, z);
		for (i = 0; i < 13; i++)
		{
			for (j = 0; j < 13; j++)
			{
				if (map[z][i][j] == 'o')
				{                                      //位置查找

					break;

				}
			}
			if (map[z][i][j] == 'o')
			{
				break;
			}
		};
		usekey = _getch();
		switch (usekey)
		{
		case 'w': {
			if (map[z][i - 1][j] == ' ')
			{
				map[z][i][j] = ' ';         //走空地地
				map[z][i - 1][j] = 'o';
			}
			if (map[z][i][j - 1] == 'G')//遇到秒杀红药水
			{

				map[z][i][j - 1] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//获得红药水
			}
			if (g >= 1)
			{
				if (map[z][i][j - 1] == '~' || map[z][i][j - 1] == '&' || map[z][i][j - 1] == '%')
				{
					if (map[z][i][j - 1] == 'B')
					{
						break;
					}
					map[z][i][j - 1] = ' ';
					g--;
				}
			}

			if (map[z][i - 1][j] == '!')
			{
				map[z][i][j] = ' ';         //捡钥匙
				map[z][i - 1][j] = 'o';
				a++;      //记录钥匙
			}
			if (map[z][i - 1][j] == 'D' && a > 0)
			{
				map[z][i - 1][j] = ' ';        //使用钥匙
				a--;

			}
			if (map[z][i - 1][j] == '~')
			{
				PK(map, z, i - 1, j, &h, &b, t);
				if (map[z][i - 1][j] = ' ')
				{
					map[z][i - 1][j] = '~';
					EXPup(&h, z, i - 1, j, map);
					map[z][i - 1][j] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i - 1][j] == '&')
			{
				PK(map, z, i - 1, j, &h, &b, t);
				if (map[z][i - 1][j] = ' ')
				{
					map[z][i - 1][j] = '&';
					EXPup(&h, z, i - 1, j, map);
					map[z][i - 1][j] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i - 1][j] == '%')
			{
				PK(map, z, i - 1, j, &h, &b, t);
				if (map[z][i - 1][j] = ' ')
				{
					map[z][i - 1][j] = '%';
					EXPup(&h, z, i - 1, j, map);
					map[z][i - 1][j] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i - 1][j] == '+')
			{
				AddBlood(&h);
			}
			if (map[z][i - 1][j] == '/')
			{
				z++;
			}
			if (map[z][i - 1][j] == '\\')
			{
				z--;
			}
			if (map[z][i - 1][j] == 'B')
			{
				PK(map, z, i - 1, j, &h, &b, t);
				goto pp;
			}
			break;
		}
		case 'a': {
			if (map[z][i][j - 1] == ' ')
			{
				map[z][i][j] = ' ';
				map[z][i][j - 1] = 'o';

			}
			if (map[z][i][j - 1] == 'G')//遇到秒杀红药水
			{
				map[z][i][j - 1] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//获得红药水
			}
			if (g >= 1)
			{
				if (map[z][i][j - 1] == '~' || map[z][i][j - 1] == '&' || map[z][i][j - 1] == '%')
				{
					if (map[z][i + 1][j] == 'B')
					{
						PK(map, z, i, j - 1, &h, &b, t);
						break;
					}
					map[z][i][j - 1] = ' ';
					g--;
				}
			}

			if (map[z][i][j - 1] == '!')
			{
				map[z][i][j] = ' ';
				map[z][i][j - 1] = 'o';
				a++;

			}
			if (map[z][i][j - 1] == 'D' && a > 0)
			{
				map[z][i][j - 1] = ' ';
				a--;

			}
			if (map[z][i][j - 1] == '~')
			{
				PK(map, z, i, j - 1, &h, &b, t);
				if (map[z][i][j - 1] == ' ')
				{
					map[z][i][j - 1] = '~';
					EXPup(&h, z, i, j - 1, map);
					map[z][i][j - 1] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;

				}
			}
			if (map[z][i][j - 1] == '&')
			{
				PK(map, z, i, j - 1, &h, &b, t);
				if (map[z][i][j - 1] == ' ')
				{
					map[z][i][j - 1] = '&';
					EXPup(&h, z, i, j - 1, map);
					map[z][i][j - 1] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;

				}
			}
			if (map[z][i][j - 1] == '%')
			{
				PK(map, z, i, j - 1, &h, &b, t);
				if (map[z][i][j - 1] == ' ')
				{
					map[z][i][j - 1] = '%';
					EXPup(&h, z, i, j - 1, map);
					map[z][i][j - 1] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i][j - 1] == '+')
			{
				AddBlood(&h);
			}
			if (map[z][i][j - 1] == '/')
			{
				z++;
			}
			if (map[z][i][j - 1] == '\\')
			{
				z--;
			}
			if (map[z][i][j - 1] == 'S')
			{
				SS(map, z, i, j, &h);
				if (h.blood <= 0)
				{
					t = t - 1;
				}
				map[z][i][j - 1] = ' ';
			}
			if (map[z][i][j - 1] == 'B')
			{
				PK(map, z, i, j - 1, &h, &f, t);
				goto pp;
			}
			break;
		}
		case 'd':
		{
			if (map[z][i][j + 1] == ' ')
			{
				map[z][i][j] = ' ';
				map[z][i][j + 1] = 'o';

			}
			if (map[z][i][j + 1] == 'G')//遇到秒杀红药水
			{
				map[z][i][j + 1] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//获得红药水
			}
			if (g >= 1)
			{
				if (map[z][i][j + 1] == '~' || map[z][i][j + 1] == '&' || map[z][i][j + 1] == '%')//使用红药水
				{
					if (map[z][i][j + 1] == 'B')
					{

						break;
					}
					map[z][i][j + 1] = ' ';
					g--;

				}
			}

			if (map[z][i][j + 1] == '!')
			{
				map[z][i][j] = ' ';
				map[z][i][j + 1] = 'o';
				a++;
			}

			if (map[z][i][j + 1] == 'D' && a > 0)
			{
				map[z][i][j + 1] = ' ';
				a--;

			}
			if (map[z][i][j + 1] == '~')
			{
				PK(map, z, i, j + 1, &h, &b, t);
				if (map[z][i][j + 1] == ' ')
				{
					map[z][i][j + 1] = '~';
					EXPup(&h, z, i, j + 1, map);
					map[z][i][j + 1] = ' ';
				}
			}
			if (h.blood <= 0)
			{
				t = t - 1;
			}
			if (map[z][i][j + 1] == '&')
			{
				PK(map, z, i, j + 1, &h, &b, t);
				if (map[z][i][j + 1] == ' ')
				{
					map[z][i][j + 1] = '&';
					EXPup(&h, z, i, j + 1, map);
					map[z][i][j + 1] = ' ';
				}
			}
			if (h.blood <= 0)
			{
				t = t - 1;
			}
			if (map[z][i][j + 1] == '%')
			{
				PK(map, z, i, j + 1, &h, &b, t);
				if (map[z][i][j + 1] == ' ')
				{
					map[z][i][j + 1] = '%';
					EXPup(&h, z, i, j + 1, map);
					map[z][i][j + 1] = ' ';
				}
			}
			if (h.blood <= 0)
			{
				t = t - 1;
			}
			EXPup(&h, z, i, j + 1, map);

			if (map[z][i][j + 1] == '+')
			{
				AddBlood(&h);

			}
			if (map[z][i][j + 1] == '/')
			{
				z++;
			}
			if (map[z][i][j + 1] == '\\')
			{
				z--;
			}
			if (map[z][i][j + 1] == 'B')
			{
				PK(map, z, i, j + 1, &h, &f, t);
				goto pp;
			}
			break;
		case 's':

			if (map[z][i + 1][j] == ' ')
			{
				map[z][i][j] = ' ';
				map[z][i + 1][j] = 'o';
			}
			if (map[z][i + 1][j] == 'G')//遇到秒杀红药水
			{
				map[z][i + 1][j] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//获得红药水
			}
			if (g >= 1)
			{
				if (map[z][i + 1][j] == '~' || map[z][i + 1][j] == '&' || map[z][i + 1][j] == '%')
				{
					if (map[z][i + 1][j] == 'B')
					{
						break;
					}

					map[z][i + 1][j] = ' ';
					g--;
				}
			}

			if (map[z][i + 1][j] == '!')
			{
				map[z][i][j] = ' ';
				map[z][i + 1][j] = 'o';
				a++;

			}
			if (map[z][i + 1][j] == 'D' && a > 0)
			{
				map[z][i + 1][j] = ' ';
				a--;

			}
			if (map[z][i + 1][j] == '~')
			{
				PK(map, z, i + 1, j, &h, &b, t);


				if (map[z][i + 1][j] == ' ')
				{
					map[z][i + 1][j] = '~';
					EXPup(&h, z, i + 1, j, map);
					map[z][i + 1][j] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i + 1][j] == '&')
			{
				PK(map, z, i + 1, j, &h, &b, t);
				if (map[z][i + 1][j] == ' ')
				{
					map[z][i + 1][j] = '&';
					EXPup(&h, z, i + 1, j, map);
					map[z][i + 1][j] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i + 1][j] == '%')
			{
				PK(map, z, i + 1, j, &h, &b, t);


				if (map[z][i + 1][j] == ' ')
				{
					map[z][i + 1][j] = '%';
					EXPup(&h, z, i + 1, j, map);
					map[z][i + 1][j] = ' ';
				}
				if (h.blood <= 0)
				{
					t = t - 1;
				}
			}
			if (map[z][i + 1][j] == '+')
			{
				AddBlood(&h);
			}
			if (map[z][i + 1][j] == '/')
			{
				z++;
			}
			if (map[z][i + 1][j] == '\\')
			{
				z--;
			}
			if (map[z][i + 1][j] == 'B')
			{
				PK(map, z, i + 1, j, &h, &f, t);
				goto pp;
			}
			break;
		case '2':
			system("cls");

			printf("1.大魔王需要你6级才打得过\n2.'S'代表死神,有二分之一的概率让你升2级，或者是扣100血\n3.秒杀红药水只能对非魔王的怪物有用\n4. ~ & % 从弱到强 击杀后有经验衰减，到4级后经验衰减固定\n");
			u = _getch();
			if (u == 2)
			{
				break;
			}

		}
		}
		Levelup(&h);
		system("cls");

	}
	if (t == 0)
	{
		printf("你已死亡\n是否重生？\n重生请按1\n");
	}
	if (t == 3)
	{
	pp:
		system("cls");
		printf("游戏结束，恭喜你，已击败魔王，你是处于水深火热人民的英雄!!\n游戏制作者:周杰钦");
	}
}

int main()
{
	Input_Name();
	system("cls");
	int put = 0;
	int g = 0;
put:
	char map[2][13][13] = { {
				'*','*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
				'*',' ',' ','*',' ','~',' ','G','*',' ',' ',' ','*',
				'*',' ',' ','*','D','*','*', '*', '*',' ','*',' ','*',
				'*', '&','!',' ',' ', ' ', ' ', ' ', '*',' ','*',' ','*',
				'*','D','*', '*', '*', '*','D','*','*',' ','*',' ','*',
				'*','!','D','~','G','*','!','&', '*',' ', '*',' ', '*',
				'*','D', '*',  '*',  '*',  '*',  '*',  '*',  '*',' ', '*',' ', '*',
				'*',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*',' ', '*',
				'*','D', '*', '*', '*', ' ', ' ', ' ', '*','D','*',' ','*',
				'*','~',' ', '~', '*','*','*','D','*', ' ','*',' ','*',
				'*',' ',' ',' ','*','!',' ','~','*',' ','*','%','*',
				'*',' ',' ','!','*', '!','o','+','*','D','&','/','*',
				'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
			{	'*','*','*','*','*','*','*','*','*','*','*','*','*',
				'*','S',' ',' ',' ','!','*','*','\\','o',' ',' ','*','*',
				 '*', 'D','*', '*', '*', '*', '*', '*', '*', '&','*', '*',
				'*', ' ',' ', ' ', ' ', ' ', ' ','*','*',' ', ' ', ' ', '*',
				'*','*','*','*','*','*',' ','*','*','!','!','!','*',
				'*','!','%',' ',' ',' ',' ',' ','*',' ',' ',' ','*','*',
				'*','*','*','*','*','*',' ','*','*',' ','*','*',
				'*', ' ', ' ', ' ', ' ', ' ', ' ','D', ' ',' ', '%','*','*',
				'*','D','*', '*', '*', 'D','*','*','*','*', 'D','*','*',
				'*', '&','~','~','*', ' ',' ',' ','*', ' ',' ','%','*',
				'*', '&','B','~','*', ' ','!',' ','*', ' ',' ','+','*',
				'*', '&','&','~','*', ' ','!',' ',' *', ' ', ' ', ' ','*',
				'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' }

	};
	KeyDown(map);
	scanf_s("%d", &put);
	if (put == 1)
	{
		goto put;
	}
	return 0;
}
