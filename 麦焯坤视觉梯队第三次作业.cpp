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
GUAI{36,50,1,40,10,40,40};//Ӣ�ۺ͹���Ļ�������
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
void game_document_keep(char wor[]){//��Ϸ�浵 
	ofstream ofs;
	ofs.open("��Ϸ�浵.text",ios::app);
	ofs<<wor<<endl; 
	ofs.close();
}
void game_document_read(){//���� 
	char a[1024];
	ifstream ifs;
	ifs.open("��Ϸ�浵.text",ios::in);
	while(ifs>>a)
	cout<<a<<endl;
	ifs.close(); 
}									   	 
void clear(){//���Ӣ�۵����Խ��м�� 
	cout<<"���Ѫ��"<<Hero.boold_max<<endl ; 
	cout<<"Ѫ����"<<Hero.boold <<endl; 
	cout<<"������"<<Hero.att <<endl;
	cout<<"������"<<Hero.defind <<endl; 
	cout<<"����ֵ��"<<Hero.ex <<endl; 
	cout<<"�ȼ���"<<Hero.grade <<endl; 
	cout<<"Կ��������"<<key <<endl; 
}
int PK(struct character M){//PK���� Ѫ��=�ҷ�Ѫ�����з�����-�з�����%�ҷ�����  Ӣ���ȹ���Ȼ�󵽵з�ֱ��һ��Ѫ��<=0   
	 while(Hero.boold >0&&M.boold >0){
	 system("cls");	
	cout<<M.name <<":"<<endl;
	cout<<"Ѫ����"<<M.boold <<endl; 
    cout<<"�ȼ���"<<M.grade <<endl;
	system("pause");//ÿ�������غ���ʾ�����Ѫ���� 
	 	Hero.boold =Hero.boold -M.att-M.att %Hero.defind   ;
	 	M.boold =M.boold -Hero.att-Hero.att %M.defind  ;
	 	if(Hero.boold <=0){
	 		cout<<"������������Ϸ����"<<endl; //���ҷ�������Ϸ�����Զ��˳�����
	 		char wor[]="������������Ϸ����"; 
			game_document_keep(wor);
		    exit(1); 
		 }
		 else if(M.boold <=0){//���ܹ���õ�����ľ��� 
		 	 Hero.ex +=M.ex;
	 		if(Hero.ex >=50){ 
	 		Hero.grade +=Hero.ex %50;
	 		if(Hero.ex %50>0){//���������Ѫ��  ������ ������������ 
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
int x_move(int x,int y,char map[10][20]){//�ƶ�������ͬ����ʱ���� 
    int i,j;
    for(i=0;i<9;i++){
    	for(j=0;j<19;j++){
    		if(map[i][j]==Hero.name[0]){
    				if(map[x][y]==32){
		map[x][y]=Hero.name[0];
		map[i][j]=32;
	}
	else if(map[x][y]==33){//Կ�� ������33 
		map[x][y]=Hero.name[0];
		map[i][j]=32;
		key++;
	} 
	else if(map[x][y]==68){//�� ��D�� 68
		if(key>0){
				map[x][y]=Hero.name[0];
				map[i][j]=32;
				key--;
		}
	}
	else if(map[x][y]==43){//��Ѫ�� ��+��43  Ѫ�����������Ѫ�� 
		map[x][y]=Hero.name[0];
		map[i][j]=32;
		Hero.boold =Hero.boold_max ;
	}
	else if(map[x][y]==42){
		if(MessageBox(NULL,"������","�Ƿ񹥻�",MB_YESNO)==IDYES){
		   if(PK(YAO)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//��'*' 42 
	else if(map[x][y]==66){
		if(MessageBox(NULL,"����ħ��","�Ƿ񹥻�",MB_YESNO)==IDYES){
		   if(PK(BOSS)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//ħ��BOSS'B'66 
	else if(map[x][y]==38){
		if(MessageBox(NULL,"������","�Ƿ񹥻�",MB_YESNO)==IDYES){
		   if(PK(GUI)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//�� &'  38
	 	else if(map[x][y]==36){
		if(MessageBox(NULL,"������","�Ƿ񹥻�",MB_YESNO)==IDYES){
		   if(PK(GUAI)==2){
		   	map[x][y]=Hero.name[0];
			map[i][j]=32;
		   }
		}
	}//�� $' 36
	else if(map[x][y]==47){//¥�� ��/��47 
		map[x][y]=Hero.name[0];
		map[i][j]=47;
		return 1;
	}
	else if(map[x][y]==92){//�ص���һ��ͼ��¥�� ��\'92 
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
			if(map[i][j]==Hero.name[0]){//�ҵ�Ӣ�� 
					switch(ch)//���̲���
					{
						case 'q' :{//�û��ֶ��˳���Ϸ 
							char wor[]="�ֶ��˳���Ϸ";	
							game_document_keep(wor); 
							exit(1);
						}
						case 'r':{//���� 
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
								}//�� 
			
						case 's':{
								switch(x_move(++i,j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//�� 
			
						case 'a':{
								switch(x_move(i,--j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//�� 
						case 'd':{
								switch(x_move(i,++j,map)){
									case 1:return 1;break;
									case 2:return 2;break;
								}
									break;
								}//�� 
					}					
		system("cls");
	for(i=0;i<10;i++){//������ͼ 
		for(j=0;j<20;j++){
			cout<<map[i][j];
		}
		cout<<endl;
					}
		clear();//���Ӣ�۵����Խ��м��		
				}
			}
		}
	}
}	
int main(){
	cout<<"��Ϸ���ܣ�"<<endl;
	cout<<"w s a d �ֱ�Ϊ���������ƶ�"<<endl;
	cout<<"'$','&','*'"<<"����"<<endl;
	cout<<"/ \ ¥��"<<" ,"<<"+ ��Ѫ��"<<" ,"<<"! Կ��"<<endl;
	cout<<"q �ֶ��˳���Ϸ"<<'\t'<<"r ��ȡ�浵"<<endl; 
	system("pause");
	system("cls"); 
	int i,j;		
c:	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			cout<<map1[i][j];
		}
		cout<<endl;//��ͼ10*20 
	}
	
	if(move(map1)==1){
		switch(move(map2)){
			case 2:{
			system("cls");
			goto c;
				break;
			}
			case 1:{
				char wor[]="˳��ͨ��"; 
				game_document_keep(wor); 
				cout<<"��ϲ��˳��ͨ��"<<endl;
				cout<<"�����ߣ�������"<<endl;
				system("pause");
				break;
			}
		}

	
	
}
	return 0;
}					   				   	
