#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h> 
#include <ctime>
#include <cstdlib>
#include<fstream>

using namespace std;


/*
����ģ��Ϊ  ����  ��Ϸ��ʼ�Ľ��� ��Ϸ�Ŀ�Ļ ������˶�  ս�����ж� ������ײ����ж� ��Ϸ��������  �������Ĺ���
1.����
2.��Ϸ��ʼ�Ľ���
3��ͼ����Ĵ�ӡ (���)
4.������˶�
5.ս�����ж�
6.�������ײ�ж�
7.�������Ĺ���(������������)
*/


/*
			====================================================
			| 1.һ��ʼ�õ���system("cls")+���´�ӡһ����ɿ��� |
			|   ����ȥ�øĹ��ķ�ʽȥ�����������             |
			| ���Ըı��������Ĵ���Ƚ���(�������µı���q)    |
			| 2.��Щ�ط������������ɫ���±Ƚ���һ��	   n    |
			====================================================
*/

//����+��ʼ��   ��ͼ����ͽ�ɫ��Ϣ  ����̨������---------------------------------------------------------------------------------------------------- 
char q;

//��ͼ
//��ͼһ
char map1[8][8] = {                               
	{'o',' ',' ',' ',' ','*','!','*'},
	{'*','*','*','*',' ','*','!','*'},
	{' ','&','+','*',' ','*','+','*'},
	{' ','*',' ','*',' ','*','~','*'},
	{' ','*','*','*',' ','*','D','*'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'%','*','*',' ','*','*','*','*'},
	{'!',' ','*',' ','D','%','D','/'} };
//��ͼ��
char map2[8][8] = {
	{'o',' ',' ',' ','*','!','!','*'},
	{'*','*','*',' ','*','*','~','*'},
	{'+','&',' ',' ','*','*','D','*'},
	{'*','*','*',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ','*','*','D','*'},
	{'%','*','*','*','*',' ','D','+'},
	{' ','%','!',' ','*',' ',' ',' '},
	{'*','*',' ',' ','*','+',' ','/'} };

//��ͼ��(Ϊ�������ͼ)
char map3[8][8] = {
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{} };
//������źͶ�ȡ��ͼ
char map3_duqu[8][8] = {
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{} };

//����
string name;
char way;
int x = 0, y = 0, flood = 1, num, n, m;
int tiao = 0;
int theb = 1;

//�����
int getRand(int min, int max)           
{
	return (rand() % (max - min + 1)) + min;
}



//�������� 
typedef struct Man {
	int blood;
	int grade;
	int define;
	int attack;
	int exp;
	int key;
}hero;
hero man = { 100,1,20,30,0,0 };

//������������ 
typedef struct  envy {
	int blood;				//Ѫ�� 
	int attack;				//���� 
	int define;				//���� 
	int exp;
	int hao;
}ghost;
ghost litgho = { 160,20,10,20,1 };
ghost betgho = { 120,25,20,30,2 };
ghost mosgho = { 130,35,25,50,3 };
ghost  big_b = { 170,75,50,0,4 };

//����-�����������������������������������������������á�����������������������������������
//���ô��� 
void topwindow()
{
	HWND hWnd = GetForegroundWindow();
	SetWindowPos(hWnd, HWND_TOPMOST, 400, 250, 0, 0, SWP_NOSIZE);
}

//������� 
void setpos(short x, short y)
{
	COORD  point = { x,y };
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}

//������� 
void Hide(int l)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,l };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//����ɫ

//ǰ����(��Ϊ��ʼ��ԭ����) 
void white()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//ǰ���� 
void green()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_GREEN);
}
//ǰ���� 
void red()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_RED);
}
//ǰ����
void yellow()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN);
}
//ǰ����
void blue()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE);

}
//ǰ������
void blue2()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE | FOREGROUND_GREEN);
}
//������ 
void redback()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, BACKGROUND_RED);
}

//���������ͼ����ͼ���İ������------------------------------------------------------------------------------------
void createmap()
{
	int x = 0, y = 0, cor = 1, r;
	int m, n;				//�м�洢λ�� 
	srand(time(0));			//�������ӣ�ȷ��ÿ���������һ�� 
	for (int i = 0; i < 8; i++)			//����һ��ͨ�ص�·�� 
	{
		r = getRand(0, 1);
		if (r == 0 && x < 4)
		{
			x++;
			map3[y][x] = ' ';
		}
		else if (y < 4)
		{
			y++;
			map3[y][x] = ' ';
		}
		else
		{
			x++;
			map3[y][x] = ' ';
		}
	}
	map3[7][7] = 'B';				//����boss�� 
	map3[7][6] = '+';
	map3[7][5] = '*';
	map3[6][7] = '+';
	map3[6][6] = 'D';
	map3[6][5] = 'D';
	map3[5][7] = '*';
	map3[5][6] = 'D';
	map3[5][5] = ' ';

	for (int i = 0; i < 5; i++)       //Ϊ����Կ�׷�λ�� 
	{
		map3[6][i] = '*';
	}
	r = getRand(0, 1);			//ͨ��·����boss������ 
	if (r == 1)
	{
		map3[5][4] = ' ';
		map3[0][0] = ' ';
	}
	else
	{
		map3[4][5] = ' ';
		map3[0][0] = ' ';
	}
	while (1)				//�����Ͻ���� 
	{
		x = getRand(2, 6);
		y = getRand(1, 2);
		m = y, n = x;
		if (map3[y - 1][x - 1] != ' ' && map3[y][x - 1] != ' ' && map3[y + 1][x - 1] != ' ' && map3[y - 1][x] != ' ' && map3[y - 1][x + 1] != ' ')
		{
			map3[y][x - 1] = '~';
			map3[y][x] = '!';
			map3[y + 1][x - 1] = '*';
			map3[y - 1][x - 1] = '*';
			map3[y + 1][x] = '*';
			map3[y - 1][x] = '*';
			map3[y + 1][x + 1] = '*';
			map3[y][x + 1] = '*';
			map3[y - 1][x + 1] = '*';
			break;
		}
	}
	x = x - 1; y = y;

	while (1)      //Ѱ· 
	{

		r = getRand(0, 1);
		if (r == 0 && x > 0)
		{
			x--;
			m = 1;
		}
		else if (y > 0)
		{
			y--;
			m = 2;
		}
		else
		{
			x--;
			m = 1;
		}
		if (map3[y][x] == ' ')
			break;
		else if (map3[y][x] == '*')
		{
			if (m == 1)
				x++;
			if (m == 2)
				y++;
		}                            //�������� 
		else
			map3[y][x] = ' ';
	}

	while (1)				//�����½����   
	{
		x = getRand(1, 3);
		y = getRand(5, 6);
		if (map3[y - 1][x - 1] != ' ' && map3[y - 1][x] != ' ' && map3[y - 1][x + 1] != ' ')
		{
			map3[y - 1][x] = 'D';
			map3[y - 1][x + 1] = '*';
			map3[y - 1][x - 1] = '*';
			map3[y + 1][x - 1] = '&';
			map3[y + 1][x] = '!';
			map3[y + 1][x + 1] = '&';
			map3[y][x + 1] = '*';
			map3[y][x] = '%';
			map3[y][x - 1] = '*';
			if (y == 5)
			{
				map3[7][x] = '+';
				map3[7][x + 1] = ' ';
				map3[7][x - 1] = ' ';
			}
			break;
		}
	}
	for (int j = 0, w = 0; j < 7; j++)
	{
		if (map3[7][j] == '\0' && w == 0)
		{
			map3[7][j] = '!';
			w = 1;
		}
		else if (map3[7][j] == '\0' && w == 1)
		{
			map3[7][j] = '&';
		}
	}
	y = y - 1;
	x = x;
	while (1)
	{

		r = getRand(0, 1);
		if (r == 0 && x > 0)
		{
			x--;
			m = 1;
		}
		else if (y > 0)
		{
			y--;
			m = 2;
		}
		else
		{
			x--;
			m = 1;
		}
		if (map3[y][x] == ' ')
			break;
		else if (map3[y][x] == '*')
		{
			if (m == 1)
				x++;
			if (m == 2)
				y++;
		}
		else
			map3[y][x] = ' ';
	}
	n = getRand(40, 45);               //���������ͼ���ܼ��̶� 
	for (int i = 0; i < n; i++)			//����ڿհ״����ù���
	{
		x = getRand(0, 6);
		y = getRand(0, 6);
		if (map3[y][x] == '\0')
		{
			m = getRand(0, 13);
			if (m >= 0 && m <= 5)
				map3[y][x] = '*';
			if (m >= 6 && m <= 8)
				map3[y][x] = '%';
			if (m >= 9 && m <= 10)
				map3[y][x] = '&';
			if (m == 11)
				map3[y][x] = '~';
			if (m == 12 || m == 13)
				map3[y][x] = '+';
		}


	}
	for (y = 0; y < 8; y++)
		for (x = 0; x < 8; x++)
			if (map3[y][x] == '\0')
				map3[y][x] = ' ';
	map3[0][0] = 'o';
}
void fuzhi()
{
	int i, j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
	{
			if (flood == 1)
				map1[i][j] = map3_duqu[i][j];
			if(flood==2)
				map2[i][j] = map3_duqu[i][j];
			if(flood==3)
				map3[i][j] = map3_duqu[i][j];
	}
}


//-------------------����ѡ��----------------------------------------------------------
void dudang(){
while (1)                                                                       //�����ѡ�� 
{
	red();
	cout << "					[-----------------------------------]" << "\n";
	white();
	cout << "					|                                   |" << "\n";
	cout << "					|         ��'1'��ʼ�µ���Ϸ         |" << "\n";
	cout << "					|         ��'2'��ȡ��Ϸ             |" << "\n";
	cout << "					|                                   |" << "\n";
	cout << "					|  (��ʼ����Ϸ���԰�'j'��������Ϸ)  |" << "\n";
	blue();
	cout << "					[-----------------------------------]" << "\n";
	white();
	cout << "        		                     	 ";
	q = _getch();
	if (q == '1')
	{
		fstream oo;
		oo.open("data.txt.txt", ios::out);
		oo.close();
		oo.open("./config", ios::trunc);
		oo.close();
		break;
	}
	if (q == '2')
	{
		int i, j;
		fstream oo;
		oo.open("data.txt.txt", ios::in);
		if (!oo.is_open())
		{
			cout << "file open failed\n";
			exit(1);
		}
		else
		{
			oo >> man.attack;
			oo >> man.blood;
			oo >> man.define;
			oo >> man.exp;
			oo >> man.grade;
			oo >> man.key;
			oo >> flood;
			oo >> x;
			oo >> y;
			for (i = 0; i < 8; i++)
				for (j = 0; j < 8; j++)
				{
					oo >> map3_duqu[i][j];
					if (map3_duqu[i][j] =='z')
						map3_duqu[i][j] =' ';
				}
		}
		oo.close();
		
		fuzhi();
		break;
	}
	if (q != '1' && q != '2')
	{
		cout << "\n";
		cout << "				               ��������ȷ������" << "\n";
		cout << "		                 		 �����������";
	}
	q = _getch();
	system("cls");

}
system("cls");
return;
}
//��ʼ����Ϸ���� (��һ����)----------------------------------------------------------------------------
void begin(void)
{
	while (1)                                                                       //�����ѡ�� 
	{
		yellow();
		cout << "					[-----------------------------------]" << "\n";         //����β���Ƕ�ε�����ɫ�������µ� 
		white();
		cout << "					|             ";
		red();
		cout << "ħ����Ϸ";
		white();
		cout << "              |" << "\n";
		cout << "					|��";
		red();
		cout << "'1'";
		white();
		cout << "��ʼ��Ϸ                      |" << "\n";
		cout << "					|��";
		red();
		cout << "'2'";
		white();
		cout << "���ڵ�ͼ�͹���Ͳ�����Ϣ      |" << "\n";
		cout << "					|                                   |" << "\n";
		cout << "					|                       ����-";
		blue();
		cout << "��XX";
		white();
		cout << "   |" << "\n";
		yellow();
		cout << "					[-----------------------------------]" << "\n";
		white();
		cout << "        		                     	          ";
		q = _getch();
		cout << "\n";
		if (q == '1')
		{
			break;
		}
		if (q == '2')
		{
			green();
			cout << "\n";
			cout << "					             ��Ϣ����                       " << "\n";
			cout << "				                 ��ͼ(������)                   " << "\n";
			cout << "				         OΪ����             %:&:~:Ϊ�ֲ�ͬ�Ĺ� " << "\n";
			cout << "				         *Ϊ�ϰ���ǽ         DΪ���ϵ���		" << "\n";
			cout << "				         +Ϊ��Ѫ��           ��ΪԿ��  		    " << "\n";
			cout << "				         BΪħ��             #Ϊ��ͼ�༭        " << "\n";
			cout << "				                 ����						    " << "\n";
			cout << "				         ����";
			red();
			cout << "2468(wasd)";
			green();
			cout << "Ϊ��������				" << "\n";
			cout << "				                 ����                           " << "\n";
			cout << "				         ����ǿ�� ";
			red();
			cout << "B > ~ > & > %";
			green();
			cout << "                 " << "\n";
			cout << "						    ��";
			red();
			cout << "�����";
			green();
			cout << "����" << "\n";
			white();
		}
		if (q != '1' && q != '2')
		{
			green();
			cout << "\n";
			cout << "				               ��������ȷ������" << "\n";
			cout << "		                 		 ��";
			red();
			cout << "�����";
			green();
			cout << "����";
			white();
		}
		q = _getch();
		white();
		system("cls");

	}
	system("cls");
	return;
}


//��Ϸ�Ŀ�Ļ---------------------------------------------------------------------------------------
void begining()															//��ӡ��Ļ�Ľ��� 
{
	cout << "					[---------------------------------]" << "\n";
	red();
	cout << "					      ���Ŀ���Ǵ�ܴ�B(ħ��)      " << "\n";
	white();
	cout << "					          �������������           " << "\n";
	cout << "					          (��Enterȷ��)		" << "\n";
	cout << "                               			 ";

	cin >> name;
	system("cls");
	q = 4;
	return;
}


//��ͼ��������Ϣ�Ĵ�ӡ----------------------------------------------------------------------------------------------------------

//qΪ���Ƹı����

/*
qΪ��ͬ�ĸ�������
q==3Ϊս��
q==4Ϊ�л���ͼ
q==5�ǽ���
q==2�����
*/

void picture(char p[][8])
{
	int i, j;
	if (q == 3 || q == 4)
	{
		system("cls");
		if (q == 3)
		{
			setpos(0, 0);
			cout << "\n";
			yellow();
			cout << "                                                ===================================" << "\n";
			white();
			cout << "                                                |             ����ս����          |" << "\n";
			cout << "                                                |                                 |" << "\n";
			cout << "                                                |            ";
			red();
			cout << "�����������";
			white();
			cout << "         |" << "\n";
			yellow();
			cout << "                                                ===================================" << "\n";
			white();
			i = _getch();
			system("cls");
		}
		green();
		cout << "						##########################" << "\n";
		white();
		for (i = 0; i < 8; i++)
		{
			green();
			cout << "						#";
			white();
			for (j = 0; j < 8; j++)									//��ӡ��ͼ 
			{
				if (p[i][j] == 'o' || p[i][j] == 'B' || p[i][j] == '/')      //�����if else��Ϊ�˸ı���ɫ 
				{
					red();          //------�ı���ɫ 
					cout << p[i][j];
					white();		//-----�������� 
					cout << "  ";
				}
				else if (p[i][j] == '*')
				{
					yellow();
					cout << p[i][j];
					white();
					cout << "  ";
				}
				else if (p[i][j] == '%' || p[i][j] == '&' || p[i][j] == '~')
				{
					blue2();
					cout << p[i][j];
					white();
					cout << "  ";
				}
				else
				{
					cout << p[i][j];
					cout << "  ";
				}
			}
			green();
			cout << "#" << "\n";
			white();
		}
		green();
		cout << "						##########################";
		white();
		cout << "\n";
		yellow();
		cout << "===================================================================================================================" << "\n";
		white();
		cout << "					                  ";
		blue();
		cout << name;
		white();
		cout << "\n";
		cout << "*    			    	  	  Ѫ��:";
		red();
		cout << man.blood;
		white();
		cout << "		" << "�ȼ�:" << man.grade << "\n";
		cout << "*    			    		������:" << man.attack << "               " << "����ֵ��" << man.exp << "\n";
		cout << "*	    		    		������:" << man.define << " 		" << "λ��(x.y)";
		blue2();
		cout << x << " " << y;
		white();
		cout << "\n";
		cout << "*	    		    		����2467(wasd)�����˶�          ����p������Ϸ";
	}
	if (q == 2)
	{
		setpos(49 + n * 3, m + 1);
		cout << " ";
	}
	if (q == 5)
	{
		setpos(49 + x * 3, y + 1);
		cout << " ";
		setpos(49 + n * 3, m + 1);                     //�ı���λ�� 
		red();
		cout << "o";
		white();
		x = n;
		y = m;
		setpos(73, 14);
		blue2();
		cout << x << " " << y;
		white();
	}
	return;
}

void print()
{
	if (flood == 1)
		picture(map1);
	if (flood == 2)
		picture(map2);
	if (flood == 3)
		picture(map3);
}


//������˶�------------------------------------------------------------------------- 
void move(void)
{
	if (way == '2' || way == 's' || way == 'S')
	{
		n = x, m = y + 1;
	}
	else if (way == '4' || way == 'a' || way == 'A')
	{
		n = x - 1, m = y;
	}
	else if (way == '6' || way == 'd' || way == 'D')
	{
		n = x + 1, m = y;
	}
	else if (way == '8' || way == 'w' || way == 'W')
	{
		n = x, m = y - 1;
	}
	else
	{
		n = -1; m = -1;
	}
	return;
}


//ս��ϵͳ----------------------------------------------------------------------------------------------------------------------------


//�������� 
void exptem()
{
	int t;
	if (man.exp >= 50)
	{
		t = man.exp / 50;
		man.exp = man.exp - t * 50;
		man.grade += t;
		man.define += 5;
		man.attack += 5;
	}
	return;
}

//�����ս�� 
void battle(ghost* ghost)
{
	int manhurt;
	if (man.attack <= (ghost->define))
		manhurt = 20;
	else
		manhurt = man.attack - ghost->define + 20;



	int ghohurt;
	if (ghost->attack <= man.attack)
		ghohurt = 10;
	else
		ghohurt = man.attack - ghost->define + 10;



	if (man.blood / ghohurt + 1 >= ghost->blood / manhurt)
	{
		man.blood = man.blood - (ghost->blood / manhurt - 1) * ghohurt;
		man.exp += ghost->exp;
		cout << "�ɹ���";
	}
	else
	{
		cout << "ʧ����";
		man.blood = 0;
	}
	exptem();
	if (ghost->hao == 4 && man.blood != 0)
	{
		flood = 0;
		tiao = 1;
	}
	return;
}
//
void move_gho(char map[][8])
{
	int i,j;
	int n=-1, m=-1,rr;
	for(i=0;i<8;i++)
		for (j = 0; j < 8; j++)
		{
			if (map[i][j] == '~' || map[i][j] == '%' || map[i][j] == '&')
			{
				rr = getRand(1, 4);
				if (rr==1)
				{
					n = j, m = i + 1;
				}
				else if (rr==2)
				{
					n = j - 1, m=i;
				}
				else if (rr==3)
				{
					n = j + 1, m = i;
				}
				else if (rr==4)
				{
					n = j, m = i - 1;
				}
				if(m>=0&&m<=7&&n<=7&&n>=0)
				{
					if (map[m][n] ==' ')
					{
						map[m][n] = map[i][j] ^ map[m][n];
						map[i][j] = map[i][j] ^ map[m][n];
						map[m][n] = map[i][j] ^ map[m][n];
					setpos(49 + j* 3, i+1 );
					cout <<"   ";
					setpos(49 + n * 3, m + 1);
					blue2();
					cout << map[m][n];
					white();

					}
				}

			}
		}


}
void move_con()                        //¥��ѡ��
{
	if (flood == 1)
		move_gho(map1);
	if (flood == 2)
		move_gho(map2);
	if (flood == 3)
		move_gho(map3);

}



//�������ײ 
void line1(char map[][8])
{
	
	int i, j = 0;
	while (1)
	{
		cout << "													";
		way = _getch();
		move_con();   
		move();											//�˶����ָ��Ϊ��һ���ж���׼�� 
		if (way == 'p')									//ֱ�ӽ���---�����ֵĴ��� 
		{
			exit(0);
		}
		if (way == 'j')
		{
			fstream oo;
			oo.open("data.txt.txt", ios::out);
			oo<< man.attack << endl;
			oo<< man.blood<< endl;
			oo<< man.define << endl;
			oo<< man.exp << endl;
			oo<< man.grade << endl;
			oo<< man.key << endl;
			oo<< flood<< endl;
			oo << x << endl;
			oo << y << endl;
			for (i=0; i < 8; i++)
				for (j = 0; j < 8; j++)
				{
					if (map[i][j] == ' ')
					oo <<"z";
					else
					oo << map[i][j];
				}
			oo.close();
			setpos(50, 16);
			cout << "����ɹ�";
			int k = _getch();
			setpos(50, 16);
			cout << "                ";
		}
		while (1)
		{
			if (n < 0 || m < 0 || n>7 || m>7)						//�����߽粻�ı� 
			{
				q = 0;
				break;
			}
			else if (map[m][n] == ' ')						//�����ո񽻻�		
			{
				map[y][x] = map[y][x] ^ map[m][n];
				map[m][n] = map[y][x] ^ map[m][n];
				map[y][x] = map[y][x] ^ map[m][n];
				q = 5;
				break;
			}
			else if (map[m][n] == '*')						//����ǽ���ı� 
			{
				q = 0;
				break;
			}
			else if (map[m][n] == 'B')						//����������ú��� 
			{
				battle(&big_b);
				map[m][n] = ' ';
				q = 3;
				break;
			}
			else if (map[m][n] == '!')
			{
				man.key++;
				map[m][n] = ' ';
				q = 2;
				break;
			}
			else if (map[m][n] == 'D')						//�������ж�Կ�� 
			{
				if (man.key <= 0)
				{
					q = 0;
					break;
				}
				else
				{
					man.key--;
					map[m][n] = ' ';
					q = 2;
					break;
				}
			}
			else if (map[m][n] == '+')						//����Ѫ���ж�Ѫ��	
			{
				man.blood += 60;
				if (man.blood >= 100 + (man.grade - 1) * 20)
					man.blood = 100 + (man.grade - 1) * 20;
				map[m][n] = ' ';
				q = 2;
				setpos(47, 12);
				cout << "     ";
				setpos(47, 12);
				red();
				cout << man.blood;
				white();
				break;
			}
			else if (map[m][n] == '/')						//������¥�ݽ��������л���ͼ 
			{
				q = 4;
				tiao=1;
				flood++;
				break;
			}
			else if (map[m][n] == '%')						//����ͬ(BOSS)���� 
			{
				battle(&litgho);
				map[m][n] = ' ';
				q = 3;
				break;
			}
			else if (map[m][n] == '&')						//����ͬ(BOSS)���� 
			{
				battle(&betgho);
				map[m][n] = ' ';
				q = 3;
				break;
			}
			else if (map[m][n] == '~')						//����ͬ(BOSS)���� 
			{
				battle(&mosgho);
				map[m][n] = ' ';
				q = 3;
				break;
			}

		}
		if ( tiao ==1 || man.blood == 0)
		{
			tiao = 0;
			system("cls");
			x = 0;
			y = 0;
			break;
		}
		print();
	}
	return;
}
void line2()											//¥����ת�� 
{
	q = 4;
	if (flood == 1)
	{
		print();
		line1(map1);
	}
	if (flood == 2)
	{
		print();
		line1(map2);
	}
	if (flood == 3)
	{
		print();
		line1(map3);
	}
}




//��Ϸ�Ľ���-------------------------------------------------------------------------------------------------------------------------- 

//���1��ӡ 
void end1()
{
	cout << "\n";
	green();
	cout << "						------------------------------------" << "\n";
	yellow();
	cout << "						          congratulation            " << "\n";
	cout << "							           ";
	blue2();
	cout << name; cout << "\n";
	yellow();
	cout << "						         ��ϲ��ͨ������Ϸ           " << "\n";
	cout << "						                                    " << "\n";
	cout << "						          ��л�������              " << "\n";
	cout << "						                     ---����";
	blue();
	cout << "(������)";
	cout << "\n";
	green();
	cout << "						------------------------------------";
	white();
}

//���2��ӡ 
void end2(void)
{
	cout << "\n";
	green();
	cout << "                      ------------------------------------" << "\n";
	yellow();
	cout << "                                     failure              " << "\n";
	cout << "                                    ";
	blue2();
	cout << name; cout << "\n";
	yellow();
	cout << "                                ���ź��㱻��������      " << "\n";
	cout << "                                                          " << "\n";
	cout << "                                  ��л�������            " << "\n";
	cout << "                                           ---����";
	blue();
	cout << "(������)";
	cout << "\n";
	green();
	cout << "                      ------------------------------------";
	white();
}

//��ֵ��ж� 
void end(void)           //�жϽ��(Ѫ��) 
{
	system("cls");
	if (man.blood == 0)
		end2();
	else
		end1();
	q = _getch();
}
//������-----------------------------------------------------------------
int main()
{
	SetConsoleTitleA("                                                                                                                          ħ����Ϸ(imca)");    //�Ŀ���̨���� 
	createmap();            //����map3�������ͼ
	topwindow(); 			//���ô���λ�úͶ��� 
	Hide(0);             	//���ع�꺯�� 
	begin();            	//������Ϸ��ʼ 33
	dudang();
	begining();				//������Ϸ�����ǵ����� 
	line2();				//(��)�� �˶�  �˶���������Ľ���  ����ĸı� ��ֵ�Ŀ��� ս�����ж� 
	end();					//���ƽ����Ľ��� 
	return 0;
}

