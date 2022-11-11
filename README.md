# VisualExam3
做游戏
#include<stdlib.h>

#include<graphics.h>

#include <windows.h>

#include<conio.h>

#include<graphics.h>

#include<windows.h>

#include <stdio.h>



void initgamePicture();  //加载游戏图片

void SetPlayer();    //显示角色信息

void initPlayer();   //初始化游戏角色

void SetMap();     //加载游戏地图

char* intToString(int Number); //把整数转化成字符串

void playGame();     //开始游戏

int Combat(int x);

int VS(int playHP, int playATT, int playDEF, int monHP, int monATT, int monDEF);



int playerx, playery;

char str[20] = "";

//地图1

int map[13][13] = {

{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

{ 0, 98, 1, 14, 15, 14, 1, 1, 1, 1, 1, 1, 0 },

{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },

{ 0, 8, 1, 1, 2, 1, 0, 5, 6, 1, 0, 1, 0 },

{ 0, 1, 12, 1, 0, 1, 0, 4, 8, 1, 0, 1, 0 },

{ 0, 0, 2, 0, 0, 1, 0, 0, 0, 14, 0, 1, 0 },

{ 0, 6, 1, 1, 0, 1, 3, 10, 11, 10, 0, 1, 0 },

{ 0, 1, 13, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0 },

{ 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },

{ 0, 1, 1, 1, 0, 0, 14, 0, 0, 0, 14, 0, 0 },

{ 0, 8, 1, 6, 0, 7, 1, 6, 0, 1, 10, 1, 0 },

{ 0, 8, 1, 6, 0, 1, 99, 1, 0, 14, 9, 14, 0 },

{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

};

IMAGE Wall, Ground, Green_Slime, Red_Slime, Blue_Cry, Red_Cry, Blue_Key, Yellow_Key,

Red_Med, Blue_Med, Ladder, Small_Skull, Big_Skull, Small_Bat, Small_Wizard,

Blue_door, Yellow_door, Player, Message;

HWND hwnd;

struct gamerole

{

	char name[20] = "黑蛋"; //玩家名字

	int HP;   //血量

	int MP;

	int DEF; //防御

	int ATT;  //攻击

	int Lv;   //等级

	int Exp;  //经验

	int Num_Blue_Key; //蓝钥匙数量

	int Num_Yellow_Key;

}player;



struct monster

{

	int HP;   //血量

	int ATT;  //攻击

	int DEF; //防御

	int Exp;  //经验

};

struct monster Green_Slime_Pro = { 50,10,12,100 };  //绿史莱姆属性   

struct monster Red_Slime_Pro = { 100, 50, 12, 500 }; //红史莱姆属性

struct monster Small_Wizard_Pro = { 100, 30, 9, 400 };//小巫师属性

struct monster Small_Bat_Pro = { 20, 10, 9, 50 };     //小蝙蝠属性

struct monster Small_Skull_Pro = { 30, 20, 10, 200 };  //小骷髅属性

struct monster Big_Skull_Pro = { 60, 50, 25, 300 };   //大骷髅属性





int main()

{

	initPlayer();

	hwnd = initgraph(60 * 14, 60 * 13);

	initgamePicture();



	while (1) {

		SetMap();

		SetPlayer();

		playGame();

	}



	return 0;

}



/*

*显示角色信息

*/

void SetPlayer()

{

	putimage(60 * 13, 0, &Message);

	outtextxy(60 * 13 + 12, 100, player.name);

	outtextxy(60 * 13 + 12, 180, intToString(player.Lv));

	outtextxy(60 * 13 + 12, 235, intToString(player.Exp));

	outtextxy(60 * 13 + 12, 362, intToString(player.HP));

	outtextxy(60 * 13 + 12, 425, intToString(player.MP));

	outtextxy(60 * 13 + 12, 517, intToString(player.ATT));

	outtextxy(60 * 13 + 12, 567, intToString(player.DEF));

	outtextxy(60 * 13 + 12, 689, intToString(player.Num_Yellow_Key));

	outtextxy(60 * 13 + 12, 759, intToString(player.Num_Blue_Key));

}



/*

*  加载游戏图片

*/

void initgamePicture()

{

	loadimage(&Wall, "墙.jpg", 60, 60);

	loadimage(&Ground, "地板.jpg", 60, 60);

	loadimage(&Green_Slime, "绿史莱姆.jpg", 60, 60);

	loadimage(&Red_Slime, "红史莱姆.jpg", 60, 60);



	loadimage(&Blue_Cry, "蓝水晶.jpg", 60, 60);

	loadimage(&Red_Cry, "红水晶.jpg", 60, 60);



	loadimage(&Blue_Key, "蓝钥匙.jpg", 60, 60);

	loadimage(&Yellow_Key, "黄钥匙.jpg", 60, 60);



	loadimage(&Red_Med, "小红药水.jpg", 60, 60);

	loadimage(&Blue_Med, "小蓝药水.jpg", 60, 60);



	loadimage(&Ladder, "梯子.jpg", 60, 60);

	loadimage(&Small_Bat, "小蝙蝠.jpg", 60, 60);

	loadimage(&Small_Wizard, "小巫师.jpg", 60, 60);

	loadimage(&Small_Skull, "骷髅兵.jpg", 60, 60);

	loadimage(&Big_Skull, "大骷髅兵.jpg", 60, 60);



	loadimage(&Blue_door, "蓝门.jpg", 60, 60);

	loadimage(&Yellow_door, "黄门.jpg", 60, 60);

	loadimage(&Player, "人.jpg", 60, 60);

	loadimage(&Message, "info.jpg");

}



/*

*初始化游戏角色

*/

void initPlayer()

{

	player.Lv = 0;

	player.ATT = 50;

	player.DEF = 50;

	player.Num_Blue_Key = 0;

	player.Num_Yellow_Key = 0;

	player.HP = 500;

	player.MP = 250;

	player.Exp = 0;

	playerx = 11;

	playery = 6;

}



//整数转换为字符

char* intToString(int Number)

{

	int len = 0;

	if (Number == 0) {

		str[0] = '0';

		len++;

	}

	while (Number)

	{

		str[len++] = Number % 10 + '0';

		Number /= 10;

	}

	for (int i = 0; i < len / 2; i++) {

		char t = str[i];

		str[i] = str[len - i - 1];

		str[len - i - 1] = t;

	}

	str[len] = '\0';

	return str;

}



/*

*加载游戏地图

*

*/

void SetMap()

{

	for (int i = 0; i < 13; i++)

	{

		for (int j = 0; j < 13; j++)

		{

			switch (map[i][j])

			{



			case 0:

				putimage(j * 60, i * 60, &Wall);     //墙

				break;

			case 1:

				putimage(j * 60, i * 60, &Ground);    //地板

				break;

			case 2:

				putimage(j * 60, i * 60, &Blue_door);   //蓝门

				break;

			case 3:

				putimage(j * 60, i * 60, &Yellow_door);  //黄门

				break;

			case 4:

				putimage(j * 60, i * 60, &Blue_Cry);     //蓝水晶

				break;

			case 5:

				putimage(j * 60, i * 60, &Red_Cry);     //红水晶

				break;

			case 6:

				putimage(j * 60, i * 60, &Blue_Key);    //蓝钥匙

				break;

			case 7:

				putimage(j * 60, i * 60, &Yellow_Key);   //黄钥匙

				break;

			case 8:

				putimage(j * 60, i * 60, &Red_Med);     //红药水

				break;

			case 9:

				putimage(j * 60, i * 60, &Blue_Med);     //蓝药水

				break;

			case 10:

				putimage(j * 60, i * 60, &Small_Bat);    //小蝙蝠


