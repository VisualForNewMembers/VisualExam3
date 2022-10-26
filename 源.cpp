#include"value.h"
void monsterinit(monsterset, monsterset, monsterset, monsterset);//初始化怪物属性
void killboss();//击杀boss
void monsterinit(monsterset monster1, monsterset monster2, monsterset monster3, monsterset boss)
{
	monster1->hp = 50;
	monster1->attack = 25;
	monster1->getexp = 20;
	monster1->defensive = 10;
	monster1->trueattack = 10;

	monster2->hp = 100;
	monster2->attack = 40;
	monster2->getexp = 40;
	monster2->defensive = 20;
	monster2->trueattack = 20;

	monster3->attack = 40;
	monster3->getexp = 80;
	monster3->defensive = 40;
	monster3->hp = 180;
	monster3->trueattack = 40;

	boss->attack = 100;
	boss->trueattack = 60;
	boss->hp = 500;
	boss->defensive = 60;
	boss->getexp = 300;
}

void initplayer(playerset player)
{
	player->attack = 30;
	player->defensive = 20;
	player->level = 1;
	player->hp = 100;
	player->hplimit = 100;
	player->x = 0;
	player->y = 0;
	player->trueattack = 20;
	player->key = 0;
	player->exp = 0;
}

void levelup(playerset player) {
	if (player->exp >= 50) 
	{
		player->exp = player->exp - 50;
		player->level += 1;
		player->hplimit += 20;
		player->defensive += 5;
		player->attack += 10;
		
		cout << "-------------升级------------------" << endl;
	}
}

void printplayer(string playername,playerset player)
{
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "玩家：" << playername<< endl;
	cout << "血量:"<<player->hp<<endl;
	cout << "攻击力:" << player->attack << endl;
	cout << "防御力:" << player->defensive << endl;
	cout << "等级:" << player->level << endl;
	cout << "经验:" << player->exp << endl;
	cout << "位置x:" << player->x << endl;
	cout << "位置y:" << player->y << endl;
	cout << "持有钥匙:" << player->key << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "输入2,4,6,8来进行下，左，右，上的移动:" << endl;
}

void moves(playerset player,mapset map) {

	int move, flag;
	cin >> move;
	switch (move)
	{
		//向下走
	case 2:
		if (map->arr[map->row + 1][map->column] == ' ') {
			player->y -= 1;
			player->x = player->x;
			map->arr[map->row + 1][map->column] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row += 1;
			map->column = map->column;
		}
		else if (map->arr[map->row + 1][map->column] == '#')
			cout << "无法越过边界" << endl;
		else if (map->arr[map->row + 1][map->column] == '*')
			cout << "无法越过障碍物" << endl;
		else if (map->arr[map->row + 1][map->column] == '%') {
			flag = vsmonster1(player);
			if (flag) {
				player->y -= 1;
				player->x = player->x;
				map->arr[map->row + 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row += 1;
				map->column = map->column;

			}
		}
		else if (map->arr[map->row + 1][map->column] == '&') {
			flag = vsmonster2(player);
			if (flag) {
				player->y -= 1;
				player->x = player->x;
				map->arr[map->row + 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row += 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row + 1][map->column] == '~') {
			flag = vsmonster3(player);
			if (flag) {
				player->y -= 1;
				player->x = player->x;
				map->arr[map->row + 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row += 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row + 1][map->column] == 'B') {
			flag = vsboss(player);
			if (flag) {
				player->y -= 1;
				player->x = player->x;
				map->arr[map->row + 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row += 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row + 1][map->column] == '!') {
			getkey(player);
			player->y -= 1;
			player->x = player->x;
			map->arr[map->row + 1][map->column] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row += 1;
			map->column = map->column;
		}
		else if (map->arr[map->row + 1][map->column] == '+') {
			heal(player);
			player->y -= 1;
			player->x = player->x;
			map->arr[map->row + 1][map->column] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row += 1;
			map->column = map->column;
		}
		break;

		//向左走
	case 4:
		if (map->arr[map->row][map->column - 1] == ' ') {
			player->x -= 1;
			player->y = player->y;
			map->arr[map->row][map->column - 1] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row = map->row;
			map->column -= 1;
		}
		else if (map->arr[map->row][map->column - 1] == '#')
			cout << "无法越过边界" << endl;
		else if (map->arr[map->row][map->column - 1] == '*')
			cout << "无法越过障碍物" << endl;
		else if (map->arr[map->row][map->column - 1] == '%') {
			flag = vsmonster1(player);
			if (flag) {
				player->x -= 1;
				player->y = player->y;
				map->arr[map->row][map->column - 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column -= 1;
			}
		}
		else if (map->arr[map->row][map->column - 1] == '&') {
			flag = vsmonster2(player);
			if (flag) {
				player->x -= 1;
				player->y = player->y;
				map->arr[map->row][map->column - 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column -= 1;
			}
		}
		else if (map->arr[map->row][map->column - 1] == '~') {
			flag = vsmonster3(player);
			if (flag) {
				player->x -= 1;
				player->y = player->y;
				map->arr[map->row][map->column - 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column -= 1;
			}
			else if (map->arr[map->row][map->column - 1] = 'B') {
				flag = vsboss(player);
				if (flag) {
					player->x -= 1;
					player->y = player->y;
					map->arr[map->row][map->column - 1] = 'o';
					map->arr[map->row][map->column] = ' ';
					map->row = map->row;
					map->column -= 1;
				}
			}
			else if (map->arr[map->row][map->column - 1] == '!') {
				getkey(player);
				player->x -= 1;
				player->y = player->y;
				map->arr[map->row][map->column - 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column -= 1;
			}
			else if (map->arr[map->row][map->column - 1] == '+') {
				heal(player);
				player->x -= 1;
				player->y = player->y;
				map->arr[map->row][map->column - 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column -= 1;
			}
			break;

	case 6:
		//向右走
		if (map->arr[map->row][map->column + 1] == ' ') {
			player->x += 1;
			player->y = player->y;
			map->arr[map->row][map->column + 1] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row = map->row;
			map->column += 1;
		}
		else if (map->arr[map->row][map->column + 1] == '#')
			cout << "无法越过边界" << endl;
		else if (map->arr[map->row][map->column + 1] == '*')
			cout << "无法越过障碍物" << endl;
		else if (map->arr[map->row][map->column + 1] == '%') {
			flag = vsmonster1(player);
			if (flag) {
				player->x += 1;
				player->y = player->y;
				map->arr[map->row][map->column + 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column += 1;
			}
		}
		else if (map->arr[map->row][map->column + 1] == '&') {
			flag = vsmonster2(player);
			if (flag) {
				player->x += 1;
				player->y = player->y;
				map->arr[map->row][map->column + 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column += 1;
			}
		}
		else if (map->arr[map->row][map->column + 1] == '~') {
			flag = vsmonster3(player);
			if (flag) {
				player->x += 1;
				player->y = player->y;
				map->arr[map->row][map->column + 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column += 1;
			}
		}
		else if (map->arr[map->row][map->column + 1] == 'B') {
			flag = vsboss(player);
			if (flag) {
				player->x += 1;
				player->y = player->y;
				map->arr[map->row][map->column + 1] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row = map->row;
				map->column += 1;
			}
		}
		else if (map->arr[map->row][map->column + 1] == '!') {
			getkey(player);
			player->x += 1;
			player->y = player->y;
			map->arr[map->row][map->column + 1] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row = map->row;
			map->column += 1;
		}
		else if (map->arr[map->row][map->column + 1] == '+') {
			heal(player);
			player->x += 1;
			player->y = player->y;
			map->arr[map->row][map->column + 1] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row = map->row;
			map->column += 1;
		}
		break;
	case 8:
		//向上走
		if (map->arr[map->row - 1][map->column] == ' ') {
			player->y += 1;
			player->x = player->x;
			map->arr[map->row - 1][map->column] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row -= 1;
			map->column = map->column;
		}
		else if (map->arr[map->row - 1][map->column] == '#')
			cout << "无法越过边界" << endl;
		else if (map->arr[map->row - 1][map->column] == '*')
			cout << "无法越过障碍物" << endl;
		else if (map->arr[map->row - 1][map->column] == '%') {
			flag = vsmonster1(player);
			if (flag) {
				player->y += 1;
				player->x = player->x;
				map->arr[map->row - 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row -= 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row - 1][map->column] == '&') {
			flag = vsmonster2(player);
			if (flag) {
				player->y += 1;
				player->x = player->x;
				map->arr[map->row - 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row -= 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row - 1][map->column] == '~') {
			flag = vsmonster3(player);
			if (flag) {
				player->y += 1;
				player->x = player->x;
				map->arr[map->row - 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row -= 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row - 1][map->column] == 'B') {
			flag = vsboss(player);
			if (flag) {
				player->y += 1;
				player->x = player->x;
				map->arr[map->row - 1][map->column] = 'o';
				map->arr[map->row][map->column] = ' ';
				map->row -= 1;
				map->column = map->column;
			}
		}
		else if (map->arr[map->row - 1][map->column] == '!') {
			getkey(player);
			player->y += 1;
			player->x = player->x;
			map->arr[map->row - 1][map->column] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row -= 1;
			map->column = map->column;
		}
		else if (map->arr[map->row - 1][map->column] == '+') {
			heal(player);
			player->y += 1;
			player->x = player->x;
			map->arr[map->row - 1][map->column] = 'o';
			map->arr[map->row][map->column] = ' ';
			map->row -= 1;
			map->column = map->column;
		}
		break;
	case 0:exit(1);
		break;
	default:flag = 0;
		}
	}
}
void lose(playerset player)
{
	if (player->hp <= 0) {
		cout << "游戏失败" << endl;
		cout << "按下回车退出" << endl;
		getchar();
		exit(1);
	}
}

void heal(playerset player) 
{
	player->hp = player->hp + 80;
	if (player->hp > player->hplimit)
		player->hp = player->hplimit;
}

bool vsmonster1(playerset player)
{
	cout << "是否与蜘蛛对战(y/n)" << endl;
	char select;
	cin >> select;
	switch(select){
	case 'y':
		monsterinit(monster1, monster2, monster3,boss);
		while (monster1->hp > 0) {
			int pattack = 0;
			int mattack = 0;
			pattack= attrule(player, monster1);
			mattack = attrule1(player, monster1);
			cout << "你造成了伤害:" << pattack << endl;
			monster1->hp = monster1->hp - pattack;
			cout << "你受到了伤害:" << mattack << endl;
			player->hp = player->hp - mattack;
			lose(player);
		};
		cout << "成功击杀蜘蛛" << endl;
		cout << "获得经验:" << monster1->getexp << endl;
		player->exp = player->exp + monster1->getexp;
		levelup(player);
		return true;
		break;
	case 'n':
		return false;
		break;
	}
}

bool vsmonster2(playerset player)
{
	cout << "是否与骷髅对战(y/n)" << endl;
	char select;
	cin >> select;
	switch (select) {
	case 'y':
		monsterinit(monster1, monster2, monster3,boss);
		while (monster2->hp > 0) {
			int pattack = 0;
			int mattack = 0;
			pattack = attrule(player, monster2);
			mattack = attrule1(player, monster2);
			cout << "你造成了伤害:" << pattack << endl;
			monster2->hp = monster2->hp - pattack;
			cout << "你受到了伤害:" << mattack << endl;
			player->hp = player->hp - mattack;
			lose(player);
		};
		cout << "成功击杀蜘蛛" << endl;
		cout << "获得经验:" << monster2->getexp << endl;
		player->exp = player->exp + monster2->getexp;
		levelup(player);
		return true;
		break;
	case 'n':
		return false;
		break;
	}
}

bool vsmonster3(playerset player)
{
	cout << "是否与蝙蝠对战(y/n)" << endl;
	char select;
	cin >> select;
	switch (select) {
	case 'y':
		monsterinit(monster1, monster2, monster3, boss);
		while (monster3->hp > 0) {
			int pattack = 0;
			int mattack = 0;
			pattack = attrule(player, monster3);
			mattack = attrule1(player, monster3);
			cout << "你造成了伤害:" << pattack << endl;
			monster3->hp = monster3->hp - pattack;
			cout << "你受到了伤害:" << mattack << endl;
			player->hp = player->hp - mattack;
			lose(player);
		};
		cout << "成功击杀蜘蛛" << endl;
		cout << "获得经验" << monster3->getexp << endl;
		player->exp = player->exp + monster3->getexp;
		levelup(player);
		return true;
		break;
	case 'n':
		return false;
		break;
	}
}

bool vsboss(playerset player)
{
	cout << "是否与魔王对战(y/n)" << endl;
	char select;
	cin >> select;
	switch (select) {
	case 'y':
		monsterinit(monster1, monster2, monster3, boss);
		while (boss->hp > 0) {
			int pattack = 0;
			int mattack = 0;
			pattack = attrule(player, boss);
			mattack = attrule1(player, boss);
			cout << "你造成了伤害:" << pattack << endl;
			boss->hp = boss->hp - pattack;
			cout << "你受到了伤害:" << mattack << endl;
			player->hp = player->hp - mattack;
			lose(player);
		};
		cout << "成功击杀蜘蛛" << endl;
		cout << "获得经验" << boss->getexp << endl;
		player->exp = player->exp + boss->getexp;
		levelup(player);
		killboss();
		return true;
		break;
	case 'n':
		return false;
		break;
	}
}

void printmap(mapset map) {
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			cout << map->arr[i][j];
		}
		cout << endl;
	}
}

void getkey(playerset player) {
	cout << "获得一条钥匙" << endl;
	player->key += 1;
}

void killboss() {
	cout << "你已成功击杀boss" << endl;
	cout << "游戏胜利" << endl;
	cout << "按下回车退出游戏" << endl;
	getchar();
	exit(1);
}
int main() {
	cout << "----------欢迎来到魔塔-----------" << endl;
	playerset player;
	player = new PLAYER;
	cout << "请输入你的用户名" << endl;
    string playername;//用户名
	cin >> playername;
	initplayer(player);//初始化角色属性
	monster1 = new MONSTER;
	monster2 = new MONSTER;
	monster3 = new MONSTER;
	boss = new MONSTER;
	mapset map;
	map = new MAP;//初始化地图
	//实际初始位置
	map->row = 10; map->column = 6;
	while (1) {
		system("cls");
		printplayer(playername, player);//角色计分板
		printmap(map);//打印地图
		moves(player,map);//角色移动
		cout << "按下回车键继续" << endl;
		getchar();
		getchar();
	}
	return 0;
}