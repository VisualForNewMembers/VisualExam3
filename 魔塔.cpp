
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
void Input_Name()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                           ħ����ճ����������˼䣬�޶���������Ϳ̿����ʬ��Ұ\n");
	Sleep(1000);
	printf("                           �콫����,���ߣ��������Ѱ�ñ���������ȫ���˵�ףԸ,̤����ħ������ħ����һ��ս\n");
	Sleep(1000);
	printf("                           �������ߣ����������>:");
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
	printf("Ѫ��: %d\n", h.blood);
	printf("������: %d\n", h.power);
	printf("������: %d\n", h.defense);
	printf("�ȼ�: %d\n", h.level);
	printf("����ֵ: %.2lf\n", (float)h.exp);
	printf("��ɱ��ҩˮ:%d\n", g);
	printf("Կ������: %d\n", h.key);
	printf("λ��x: %d \n", h.y);
	printf("λ��y: %d\n", h.x);
	printf("------------------\n");
	printf("����o����  !��Կ�� D�Ǵ��� G����ɱ��ҩˮ  ~ & %% �Ǵ�����ǿ�Ĺ���  +�ǻ�Ѫ��\nͨ��wasd���в���\n��2���빥�ԣ��ٰ�һ���˳�����\n\n\n");
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
void SS(char map[2][13][13],int z,int i,int j,struct humanrole* ���� )      //�������� ����֮һ�ĸ�����2�� ���߿�100Ѫ
{
	srand((unsigned int)time(NULL));
	int time = rand() % 100 ;
	if (time < 50)
	{
		����->level = ����->level + 2;

	}
	else {
		����->blood = ����->blood - 100;
	}
	
}
void PK(char map[2][13][13], int z, int i, int j, struct humanrole* ����, struct monsterrole* ����, int t)                   //�Ծֹ���
{
	int p = 20;//����͹���Ļ���������

	����->blood = ����->blood - ����->power + ����->defense - p;
	if (����->blood > 0)
	{
		����->blood = ����->blood - ����->power + ����->defense - p;
		if (����->blood <= 0)
		{
			printf("��������");
		}
		else
		{
			����->blood = ����->blood - ����->power + ����->defense - p;
			if (����->blood <= 0)
			{
				map[z][i][j] = ' ';
			}
			else if (����->blood > 0)
			{
				����->blood = ����->blood - ����->power + ����->defense - p;
				if (����->blood <= 0)
				{

					printf("��������");
				}
				else
				{
					����->blood = ����->blood - ����->power + ����->defense - p;
					if (����->blood <= 0);
					{

						map[z][i][j] = ' ';
					}
				}
			}
		}
	}
	if (����->blood <= 0);
	{

		map[z][i][j] = ' ';
	}
}
void AddBlood(struct humanrole* ����)     //��Ѫ����
{
	if (����->level == 1)
	{
		if (����->blood > 20 && ����->blood < 100)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 100)
					break;
			}
		}
		if (����->blood <= 20 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;

		}
	}
	if (����->level == 2)
	{
		if (����->blood <= 40 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 40 && ����->blood < 120)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 120)
					break;
			}
		}
	}
	if (����->level == 3)
	{
		if (����->blood <= 60 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 60 && ����->blood < 140)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 140)
					break;
			}
		}

	}
	if (����->level == 4)
	{
		if (����->blood <= 60 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 60 && ����->blood < 160)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 160)
					break;
			}
		}

	}
	if (����->level == 5)
	{
		if (����->blood <= 60 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 60 && ����->blood < 180)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 180)
					break;
			}
		}

	}
	if (����->level == 6)
	{
		if (����->blood <= 60 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 60 && ����->blood < 200)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 200)
					break;
			}
		}

	}
	if (����->level == 7)
	{
		if (����->blood <= 60 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 60 && ����->blood < 220)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 220)
					break;
			}
		}

	}
	if (����->level == 8)
	{
		if (����->blood <= 60 && ����->blood > 0)
		{
			����->blood = ����->blood + 80;
		}
		if (����->blood > 60 && ����->blood < 240)
		{
			int i = 0; int j = 0;
			for (i = 0; i <= 80; i++)
			{
				����->blood++;
				if (����->blood >= 240)
					break;
			}
		}

	}
}

void EXPup(struct humanrole* ����, int z, int i, int j, char map[2][13][13])   //��ֵþ��� �����ŵȼ�������˥��
{
	if (map[z][i][j] == '~')
	{
		if (����->level == 1 )
		{
			����->exp = ����->exp + 25.0;
		}
		if (����->level == 2 )
		{
			����->exp = ����->exp + 12.5;
		}
		if (����->level == 3|| ����->level==4|| ����->level==5|| ����->level==6 || ����->level == 7)
		{
			����->exp = ����->exp + 12.5 / 2;
		}
	}
	if (map[z][i][j] == '&')
	{
		if (����->level == 1)
		{
			����->exp = ����->exp + 25.0;
		}
		if (����->level == 2)
		{
			����->exp = ����->exp + 25.0;
		}
		if (����->level == 3 || ����->level == 4 || ����->level == 5 || ����->level == 6 || ����->level == 7)
		{
			����->exp = ����->exp + 25.0 / 2;
		}
	}
	if (map[z][i][j] == '%')
	{
		if (����->level == 2)
		{
			����->exp = ����->exp + 50.0;
		}
		if (����->level == 3 || ����->level == 4 || ����->level == 5 || ����->level == 6||����->level==7)
		{
			����->exp = ����->exp + 25.0;
		}
	}
}
void Levelup(struct humanrole* ����)        //��������
{
	if (����->exp >= 50)
	{
		����->exp = ����->exp - 50;
		����->level = ����->level + 1;
		����->blood = ����->blood + 20;
		����->power = ����->power + 10;
		����->defense = ����->defense + 5;
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
	int  t = 0; t = t + 1;//��������ʱi=0������whileѭ�� 
	int a = 0;//���ڼ�¼Կ��  
	int p = 0;//Ϊ������ͼ
	int u = 0;//Ϊ�˴򿪹���
	
	humanrole h = { 100,30,20,1,0,a,i,j };//��������
	while (t) {
		monsterrole b = { 'RNG',100,50,0 }; monsterrole c = { 'JDG', 110, 60, 5 };	monsterrole d = { 'T1',120,70,10 };//3ֻС�ֵ�����
		monsterrole f = { 'DRX', 150, 110, 30 };


		UI(h.blood, h.power, h.defense, h.level, h.exp, i + 1, j + 1, a, g);

		MadeMap(map, z);
		for (i = 0; i < 13; i++)
		{
			for (j = 0; j < 13; j++)
			{
				if (map[z][i][j] == 'o')
				{                                      //λ�ò���

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
				map[z][i][j] = ' ';         //�߿յص�
				map[z][i - 1][j] = 'o';
			}
			if (map[z][i][j - 1] == 'G')//������ɱ��ҩˮ
			{

				map[z][i][j - 1] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//��ú�ҩˮ
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
				map[z][i][j] = ' ';         //��Կ��
				map[z][i - 1][j] = 'o';
				a++;      //��¼Կ��
			}
			if (map[z][i - 1][j] == 'D' && a > 0)
			{
				map[z][i - 1][j] = ' ';        //ʹ��Կ��
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
			if (map[z][i][j - 1] == 'G')//������ɱ��ҩˮ
			{
				map[z][i][j - 1] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//��ú�ҩˮ
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
			if (map[z][i][j + 1] == 'G')//������ɱ��ҩˮ
			{
				map[z][i][j + 1] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//��ú�ҩˮ
			}
			if (g >= 1)
			{
				if (map[z][i][j + 1] == '~' || map[z][i][j + 1] == '&' || map[z][i][j + 1] == '%')//ʹ�ú�ҩˮ
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
			if (map[z][i + 1][j] == 'G')//������ɱ��ҩˮ
			{
				map[z][i + 1][j] = map[z][i][j];
				map[z][i][j] = ' ';
				g++;//��ú�ҩˮ
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

			printf("1.��ħ����Ҫ��6���Ŵ�ù�\n2.'S'��������,�ж���֮һ�ĸ���������2���������ǿ�100Ѫ\n3.��ɱ��ҩˮֻ�ܶԷ�ħ���Ĺ�������\n4. ~ & % ������ǿ ��ɱ���о���˥������4������˥���̶�\n");
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
		printf("��������\n�Ƿ�������\n�����밴1\n");
	}
	if (t == 3)
	{
	pp:
		system("cls");
		printf("��Ϸ��������ϲ�㣬�ѻ���ħ�������Ǵ���ˮ����������Ӣ��!!\n��Ϸ������:�ܽ���");
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
