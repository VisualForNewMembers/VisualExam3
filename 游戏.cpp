#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string>
#include <fstream>

using namespace std;

struct Ui{
	int Blood;
	int attack;
	int defense;
	int Grade;
	int experience;
	int MAX_Blood;
	int X;
	int Y;
};

struct monster{//怪物的面板
    string name; 
	int Blood;
	int attack;
	int defense;
	int get_experience;
	int fixed_attack;
};


char a[20][20]{"###############",
			   "# *! *  *+&D  #",
			   "#o*~ D  *+~*% #",
			   "# *+ *  *%+* %#",
			   "# ****  ****  #",
			   "#   &     ~   #",
			   "# *** **** ** #",
			   "#  !* *+&* *  #",
			   "#**** ** * * %#",
			   "#/*+*%*!   *+ #",
			   "# *%* **** *~ #",
			   "#~* D *&   %  #",
			   "# *** ****D***#",
			   "#&%    ~+*  ++#",
			   "###############",};
			   
char b[20][20]{"###############",
			   "#   **   **   #",
			   "#   **   **   #",
			   "#   **   **   #",
			   "#*****   *****#",
			   "#*****   *****#",
			   "#      B      #",
			   "#*****   *****#",
			   "#*****   *****#",
			   "#   **   **   #",
			   "#o  **   **   #",
			   "#   **   **   #",
			   "#   **   **   #",
			   "#             #",
			   "###############",};	
	char n;//存储用户输入变量		   	   	   
	int h = 2; //行数
	int l = 1; //列数
	int h1,l1; //用于存储前方交互物品变量 
	int h2,l2; //地图输出变量
    int get_key = 0; //获过的最大钥匙数
    int chenshu = 1;//层数变量
	char p;//存储移动前方信息变量
	int key = 0; 	//钥匙数量变量
	int n1 = 0;	 //与怪物交互次数统计变量
	int A = 0;//怪物击杀数量
	int monsterZ = 19;//第一层怪物总量
	int n2 = 0;//魔王识别码
	
	struct Ui ui ={100, 30, 20,1,0,100,l,14-h}; //玩家三维
	struct monster monster1 ={"哥布林",100,5,20,30,5}; //第一个怪物的三维
	struct monster monster2 ={"吸血鬼",150,10,5,40,6};
	struct monster monster3 ={"巨魔",200,5,30,40,8};
	struct monster monsterB ={"魔王",350,50,50,100,15};
	
		   
//////////////第一个函数////////////////////////				   
  char panduan(char n){//收集输入符号
      if(chenshu==1){	
      switch(n){  //检测输入符号是否首先符合移动要求
      	case'a':
      	 if(a[h][l-1]==' '){
      	 	a[h][l] = ' ';
            l--;
            a[h][l] = 'o';
      	 	return 'l';//符合返回原指令
		   }else{
		   	h1 = h;
		   	l1 = l-1;
		    p = a[h][l-1];
		   	break;
		   }
      	case's':
      	  if(a[h+1][l]==' '){
      	  	a[h][l] = ' ';
            h++;
            a[h][l] = 'o';
      	 	return 'l';
		   }else{
		   	h1 = h+1;
		   	l1 = l;
		    p = a[h+1][l];  //不符合收集移动方向的字符判断是否是怪物品墙壁
		   	break;
		   }	
		case'w':
		  if(a[h-1][l]==' '){
		  	a[h][l] = ' ';
            h--;
            a[h][l] = 'o';
      	 	return 'l';
		   }else{
		   	h1 = h-1;
		   	l1 = l;
		   	p = a[h-1][l];
		   	break;
		   }
      	case'd': 
		  if(a[h][l+1]==' '){
		  	a[h][l] = ' ';
            l++;
            a[h][l] = 'o';
      	 	return 'l';
		   }else{
		   	h1 = h;
		   	l1 = l+1;
		   	p = a[h][l+1];
		   	break;
		   }
		case'G':
		  return 'G';    	
	  }
    }
    if(chenshu==2){ //第二层移动控制
          switch(n){  //检测输入符号是否首先符合移动要求
      	case'a':
      	 if(b[h][l-1]==' '){
      	 	b[h][l] = ' ';
            l--;
            b[h][l] = 'o';
      	 	return 'l';//符合返回原指令
		   }else{
		   	h1 = h;
		   	l1 = l-1;
		    p = b[h][l-1];
		   	break;
		   }
      	case's':
      	  if(b[h+1][l]==' '){
      	  	b[h][l] = ' ';
            h++;
            b[h][l] = 'o';
      	 	return 'l';
		   }else{
		   	h1 = h+1;
		   	l1 = l;
		    p = b[h+1][l];  //不符合收集移动方向的字符判断是否是怪物品墙壁
		   	break;
		   }	
		case'w':
		  if(b[h-1][l]==' '){
		  	b[h][l] = ' ';
            h--;
            b[h][l] = 'o';
      	 	return 'l';
		   }else{
		   	h1 = h-1;
		   	l1 = l;
		   	p = b[h-1][l];
		   	break;
		   }
      	case'd': 
		  if(b[h][l+1]==' '){
		  	b[h][l] = ' ';
            l++;
            b[h][l] = 'o';
      	 	return 'l';
		   }else{
		   	h1 = h;
		   	l1 = l+1;
		   	p = b[h][l+1];
		   	break;
		   }
		case'G':
		  return 'G';    	
	  }
    }		
    
    if(p=='#'||p=='*'){ //黑名单
	  return 'l';
     }else if(p=='!'||p==39||p=='D'||p=='+'
	 ||p=='%'||p=='&'||p=='~'||p=='/'||p=='B'){ //白名单
	  return p;
     }	  
	  return 'N';
}

/////////////物品交互函数///////////////////////
char wuping(char k){ 
		if(k=='!'){
		a[h][l] = ' ';
		 key++;
		 get_key++;
		a[h1][l1] = 'o';
		h = h1,l=l1; 
		p = ' ';
		return 'N';
	}else if(k=='D'&&key>0){
		a[h][l] = ' ';
         key--;
		a[h1][l1] = 'o'; 
		h = h1,l=l1;
		p = ' ';
		return 'N';
	}else if(k=='+'){
		a[h][l] = ' ';
		a[h1][l1] = 'o'; 
		h = h1,l=l1;
		p = ' ';
		if(ui.Blood<=(ui.MAX_Blood-80)){
			ui.Blood+=80;
		}else{
			ui.Blood = ui.MAX_Blood;
		}
		return 'N';
	}
	return 'N';//返回一个无用字符
}


///////////////////地图刷新函数//////////////////////////////
char shuaxing(char G = 'l',int monster1_Blood=monster1.Blood,
   int monster2_Blood=monster2.Blood,int monster3_Blood=monster3.Blood,
   int monsterB_Blood=monsterB.Blood){ 
   //数组下标转换坐标//
	 ui.X = l;
	 ui.Y = 14-h;
   //临时存储怪物三维//	 
	 int monster_Blood;
	 string monster_Name;
	 int monster_Attack;
	 int monster_Defense;
	 int monster_Fixed_Attack;
	 //交互语句存储变量//
	 string jiaohu1 = "";
	 string jiaohu2 = "";
	 string jiaohu3 = "";
	 string jiaohu4 = "";
	 string jiaohu5 = "";
	 //基本地图刷新//
	 if(G=='l'){
	 if(key>=1&&get_key>=3){
	 	jiaohu1 = "     (包裹在钥匙上的的陈旧纸条)：";
	 	jiaohu2 = "    在第二层魔王会封锁勇者SL技能";
	 	jiaohu3 = "     魔王会妨碍勇者窥视而伪装属性";
	 	jiaohu4 = "    魔王会吸收一层剩余的怪物的生命值";
	 	jiaohu5 = "    我们拼命换来的情报留个下一个来挑战的勇士!";
	 }	
	  system("cls");
	  cout<<"血量："<<ui.Blood<<endl;
	  cout<<"攻击力："<<ui.attack<<endl;
      cout<<"防御力："<<ui.defense<<endl;
	  cout<<"等级："<<ui.Grade<<jiaohu1<<endl;
	  cout<<"经验值："<<ui.experience<<jiaohu2<<endl;
	  cout<<"钥匙数量："<<key<<jiaohu3<<endl;
	  cout<<"位置x:"<<ui.X<<jiaohu4<<endl;
	  cout<<"位置y："<<ui.Y<<jiaohu5<<endl;
	  cout<<"输入w,a,s,d进行上,左,下,右移动"<<endl;
	  cout<<"------------------------------------------------------"<<endl;
	  if(chenshu==1){
      for(h2=0;h2<15;h2++){
   	  for(l2=0;l2<15;l2++){
   		cout<<a[h2][l2];
	   }
	   cout<<endl;
   }
}
      if(chenshu==2){
      for(h2=0;h2<15;h2++){
   	  for(l2=0;l2<15;l2++){
   		cout<<b[h2][l2];
	   }
	   cout<<endl;
   }
}
		n1 = 0;	
	}
   //遇到怪物时显示怪物三维和攻击过程刷新//	
	if(G=='%'||G=='&'||G=='~'||G=='B'){
		if(G=='%'){
		monster_Blood = monster1_Blood;	
		monster_Name = monster1.name;
		monster_Attack = monster1.attack;
		monster_Defense = monster1.defense;
		monster_Fixed_Attack = monster1.fixed_attack;
		}else if(G=='&'){
	    monster_Blood = monster2_Blood;		
		monster_Name = monster2.name;
		monster_Attack = monster2.attack;
		monster_Defense = monster2.defense;
		monster_Fixed_Attack = monster2.fixed_attack;	
		}else if(G=='~'){
		monster_Blood = monster3_Blood;		
		monster_Name = monster3.name;
		monster_Attack = monster3.attack;
		monster_Defense = monster3.defense;
		monster_Fixed_Attack = monster2.fixed_attack;		
		}else if(G='B'){
		monster_Blood = monsterB_Blood;		
		monster_Name = monsterB.name;
		monster_Attack = monsterB.attack;
		monster_Defense = monsterB.defense;
		monster_Fixed_Attack = monsterB.fixed_attack;	
		}
	  system("cls");
	  cout<<"血量："<<ui.Blood<<"              怪血量："<<monster_Blood<<endl;
	  cout<<"攻击力："<<ui.attack<<"              攻击力："<<monster_Attack<<endl;
      cout<<"防御力："<<ui.defense<<"              防御力："<<monster_Defense<<endl;
	  cout<<"等级："<<ui.Grade<<"                 固定伤害："<<monster_Fixed_Attack<<endl;
	  cout<<"经验值："<<ui.experience<<"               怪物名："<<monster_Name<<endl;
	  cout<<"钥匙数量："<<key<<endl;
	  cout<<"位置x:"<<ui.X<<endl;
	  cout<<"位置y："<<ui.Y<<endl;
	  cout<<"再次按下前进键位攻击,其他方位键退出战斗"<<endl;
	  cout<<"------------------------------------------------------"<<endl;
     if(chenshu==1){
      for(h2=0;h2<15;h2++){
   	  for(l2=0;l2<15;l2++){
   		cout<<a[h2][l2];
	   }
	   cout<<endl;
   }
}
      if(chenshu==2){
      for(h2=0;h2<15;h2++){
   	  for(l2=0;l2<15;l2++){
   		cout<<b[h2][l2];
	   }
	   cout<<endl;
   }
  }
     n1++;
}
////////死亡或胜利的屏幕刷新//////////
    if(G=='W'){
      system("cls");
      cout<<"游戏结束"<<endl;
      cout<<"你已经成功击杀魔王！"<<endl;
      cout<<"作者：王宏宇"<<endl;
      cout<<"输入G可读取到上一次存档位置:"<<endl;
	}
  	if(G=='K'){
  	 system("cls");	
  	 cout<<"游戏结束"<<endl;
     cout<<"死因：被魔王击杀"<<endl;
     cout<<"作者：王宏宇"<<endl;
     cout<<"输入G读取存档:"<<endl;
	}
	if(G=='J'){
  	 system("cls");	
  	 cout<<"游戏结束"<<endl;
     cout<<"死因：被魔王军击杀"<<endl;
     cout<<"作者：王宏宇"<<endl;
     cout<<"输入G读取存档:"<<endl;
	}
	return 'N';		
}
///////////////////怪物交互函数//////////////////////////////
char guaiwu(char k){
	//临时存储怪物三维变量//
	int monster_Blood;
	int monster_defense;
	int monster_attack;
	int monster_exp;
	int monster_Fixed_attack;
	
	//攻击计算//
	if((k=='&'||k=='%'||k=='~'||k=='B')&&n1>=2){
	//怪物种类分配//	
	if(k=='%'){
		monster_Blood = monster1.Blood;
		monster_defense = monster1.defense;
		monster_attack = monster1.attack;
		monster_exp = monster1.get_experience;
		monster_Fixed_attack = monster1.fixed_attack;
	}else if(k=='&'){
		monster_Blood = monster2.Blood;
		monster_defense = monster2.defense;
		monster_attack = monster2.attack;
		monster_exp = monster2.get_experience;
		monster_Fixed_attack = monster2.fixed_attack;
	}else if(k=='~'){
		monster_Blood = monster3.Blood;
		monster_defense = monster3.defense;
		monster_attack = monster3.attack;
		monster_exp = monster3.get_experience;
		monster_Fixed_attack = monster3.fixed_attack;
	}else if(k=='B'){
		n2 = 1;
		monster_Blood = monsterB.Blood + (monsterZ-A)*20;
		monster_defense = monsterB.defense;
		monster_attack = monsterB.attack;
		monster_exp = monsterB.get_experience;
		monster_Fixed_attack = monsterB.fixed_attack;
	}
		while(1){
		//勇者伤害计算//
		 int attack1 = 20;	
		 int attack2 = ui.attack - monster_defense;
		 int attack3 = 0;
		 if(attack2<=0){
		 	attack3 = attack1 + 0;
		 }else{
		 	attack3 = attack1 + attack2;
		 }
		//怪物伤害计算//
		 int m_attack1 = monster_Fixed_attack;
		 int m_attack2 = monster_attack - ui.defense ;
		 int m_attack3 = 0;
		 if(m_attack2<=0){
		 	m_attack3 = m_attack1 + 0;
		 }else{
		 	m_attack3 = m_attack1 + m_attack2;
		 }
        //伤害合算//
		 ui.Blood = ui.Blood - m_attack3;
		 monster_Blood = monster_Blood - attack3;
		 
		 if(ui.Blood<0){
		 	ui.Blood = 0;
		 }
		 
		 if(monster_Blood<0){
		 	monster_Blood = 0;
		 }
		 //攻击动画处理//
		 sleep(1);
		 shuaxing(p,monster_Blood,monster_Blood,monster_Blood,
		 monster_Blood);
		 //判断勇者是否死亡//
		 if(ui.Blood==0){
		 	if(n2==1){
		 		return 'K';//返回状态识别码
			 }else{
			 	return 'J';//返回状态识别码
			 }	 
		 }
		 //判断怪物是否死亡//
		 if(monster_Blood==0){
		 	if(n2==1){
		 	  return 'W';//返回状态识别码
			}
		 	a[h][l] = ' ';
		    a[h1][l1] = 'o'; 
		    h = h1,l=l1;
		    ui.experience = ui.experience + monster_exp;
		    A++;
		    shuaxing();
		 	break;
		 }
		}
    }
    return 'N';
}
/////////////////////////经验计算函数/////////////////////////
void exp_up(){
	if(ui.experience>50){
		ui.experience = ui.experience -50;
		ui.attack = ui.attack + 10;
		ui.Grade = ui.Grade + 1;
		ui.MAX_Blood = ui.MAX_Blood + 20;
		ui.defense = ui.defense + 5;
	}
}
/////////////存档读档函数////////////////////////////////////
void G(){
	int c;//存储文件中字符变量
	int i;//循环次数变量
	//数组下标临时存储变量//
	int h3 =0;
    int l3 =0;
    if(chenshu==1){
    system("cls");
    cout<<"输入D键读档"<<endl;
    cout<<"输入H键存档"<<endl;
    cout<<"------------------------------------------------------"<<endl;
	cin>>n;
	if(n=='D'){
		//写入地图数据//
		ifstream infile1;
        infile1.open("Map.dat");
		while(c=infile1.get()){
		a[h3][l3] = c;
		l3++;
		if(l3>15){
			h3++;
			l3 = 0;
		}
		if(h3>15){
			break;
		}
	}
	    infile1.close();
		//开始写入玩家数据//	
		ifstream infile2;
		infile2.open("Player.dat");
		for(i=1;i<=11;i++){
			if(i==1) infile2 >> ui.Blood;
			if(i==2) infile2 >> ui.attack;
			if(i==3) infile2 >> ui.defense;
			if(i==4) infile2 >> ui.Grade;
			if(i==5) infile2 >> ui.experience;
			if(i==6) infile2 >> ui.MAX_Blood;
			if(i==7) infile2 >> h;
			if(i==8) infile2 >> l;	
			if(i==9) infile2 >> key;
			if(i==10) infile2 >> get_key;
			if(i==11) infile2 >> A;
		}
		infile2.close();
	}
	
	if(n=='H'){
	//读取地图数据//
	 ofstream outfile1;
	 outfile1.open("Map.dat", ios::out | ios::trunc);	
	 for(h3=0;h3<15;h3++){
		for(l3=0;l3<15;l3++){
			outfile1<<a[h3][l3];
		}
		outfile1<<endl;
	}
	outfile1.close();
	//读取玩家数据//
	ofstream outfile2;
	outfile2.open("Player.dat", ios::out | ios::trunc);
	for(i=1;i<=11;i++){
			if(i==1) outfile2 << ui.Blood << endl;
			if(i==2) outfile2 << ui.attack << endl;
			if(i==3) outfile2 << ui.defense << endl;
			if(i==4) outfile2 << ui.Grade << endl;
			if(i==5) outfile2 << ui.experience << endl;
			if(i==6) outfile2 << ui.MAX_Blood << endl;
			if(i==7) outfile2 << h << endl;
			if(i==8) outfile2 << l << endl;	
			if(i==9) outfile2 << key << endl;
			if(i==10) outfile2 << get_key << endl;
			if(i==11) outfile2 << A << endl;	
		}
		outfile2.close();
	}
  }
  if(chenshu==2){
  	system("cls");
    cout<<"*ERROR*SL技能失效*ERROR*"<<endl;
    cout<<"-----------------------------------"<<endl;
    sleep(3);
    shuaxing();
  }
}
////////////主运行函数/////////////////////////////////////	
int main(){
	char n;//用户输入变量
    char k;//判断返回值存储变量
	system("chcp 65001"); 
    shuaxing();
      
    while(1){
    	cin>>n;
    	k = panduan(n);
        if(k=='!'||k==39||k=='D'||k=='+'){
        	wuping(k);
        	shuaxing();
		}else if(k=='%'||k=='&'||k=='~'||k=='B'){
		   shuaxing(k);	
		   k=guaiwu(k);
		   exp_up();
		   shuaxing(k);		
		}else if(k=='G'){
		   G();
		   shuaxing();
		}else if(k=='/'){
		  chenshu = 2;
		  shuaxing();	
		}else if(n=='L'){
			break;	
		}else{
		  shuaxing();
		}
	}	
	return 0;
}
