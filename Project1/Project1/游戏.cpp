#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include<conio.h>
#include<windows.h>
#include<fstream>

void setplayer();//加载角色信息
void initplay();//初定义角色信息
void playgame();//角色移动
void setmap1();//加载地图
int fight();//打怪
int guai();//提示是否要进行打怪
int playerx, playery,playerz;//人物的坐标
//创建怪物的属性
struct monster
{
	int hp;//血量
	int att;//攻击
	int def;//防御
	int exp;//经验值
};
struct monster 妖 = { 160,30,10,15 };
struct monster 怪 = { 135,50,5,35 };
struct monster 魔王 = { 550,70,60,50 };
struct monster 小小怪 = { 50,5,5,10 };
//定义角色的数据
struct gamerole
{
	char name[30];
	int hp;//血量
	int def;//防御
	int att;//攻击
	int lv;//等级
	int exp;//经验值
	int key;//钥匙
	int maxhp;//最大血量
}player;
//地图1
char map1[2][13][13] = {
	//第一层地图
	{
	{42,42,42,42,42,42,42,42,42,42,42,42,42},
	{42,47,32,37,38,126,32,32,32,32,32,32,42},
	{42,42,42,42,42,42,42,42,42,42,42,32,42},
	{42,43,32,32,68,32,42,32,33,32,42,32,42},
	{42,126,126,32,42,32,42,32,43,32,42,32,42},
	{42,42,68,42,42,32,42,42,42,32,42,32,42},
	{42,33,32,32,42,32,33,32,38,32,42,32,42},
	{42,32,37,32,42,32,42,42,42,42,42,32,42},
	{42,42,68,42,42,32,32,32,32,32,32,32,42},
	{42,126,32,32,42,42,126,42,42,42,126,42,42},
	{42,43,32,33,42,33,32,32,42,32,32,43,42},
	{42,43,32,32,42,32,111,32,42,32,33,32,42},
	{42,42,42,42,42,42,42,42,42,42,42,42,42},
	},
//第二层地图
{
	{42,42,42,42,42,42,42,42,42,42,42,42,42},
	{42,32,32,32,32,32,32,32,32,42,32,66,42},
	{42,42,42,42,42,42,32,32,32,42,32,32,42},
	{42,38,32,42,32,42,32,32,32,68,43,32,42},
	{42,43,33,68,32,68,32,32,32,42,42,42,42},
	{42,42,42,42,32,42,42,42,32,42,42,42,42},
	{42,33,37,32,32,42,68,32,32,42,32,126,42},
	{42,42,42,42,42,42,42,42,32,42,33,32,42},
	{42,43,33,37,38,32,32,32,32,68,32,43,42},
	{42,42,42,42,42,42,42,42,32,42,42,42,42},
	{42,33,32,42,32,42,43,32,38,32,33,42,42},
	{42,92,111,68,32,32,32,32,33,32,32,42,42},
	{42,42,42,42,42,42,42,42,42,42,42,42,42}
}
};
//加载角色信息
void setplayer()
{
	cout<<"角色的名字为：" << player.name << "\n";
	cout<<"血量为：" << player.hp << "\n";
	cout<<"攻击力："<< player.att << "\n";
	cout<<"防御力："<< player.def << "\n";
	cout<<"等级："<< player.lv << "\n";
	cout<<"经验值："<< player.exp << "\n";
	cout << "钥匙数为：" << player.key << "\n";
	cout<<"角色横坐标为："<< playerx << "\n";
	cout<<"角色纵坐标为："<< playery << "\n";
	cout<<"地图为："<< playerz << "\n";
}
//初始化角色
void initplayer()
{
	player.hp =100;
	player.maxhp = 100;
	player.att = 30;
	player.def = 20;
	player.lv = 0;
	player.exp = 1;
	player.key = 0;
	playerx = 6;
	playery = 11;
	playerz = 0;
}
//加载第一个地图
void setmap1(int n)
{
	int i, j;
	for (i = 0; i < 13; i++)//[n][i][j]
	{
		for (j = 0; j < 13; j++)
		{
			cout << map1[n][i][j];
		}
		cout << "\n";
	}

}
//打斗血量的公式
int fight (int rolehp, int roleatt, int roledef, int monhp, int monatt, int mondef)
{
	int i = 20;//勇者的固定伤害;
	int j = 10;//怪物的固定伤害；
	int k;//勇者的基础伤害
	int n;//怪物的基础伤害
	k = roleatt - mondef;//勇者基础伤害计算公式
	n = monatt - roledef;//怪物基础伤害计算公式
	if (k <= 0)
	{
		k = 0;
	}
	else if (n <= 0)
	{
		n = 0;
	}
	while (rolehp > 0 || monhp > 0)
	{
		monhp -= (i + k);
		if (monhp <= 0)
			break;
		rolehp -= (j + n);
		if (rolehp <= 0)
			break;
	}
	if (rolehp > 0)
	{
		player.hp = rolehp;
		cout << "打过了呢，你真棒" << "\n";
		return 1;
	}
	else if (rolehp <= 0)
	{
		exit(0);
	}
}

//提示是否打怪
int daguai(char x)
{
		char ip[10];
		switch (x)
		{
		//打妖
		case 37:
		{
			cout << "遇到妖，是否要进行战斗，请输入yes或no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, 妖.hp, 妖.att, 妖.def))
				{
					player.exp += 妖.exp;
					return 1;
				}
			}
			break;
		}
		case 38:
		{
		  //打怪
			cout << "遇到怪，是否要进行战斗，请输入yes或no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, 怪.hp, 怪.att, 怪.def))
				{
					player.exp += 怪.exp;
					return 1;
				}
			}
			break;
		}
		case 126:
		{
			//打小小怪
			cout << "遇到小小怪，是否进行战斗，请输入yes或no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, 小小怪.hp, 小小怪.att, 小小怪.def))
				{
					player.exp += 小小怪.exp;
					return 1;
				}
			}
			break;
		}
		case 66:
		{
			//打魔王
			cout << "遇到魔王，是否要进行战斗，请输入yes或no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, 魔王.hp, 魔王.att, 魔王.def))
				{
						player.exp += 魔王.exp;
						exit(0);
				}
			}
			break;
		}
		}
		return 0;
}
struct cd
{
	void loadplayer()//加载角色信息
	{
		ifstream cd("D:\\vs\\Project1\\saveplayer.txt");
		cd >> player.name;
		cd >> player.hp;
		cd >> player.att;
		cd >> player.def;
		cd >> player.lv;
		cd >> player.exp;
		cd >> player.key;
		cd >> player.maxhp;
		cd.close();
		cout << "存档成功";

	}
	void saveplayer()
	{
		ofstream cd("D:\\vs\\Project1\\saveplayer.txt");//保存角色信息
		cd << "角色名字为：";
		cd << player.name;
		cd << "\n";
		cd << "血量为：";
		cd << player.hp;
		cd << "\n";
		cd << "攻击力为：";
		cd << player.att;
		cd << "\n";
		cd << "防御力为：";
		cd << player.def;
		cd << "\n";
		cd << "等级为：";
		cd << player.lv;
		cd << "\n";
		cd << "经验为：";
		cd << player.exp;
		cd << "\n";
		cd << "钥匙数为：";
		cd << player.key;
		cd << "\n";
		cd << "最大血量为：";
		cd << player.maxhp;
		cd << "\n";
		cd.close();
		cout << "加载成功"<<"\n";
	}
	void loadmap(int n)
	{
		ifstream cd("D:\\VS\\Project1\\savemap.txt");//加载地图
		
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				cd >> map1[n][i][j];
			}
		}
		cd.close();
	}
	void savemap(int n)
	{
		ofstream cd("D:\\VS\\Project1\\savemap.txt");//保存地图
	    for(int i=0;i<13;i++)
		{
			for (int j = 0; j < 13; j++)
			{
				cd << map1[n][i][j];
			}
			cd << "\n";
		}
		cd.close();
	}
}cd;
//角色移动
void playgame()
{
	while (1)
	{
		char ch;
		ch = _getch();
		switch (ch)
		{
		case'8'://向上走
		case 'w':
		{
			//通道的移动
			if (map1[playerz][playery - 1][playerx] == 32)
			{
				map1[playerz][playery - 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery--;
			}
			//捡钥匙
			else if (map1[playerz][playery - 1][playerx] == 33)
			{
				player.key++;
				map1[playerz][playery - 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery--;
			}
			//遇到怪物
			else if (map1[playerz][playery - 1][playerx] == 37 || map1[playerz][playery - 1][playerx] == 38 || map1[playerz][playery - 1][playerx] == 126 || map1[playerz][playery - 1][playerx] == 66)
			{
				int m = daguai(map1[playerz][playery - 1][playerx]);
				if (m == 1)
				{
					//打败魔王后，游戏结束
					if (魔王.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//角色升级
						if (player.exp >= 50)
						{
							player.maxhp += 20;
							player.lv++;
							player.att += 10;
							player.def += 5;
							player.exp -= 50;
						}
						map1[playerz][playery - 1][playerx] = 111;
						map1[playerz][playery][playerx] = 32;
						playery--;
					}
				}
			}
			//遇到门
			else if (map1[playerz][playery - 1][playerx] == 68)
			{
				char k[10];
				cout << "是否要消耗一个钥匙开门，请输入yes或no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//判断你的是否有钥匙
					if (player.key <= 0)
					{
						cout << "不好意思，你没有可消耗的钥匙" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery - 1][playerx] = 111;
					map1[playerz][playery][playerx] = 32;
					playerz--;
				}
			}
			//捡红药水
			else if (map1[playerz][playery - 1][playerx] == 43)
			{
				player.hp += 80;
				map1[playerz][playery - 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery--;
				//规定的最大加血量
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//遇到楼梯
			//上楼梯
			else if (map1[playerz][playery - 1][playerx] == 47)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz + 1][11][2] = 111;
					map1[playerz][playery - 1][playerx] = 47;
					playery = 11;
					playerx = 2;
					playerz++;
				}
			}
			//下楼梯
			else if (map1[playerz][playery - 1][playerx] == 92)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz - 1][1][2] = 111;
					map1[playerz][playery - 1][playerx] = 92;
					playery = 1;
					playerx = 2;
					playerz--;
				}
			}
			break;
		}
		case'2'://向下走
		case 's':
		{
			//通道的移动
			if (map1[playerz][playery + 1][playerx] == 32)
			{
				map1[playerz][playery + 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery++;
			}
			//捡钥匙
			else if (map1[playerz][playery + 1][playerx] == 33)
			{
				player.key++;
				map1[playerz][playery + 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery++;
			}
			//遇到怪物
			else if (map1[playerz][playery + 1][playerx] == 37 || map1[playerz][playery + 1][playerx] == 38 || map1[playerz][playery + 1][playerx] == 126 || map1[playerz][playery + 1][playerx] == 66)
			{
				int m = daguai(map1[playerz][playery + 1][playerx]);
				if (m == 1)
				{
					//打败魔王，游戏停止
					if (魔王.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//角色升级
						if (player.exp >= 50)
						{
							player.lv++;
							player.maxhp += 20;
							player.att += 10;
							player.def += 5;
							player.exp -= 50;
						}
						map1[playerz][playery + 1][playerx] = 111;
						map1[playerz][playery][playerx] = 32;
						playery++;
					}
				}
			}
			//遇到门
			else if (map1[playerz][playery + 1][playerx] == 68)
			{
				char k[10];
				cout << "是否要消耗一个钥匙开门，请输入yes或no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//判断是否有钥匙
					if (player.key <= 0)
					{
						cout << "不好意思，你没有可消耗的钥匙" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery + 1][playerx] = 111;
					map1[playerz][playery][playerx] = 32;
					playery++;
				}
			}
			//捡红药水
			else if (map1[playerz][playery + 1][playerx] == 43)
			{
				player.hp += 80;
				map1[playerz][playery + 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery++;
				//加血加到的最大血量
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//遇到楼梯
			//上楼梯
			else if (map1[playerz][playery + 1][playerx] == 47)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz + 1][11][2] = 111;
					map1[playerz][playery + 1][playerx] = 47;
					playery = 11;
					playerx = 2;
					playerz++;
				}
			}
			//下楼梯
			else if (map1[playerz][playery + 1][playerx] == 92)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz - 1][1][2] = 111;
					map1[playerz][playery + 1][playerx] = 92;
					playery = 1;
					playerx = 2;
					playerz--;
				}
			}
			break;
		}
		case '4'://向左走
		case 'a':
		{
			//通道的移动
			if (map1[playerz][playery][playerx - 1] == 32)
			{
				map1[playerz][playery][playerx - 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx--;
			}
			//捡钥匙
			else if (map1[playerz][playery][playerx - 1] == 33)
			{
				player.key++;
				map1[playerz][playery][playerx - 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx--;
			}
			//遇到怪物
			else if (map1[playerz][playery][playerx - 1] == 37 || map1[playerz][playery][playerx - 1] == 38 || map1[playerz][playery][playerx - 1] == 126 || map1[playerz][playery][playerx - 1] == 66)
			{
				int m = daguai(map1[playerz][playery][playerx - 1]);
				if (m == 1)
				{
					//打败魔王，游戏停止
					if (魔王.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//角色升级
						if (player.exp >= 50)
						{
							player.lv++;
							player.maxhp += 20;
							player.att += 10;
							player.def += 5;
							player.exp -= 50;
						}
						map1[playerz][playery][playerx - 1] = 111;
						map1[playerz][playery][playerx] = 32;
						playerx--;
					}
				}
			}
			//遇到门
			else if (map1[playerz][playery][playerx - 1] == 68)
			{
				char k[10];
				cout << "是否要消耗一个钥匙开门，请输入yes或no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//判断你是有钥匙
					if (player.key <= 0)
					{
						cout << "不好意思，你没有可消耗的钥匙" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery][playerx - 1] = 111;
					map1[playerz][playery][playerx] = 32;
					playerx--;
				}
			}
			//捡红药水
			else if (map1[playerz][playery][playerx - 1] == 43)
			{
				player.hp += 80;
				map1[playerz][playery][playerx - 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx--;
				//角色加血的最大血量
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//遇到楼梯
			//上楼
			else if (map1[playerz][playery][playerx - 1] == 47)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz + 1][11][2] = 111;
					map1[playerz][playery][playerx - 1] = 47;
					playery = 11;
					playerx = 2;
					playerz++;
				}
			}
			//下楼
			else if (map1[playerz][playery][playerx - 1] == 92)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz - 1][1][2] = 111;
					map1[playerz][playery][playerx - 1] = 92;
					playery = 1;
					playerx = 2;
					playerz--;
				}
			}
			break;
		}
		case '6'://向右走
		case'd':
		{
			//通道的移动
			if (map1[playerz][playery][playerx + 1] == 32)
			{
				map1[playerz][playery][playerx + 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx++;
			}
			//捡钥匙
			else if (map1[playerz][playery][playerx + 1] == 33)
			{
				player.key++;
				map1[playerz][playery][playerx + 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx++;
			}
			//遇到怪物
			else if (map1[playerz][playery][playerx + 1] == 37 || map1[playerz][playery][playerx + 1] == 38 || map1[playerz][playery][playerx + 1] == 126 || map1[playerz][playery][playerx + 1] == 66)
			{
				int m = daguai(map1[playerz][playery][playerx + 1]);
				if (m == 1)
				{
					//打败魔王，游戏停止
					if (魔王.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//角色升级
						if (player.exp >= 50)
						{
							player.lv++;
							player.maxhp += 20;
							player.att += 10;
							player.def += 5;
							player.exp -= 50;
						}
						map1[playerz][playery][playerx + 1] = 111;
						map1[playerz][playery][playerx] = 32;
						playerx++;
					}
				}
			}
			//遇到门
			else if (map1[playerz][playery][playerx + 1] == 68)
			{
				char k[10];
				cout << "是否要消耗一个钥匙开门，请输入yes或no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//判断是否有钥匙
					if (player.key <= 0)
					{
						cout << "不好意思，你没有可消耗的钥匙" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery][playerx + 1] = 111;
					map1[playerz][playery][playerx] = 32;
					playerx++;
				}
			}
			//捡红药水
			else if (map1[playerz][playery][playerx + 1] == 43)
			{
				player.hp += 80;
				map1[playerz][playery][playerx + 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx++;
				//加血的最大血量
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//遇到楼梯
			//上楼
			else if (map1[playerz][playery][playerx + 1] == 47)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz + 1][11][2] = 111;
					map1[playerz][playery][playerx + 1] = 47;
					playery = 11;
					playerx = 2;
					playerz++;
				}
			}
			//下楼
			else if (map1[playerz][playery][playerx + 1] == 92)
			{
				char l[10];
				cout << "遇到楼梯，是否要切换地图，请输入yes或no";
				cin >> l;
				if (l[0] == 'y' && l[1] == 'e' && l[2] == 's' && l[3] == '\0')
				{
					map1[playerz - 1][1][2] = 111;
					map1[playerz][playery][playerx + 1] = 92;
					playery = 1;
					playerx = 2;
					playerz--;
				}
			}
			break;
		}
		}
		setmap1(playerz);//重新显示地图
		setplayer();//重新显示角色
		cd.saveplayer();//存档角色
		cd.savemap(playerz);//存档地图
	}
}
//主函数运行
int main()
{

	cout << "请输入字符2，4，6，8或'w','a','d','s'来进行，下，左，右，上的移动" << "\n";
	cout << "请输入你的名字";
	cin >> player.name;
	initplayer();
	while (1)
	{
		setplayer();
		setmap1(playerz);
		playgame();
	}
	return 0;
}