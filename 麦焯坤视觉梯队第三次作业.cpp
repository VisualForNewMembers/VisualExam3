#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<fstream>
using namespace std;
int key=0;
struct character {
	char name[1];
	int ex;
	int grade;
	int boold;
	int defind;
	int att;
	int boold_max;
}Hero={72,0,0,100,20,30,100},BOSS={66,100,10,500,200,100,500},YAO{42,50,1,50,5,20,50},GUI{38,50,1,100,10,5,100},
GUAI{36,50,1,40,10,40,40};//英雄和怪物的基本属性
char map1[10][20]={  {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35},
                     {35,72,32,33,68,42,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                     {35,35,35,35,35,35,32,32,38,32,32,32,32,32,32,32,32,32,32,35},
                     {35,32,32,32,32,32,35,36,33,36,32,32,32,32,32,32,32,32,32,35},
                     {35,32,32,32,32,32,32,35,38,32,32,32,32,32,32,32,32,32,32,35},
                     {35,32,32,32,32,32,32,32,68,32,32,32,32,32,32,32,32,32,32,35},
                     {35,32,32,32,32,32,32,32,32,35,32,32,32,32,32,35,35,35,35,35},
                     {35,32,43,33,32,32,32,32,32,32,35,32,32,32,32,35,32,32,42,35},
                     {35,32,32,32,32,32,32,32,32,32,32,35,32,32,32,68,32,38,47,35},
				   	 {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};
char map2[10][20]={  {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35},
                     {35,92,33,72,68,42,32,32,32,32,32,32,32,35,32,32,32,32,32,35},
                     {35,35,35,35,35,35,32,32,32,32,32,32,32,35,32,32,32,32,32,35},
                     {35,32,32,32,32,35,32,32,32,32,32,32,32,68,32,32,32,32,32,35},
                     {35,32,32,32,32,68,32,32,33,32,33,32,32,35,42,32,32,32,32,35},
                     {35,36,36,35,35,35,35,35,35,68,35,35,35,35,43,38,32,32,32,35},
                     {35,32,32,35,33,32,32,32,32,32,32,32,43,35,35,35,35,35,35,35},
                     {35,32,32,35,42,38,36,36,38,42,42,38,36,35,32,32,32,32,32,35},
                     {35,33,43,35,32,32,32,32,32,32,32,32,66,68,32,32,32,32,47,35},
				   	 {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};
void game_document_keep(char wor[]){//游戏存档 
	ofstream ofs;
	ofs.open("游戏存档.text",ios::app);
	ofs<<wor<<endl; 
	ofs.close();
}
void game_document_read(){//读档 
	char a[1024];
	ifstream ifs;
	ifs.open("游戏存档.text",ios::in);
	while(ifs>>a)
	cout<<a<<endl;
	ifs.close(); 
}									   	 
void clear(){//输出英雄的属性进行监控 
	cout<<"最大血量"<<Hero.boold_max<<endl ; 
	cout<<"血量："<<Hero.boold <<endl; 
	cout<<"攻击力"<<Hero.att <<endl;
	cout<<"防御力"<<Hero.defind <<endl; 
	cout<<"经验值："<<Hero.ex <<endl; 
	cout<<"等级："<<Hero.grade <<endl; 
	cout<<"钥匙数量："<<key <<endl; 
}
int PK(struct character M){//PK机制 血量=我方血量—敌方攻击-敌方攻击%我方防御  英雄先攻击然后到敌方直到一方血量<=0   
	 while(Hero.boold >0&&M.boold >0){
	 system("cls");	
	cout<<M.name <<":"<<endl;
	cout<<"血量："<<M.boold <<endl; 
    cout<<"等级："<<M.grade <<endl;
	system("pause");//每个攻击回合显示怪物的血量等 
	 	Hero.boold =Hero.boold -M.att-M.att %Hero.defind   ;
	 	M.boold =M.boold -Hero.att-Hero.att %M.defind  ;
	 	if(Hero.boold <=0){
	 		cout<<"你已阵亡，游戏结束"<<endl; //若我方阵亡游戏结束自动退出程序
	 		char wor[]="你已阵亡，游戏结束"; 
			game_document_keep(wor);
		    exit(1); 
		 }
		 else if(M.boold <=0){//击败怪物得到怪物的经验 
		 	 Hero.ex +=M.ex;
	 		if(Hero.ex >=50){ 
	 		Hero.grade +=Hero.ex %50;
	 		if(Hero.ex %50>0){//升级后最大血量  攻击力 防御力的提升 
	 				Hero.att +=10;
					Hero.boold_max +=20;
					Hero.defind +=5;
			 }
			Hero.ex =Hero.ex /50;
		 }
		 return 2;
	 }
}
}	   	
int x_move(int x,int y,char map[10][20]){//移动遇到不同对象时操作 
    int i,j;
    for(i=0;i<9;i++){
    	for(j=0;j<19;j++){
    		if(map[i][j]==Hero.name[0]){
    				if(map[x][y]==32){
		map[x][y]=Hero.name[0];
		map[i][j]=32;
	}
	else if(map[x][y]==33){//钥匙 ‘！’33 
		map[x][y]=Hero.name[0];
		map[i][j]=32;
		key++;
	} 
	else if(map[x][y]==68){//门 ‘D’ 68
		if(key>0){
				map[x][y]=Hero.name[0];
				map[i][j]=32;
				key--;
		}
	}
	else if(map[x][y]==43){//回血点 ‘+’43  血量回满到最大血量 
		map[x][y]=Hero.name[0];
		map[i][j]=32;
		Hero.boold =Hero.boold_max ;
	}
	else if(map[x][y]==42){
		if(MessageBox(NULL,"遇到妖","是否攻击",MB_YESNO)==IDYES){
		   if(PK(YAO)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//妖'*' 42 
	else if(map[x][y]==66){
		if(MessageBox(NULL,"遇到魔王","是否攻击",MB_YESNO)==IDYES){
		   if(PK(BOSS)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//魔王BOSS'B'66 
	else if(map[x][y]==38){
		if(MessageBox(NULL,"遇到鬼","是否攻击",MB_YESNO)==IDYES){
		   if(PK(GUI)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//鬼 &'  38
	 	else if(map[x][y]==36){
		if(MessageBox(NULL,"遇到妖","是否攻击",MB_YESNO)==IDYES){
		   if(PK(GUAI)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//怪 $' 36
	else if(map[x][y]==47){//楼梯 ‘/’47 
		map[x][y]=Hero.name[0];
		map[i][j]=47;
		return 1;
	}
	else if(map[x][y]==92){//回到上一张图的楼梯 ‘\'92 
			map[x][y]=Hero.name[0];
		    map[i][j]=92;
		    return 2;
	} 
			}
		}
	}

}	
int move(char map[10][20])
{
	            int i,j;
	            char ch;
				while(1){
	 ch=getch();				
	for(i=0;i<9;i++){
		for(j=0;j<19;j++){
			if(map[i][j]==Hero.name[0]){//找到英雄 
					switch(ch)//键盘操作
					{
						case 'q' :{//用户手动退出游戏 
							char wor[]="手动退出游戏";	
							game_document_keep(wor); 
							exit(1);
						}
						case 'r':{//读档 
							game_document_read();
							system("pause");
							break;
						}
						case 'w':{
								switch(x_move(--i,j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//上 
			
						case 's':{
								switch(x_move(++i,j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//下 
			
						case 'a':{
								switch(x_move(i,--j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//左 
						case 'd':{
								switch(x_move(i,++j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//右 
					}					
		system("cls");
	for(i=0;i<10;i++){//画出地图 
		for(j=0;j<20;j++){
			cout<<map[i][j];
		}
		cout<<endl;
					}
		clear();//输出英雄的属性进行监控		
				}
			}
		}
	}
}	
int main(){
	cout<<"游戏介绍："<<endl;
	cout<<"w s a d 分别为上下左右移动"<<endl;
	cout<<"'$','&','*'"<<"怪物"<<endl;
	cout<<"/ \ 楼梯"<<" ,"<<"+ 回血点"<<" ,"<<"! 钥匙"<<endl;
	cout<<"q 手动退出游戏"<<'\t'<<"r 读取存档"<<endl; 
	system("pause");
	system("cls"); 
	int i,j;		
c:	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			cout<<map1[i][j];
		}
		cout<<endl;//地图10*20 
	}
	
	if(move(map1)==1){
		switch(move(map2)){
			case 2:{
			system("cls");
			goto c;
				break;
			}
			case 1:{
				char wor[]="顺利通关"; 
				game_document_keep(wor); 
				cout<<"恭喜你顺利通关"<<endl;
				cout<<"制作者：麦焯坤"<<endl;
				system("pause");
				break;
			}
		}

	
	
}
	return 0;
}					   				   	
