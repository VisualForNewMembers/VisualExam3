#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include<conio.h>
#include<windows.h>
#include<fstream>

void setplayer();//���ؽ�ɫ��Ϣ
void initplay();//�������ɫ��Ϣ
void playgame();//��ɫ�ƶ�
void setmap1();//���ص�ͼ
int fight();//���
int guai();//��ʾ�Ƿ�Ҫ���д��
int playerx, playery,playerz;//���������
//�������������
struct monster
{
	int hp;//Ѫ��
	int att;//����
	int def;//����
	int exp;//����ֵ
};
struct monster �� = { 160,30,10,15 };
struct monster �� = { 135,50,5,35 };
struct monster ħ�� = { 550,70,60,50 };
struct monster СС�� = { 50,5,5,10 };
//�����ɫ������
struct gamerole
{
	char name[30];
	int hp;//Ѫ��
	int def;//����
	int att;//����
	int lv;//�ȼ�
	int exp;//����ֵ
	int key;//Կ��
	int maxhp;//���Ѫ��
}player;
//��ͼ1
char map1[2][13][13] = {
	//��һ���ͼ
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
//�ڶ����ͼ
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
//���ؽ�ɫ��Ϣ
void setplayer()
{
	cout<<"��ɫ������Ϊ��" << player.name << "\n";
	cout<<"Ѫ��Ϊ��" << player.hp << "\n";
	cout<<"��������"<< player.att << "\n";
	cout<<"��������"<< player.def << "\n";
	cout<<"�ȼ���"<< player.lv << "\n";
	cout<<"����ֵ��"<< player.exp << "\n";
	cout << "Կ����Ϊ��" << player.key << "\n";
	cout<<"��ɫ������Ϊ��"<< playerx << "\n";
	cout<<"��ɫ������Ϊ��"<< playery << "\n";
	cout<<"��ͼΪ��"<< playerz << "\n";
}
//��ʼ����ɫ
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
//���ص�һ����ͼ
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
//��Ѫ���Ĺ�ʽ
int fight (int rolehp, int roleatt, int roledef, int monhp, int monatt, int mondef)
{
	int i = 20;//���ߵĹ̶��˺�;
	int j = 10;//����Ĺ̶��˺���
	int k;//���ߵĻ����˺�
	int n;//����Ļ����˺�
	k = roleatt - mondef;//���߻����˺����㹫ʽ
	n = monatt - roledef;//��������˺����㹫ʽ
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
		cout << "������أ������" << "\n";
		return 1;
	}
	else if (rolehp <= 0)
	{
		exit(0);
	}
}

//��ʾ�Ƿ���
int daguai(char x)
{
		char ip[10];
		switch (x)
		{
		//����
		case 37:
		{
			cout << "���������Ƿ�Ҫ����ս����������yes��no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, ��.hp, ��.att, ��.def))
				{
					player.exp += ��.exp;
					return 1;
				}
			}
			break;
		}
		case 38:
		{
		  //���
			cout << "�����֣��Ƿ�Ҫ����ս����������yes��no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, ��.hp, ��.att, ��.def))
				{
					player.exp += ��.exp;
					return 1;
				}
			}
			break;
		}
		case 126:
		{
			//��СС��
			cout << "����СС�֣��Ƿ����ս����������yes��no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, СС��.hp, СС��.att, СС��.def))
				{
					player.exp += СС��.exp;
					return 1;
				}
			}
			break;
		}
		case 66:
		{
			//��ħ��
			cout << "����ħ�����Ƿ�Ҫ����ս����������yes��no:";
			cin >> ip;
			if (ip[0] == 'y' && ip[1] == 'e' && ip[2] == 's' && ip[3] == '\0')
			{
				if (fight(player.hp, player.att, player.def, ħ��.hp, ħ��.att, ħ��.def))
				{
						player.exp += ħ��.exp;
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
	void loadplayer()//���ؽ�ɫ��Ϣ
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
		cout << "�浵�ɹ�";

	}
	void saveplayer()
	{
		ofstream cd("D:\\vs\\Project1\\saveplayer.txt");//�����ɫ��Ϣ
		cd << "��ɫ����Ϊ��";
		cd << player.name;
		cd << "\n";
		cd << "Ѫ��Ϊ��";
		cd << player.hp;
		cd << "\n";
		cd << "������Ϊ��";
		cd << player.att;
		cd << "\n";
		cd << "������Ϊ��";
		cd << player.def;
		cd << "\n";
		cd << "�ȼ�Ϊ��";
		cd << player.lv;
		cd << "\n";
		cd << "����Ϊ��";
		cd << player.exp;
		cd << "\n";
		cd << "Կ����Ϊ��";
		cd << player.key;
		cd << "\n";
		cd << "���Ѫ��Ϊ��";
		cd << player.maxhp;
		cd << "\n";
		cd.close();
		cout << "���سɹ�"<<"\n";
	}
	void loadmap(int n)
	{
		ifstream cd("D:\\VS\\Project1\\savemap.txt");//���ص�ͼ
		
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
		ofstream cd("D:\\VS\\Project1\\savemap.txt");//�����ͼ
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
//��ɫ�ƶ�
void playgame()
{
	while (1)
	{
		char ch;
		ch = _getch();
		switch (ch)
		{
		case'8'://������
		case 'w':
		{
			//ͨ�����ƶ�
			if (map1[playerz][playery - 1][playerx] == 32)
			{
				map1[playerz][playery - 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery--;
			}
			//��Կ��
			else if (map1[playerz][playery - 1][playerx] == 33)
			{
				player.key++;
				map1[playerz][playery - 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery--;
			}
			//��������
			else if (map1[playerz][playery - 1][playerx] == 37 || map1[playerz][playery - 1][playerx] == 38 || map1[playerz][playery - 1][playerx] == 126 || map1[playerz][playery - 1][playerx] == 66)
			{
				int m = daguai(map1[playerz][playery - 1][playerx]);
				if (m == 1)
				{
					//���ħ������Ϸ����
					if (ħ��.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//��ɫ����
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
			//������
			else if (map1[playerz][playery - 1][playerx] == 68)
			{
				char k[10];
				cout << "�Ƿ�Ҫ����һ��Կ�׿��ţ�������yes��no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//�ж�����Ƿ���Կ��
					if (player.key <= 0)
					{
						cout << "������˼����û�п����ĵ�Կ��" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery - 1][playerx] = 111;
					map1[playerz][playery][playerx] = 32;
					playerz--;
				}
			}
			//���ҩˮ
			else if (map1[playerz][playery - 1][playerx] == 43)
			{
				player.hp += 80;
				map1[playerz][playery - 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery--;
				//�涨������Ѫ��
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//����¥��
			//��¥��
			else if (map1[playerz][playery - 1][playerx] == 47)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
			//��¥��
			else if (map1[playerz][playery - 1][playerx] == 92)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
		case'2'://������
		case 's':
		{
			//ͨ�����ƶ�
			if (map1[playerz][playery + 1][playerx] == 32)
			{
				map1[playerz][playery + 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery++;
			}
			//��Կ��
			else if (map1[playerz][playery + 1][playerx] == 33)
			{
				player.key++;
				map1[playerz][playery + 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery++;
			}
			//��������
			else if (map1[playerz][playery + 1][playerx] == 37 || map1[playerz][playery + 1][playerx] == 38 || map1[playerz][playery + 1][playerx] == 126 || map1[playerz][playery + 1][playerx] == 66)
			{
				int m = daguai(map1[playerz][playery + 1][playerx]);
				if (m == 1)
				{
					//���ħ������Ϸֹͣ
					if (ħ��.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//��ɫ����
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
			//������
			else if (map1[playerz][playery + 1][playerx] == 68)
			{
				char k[10];
				cout << "�Ƿ�Ҫ����һ��Կ�׿��ţ�������yes��no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//�ж��Ƿ���Կ��
					if (player.key <= 0)
					{
						cout << "������˼����û�п����ĵ�Կ��" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery + 1][playerx] = 111;
					map1[playerz][playery][playerx] = 32;
					playery++;
				}
			}
			//���ҩˮ
			else if (map1[playerz][playery + 1][playerx] == 43)
			{
				player.hp += 80;
				map1[playerz][playery + 1][playerx] = 111;
				map1[playerz][playery][playerx] = 32;
				playery++;
				//��Ѫ�ӵ������Ѫ��
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//����¥��
			//��¥��
			else if (map1[playerz][playery + 1][playerx] == 47)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
			//��¥��
			else if (map1[playerz][playery + 1][playerx] == 92)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
		case '4'://������
		case 'a':
		{
			//ͨ�����ƶ�
			if (map1[playerz][playery][playerx - 1] == 32)
			{
				map1[playerz][playery][playerx - 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx--;
			}
			//��Կ��
			else if (map1[playerz][playery][playerx - 1] == 33)
			{
				player.key++;
				map1[playerz][playery][playerx - 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx--;
			}
			//��������
			else if (map1[playerz][playery][playerx - 1] == 37 || map1[playerz][playery][playerx - 1] == 38 || map1[playerz][playery][playerx - 1] == 126 || map1[playerz][playery][playerx - 1] == 66)
			{
				int m = daguai(map1[playerz][playery][playerx - 1]);
				if (m == 1)
				{
					//���ħ������Ϸֹͣ
					if (ħ��.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//��ɫ����
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
			//������
			else if (map1[playerz][playery][playerx - 1] == 68)
			{
				char k[10];
				cout << "�Ƿ�Ҫ����һ��Կ�׿��ţ�������yes��no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//�ж�������Կ��
					if (player.key <= 0)
					{
						cout << "������˼����û�п����ĵ�Կ��" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery][playerx - 1] = 111;
					map1[playerz][playery][playerx] = 32;
					playerx--;
				}
			}
			//���ҩˮ
			else if (map1[playerz][playery][playerx - 1] == 43)
			{
				player.hp += 80;
				map1[playerz][playery][playerx - 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx--;
				//��ɫ��Ѫ�����Ѫ��
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//����¥��
			//��¥
			else if (map1[playerz][playery][playerx - 1] == 47)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
			//��¥
			else if (map1[playerz][playery][playerx - 1] == 92)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
		case '6'://������
		case'd':
		{
			//ͨ�����ƶ�
			if (map1[playerz][playery][playerx + 1] == 32)
			{
				map1[playerz][playery][playerx + 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx++;
			}
			//��Կ��
			else if (map1[playerz][playery][playerx + 1] == 33)
			{
				player.key++;
				map1[playerz][playery][playerx + 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx++;
			}
			//��������
			else if (map1[playerz][playery][playerx + 1] == 37 || map1[playerz][playery][playerx + 1] == 38 || map1[playerz][playery][playerx + 1] == 126 || map1[playerz][playery][playerx + 1] == 66)
			{
				int m = daguai(map1[playerz][playery][playerx + 1]);
				if (m == 1)
				{
					//���ħ������Ϸֹͣ
					if (ħ��.hp <= 0)
					{
						exit(0);
					}
					else
					{
						//��ɫ����
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
			//������
			else if (map1[playerz][playery][playerx + 1] == 68)
			{
				char k[10];
				cout << "�Ƿ�Ҫ����һ��Կ�׿��ţ�������yes��no";
				cin >> k;
				if (k[0] == 'y' && k[1] == 'e' && k[2] == 's' && k[3] == '\0')
				{
					//�ж��Ƿ���Կ��
					if (player.key <= 0)
					{
						cout << "������˼����û�п����ĵ�Կ��" << "\n";
						break;
					}
					player.key--;
					map1[playerz][playery][playerx + 1] = 111;
					map1[playerz][playery][playerx] = 32;
					playerx++;
				}
			}
			//���ҩˮ
			else if (map1[playerz][playery][playerx + 1] == 43)
			{
				player.hp += 80;
				map1[playerz][playery][playerx + 1] = 111;
				map1[playerz][playery][playerx] = 32;
				playerx++;
				//��Ѫ�����Ѫ��
				if (player.hp >= player.maxhp)
				{
					player.hp = player.maxhp;
				}
			}
			//����¥��
			//��¥
			else if (map1[playerz][playery][playerx + 1] == 47)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
			//��¥
			else if (map1[playerz][playery][playerx + 1] == 92)
			{
				char l[10];
				cout << "����¥�ݣ��Ƿ�Ҫ�л���ͼ��������yes��no";
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
		setmap1(playerz);//������ʾ��ͼ
		setplayer();//������ʾ��ɫ
		cd.saveplayer();//�浵��ɫ
		cd.savemap(playerz);//�浵��ͼ
	}
}
//����������
int main()
{

	cout << "�������ַ�2��4��6��8��'w','a','d','s'�����У��£����ң��ϵ��ƶ�" << "\n";
	cout << "�������������";
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