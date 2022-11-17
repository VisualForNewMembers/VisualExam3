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
制作模块为  定义  游戏开始的界面 游戏的开幕 人物的运动  战斗的判定 人物碰撞后的判定 游戏结束界面  主函数的构成
1.定义
2.游戏开始的界面
3地图人物的打印 (输出)
4.人物的运动
5.战斗的判定
6.人物的碰撞判定
7.主函数的构成(串联各个函数)
*/


/*
			====================================================
			| 1.一开始用的是system("cls")+重新打印一遍造成卡顿 |
			|   后面去用改光标的方式去解决卡顿问题             |
			| 所以改变界面那里的代码比较乱(引入了新的变量q)    |
			| 2.有些地方后面改字体颜色导致比较乱一点	   n    |
			====================================================
*/

//定义+初始化   地图怪物和角色信息  控制台的设置---------------------------------------------------------------------------------------------------- 
char q;

//地图
//地图一
char map1[8][8] = {                               
	{'o',' ',' ',' ',' ','*','!','*'},
	{'*','*','*','*',' ','*','!','*'},
	{' ','&','+','*',' ','*','+','*'},
	{' ','*',' ','*',' ','*','~','*'},
	{' ','*','*','*',' ','*','D','*'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'%','*','*',' ','*','*','*','*'},
	{'!',' ','*',' ','D','%','D','/'} };
//地图二
char map2[8][8] = {
	{'o',' ',' ',' ','*','!','!','*'},
	{'*','*','*',' ','*','*','~','*'},
	{'+','&',' ',' ','*','*','D','*'},
	{'*','*','*',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ','*','*','D','*'},
	{'%','*','*','*','*',' ','D','+'},
	{' ','%','!',' ','*',' ',' ',' '},
	{'*','*',' ',' ','*','+',' ','/'} };

//地图三(为半随机地图)
char map3[8][8] = {
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{} };
//用来存放和读取地图
char map3_duqu[8][8] = {
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{} };

//定义
string name;
char way;
int x = 0, y = 0, flood = 1, num, n, m;
int tiao = 0;
int theb = 1;

//随机数
int getRand(int min, int max)           
{
	return (rand() % (max - min + 1)) + min;
}



//主角属性 
typedef struct Man {
	int blood;
	int grade;
	int define;
	int attack;
	int exp;
	int key;
}hero;
hero man = { 100,1,20,30,0,0 };

//怪物属性设置 
typedef struct  envy {
	int blood;				//血量 
	int attack;				//攻击 
	int define;				//防御 
	int exp;
	int hao;
}ghost;
ghost litgho = { 160,20,10,20,1 };
ghost betgho = { 120,25,20,30,2 };
ghost mosgho = { 130,35,25,50,3 };
ghost  big_b = { 170,75,50,0,4 };

//——-————————————————————窗口设置——————————————————
//顶置窗口 
void topwindow()
{
	HWND hWnd = GetForegroundWindow();
	SetWindowPos(hWnd, HWND_TOPMOST, 400, 250, 0, 0, SWP_NOSIZE);
}

//光标设置 
void setpos(short x, short y)
{
	COORD  point = { x,y };
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}

//光标隐藏 
void Hide(int l)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,l };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//改颜色

//前景白(作为初始化原背景) 
void white()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//前景绿 
void green()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_GREEN);
}
//前景红 
void red()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_RED);
}
//前景黄
void yellow()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN);
}
//前景蓝
void blue()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE);

}
//前景淡蓝
void blue2()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE | FOREGROUND_GREEN);
}
//背景红 
void redback()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(outputHandle, BACKGROUND_RED);
}

//创建随机地图（地图三的半随机）------------------------------------------------------------------------------------
void createmap()
{
	int x = 0, y = 0, cor = 1, r;
	int m, n;				//中间存储位置 
	srand(time(0));			//重置种子，确保每次随机数不一样 
	for (int i = 0; i < 8; i++)			//创建一条通关的路径 
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
	map3[7][7] = 'B';				//设立boss区 
	map3[7][6] = '+';
	map3[7][5] = '*';
	map3[6][7] = '+';
	map3[6][6] = 'D';
	map3[6][5] = 'D';
	map3[5][7] = '*';
	map3[5][6] = 'D';
	map3[5][5] = ' ';

	for (int i = 0; i < 5; i++)       //为两把钥匙放位置 
	{
		map3[6][i] = '*';
	}
	r = getRand(0, 1);			//通关路径与boss区相连 
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
	while (1)				//在右上角随机 
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

	while (1)      //寻路 
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
		}                            //存在问题 
		else
			map3[y][x] = ' ';
	}

	while (1)				//在左下角随机   
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
	n = getRand(40, 45);               //可以随机地图的密集程度 
	for (int i = 0; i < n; i++)			//随机在空白处放置怪物
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


//-------------------读档选择----------------------------------------------------------
void dudang(){
while (1)                                                                       //让玩家选择 
{
	red();
	cout << "					[-----------------------------------]" << "\n";
	white();
	cout << "					|                                   |" << "\n";
	cout << "					|         按'1'开始新的游戏         |" << "\n";
	cout << "					|         按'2'读取游戏             |" << "\n";
	cout << "					|                                   |" << "\n";
	cout << "					|  (开始后游戏可以按'j'键保存游戏)  |" << "\n";
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
		cout << "				               请输入正确的数字" << "\n";
		cout << "		                 		 按任意键继续";
	}
	q = _getch();
	system("cls");

}
system("cls");
return;
}
//开始的游戏界面 (第一部分)----------------------------------------------------------------------------
void begin(void)
{
	while (1)                                                                       //让玩家选择 
	{
		yellow();
		cout << "					[-----------------------------------]" << "\n";         //这里参差不齐是多次调用颜色函数导致的 
		white();
		cout << "					|             ";
		red();
		cout << "魔塔游戏";
		white();
		cout << "              |" << "\n";
		cout << "					|按";
		red();
		cout << "'1'";
		white();
		cout << "开始游戏                      |" << "\n";
		cout << "					|按";
		red();
		cout << "'2'";
		white();
		cout << "关于地图和怪物和操作信息      |" << "\n";
		cout << "					|                                   |" << "\n";
		cout << "					|                       作者-";
		blue();
		cout << "蓝XX";
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
			cout << "					             信息如下                       " << "\n";
			cout << "				                 地图(共两种)                   " << "\n";
			cout << "				         O为勇者             %:&:~:为种不同的怪 " << "\n";
			cout << "				         *为障碍或墙         D为锁上的门		" << "\n";
			cout << "				         +为回血点           ！为钥匙  		    " << "\n";
			cout << "				         B为魔王             #为地图编辑        " << "\n";
			cout << "				                 操作						    " << "\n";
			cout << "				         输入";
			red();
			cout << "2468(wasd)";
			green();
			cout << "为下左右上				" << "\n";
			cout << "				                 怪物                           " << "\n";
			cout << "				         能力强度 ";
			red();
			cout << "B > ~ > & > %";
			green();
			cout << "                 " << "\n";
			cout << "						    按";
			red();
			cout << "任意键";
			green();
			cout << "返回" << "\n";
			white();
		}
		if (q != '1' && q != '2')
		{
			green();
			cout << "\n";
			cout << "				               请输入正确的数字" << "\n";
			cout << "		                 		 按";
			red();
			cout << "任意键";
			green();
			cout << "继续";
			white();
		}
		q = _getch();
		white();
		system("cls");

	}
	system("cls");
	return;
}


//游戏的开幕---------------------------------------------------------------------------------------
void begining()															//打印开幕的界面 
{
	cout << "					[---------------------------------]" << "\n";
	red();
	cout << "					      你的目标是打败大B(魔王)      " << "\n";
	white();
	cout << "					          请输入你的名字           " << "\n";
	cout << "					          (按Enter确认)		" << "\n";
	cout << "                               			 ";

	cin >> name;
	system("cls");
	q = 4;
	return;
}


//地图和人物信息的打印----------------------------------------------------------------------------------------------------------

//q为控制改变界面

/*
q为不同的更改类型
q==3为战斗
q==4为切换地图
q==5是交换
q==2是清除
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
			cout << "                                                |             正在战斗中          |" << "\n";
			cout << "                                                |                                 |" << "\n";
			cout << "                                                |            ";
			red();
			cout << "按任意键继续";
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
			for (j = 0; j < 8; j++)									//打印地图 
			{
				if (p[i][j] == 'o' || p[i][j] == 'B' || p[i][j] == '/')      //这里的if else是为了改变颜色 
				{
					red();          //------改变颜色 
					cout << p[i][j];
					white();		//-----调回正常 
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
		cout << "*    			    	  	  血量:";
		red();
		cout << man.blood;
		white();
		cout << "		" << "等级:" << man.grade << "\n";
		cout << "*    			    		攻击力:" << man.attack << "               " << "经验值：" << man.exp << "\n";
		cout << "*	    		    		防御力:" << man.define << " 		" << "位置(x.y)";
		blue2();
		cout << x << " " << y;
		white();
		cout << "\n";
		cout << "*	    		    		输入2467(wasd)进行运动          输入p结束游戏";
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
		setpos(49 + n * 3, m + 1);                     //改变光标位置 
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


//人物的运动------------------------------------------------------------------------- 
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


//战斗系统----------------------------------------------------------------------------------------------------------------------------


//经验升级 
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

//与敌人战斗 
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
		cout << "成功了";
	}
	else
	{
		cout << "失败了";
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
void move_con()                        //楼层选择
{
	if (flood == 1)
		move_gho(map1);
	if (flood == 2)
		move_gho(map2);
	if (flood == 3)
		move_gho(map3);

}



//人物的碰撞 
void line1(char map[][8])
{
	
	int i, j = 0;
	while (1)
	{
		cout << "													";
		way = _getch();
		move_con();   
		move();											//运动后的指向为下一步判定做准备 
		if (way == 'p')									//直接结束---有死局的存在 
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
			cout << "保存成功";
			int k = _getch();
			setpos(50, 16);
			cout << "                ";
		}
		while (1)
		{
			if (n < 0 || m < 0 || n>7 || m>7)						//超过边界不改变 
			{
				q = 0;
				break;
			}
			else if (map[m][n] == ' ')						//碰到空格交换		
			{
				map[y][x] = map[y][x] ^ map[m][n];
				map[m][n] = map[y][x] ^ map[m][n];
				map[y][x] = map[y][x] ^ map[m][n];
				q = 5;
				break;
			}
			else if (map[m][n] == '*')						//碰到墙不改变 
			{
				q = 0;
				break;
			}
			else if (map[m][n] == 'B')						//碰到怪物调用函数 
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
			else if (map[m][n] == 'D')						//碰到门判定钥匙 
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
			else if (map[m][n] == '+')						//碰到血包判定血量	
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
			else if (map[m][n] == '/')						//碰到下楼梯结束函数切换地图 
			{
				q = 4;
				tiao=1;
				flood++;
				break;
			}
			else if (map[m][n] == '%')						//怪物同(BOSS)类似 
			{
				battle(&litgho);
				map[m][n] = ' ';
				q = 3;
				break;
			}
			else if (map[m][n] == '&')						//怪物同(BOSS)类似 
			{
				battle(&betgho);
				map[m][n] = ' ';
				q = 3;
				break;
			}
			else if (map[m][n] == '~')						//怪物同(BOSS)类似 
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
void line2()											//楼层间的转换 
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




//游戏的结束-------------------------------------------------------------------------------------------------------------------------- 

//结局1打印 
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
	cout << "						         恭喜你通过了游戏           " << "\n";
	cout << "						                                    " << "\n";
	cout << "						          感谢你的游玩              " << "\n";
	cout << "						                     ---作者";
	blue();
	cout << "(蓝斌铨)";
	cout << "\n";
	green();
	cout << "						------------------------------------";
	white();
}

//结局2打印 
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
	cout << "                                很遗憾你被怪物打败了      " << "\n";
	cout << "                                                          " << "\n";
	cout << "                                  感谢你的游玩            " << "\n";
	cout << "                                           ---作者";
	blue();
	cout << "(蓝斌铨)";
	cout << "\n";
	green();
	cout << "                      ------------------------------------";
	white();
}

//结局的判断 
void end(void)           //判断结局(血量) 
{
	system("cls");
	if (man.blood == 0)
		end2();
	else
		end1();
	q = _getch();
}
//主函数-----------------------------------------------------------------
int main()
{
	SetConsoleTitleA("                                                                                                                          魔塔游戏(imca)");    //改控制台标题 
	createmap();            //创建map3的随机地图
	topwindow(); 			//设置窗口位置和顶置 
	Hide(0);             	//隐藏光标函数 
	begin();            	//控制游戏开始 33
	dudang();
	begining();				//输入游戏的主角的名字 
	line2();				//(主)含 运动  运动后与物体的交互  界面的改变 数值的控制 战斗的判定 
	end();					//控制结束的界面 
	return 0;
}

