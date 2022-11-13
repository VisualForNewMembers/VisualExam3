#include<iostream>
#include<string >
#include<fstream>
#include<string>
#include<math.h>
using namespace std;


//地图
char arr[2][15][15] = { {{(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35)},
						{(35),(32),(43),(33),(68),(32),(32),(42),(33),(42),(43),(32),(32),(79),(35)},
						{(35),(38),(42),(42),(42),(42),(37),(42),(37),(32),(32),(32),(42),(42),(35)},
				  {(35),(32),(32),(32),(32),(32),(32),(32),(42),(32),(42),(42),(42),(43),(35)},
				  {(35),(32),(42),(42),(42),(42),(42),(32),(42),(32),(68),(32),(37),(43),(35)},
				  {(35),(37),(42),(43),(33),(43),(42),(32),(68),(32),(42),(32),(37),(38),(35)},
				  {(35),(32),(42),(38),(43),(42),(42),(37),(42),(32),(42),(42),(42),(33),(35)},
				  {(35),(32),(42),(37),(38),(42),(43),(33),(42),(32),(32),(32),(32),(38),(35)},
				  {(35),(32),(68),(32),(42),(42),(42),(42),(42),(32),(42),(42),(42),(32),(35)},
				  {(35),(32),(42),(32),(32),(37),(32),(32),(42),(32),(42),(43),(42),(32),(35)},
				  {(35),(33),(42),(68),(42),(42),(42),(32),(42),(32),(68),(32),(38),(37),(35)},
				  {(35),(38),(42),(43),(42),(37),(32),(32),(68),(32),(42),(42),(68),(42),(35)},
				  {(35),(38),(38),(38),(32),(32),(42),(68),(42),(32),(37),(126),(43),(43),(35)},
				  {(35),(47),(38),(37),(32),(33),(42),(32),(42),(32),(32),(42),(43),(43),(35)},
				  {(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35)}},
				  {{(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35)},
					  {(35), (43), (43), (32), (32), (32), (32), (32), (32), (32), (32), (32), (32), (32), (35)},
				   { (35),(43),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(35) },
				   { (35),(32),(32),(43),(126),(42),(42),(42),(42),(42),(42),(42),(32),(32),(35) },
				   { (35),(32),(32),(126),(126),(32),(32),(32),(32),(32),(32),(42),(32),(32),(35) },
				  { (35),(32),(32),(42),(32),(42),(42),(36),(42),(42),(32),(42),(32),(32),(35) },
				  { (35),(32),(32),(42),(32),(42),(32),(32),(32),(42),(32),(42),(32),(32),(35) },
				  { (35),(32),(32),(42),(32),(36),(32),(66),(32),(36),(32),(42),(32),(32),(35) },
				  { (35),(32),(32),(42),(32),(42),(32),(32),(32),(42),(32),(42),(32),(32),(35) },
				  { (35),(32),(32),(42),(32),(42),(42),(36),(42),(42),(32),(42),(32),(32),(35) },
	{ (35),(32),(32),(42),(32),(32),(32),(32),(32),(32),(126),(126),(32),(32),(35) },
	{ (35),(32),(32),(42),(42),(42),(42),(42),(42),(42),(126),(43),(32),(32),(35) },
	{ (35),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(43),(35) },
	{ (35),(92),(32),(32),(32),(32),(32),(32),(32),(32),(32),(32),(43),(43),(35) },
	{ (35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35),(35) }} };
int attribute[10]={0};
//人物初始属性按顺序为等级，血量，防御力，攻击力，经验值,怪物没有等级，怪物等级改为杀死后的经验值
int Lv = 1, HP = 100, DEF = 20, ATK = 30, EXP = 0,HP0=100,key=0;
int x = 1, y = 13, l = 0; int o = 0;

int monster1[6][4] = { {20,50,20,10},
						  {30,100,50,40},
						 {40,150,80,700} ,
	                      {50,300,100,90},
	                        {50,500,150,140} };

//障碍物阻挡,返回值为0时无障碍物，返回值为1有障碍物，返回值为2遇到怪
int  move(int q, int w,int *p,int a,int b) {

	if (a!=1,b!=10 && arr[0][1][10] != char(43)) {
		arr[0][1][10] = char(43);
	}



	if (arr[l][q][w] == char(92)) { l = 0; arr[1][a][b] = char(32); arr[0][a][b] = char(79); return 1; }
	else if (arr[l][q][w] == char(47)) { l = 1; arr[0][a][b] = char(32); arr[1][a][b] = char(79); return 1; }

	//L为1代表移动方向有障碍物2代表有怪
	if (arr[l][q][w] == char(43)) { arr[l][q][w] = char(32); HP += 80; if (HP > HP0) { HP = HP0; } return 0; }
	
	 if (arr[l][q][w] == char(68) && key > 0) { arr[l][q][w] = char(32); key--; return 0; }
	 else if (arr[l][q][w] == char(68) && key == 0) { cout << "钥匙不足" << endl; system("pause"); return 1; }
	
	if (arr[l][q][w] == char(35) || arr[l][q][w] == char(42)) {
		cout << "障碍物阻挡" << endl;
		return 1;
	}
	else if (arr[l][q][w] == char(33)) { key++;arr[l][q][w]=char(32); return 0; }
	
		if (arr[l][q][w] == char(37)) { *p = 0; return 2;
		}
		else if (arr[l][q][w] == char(38)) { *p = 1; return 2;
		}
		else if (arr[l][q][w] == char(126)) { *p = 2; return 2; }
		else if (arr[l][q][w] == char(36)) { *p = 3; return 2; }
		else if (arr[l][q][w] == char(66)) { *p = 4; return 2; }
	else { return 0; }
}
//打怪战斗函数
int fight(int x1,int y1,int p1 ) {	
	//英雄对怪物伤害为hurt,怪物对英雄伤害为hurt1
	int hurt,hurt1,b=1;
	for (int z=1; 1;z++) {
		if (ATK <= monster1[p1][2]) {hurt = 20;}
		else {hurt = 20 + ATK - monster1[p1][2];};
		if (monster1[p1][4] <= DEF) { hurt1 = 20; }
		else { hurt1 = 20 + monster1[p1][4] - DEF; };




		//选择继续战斗或逃跑
		int a;
		if (z>1&&b) {
			cout << "扣1继续战斗，扣0逃跑,扣6自动战斗" << endl;
			cin >> a;
			if (a == 0) { return 0; break; }
			if (a == 6) { b = 0; }
		}

		HP = HP - hurt1;
		monster1[p1][1] -= hurt;

		//每回合数据输出
		cout << "第" << z << "回合" << endl;
		cout << "你对怪物造成" << hurt << "点伤害" << endl;
		cout << "怪物对你造成" << hurt1 << "点伤害" << endl;
		cout << "你剩余血量为：" << HP << "\t" << "怪物剩余血量为：" << monster1[p1][1] << endl;
	

		//战斗失败
		if (HP <= 0) {
			cout << "你已死亡" << endl << "怪物剩余血量为：" << monster1[p1][1] << endl;
			system("pause");
			return 0;
			break;	}
		//战斗胜利
		if (monster1[p1][1] <= 0) {
			cout << "恭喜你战斗胜利" << endl << "获得" << monster1[p1][0] << "经验值";
			EXP += monster1[p1][0];
			
			//升级
			if (EXP >= 50) {
				EXP -= 50; Lv += 1; HP += 20; DEF += 5; ATK += 10; HP0 += 20;
				cout << "恭喜升级，等级提升为Lv" << Lv << endl;
			}
			if (monster1[3][1] <= 0)
			{
				
				if (o == 0) {
					cout << "恭喜获得绿毒裁决  攻击+99" << endl;
					monster1[3][1] = 1000; ATK += 99; o=1;
				}
				else if (o == 1) {
					cout << "恭喜获得麻痹戒指  防御+66" << endl;
					monster1[3][1] = 1900;
					monster1[3][3] = 130;
					o++;
				}
				else if (o == 2) {
					cout << "魔王心腹干部被杀，魔王暴怒，攻击+50，血量+2000";
					monster1[3][1] += 500;
					monster1[4][1] += 2000;
					monster1[4][3] += 50;
					o++;
				}
				else if (o == 3) { cout << "魔王干部死光光，魔王怒急攻心，血量-1000，攻击+10";
				monster1[4][1] -= 1000;
				monster1[4][3] += 10;
				o++;
				}

			}
			monster1[0][1] = 50;
			monster1[1][1] = 100;
			monster1[2][1] = 150;
			
			system("pause");
			return 1;
			break;}

		



		
	}
}
//系统设置
   //存档
void keep() {



	//写入文件
	ofstream ofs;
	ofs.open("test.txt", ios::trunc);
	ofs << arr[0][0];
	ofs.close();
	ofstream ofs1;
	ofs1.open("test1.txt", ios::trunc);
	ofs1 << Lv << "," << HP << "," << DEF << "," << ATK << "," << EXP << "," << HP0 << "," << key << "," << x << "," << y << "," << l << ",";
	ofs1.close();


}
//读档
int open() {//打开文件
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;

	}


	//读数据
	


	for (int c = 0; c < 2; c++) {
		for (int a = 0; a < 15; a++) {
			for (int b = 0; b < 15; b++) {
				arr[c][a][b] = ifs.get();
			}
		}
	}
	ifs.close();
	ifstream ifs1;
	ifs1.open("test1.txt", ios::in);
	if (!ifs1.is_open()) {
		cout << "文件打开失败" << endl;

	}
	int a = 0, r = 0, s = 0, d;
	int a1=0, a2=0, a3, a4;
	char lv;
	int shu[1024];
	int shu1[10];
	
	while ((lv = ifs1.get()) != EOF) {
		shu[a] = int(lv); a++;
	}
	for (a = 0; a < 1024; a++)
	{
		if (shu[a] == 44) { shu1[r] = a; r++; }
	}

	for (int f = 0; f < shu1[0]; f++) {
		attribute[0] += (shu[f]-48) * pow(10, shu1[0] - f - 1);
	}
	for (int f = 0; f < shu1[1] - shu1[0] - 1; f++) {
		attribute[1] += (shu[shu1[0] +f+ 1]-48) * pow(10, shu1[1] - shu1[0] - f - 2);
		
	}
	for (int f = 0; f < shu1[2] - shu1[1] - 1; f++) {
		attribute[2] += (shu[shu1[1]+f + 1]-48) * pow(10, shu1[2] - shu1[1] - f - 2);
	}
	for (int f = 0; f < shu1[3] - shu1[2] - 1; f++) {
		attribute[3] += (shu[shu1[2] + f + 1]-48) * pow(10, shu1[3] - shu1[2] - f - 2);
	}for (int f = 0; f < shu1[4] - shu1[3] - 1; f++) {
		attribute[4] += (shu[shu1[3] + f + 1]-48) * pow(10, shu1[4] - shu1[3] - f - 2);
	}
	for (int f = 0; f < shu1[5] - shu1[4] - 1; f++) {
		attribute[5] += (shu[shu1[4] + f + 1]-48) * pow(10, shu1[5] - shu1[4] - f - 2);
	}
	for (int f = 0; f < shu1[6] - shu1[5] - 1; f++) {
		attribute[6] += (shu[shu1[5] + f + 1]-48) * pow(10, shu1[6] - shu1[5] - f - 2);
	}
	for (int f = 0; f < shu1[7] - shu1[6] - 1; f++) {
		attribute[7] += (shu[shu1[6] + f + 1]-48) * pow(10, shu1[7] - shu1[6] - f - 2);
	}
	for (int f = 0; f < shu1[8] - shu1[7] - 1; f++) {
		attribute[8] += (shu[shu1[7] + f + 1]-48) * pow(10, shu1[8] - shu1[7] - f - 2);
	}
	for (int f = 0; f < shu1[9] - shu1[8] - 1; f++) {
		attribute[9] += (shu[shu1[8] + f + 1]-48) * pow(10, shu1[9] - shu1[8] - f - 2);

	}
	Lv = attribute[0];
	HP= attribute[1];
	DEF = attribute[2];
	ATK = attribute[3];
	EXP= attribute[4];
	HP0 = attribute[5];
	key = attribute[6];
	x = attribute[7];
	y = attribute[8];
	l= attribute[9];
	ifs1.close();
	return 1;
}
int system1() {
	system("cls");
	cout << "移动方式上下左右:" << 8546 << endl;
	cout<<" \"O\"勇者"<<endl;
	cout << " \"B\"魔王" << endl;
	cout << " \"*\"墙壁" << endl;
	cout << " \"D\"上锁的门" << endl;
	cout << " \"+\"血瓶（存在一个无限血瓶）" << endl;
	cout << " \"！\"钥匙" << endl;
	cout << " \"\\,/\"上下楼梯" << endl;
	cout << " \"%<&<~<$\"怪物（按强度排序）" << endl;
	cout << " 输入334455修改角色属性" << endl;
	cout << "输入33进行存档，输入44读取存档" << endl;
	cout << "输入0退出设置"<<endl;
	int f;
	cin >> f;
	if (f == 33) { keep(); }
	else if (f == 44) { open(); }



	if (f == 0) { return 0; }
	else if (f == 334455) {
		system("cls");
		cout << "选择人物属性：" << endl;
		cout << "1.血量" << endl << "2.防御" << endl << "3.攻击" << endl << "4.钥匙数" << endl;
		int z,w;
		cin >> z;
		cout << "请输入修改数值" << endl;
		cin >> w;

		switch (z) {
		case 1:HP = HP0 = w; break;
		case 2:DEF = w; break;
		case 3:ATK = w; break;
		case 4:key = w; break;
		}
	}
	return 0;
}
void aas(){
	cout << "移动方式上下左右:" << 8546 << endl;
	cout << " \"O\"勇者" << endl;
	cout << " \"B\"魔王" << endl;
	cout << " \"*\"墙壁" << endl;
	cout << " \"D\"上锁的门" << endl;
	cout << " \"+\"血瓶（存在一个无限血瓶）" << endl;
	cout << " \"！\"钥匙" << endl;
	cout << " \"\\,/\"上下楼梯" << endl;
	cout << " \"%<&<~<$\"怪物（按强度排序）" << endl;
	cout << "输入123呼出系统设置" << endl;
}
//打印地图人物属性
int xx() {

	cout << "等级:" << Lv << endl;
	cout << "血量:" << HP << "/" << HP0 << endl;
	cout << "防御力:" << DEF << endl;
	cout << "攻击力:" << ATK << endl;
	cout << "经验值:" << EXP << "/50" << endl;
	cout << "钥匙：" << key << endl;
	cout << "角色位置：（" << y << "," << x << ")" << endl;
	for (int a = 0; a < 15; a++) {
		for (int b = 0; b < 15; b++) {
			cout << arr[l][a][b];
		}cout << endl;
	}



	return 0;
};

int main() {//游戏简介
	aas();
	cout << "开始游戏";
	system("pause");
	system("cls");
	//地图人物属性打印
	xx();
	//控制角色移动,怪物类型p
	int temp1;
	int p = 0;
	for (int a; 1;) {
		//L为1代表移动方向有障碍物
		int L = 0;
		L = 0;
		//8546控制上下左右移动,先判断移动方向是否有障碍物，没有就进行移动
		cin >> a;
		switch (a)
		{
		case 4:L = move(x, y - 1, &p, x, y); break;
		case 5:L = move(x + 1, y, &p, x, y); break;
		case 6:L = move(x, y + 1, &p, x, y); break;
		case 8:L = move(x - 1, y, &p, x, y); break;
		case 123:system1(); break;
		case 110:keep(); break;
		case 119:open(); break;
		default:cout << "请用8546控制角色移动" << endl;
		}
		//L=0正常移动
		if (L == 0) {
			switch (a)
			{
			case 4: temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x][y - 1], arr[l][x][y - 1] = temp1, y -= 1; break;
			case 5:temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x + 1][y], arr[l][x + 1][y] = temp1, x += 1; break;
			case 6:  temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x][y + 1], arr[l][x][y + 1] = temp1, y += 1; break;
			case 8:  temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x - 1][y], arr[l][x - 1][y] = temp1, x -= 1; break;
				
			}
			}
			//L=2遇到怪
		else if (L == 2) {
			if (fight(x, y, p)) {
				switch (a)
				{
				case 4: temp1 = arr[l][x][y],  arr[l][x][y]=arr[l][x][y - 1], arr[l][x][y - 1] = temp1, arr[l][x][y]=char(32),y -= 1; break;
				case 5: temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x + 1][y], arr[l][x + 1][y] = temp1, arr[l][x][y] = char(32), x += 1; break;
				case 6:  temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x][y + 1], arr[l][x][y + 1] = temp1, arr[l][x][y] = char(32), y += 1; break;
				case 8:  temp1 = arr[l][x][y], arr[l][x][y] = arr[l][x - 1][y], arr[l][x - 1][y] = temp1, arr[l][x][y] = char(32), x -= 1; break;
				};
			}
			if(HP<=0) { cout << "游戏结束" << endl; system("pause"); return 0; }
		}
			//清除
		system("cls");
			//地图人物属性打印
			xx();
			if (monster1[4][1] <= 0) {
				system("cls");
				cout << "你成功的打败了魔王" << endl << "   游戏结束" << endl << "制作人：龙翔" << endl << "联系电话：15915963991";
				return 0;
			}

	}




	system("pause");
	return 0;
}

