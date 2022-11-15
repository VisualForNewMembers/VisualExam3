#include<iostream>
#include<stdlib.h>
#include<conio.h> 
#include<windows.h>
#include<fstream>
using namespace std;

#define ESC 27           
		               
int gameover=0; //判断游戏进程 
 
struct hunter{
	int hp=100;        //定义勇者的初始血量(health point) 
	int max=100;       //定义勇者的初始最大血量  
	int lv=1;          //定义勇者的初始等级(level)
	int atk=30,def=20; //定义勇者的初始攻击力(attack),防御力(defence)
	int exp=0;         //定义勇者的初始经验值(experience)
	int key=0;         //定义勇者的初始钥匙数量 
	int i,j;           //勇者的位置 
}fighter;

struct ganster{
	int h,a,d;
};//怪物的数据 

ganster monster[3]={{30,25,10},{60,30,20},{90,35,30}};

ganster boss={150,100,50};

int cas=0; //地图层 
                                      
int map[2][25][50]=
{//         5         10        15        20        25        30        35        40        45        50      
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          //1
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,6,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //2
	0,1,1,6,1,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,2,2,0,0,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0,          //3
	0,1,1,2,1,1,1,1,1,6,1,2,2,2,2,2,1,1,1,2,1,0,0,0,2,2,0,0,0,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,0,          //4
	0,1,1,2,1,2,8,2,1,1,1,1,1,1,1,2,1,6,9,2,1,0,0,0,2,2,0,0,0,1,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,0,          //5
	0,1,1,2,1,2,2,2,2,2,2,2,1,6,1,2,1,1,1,2,1,1,0,0,2,2,0,0,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,0,          //6
	0,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,1,1,6,2,1,1,1,1,13,2,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,0,         //7
	0,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,1,1,1,1,0,          //8
	0,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,6,1,2,2,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,0,          //9
	0,1,1,2,1,2,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,2,1,1,1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1,1,1,0,          //10
	0,1,1,2,1,2,1,2,2,2,2,2,2,6,1,2,1,1,2,1,1,1,1,1,2,2,1,1,1,2,1,1,2,1,1,2,1,1,1,2,1,1,2,1,1,2,1,1,1,0,          //11
	0,1,1,2,1,2,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,0,          //12     
	0,1,1,2,1,2,1,2,2,2,2,2,2,2,2,2,1,1,2,1,1,1,1,1,2,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,          //13
	0,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,2,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,          //14
	0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,8,9,2,9,9,9,9,9,2,2,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,0,          //15
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,6,2,1,1,1,1,1,2,6,2,1,1,1,1,1,1,0,          //16
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,9,9,1,1,1,2,1,2,1,2,1,1,1,2,1,2,1,2,1,1,1,1,1,0,          //17
	0,1,1,8,1,2,22,2,1,2,2,2,1,2,22,2,1,1,1,1,1,1,1,1,2,2,1,9,1,1,2,1,1,2,1,1,2,1,2,1,1,2,1,1,2,1,1,1,1,0,        //18
	0,1,1,8,1,2,1,2,1,2,1,2,1,2,1,2,1,1,1,1,1,1,1,1,2,2,1,9,1,2,1,1,1,12,1,1,1,2,1,1,1,11,1,1,1,2,1,1,1,0,        //19
	0,1,1,8,1,2,1,2,22,2,1,2,2,2,1,2,1,1,1,1,1,1,1,1,2,2,1,9,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,         //20
	0,1,1,8,1,2,2,2,1,2,22,2,1,2,2,2,1,1,3,1,1,1,1,1,2,2,1,9,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,0,         //21
	0,1,1,8,1,2,1,2,1,2,1,2,1,2,1,2,1,1,2,1,1,1,1,1,2,2,1,9,1,1,1,7,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //22
	0,1,1,2,2,2,1,2,2,2,1,2,22,2,1,2,9,8,2,2,2,10,2,2,2,2,1,9,9,6,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,0,        //23
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,4,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,          //24
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          //25
 //         5         10        15        20        25        30        35        40        45        50  	
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          //1
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,          //2
	0,1,1,7,1,7,2,1,1,2,9,2,2,1,8,1,1,3,2,2,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,3,3,1,1,1,1,0,          //3
	0,1,1,2,1,1,9,1,1,7,1,2,2,11,2,1,1,1,2,8,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,3,3,3,3,1,3,3,3,3,1,1,1,0,         //4
	0,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,7,2,2,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,1,1,0,          //5
	0,1,1,1,1,12,1,1,1,2,10,2,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,1,1,1,0,        //6
	0,1,1,1,1,8,1,1,1,8,1,2,9,2,2,1,1,1,7,2,2,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,3,3,3,3,1,1,1,1,0,          //7
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,3,3,1,1,1,1,1,0,          //8
	0,1,1,1,1,1,1,1,1,8,8,8,1,1,1,1,1,1,1,1,2,2,7,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,0,          //9
	0,1,1,1,1,1,1,1,1,8,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,3,1,1,1,1,1,1,1,0,          //10
	0,1,1,1,1,1,1,1,1,8,8,8,2,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,2,1,1,1,1,1,1,1,0,          //11
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,          //12     
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,          //13
	0,1,2,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //14
	0,1,2,2,1,2,1,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //15
	0,1,1,2,1,2,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,2,2,1,2,1,1,1,1,1,1,1,1,7,1,1,1,2,1,1,1,7,1,1,1,1,1,1,1,0,          //16
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,2,1,1,2,2,2,1,1,2,1,1,1,1,1,1,1,0,          //17
	0,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,2,2,2,1,1,2,1,1,1,2,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,          //18
	0,1,2,1,1,1,8,2,2,2,2,2,1,1,1,1,2,2,2,2,1,2,2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,0,          //19
	0,1,2,1,1,1,1,1,1,1,1,2,3,1,1,1,1,1,2,2,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //20
	0,1,2,9,2,2,2,2,2,2,2,2,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //21
	0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,0,          //22
	0,1,1,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,1,2,2,2,1,1,2,2,2,2,7,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,0,          //23
	0,1,1,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,          //24
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          //25
 //         5         10        15        20        25        30        35        40        45        50  
}; 
//上面是地图的设置 "0"是地图边界，1"是墙，"2"是路，"3"是回血点，"4"是勇者(后面也会用"5"来表达勇者)，
//"6"是上楼梯，"7"是下楼梯，"8"是钥匙，"9"是锁上的门。"10","11","12"是怪物，"13"是最终boss， 


void gotoxy(unsigned char x,unsigned char y)
{    
    COORD cor;  
    HANDLE hout;   
    cor.X = x;
    cor.Y = y;
    hout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hout, cor);   
}


void foreword()
{
    cout<<"你是一名勇者\n任务：探索地图中各板块（移动迷宫，怪物基地，藏宝库，迷雾森林，魔王殿），消除小怪，打败魔王！"<<endl;
    cout<<"\033[47;36;5m!\033[0m\033[47;36;5m!\033[0m\033[47;36;5m!\033[0m：钥匙  \033[47;36mD\033[0m\033[47;36mD\033[0m\033[47;36mD\033[0m：门  ";
    cout<<"\033[47;34m/\033[0m\033[47;34m/\033[0m\033[47;34m/\033[0m：上楼梯  \033[47;34m\\\033[0m\033[47;34m\\\033[0m\033[47;34m\\\033[0m：下楼梯  ";
	cout<<"\033[47;32m%\033[0m\033[47;32m%\033[0m\033[47;32m%\033[0m：史莱姆  \033[47;33m&\033[0m\033[47;33m&\033[0m\033[47;33m&\033[0m：岩浆兽  ";
	cout<<"\033[47;31m~\033[0m\033[47;31m~\033[0m\033[47;31m~\033[0m：恶灵骑士  \033[47;35mB\033[0m\033[47;35mB\033[0m\033[47;35mB\033[0m：魔王"<<endl; 
    cout<<"“f”:确认键，“g”：取消键，“ESC”是退出键（退出时存档）\n\n"; 
}  


int load() //读档 
{
	int way;
	int load;
	cout<<"继续游戏请按“1”\n  新游戏请按“2”\n";
	cin>>way;	
	if(way==2)
	{
	    return 0; 
	}
	else if(way==1) 
	{
	    for(int w=0;w<5;w++)
	    {
	    	cout<<"存档"<<w+1<<endl;
		}
		cout<<"选择序号读档：";
		cin>>load;
	    ifstream mem;
	    switch(load)
	    {
	    	case 1:
	    	mem.open("存档1.txt", ios::in);break;
	        case 2:
			mem.open("存档2.txt", ios::in);break;
			case 3:
			mem.open("存档3.txt", ios::in);break;
			case 4:
			mem.open("存档4.txt", ios::in);break;	
			case 5:
			mem.open("存档5.txt", ios::in);break;
		}	
		if (!mem.is_open())
	    {
	        cout<<"file open failed"<<endl; 
	        exit(1);
	    } 
	    for(int i=0;i<2;i++)
	    {
	    	for(int j=0;j<25;j++)
	    	{
	    		for(int k=0;k<50;k++)
	    		{
	    			mem>>map[i][j][k];
				}
			}
		}
		mem>>fighter.hp;		
		mem>>fighter.max;
		mem>>fighter.lv;
		mem>>fighter.atk;
		mem>>fighter.def;
		mem>>fighter.exp;
		mem>>fighter.key;
		mem>>fighter.i;
		mem>>fighter.j;
		mem>>gameover;
		mem>>cas;
	    mem.close();
	    return 0;
	}
}


void save() //存档 
{ 
    int save;
    for(int w=0;w<5;w++)
    {
    	cout<<"存档"<<w+1<<endl;
	}
	cout<<"选择序号存档：";
	cin>>save;
    ofstream mem;
    switch(save)
    {
    	case 1:
        mem.open("存档1.txt",ios::out);break;
        case 2:
		mem.open("存档2.txt",ios::out);break;
		case 3:
		mem.open("存档3.txt",ios::out);break;
		case 4:
		mem.open("存档4.txt",ios::out);break;	
		case 5:
	    mem.open("存档5.txt",ios::out);break;
	}
    if (!mem.is_open())
    {
        cout<<"file open failed"<<endl; 
        exit(1);
    }
    for(int i=0;i<2;i++)
    {
		for(int j=0;j<25;j++)
		{
			for(int k=0;k<50;k++)
			{
				mem << map[i][j][k] << endl;
			}
		}	
    }
	mem << fighter.hp << endl;
	
	mem << fighter.max << endl;
	mem << fighter.lv << endl;
	mem << fighter.atk << endl;
	mem << fighter.def << endl;
	mem << fighter.exp << endl;
	mem << fighter.key << endl;
	mem << fighter.i << endl;
    mem << fighter.j << endl;
	mem << gameover << endl;
	mem << cas << endl;
	mem.close();
}


void drawstate()//画勇者状态的函数
{
	cout<<"    血量:"<<fighter.hp<<"     "<<endl;
	cout<<"    等级:"<<fighter.lv<<"     "<<endl;
	cout<<"  攻击力:"<<fighter.atk<<"     "<<endl;
	cout<<"  防御力:"<<fighter.def<<"     "<<endl;
	cout<<"  经验值:"<<fighter.exp<<"     "<<endl;
	cout<<"钥匙数量:"<<fighter.key<<"     "<<endl; 
	cout<<"  位置 x:"<<fighter.j+1<<"     "<<endl;
    cout<<"       y:"<<25-fighter.i<<"     "<<endl;   
}


void initmap() //初始化地图 
{
	gotoxy(0,11);
    if(cas==0)
    {
    	for(int w=0;w<25;w++)
    	{
        	for(int c=0;c<50;c++)
    	    {
    	    	switch(map[cas][w][c])
    	    	{
    		        case 0:
		            cout<<"\033[100;34m#\033[0m";break;     //地图边界用"#"表示 
    	        	case 1:
    	            case 22: 
		        	cout<<"\033[;100m \033[0m";break;       //墙用"*"表示 
    	            case 2:
		        	cout<<"\033[47;37m \033[0m";break;      //路用" "表示 
	    	    	case 3:
	        		cout<<"\033[47;31m+\033[0m";break;      //回血点"+"表示 
	        		case 4:
		        	case 5:
		        	cout<<"\033[47;31mo\033[0m";break;      //勇者用"o"表示 
		        	case 6:
		        	cout<<"\033[47;34m/\033[0m";break;      //上楼梯用"/"表示 
		        	case 7:      
		        	cout<<"\033[47;34m\\\033[0m";break;     //下楼梯用"\"表示 
		        	case 8: 
		        	cout<<"\033[47;36;5m!\033[0m";break;    //钥匙用"!"表示
					case 9: 
		        	cout<<"\033[47;36mD\033[0m";break;      //门用"D"表示 
		         	case 10:
		        	cout<<"\033[47;32m%\033[0m";break;     //怪用"%"表示 
		        	case 11:
		        	cout<<"\033[47;33m&\033[0m";break;      //怪用"&"表示 
		        	case 12:
		        	cout<<"\033[47;31m~\033[0m";break;      //怪用"~"表示
                    case 13:
		        	cout<<"\033[47;35mB\033[0m";break;      //魔王用"B"表示 
		        }
		    }
		    cout<<endl; 
        }
    }
    else if(cas==1)
	{
		for(int w=0;w<13;w++)
		{
			for(int c=0;c<50;c++)
			{
    	        switch(map[cas][w][c])
         	    {
    		        case 0:
		            cout<<"\033[100;34m#\033[0m";break;     //地图边界用"#"表示 
    	        	case 1:
		        	cout<<"\033[;100m \033[0m";break;       //墙用"*"表示 
    	            case 2:
		        	cout<<"\033[47;37m \033[0m";break;      //路用" "表示 
	    	    	case 3:
	        		cout<<"\033[47;31m+\033[0m";break;      //回血点"+"表示 
	        		case 4:
		        	case 5: 
		        	cout<<"\033[47;31mo\033[0m";break;      //勇者用"o"表示 
		        	case 6:
		        	cout<<"\033[47;34m/\033[0m";break;      //上楼梯用"/"表示 
		        	case 7:      
		        	cout<<"\033[47;34m\\\033[0m";break;     //下楼梯用"\"表示 
		        	case 8: 
		        	cout<<"\033[47;36;5m!\033[0m";break;    //钥匙用"!"表示
					case 9: 
		        	cout<<"\033[47;36mD\033[0m";break;      //门用"D"表示 
		         	case 10:
		        	cout<<"\033[47;32m%\033[0m";break;     //怪用"%"表示 
		        	case 11:
		        	cout<<"\033[47;33m&\033[0m";break;      //怪用"&"表示 
		        	case 12:
		        	cout<<"\033[47;31m~\033[0m";break;      //怪用"~"表示
                    case 13:
		        	cout<<"\033[47;35mB\033[0m";break;      //魔王用"B"表示 
	            }
		    }
		    cout<<endl;
	    }
		for(int w=13;w<24;w++)
		{
	    	cout<<"\033[100;34m#\033[0m"; 
	    	cout<<"\033[0;100m \033[0m";
			for(int c=2;c<48;c++)
			{
				if(map[cas][w+1][c+2]==4||map[cas][w][c+2]==4||map[cas][w-1][c+2]==4||
				map[cas][w+1][c+1]==4||map[cas][w][c+1]==4||map[cas][w-1][c+1]==4||
				map[cas][w+1][c]==4||map[cas][w][c]==4||map[cas][w-1][c]==4||
				map[cas][w+1][c-1]==4||map[cas][w][c-1]==4||map[cas][w-1][c-1]==4||
				map[cas][w+1][c-2]==4||map[cas][w][c-2]==4||map[cas][w-1][c-2]==4||
                map[cas][w+1][c+2]==5||map[cas][w][c+2]==5||map[cas][w-1][c+2]==5||
				map[cas][w+1][c+1]==5||map[cas][w][c+1]==5||map[cas][w-1][c+1]==5||
				map[cas][w+1][c]==5||map[cas][w][c]==5||map[cas][w-1][c]==5||
				map[cas][w+1][c-1]==5||map[cas][w][c-1]==5||map[cas][w-1][c-1]==5||
				map[cas][w+1][c-2]==5||map[cas][w][c-2]==5||map[cas][w-1][c-2]==5)
				{
    	            switch(map[cas][w][c])
    	    	    {
    		        case 0:
		            cout<<"\033[100;34m#\033[0m";break;     //地图边界用"#"表示 
    	        	case 1:
		        	cout<<"\033[43;32m*\033[0m";break;      //墙用"*"表示 
    	            case 2:
		        	cout<<"\033[43;33m \033[0m";break;      //路用" "表示 
	    	    	case 3:
	        		cout<<"\033[43;31m+\033[0m";break;      //回血点"+"表示 
	        		case 4:
		        	case 5: 
		        	cout<<"\033[43;31mo\033[0m";break;      //勇者用"o"表示 
		        	case 6:
		        	cout<<"\033[43;34m/\033[0m";break;      //上楼梯用"/"表示 
		        	case 7:      
		        	cout<<"\033[43;34m\\\033[0m";break;     //下楼梯用"\"表示 
		        	case 8: 
		        	cout<<"\033[43;36;5m!\033[0m";break;    //钥匙用"!"表示
					case 9: 
		        	cout<<"\033[43;36mD\033[0m";break;      //门用"D"表示 
		         	case 10:
		        	cout<<"\033[43;32m%\033[0m";break;     //怪用"%"表示 
		        	case 11:
		        	cout<<"\033[43;33m&\033[0m";break;      //怪用"&"表示 
		        	case 12:
		        	cout<<"\033[43;31m~\033[0m";break;      //怪用"~"表示
                    case 13:
		        	cout<<"\033[43;35mB\033[0m";break;      //魔王用"B"表示 
		            }
		        }
			    else 
			    {
	    	    	cout<<" ";
		        }
			}
			cout<<"\033[0;100m \033[0m";
			cout<<"\033[100;34m#\033[0m\n"; 
		}
	    for(int w=0;w<50;w++)
		{
		    cout<<"\033[100;34m#\033[0m"; 	
		}
		cout<<endl;
	} 
	gotoxy(0,0);
}


void drawmap_1(int *p) //普通的画地图 
{
	switch(*p)
	{
	    case 0:
	    cout<<"\033[100;34m#\033[0m";break;     //地图边界用"#"表示 
	  	case 1:
	    case 22: 
	   	cout<<"\033[;100m \033[0m";break;       //墙用"*"表示 
	    case 2:
	   	cout<<"\033[47;37m \033[0m";break;      //路用" "表示 
	  	case 3:
		cout<<"\033[47;31m+\033[0m";break;      //回血点"+"表示 
		case 4:
		case 5:
	   	cout<<"\033[47;31mo\033[0m";break;      //勇者用"o"表示 
	   	case 6:
	 	cout<<"\033[47;34m/\033[0m";break;      //上楼梯用"/"表示 
		case 7:      
	 	cout<<"\033[47;34m\\\033[0m";break;     //下楼梯用"\"表示 
		case 8: 
	   	cout<<"\033[47;36;5m!\033[0m";break;    //钥匙用"!"表示
		case 9: 
	 	cout<<"\033[47;36mD\033[0m";break;      //门用"D"表示 
	 	case 10:
	 	cout<<"\033[47;32m%\033[0m";break;     //怪用"%"表示 
	   	case 11:
	   	cout<<"\033[47;33m&\033[0m";break;      //怪用"&"表示 
	    case 12:
	   	cout<<"\033[47;31m~\033[0m";break;      //怪用"~"表示
	    case 13:
	   	cout<<"\033[47;35mB\033[0m";break;      //魔王用"B"表示 
	}
}


void drawmap_2() //迷雾森林中的画地图 
{
	for(int w=fighter.i-2;w<=fighter.i+2;w++)
	{
		for(int c=fighter.j-3;c<=fighter.j+3;c++)
		{
			if(w>12&&w<24&&c>1&&c<48)
			{
				gotoxy(c,w+11);
				if(map[cas][w+1][c+2]==4||map[cas][w][c+2]==4||map[cas][w-1][c+2]==4||
				map[cas][w+1][c+1]==4||map[cas][w][c+1]==4||map[cas][w-1][c+1]==4||
				map[cas][w+1][c]==4||map[cas][w][c]==4||map[cas][w-1][c]==4||
				map[cas][w+1][c-1]==4||map[cas][w][c-1]==4||map[cas][w-1][c-1]==4||
				map[cas][w+1][c-2]==4||map[cas][w][c-2]==4||map[cas][w-1][c-2]==4||
                map[cas][w+1][c+2]==5||map[cas][w][c+2]==5||map[cas][w-1][c+2]==5||
				map[cas][w+1][c+1]==5||map[cas][w][c+1]==5||map[cas][w-1][c+1]==5||
				map[cas][w+1][c]==5||map[cas][w][c]==5||map[cas][w-1][c]==5||
				map[cas][w+1][c-1]==5||map[cas][w][c-1]==5||map[cas][w-1][c-1]==5||
				map[cas][w+1][c-2]==5||map[cas][w][c-2]==5||map[cas][w-1][c-2]==5)
				{
			        switch(map[cas][w][c])
				    {
				        case 0:
				        cout<<"\033[100;34m#\033[0m";break;     //地图边界用"#"表示 
				    	case 1:
				    	cout<<"\033[43;32m*\033[0m";break;      //墙用"*"表示 
				        case 2:
				    	cout<<"\033[43;33m \033[0m";break;      //路用" "表示 
				    	case 3:
						cout<<"\033[43;31m+\033[0m";break;      //回血点"+"表示 
						case 4:
				    	case 5: 
				    	cout<<"\033[43;31mo\033[0m";break;      //勇者用"o"表示 
				    	case 6:
				    	cout<<"\033[43;34m/\033[0m";break;      //上楼梯用"/"表示 
				    	case 7:      
				    	cout<<"\033[43;34m\\\033[0m";break;     //下楼梯用"\"表示 
				    	case 8: 
				    	cout<<"\033[43;36;5m!\033[0m";break;    //钥匙用"!"表示
						case 9: 
				    	cout<<"\033[43;36mD\033[0m";break;      //门用"D"表示 
				     	case 10:
				    	cout<<"\033[43;32m%\033[0m";break;     //怪用"%"表示 
				    	case 11:
				    	cout<<"\033[43;33m&\033[0m";break;      //怪用"&"表示 
				    	case 12:
				    	cout<<"\033[43;31m~\033[0m";break;      //怪用"~"表示
				        case 13:
				    	cout<<"\033[43;35mB\033[0m";break;      //魔王用"B"表示 
			        }
				}
				else
				{
					cout<<" ";
				}
		    }
		}
    }
}

void drawmap_3() //移动迷宫中的画地图 
{
    for(int w=17;w<=20;w+=3)
	{
	    for(int c=6;c<=14;c+=4)
		{
			gotoxy(c,w+11);	
	        if(map[cas][w][c]==22)
			{
		        cout<<"\033[;100m \033[0m";		
			}	
			else if(map[cas][w][c]==2)
			{
			    cout<<"\033[47;37m \033[0m";	
		    }
		    else
		    {
		    	cout<<"\033[47;31mo\033[0m";
			}
		}	
	}
    for(int w=19;w<=22;w+=3)
	{
	    for(int c=8;c<=12;c+=4)
		{
			gotoxy(c,w+11);	
	        if(map[cas][w][c]==22)
			{
		        cout<<"\033[;100m \033[0m";		
			}	
			else if(map[cas][w][c]==2)
			{
			    cout<<"\033[47;37m \033[0m";	
		    }
		    else
		    {
		    	cout<<"\033[47;31mo\033[0m";
			}
		}	
	}		
} 


void search() //寻找勇者的函数 
{ 
	for(fighter.i=0;fighter.i<25;fighter.i++)
	{
    	for(fighter.j=0;fighter.j<50;fighter.j++)
    	{
    		if(map[cas][fighter.i][fighter.j]==4||map[cas][fighter.i][fighter.j]==5)
    		{
    			break; 
			}
		}
		if(map[cas][fighter.i][fighter.j]==4||map[cas][fighter.i][fighter.j]==5)	
   		{
    		break; 
		}  
	}  //找出勇者
}


void type() //周边怪物的种类 
{
	gotoxy(55,13);
	int typefind=0;
	if(map[cas][fighter.i-1][fighter.j-1]==10||map[cas][fighter.i][fighter.j-1]==10||map[cas][fighter.i+1][fighter.j-1]==10||map[cas][fighter.i-1][fighter.j]==10||
	map[cas][fighter.i+1][fighter.j]==10||map[cas][fighter.i-1][fighter.j+1]==10||map[cas][fighter.i][fighter.j+1]==10||map[cas][fighter.i+1][fighter.j+1]==10)
	{
	    cout<<"旁边有绿色的“史莱姆”(小怪)   ";
	    gotoxy(55,14);
		cout<<"血量："<<monster[0].h<<" 攻击力："<<monster[0].a<<" 防御力："<<monster[0].d;
		typefind=1; 
	}
	else if(map[cas][fighter.i-1][fighter.j-1]==11||map[cas][fighter.i][fighter.j-1]==11||map[cas][fighter.i+1][fighter.j-1]==11||map[cas][fighter.i-1][fighter.j]==11||
	map[cas][fighter.i+1][fighter.j]==11||map[cas][fighter.i-1][fighter.j+1]==11||map[cas][fighter.i][fighter.j+1]==11||map[cas][fighter.i+1][fighter.j+1]==11)
	{
		cout<<"旁边有黄色的“岩浆兽”(小怪)   ";
		gotoxy(55,14);
		cout<<"血量："<<monster[1].h<<" 攻击力："<<monster[1].a<<" 防御力："<<monster[1].d;
		typefind=1;
	}
	else if(map[cas][fighter.i-1][fighter.j-1]==12||map[cas][fighter.i][fighter.j-1]==12||map[cas][fighter.i+1][fighter.j-1]==12||map[cas][fighter.i-1][fighter.j]==12||
	map[cas][fighter.i+1][fighter.j]==12||map[cas][fighter.i-1][fighter.j+1]==12||map[cas][fighter.i][fighter.j+1]==12||map[cas][fighter.i+1][fighter.j+1]==12)
	{
		cout<<"旁边有红色的“恶灵骑士”(小怪) ";
		gotoxy(55,14);
		cout<<"血量："<<monster[2].h<<" 攻击力："<<monster[2].a<<" 防御力："<<monster[2].d;
		typefind=1;
	}
	else if(map[cas][fighter.i-1][fighter.j-1]==13||map[cas][fighter.i][fighter.j-1]==13||map[cas][fighter.i+1][fighter.j-1]==13||map[cas][fighter.i-1][fighter.j]==13||
	map[cas][fighter.i+1][fighter.j]==13||map[cas][fighter.i-1][fighter.j+1]==13||map[cas][fighter.i][fighter.j+1]==13||map[cas][fighter.i+1][fighter.j+1]==13)
	{
		cout<<"旁边有紫色的“魔王”（boss）   "; 
		gotoxy(55,14);
		cout<<"血量："<<boss.h<<" 攻击力："<<boss.a<<" 防御力："<<boss.d;
		typefind=1;
	}
	else if(!typefind)
	{
		cout<<"旁边没有怪                     ";
		gotoxy(55,14);
		cout<<"                               "; 
	}
	else
	{
		cout<<"                               ";
		gotoxy(55,14);
		cout<<"                               ";
	}
	gotoxy(0,0);
}


void location() //玩家当前的位置 
{
	gotoxy(55,16);
	if((fighter.i>1&&fighter.i<7)&&(fighter.j>2&&fighter.j<20))
	{
		cout<<"你正在怪物的基地";
		gotoxy(55,17);
		cout<<"打败怪物并通过这里去到里面的藏宝库吧！";
		gotoxy(55,18);
		cout<<"\033[40;31m（藏宝库存放着通往迷雾森林的钥匙）\033[0m       "; 
	}
	else if(cas==0&&(fighter.i>7&&fighter.i<15)&&(fighter.j>2&fighter.j<16))
	{
		cout<<"你正在藏宝库    ";
		gotoxy(55,17);
		cout<<"快去拿通往迷雾森林的钥匙！            ";
		gotoxy(55,18);
		cout<<"                                                           "; 
	}
	else if(cas==0&&(fighter.i>1&&fighter.i<7)&&(fighter.j>20&fighter.j<29))
	{
		cout<<"你正在魔王殿    ";
		gotoxy(55,17);
		cout<<"快去打败魔王吧！                      ";
		gotoxy(55,18);
		cout<<"                                                           ";
	}
	else if(cas==0&&(fighter.i>16&&fighter.i<23)&&(fighter.j>2&fighter.j<16))
	{
		cout<<"你正在移动迷宫  ";
		gotoxy(55,17);
		cout<<"想好了再操作噢，可别被墙压扁了！      ";
		gotoxy(55,18);
		cout<<"\033[40;31m（移动迷宫内部可以拿到进怪物基地的钥匙）\033[0m "; 
	}
	else if(cas==1&&(fighter.i>12&&fighter.i<24)&&(fighter.j>0&&fighter.j<49))
	{
		cout<<"你正在迷雾森林  ";
		gotoxy(55,17);
		cout<<"抹黑前行并找到通往魔王殿的路吧！      "; 
		gotoxy(55,18);
		cout<<"                                                           "; 
	}
	else
	{
        cout<<"                ";
        gotoxy(55,17);
		cout<<"                                      ";
		gotoxy(55,18);
		cout<<"                                                           ";		
    }	 
}


int interaction(int num) //游玩时的交互 
{
	switch(num)
    {
        case 6:
		cout<<"是否上楼梯\n按“f”确认，按其他键取消\n";break; 
		case 7:
		cout<<"是否下楼梯\n按“f”确认，按其他键取消\n";break; 
		case 9:
		if(fighter.key)
		{
    		cout<<"你有"<<fighter.key<<"把钥匙,是否使用一把开门\n按“f”并确认，按其他键取消\n";break;
        }
		else
    	{
		    cout<<"你现在没有钥匙\n按“f”继续\n";break; 
	    }
		case 10:
    	case 11:
    	case 12:
    	cout<<"是否和怪物交战\n按“f”确认，按其他键取消\n";break; 	
		case 13:
		cout<<"是否和魔王交战\n按“f”确认，按其他键取消\n";break;        
	}
	char one=_getch();
	gotoxy(0,40);
	cout<<"                                        \n                                        \n";		
	if(one=='f'||one=='F')  
	{
		return 1;
	}
	else
	{
		return 0;
	}
    
}


void addhp() //加血的函数 
{
	fighter.hp+=999;
	if(fighter.hp>fighter.max)
	{
	fighter.hp=fighter.max;
    }
}


void upgrade() //升级的函数
{
	while(fighter.exp>=50)
	{
	    fighter.lv+=1;
		fighter.max+=20;
		fighter.atk+=10;
		fighter.def+=5;
		fighter.exp-=50;	
	} 
}


void battle(int *p) //战斗的函数 
{   //x是固定伤害,y是基础伤害,z是总伤害 
    int h_1=monster[0].h;
    int h_2=monster[1].h;
    int h_3=monster[2].h;
    int h_4=boss.h;
	int x1,y1,z1; //定义勇者的数据 
	int x2,y2,z2; //定义怪的数据 
    switch(*p)
    {
        case 10:
		x1=20; y1=fighter.atk-monster[0].d; z1=x1+y1; //勇者的攻击数据 
        x2=20; y2=monster[0].a-fighter.def; z2=x2+y2; //一号怪的攻击数据
        while(fighter.hp>0&&h_1>0)
        { 
        	h_1-=z1;
        	fighter.hp-=z2;
		}
		if(fighter.hp>0)
		{
			map[cas][fighter.i][fighter.j]-=2;
		    *p-=6;
	    	fighter.exp+=40;
	    }
		else
		{
		    gameover=1;
	    }
		break;
		case 11:
		x1=20;y1=fighter.atk-monster[1].d;z1=x1+y1; //勇者的攻击数据
		x2=20;y2=monster[1].a-fighter.def;z2=x2+y2; //二号怪的攻击数据
	    while(fighter.hp>0&&h_2>0)
        {
        	h_2-=z1;
        	fighter.hp-=z2;
		}
		if(fighter.hp>0)
		{
			map[cas][fighter.i][fighter.j]-=2;
	    	*p-=7;
		    fighter.exp+=50;
	    }
		else
		{
		    gameover=1;
	    }
		break; 
        case 12:
		x1=20; y1=fighter.atk-monster[2].d; z1=x1+y1; //勇者的攻击数据 
        x2=20; y2=monster[2].a-fighter.def; z2=x2+y2; //三号怪的攻击数据
        while(fighter.hp>0&&h_3>0)
        {
        	h_3-=z1;
        	fighter.hp-=z2;
		}
		if(fighter.hp>0)
		{
			map[cas][fighter.i][fighter.j]-=2;
		    *p-=8;
		    fighter.exp+=60;
	    }
		else
		{
		    gameover=1;
	    }
		break;
        case 13:
		x1=20; y1=fighter.atk-boss.d; z1=x1+y1; //勇者的攻击数据 
        x2=20; y2=boss.a-fighter.def; z2=x2+y2; //魔王的攻击数据
        while(fighter.hp>0&&h_4>0)
        {
        	h_4-=z1;
        	fighter.hp-=z2;
		}
		if(fighter.hp>0)
		{
            gameover=2;
	    }
		else
		{
		    gameover=1;
	    }
		break;				
	}

}


void keydown() //操控勇者移动 
{
	
    int keydown=_getch();
    if(keydown==ESC)
    {
    	system("cls");
    	save();
    	exit(0); 
	}
    else
    {
	    switch(keydown)
	    {
	        case 'W':
	        case 'w':
	        if(map[cas][fighter.i-1][fighter.j]==2||map[cas][fighter.i-1][fighter.j]==3) //判断前面是否为路或回血点 
		    { 
	
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i-1][fighter.j]+=2;
		        if(map[cas][fighter.i-1][fighter.j]==5)
		        {
		            addhp();
		        }
	        }
	        else
			if(map[cas][fighter.i-1][fighter.j]==6||map[cas][fighter.i-1][fighter.j]==7) //判断前面是否为楼梯 
			{
				if(interaction(map[cas][fighter.i-1][fighter.j])==1)
				{
			        if(map[cas][fighter.i-1][fighter.j]==6)
			        {
			        	map[cas][fighter.i][fighter.j]-=2;
			        	cas+=1;	
				    	map[cas][fighter.i][fighter.j]+=2;	    	
			        	break;
				    }
				    if(map[cas][fighter.i-1][fighter.j]==7)
			    	{
			    		map[cas][fighter.i][fighter.j]-=2;
			    		cas-=1;
			    		map[cas][fighter.i][fighter.j]+=2;
			    		break;
			    	}
	            }
			}
	        else 
			if(map[cas][fighter.i-1][fighter.j]==8) //判断前面是否是钥匙 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i-1][fighter.j]-=4;
		        fighter.key+=1;
			} 
			else 
			if(map[cas][fighter.i-1][fighter.j]==9) //判断前面是否是门 
			{
				if(interaction(map[cas][fighter.i-1][fighter.j])==1)
				{
			        if(!fighter.key)
			        {
		    	    	break;
		    		}
			    	else
			    	{
			    	    map[cas][fighter.i][fighter.j]-=2;
			    	    map[cas][fighter.i-1][fighter.j]-=5;
				        fighter.key-=1;
			        }
			    }
			}
			else
			if(map[cas][fighter.i-1][fighter.j]==22) //判断前面是否为移动的墙 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i-1][fighter.j]==10||map[cas][fighter.i-1][fighter.j]==11||map[cas][fighter.i-1][fighter.j]==12||map[cas][fighter.i-1][fighter.j]==13) //判断前面是否为怪或魔王
			{
	            if(interaction(map[cas][fighter.i-1][fighter.j])==1)
	            {
			        battle(&map[cas][fighter.i-1][fighter.j]);
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //不在“迷雾森林”时的地图刷新 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i-1>12&&fighter.i-1<24&&fighter.j>0&&fighter.j<49)) //不在“迷雾森林”时的地图刷新 
			{
				gotoxy(fighter.j,fighter.i+10);
			    drawmap_1(&map[cas][fighter.i-1][fighter.j]);
			}		
			break;
	        case 'S':
	        case 's':
	        if(map[cas][fighter.i+1][fighter.j]==2||map[cas][fighter.i+1][fighter.j]==3) //判断后面是否为路或回血点 
	        {
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i+1][fighter.j]+=2;
		        if(map[cas][fighter.i+1][fighter.j]==5)
		        {
		            addhp();
		        }
	        }
			else
			if(map[cas][fighter.i+1][fighter.j]==6||map[cas][fighter.i+1][fighter.j]==7) //判断后面是否为楼梯 
			{
				if(interaction(map[cas][fighter.i+1][fighter.j])==1)
				{
				    if(map[cas][fighter.i+1][fighter.j]==6)
				    {
				    	map[cas][fighter.i][fighter.j]-=2;
			 		   	cas+=1;
				    	map[cas][fighter.i][fighter.j]+=2;
				    	break;
					}
					if(map[cas][fighter.i+1][fighter.j]==7)
					{
						map[cas][fighter.i][fighter.j]-=2;
						cas-=1;
						map[cas][fighter.i][fighter.j]+=2;
						break;
					}
				}
		    }
	        else 
			if(map[cas][fighter.i+1][fighter.j]==8) //判断后面是否是钥匙 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i+1][fighter.j]-=4;
		        fighter.key+=1;
			} 
			else 
			if(map[cas][fighter.i+1][fighter.j]==9) //判断后面是否是门 
			{
				if(interaction(map[cas][fighter.i+1][fighter.j])==1)
				{
			        if(!fighter.key)
		    	    {
		    	    	break;
		    		}
	    			else
		    		{
			    	    map[cas][fighter.i][fighter.j]-=2;
				        map[cas][fighter.i+1][fighter.j]-=5;
			         	fighter.key-=1;
			        }
			    }
			}
			else
			if(map[cas][fighter.i+1][fighter.j]==22) //判断后面是否为移动的墙 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i+1][fighter.j]==10||map[cas][fighter.i+1][fighter.j]==11||map[cas][fighter.i+1][fighter.j]==12||map[cas][fighter.i+1][fighter.j]==13) //判断后面是否为怪或魔王 
		    {
		    	if(interaction(map[cas][fighter.i+1][fighter.j])==1)
		    	{
			        battle(&map[cas][fighter.i+1][fighter.j]); 
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //不在“迷雾森林”时的地图刷新 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i+1>12&&fighter.i+1<24&&fighter.j>0&&fighter.j<49)) //不在“迷雾森林”时的地图刷新 
			{
				gotoxy(fighter.j,fighter.i+12);
			    drawmap_1(&map[cas][fighter.i+1][fighter.j]);
			}
			break;
	        case 'A':
	        case 'a':
	        if(map[cas][fighter.i][fighter.j-1]==2||map[cas][fighter.i][fighter.j-1]==3) //判断左边是否为路或回血点 
	        {
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j-1]+=2;
		        if(map[cas][fighter.i][fighter.j-1]==5)
		        {
		            addhp();
		        }
	        }
			else
			if(map[cas][fighter.i][fighter.j-1]==6||map[cas][fighter.i][fighter.j-1]==7) //判断左边是否为楼梯 
			{ 
				if(interaction(map[cas][fighter.i][fighter.j-1])==1)
				{
			
			   	    if(map[cas][fighter.i][fighter.j-1]==6)
			       	{
			    	   	map[cas][fighter.i][fighter.j]-=2;
			       		cas+=1;
	   			    	map[cas][fighter.i][fighter.j]+=2;
		   		    	break;
			   		}
	   				if(map[cas][fighter.i][fighter.j-1]==7)
		   			{
			   			map[cas][fighter.i][fighter.j]-=2;
				   		cas-=1;
				   		map[cas][fighter.i][fighter.j]+=2;
					   	break;
				   	} 
	            }
			}
	        else 
			if(map[cas][fighter.i][fighter.j-1]==8) //判断左边是否是钥匙 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j-1]-=4;
		        fighter.key+=1;
			} 
			else 
			if(map[cas][fighter.i][fighter.j-1]==9) //判断左边是否是门 
			{
				if(interaction(map[cas][fighter.i][fighter.j-1])==1)
				{
			        if(!fighter.key)
		    	    {
	    		    	break;
	    			}
		    		else
			    	{
				        map[cas][fighter.i][fighter.j]-=2;
				        map[cas][fighter.i][fighter.j-1]-=5;
		    		    fighter.key-=1;
			        }
			    }
			}
			else
			if(map[cas][fighter.i][fighter.j-1]==22) //判断左边是否为移动的墙 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i][fighter.j-1]==10||map[cas][fighter.i][fighter.j-1]==11||map[cas][fighter.i][fighter.j-1]==12||map[cas][fighter.i][fighter.j-1]==13) //判断左边是否为怪或魔王
			{ 
			    if(interaction(map[cas][fighter.i][fighter.j-1])==1)
			    {
			    	battle(&map[cas][fighter.i][fighter.j-1]); 
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //不在“迷雾森林”时的地图刷新 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j-1>0&&fighter.j-1<49)) //不在“迷雾森林”时的地图刷新 
			{
				gotoxy(fighter.j-1,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j-1]);
			}
			break;
	        case 'D':
	        case 'd':
	        if(map[cas][fighter.i][fighter.j+1]==2||map[cas][fighter.i][fighter.j+1]==3) //判断右边是否为路或回血点 
	        {
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j+1]+=2;
		        if(map[cas][fighter.i][fighter.j+1]==5) 
		        {
		            addhp();
		        }
	        }
			else
			if(map[cas][fighter.i][fighter.j+1]==6||map[cas][fighter.i][fighter.j+1]==7) //判断右边是否为楼梯 
			{
				if(interaction(map[cas][fighter.i][fighter.j+1])==1)
				{
			        if(map[cas][fighter.i][fighter.j+1]==6)
			        {
			        	map[cas][fighter.i][fighter.j]-=2;
			    	    cas+=1;
	    		    	map[cas][fighter.i][fighter.j]+=2;
		    	    	break;
			    	}
				    if(map[cas][fighter.i][fighter.j+1]==7)
	    			{
		    			map[cas][fighter.i][fighter.j]-=2;
			    		cas-=1;
				    	map[cas][fighter.i][fighter.j]+=2;
					    break;
			    	}
		        }
			}
	        else 
			if(map[cas][fighter.i][fighter.j+1]==8) //判断右边是否是钥匙 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j+1]-=4;
		        fighter.key+=1;
			} 
			else
			if(map[cas][fighter.i][fighter.j+1]==9) //判断右边是否是门 
			{
				if(interaction(map[cas][fighter.i][fighter.j+1])==1)
			    {
			    	if(!fighter.key)
	    		    {
		    	    	break;
			    	}
				    else
	    			{
		    		    map[cas][fighter.i][fighter.j]-=2;
			    	    map[cas][fighter.i][fighter.j+1]-=5;
				        fighter.key-=1;
			        }
			    }
			}
			else
			if(map[cas][fighter.i][fighter.j+1]==22) //判断右边是否为移动的墙 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i][fighter.j+1]==10||map[cas][fighter.i][fighter.j+1]==11||map[cas][fighter.i][fighter.j+1]==12||map[cas][fighter.i][fighter.j+1]==13) //判断右边是否为怪或魔王
			{
				if(interaction(map[cas][fighter.i][fighter.j+1])==1)
				{
			    	battle(&map[cas][fighter.i][fighter.j+1]); 
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //不在“迷雾森林”时的地图刷新 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j+1>0&&fighter.j+1<49)) //不在“迷雾森林”时的地图刷新 
			{
				gotoxy(fighter.j+1,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j+1]);
			}
			break;
	    }
    }
}


void changemap() //改变地图（移动迷宫）的函数 
{
	for(int w=17;w<=20;w+=3)
	{
		for(int c=6;c<=14;c+=4)
		{
		    if(map[0][w][c]==2||map[0][w][c]==4)
			map[0][w][c]+=20;
			else if(map[0][w][c]==22)
			map[0][w][c]-=20;	
		}
	}
	for(int w=19;w<=22;w+=3)
	{
		for(int c=8;c<=12;c+=4)
		{
		    if(map[0][w][c]==2||map[0][w][c]==4)
			map[0][w][c]+=20;
			else if(map[0][w][c]==22)
			map[0][w][c]-=20;
		}
	}
}


void judge() //判断勇者是否被移动迷宫中的墙压扁的函数 
{
	for(int w=17;w<=20;w+=3)
	{
		for(int c=6;c<=14;c+=4)
		{
		    if(map[0][w][c]==24)
		    gameover=3;
		}
	}
	for(int w=19;w<=22;w+=3)
	{
		for(int c=8;c<=12;c+=4)
		{
		    if(map[0][w][c]==24)
		    gameover=3;
		}
	}
}


int main()
{
	system("mode con cols=120 lines=50");
	foreword(); 
	Sleep(2000);  
    cout<<"游戏开始：\n\n";   
    Sleep(1000);
    load();
	system("cls"); 	
	while(gameover==0)
	{
		initmap();
    	while(cas==0&&gameover==0) 
    	{
    		search();                                                        
		    drawstate();                                                      
		    cout<<"请输入'w''s''a''d'控制勇者进行上下左右的移动\n";          
		    cout<<"------------------------------------------------------------\n";                                          
		    cout<<"地图:\n"; 
		    drawmap_3();
			changemap();                                                       
			gotoxy(0,36);
			cout<<"注：图左下角为原点，右为 x 轴正方向，上为 y 轴正方向\n\n";
			gotoxy(55,11); 
			cout<<"HUD：";			
			type(); 			
			location();
			gotoxy(0,40);
			keydown();                                                                                                                
			upgrade();  	
			judge();		                                                     
			gotoxy(0,0);
		}
		system("cls");
		initmap();
		while(cas==1&&gameover==0) 
	   	{
			search();                                                          
		    drawstate();                                                        
		    cout<<"请输入'w''s''a''d'控制勇者进行上下左右的移动\n";          
		    cout<<"------------------------------------------------------------\n";                                          
		    cout<<"地图:\n"; 
		    drawmap_2();
			changemap();                                                      
			gotoxy(0,36);
			cout<<"注：图左下角为原点，右为 x 轴正方向，上为 y 轴正方向\n\n";
			gotoxy(55,11);
			cout<<"HUD：";
			type(); 
			location(); 
			gotoxy(0,40);
			keydown();                                                                                                              
		 	upgrade(); 		                                                     
			gotoxy(0,0);
		}
		system("cls");
	}
	if(gameover==1)
	{ 
	    cout<<"你被怪杀死了！！！不要气馁，再来一次吧";
    }
	else if(gameover==2)
	{
	    cout<<"W I N !!!\n恭喜你完成了挑战\n游戏结束了，生活还在继续，让我们继续以“勇者”的身份克服每一个挑战吧\n\n\n视觉组王吉畅巨献\n\n\n游戏制作：王吉畅\n游戏创意：王吉畅";	
    }
    else if(gameover==3)
    {
    	cout<<"你被墙压扁了！！！下次要小心哦";
	}
	
	return 0;
}
