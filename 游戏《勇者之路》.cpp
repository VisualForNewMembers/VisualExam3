#include<iostream>
#include<stdlib.h>
#include<conio.h> 
#include<windows.h>
#include<fstream>
using namespace std;

#define ESC 27           
		               
int gameover=0; //�ж���Ϸ���� 
 
struct hunter{
	int hp=100;        //�������ߵĳ�ʼѪ��(health point) 
	int max=100;       //�������ߵĳ�ʼ���Ѫ��  
	int lv=1;          //�������ߵĳ�ʼ�ȼ�(level)
	int atk=30,def=20; //�������ߵĳ�ʼ������(attack),������(defence)
	int exp=0;         //�������ߵĳ�ʼ����ֵ(experience)
	int key=0;         //�������ߵĳ�ʼԿ������ 
	int i,j;           //���ߵ�λ�� 
}fighter;

struct ganster{
	int h,a,d;
};//��������� 

ganster monster[3]={{30,25,10},{60,30,20},{90,35,30}};

ganster boss={150,100,50};

int cas=0; //��ͼ�� 
                                      
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
//�����ǵ�ͼ������ "0"�ǵ�ͼ�߽磬1"��ǽ��"2"��·��"3"�ǻ�Ѫ�㣬"4"������(����Ҳ����"5"���������)��
//"6"����¥�ݣ�"7"����¥�ݣ�"8"��Կ�ף�"9"�����ϵ��š�"10","11","12"�ǹ��"13"������boss�� 


void gotoxy(unsigned char x,unsigned char y)
{    
    COORD cor;  
    HANDLE hout;   
    cor.X = x;
    cor.Y = y;
    hout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hout, cor);   
}


int foreword()
{
    cout<<"����һ������\n����̽����ͼ�и���飨�ƶ��Թ���������أ��ر��⣬����ɭ�֣�ħ���������С�֣����ħ����\n";
    cout<<"\033[47;36;5m!\033[0m��Կ�ף�\033[47;36mD\033[0m���ţ�\033[47;34m/\033[0m����¥�ݣ�\033[47;34m\\\033[0m����¥�ݣ�";
	cout<<"\033[47;32m%\033[0m:ʷ��ķ��\033[47;33m&\033[0m���ҽ��ޣ�\033[47;31m~\033[0m��������ʿ��\033[47;35mB\033[0m��ħ��\n"; 
    cout<<"��f��:ȷ�ϼ�����g����ȡ��������ESC�����˳������˳�ʱ�浵��\n\n"; 
}  


int load() //���� 
{
	int way;
	int load;
	cout<<"������Ϸ�밴��1��\n  ����Ϸ�밴��2��\n";
	cin>>way;	
	if(way==2)
	{
	    return 0; 
	}
	else if(way==1) 
	{
	    for(int w=0;w<5;w++)
	    {
	    	cout<<"�浵"<<w+1<<"\n";
		}
		cout<<"ѡ����Ŷ�����";
		cin>>load;
	    ifstream mem;
	    switch(load)
	    {
	    	case 1:
	    	mem.open("�浵1.txt", ios::in);break;
	        case 2:
			mem.open("�浵2.txt", ios::in);break;
			case 3:
			mem.open("�浵3.txt", ios::in);break;
			case 4:
			mem.open("�浵4.txt", ios::in);break;	
			case 5:
			mem.open("�浵5.txt", ios::in);break;
		}	
		if (!mem.is_open())
	    {
	        cout<<"file open failed\n"; 
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


void save() //�浵 
{ 
    int save;
    for(int w=0;w<5;w++)
    {
    	cout<<"�浵"<<w+1<<endl;
	}
	cout<<"ѡ����Ŵ浵��";
	cin>>save;
    ofstream mem;
    switch(save)
    {
    	case 1:
        mem.open("�浵1.txt",ios::out);break;
        case 2:
		mem.open("�浵2.txt",ios::out);break;
		case 3:
		mem.open("�浵3.txt",ios::out);break;
		case 4:
		mem.open("�浵4.txt",ios::out);break;	
		case 5:
	    mem.open("�浵5.txt",ios::out);break;
	}
    if (!mem.is_open())
    {
        cout<<"file open failed\n"; 
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


void drawstate()//������״̬�ĺ���
{
	cout<<"    Ѫ��:"<<fighter.hp<<"     "<<endl;
	cout<<"    �ȼ�:"<<fighter.lv<<"     "<<endl;
	cout<<"  ������:"<<fighter.atk<<"     "<<endl;
	cout<<"  ������:"<<fighter.def<<"     "<<endl;
	cout<<"  ����ֵ:"<<fighter.exp<<"     "<<endl;
	cout<<"Կ������:"<<fighter.key<<"     "<<endl; 
	cout<<"  λ�� x:"<<fighter.j+1<<"     "<<endl;
    cout<<"       y:"<<25-fighter.i<<"     "<<endl;   
}


void initmap() //��ʼ����ͼ 
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
		            cout<<"\033[100;34m#\033[0m";break;     //��ͼ�߽���"#"��ʾ 
    	        	case 1:
    	            case 22: 
		        	cout<<"\033[;100m \033[0m";break;       //ǽ��"*"��ʾ 
    	            case 2:
		        	cout<<"\033[47;37m \033[0m";break;      //·��" "��ʾ 
	    	    	case 3:
	        		cout<<"\033[47;31m+\033[0m";break;      //��Ѫ��"+"��ʾ 
	        		case 4:
		        	case 5:
		        	cout<<"\033[47;31mo\033[0m";break;      //������"o"��ʾ 
		        	case 6:
		        	cout<<"\033[47;34m/\033[0m";break;      //��¥����"/"��ʾ 
		        	case 7:      
		        	cout<<"\033[47;34m\\\033[0m";break;     //��¥����"\"��ʾ 
		        	case 8: 
		        	cout<<"\033[47;36;5m!\033[0m";break;    //Կ����"!"��ʾ
					case 9: 
		        	cout<<"\033[47;36mD\033[0m";break;      //����"D"��ʾ 
		         	case 10:
		        	cout<<"\033[47;32m%\033[0m";break;     //����"%"��ʾ 
		        	case 11:
		        	cout<<"\033[47;33m&\033[0m";break;      //����"&"��ʾ 
		        	case 12:
		        	cout<<"\033[47;31m~\033[0m";break;      //����"~"��ʾ
                    case 13:
		        	cout<<"\033[47;35mB\033[0m";break;      //ħ����"B"��ʾ 
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
		            cout<<"\033[100;34m#\033[0m";break;     //��ͼ�߽���"#"��ʾ 
    	        	case 1:
		        	cout<<"\033[;100m \033[0m";break;       //ǽ��"*"��ʾ 
    	            case 2:
		        	cout<<"\033[47;37m \033[0m";break;      //·��" "��ʾ 
	    	    	case 3:
	        		cout<<"\033[47;31m+\033[0m";break;      //��Ѫ��"+"��ʾ 
	        		case 4:
		        	case 5: 
		        	cout<<"\033[47;31mo\033[0m";break;      //������"o"��ʾ 
		        	case 6:
		        	cout<<"\033[47;34m/\033[0m";break;      //��¥����"/"��ʾ 
		        	case 7:      
		        	cout<<"\033[47;34m\\\033[0m";break;     //��¥����"\"��ʾ 
		        	case 8: 
		        	cout<<"\033[47;36;5m!\033[0m";break;    //Կ����"!"��ʾ
					case 9: 
		        	cout<<"\033[47;36mD\033[0m";break;      //����"D"��ʾ 
		         	case 10:
		        	cout<<"\033[47;32m%\033[0m";break;     //����"%"��ʾ 
		        	case 11:
		        	cout<<"\033[47;33m&\033[0m";break;      //����"&"��ʾ 
		        	case 12:
		        	cout<<"\033[47;31m~\033[0m";break;      //����"~"��ʾ
                    case 13:
		        	cout<<"\033[47;35mB\033[0m";break;      //ħ����"B"��ʾ 
	            }
		    }
		    cout<<endl;
	    }
		for(int w=13;w<24;w++)
		{
	    	cout<<("\033[100;34m#\033[0m"); 
	    	cout<<("\033[0;100m \033[0m");
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
		            cout<<"\033[100;34m#\033[0m";break;     //��ͼ�߽���"#"��ʾ 
    	        	case 1:
		        	cout<<"\033[43;32m*\033[0m";break;      //ǽ��"*"��ʾ 
    	            case 2:
		        	cout<<"\033[43;33m \033[0m";break;      //·��" "��ʾ 
	    	    	case 3:
	        		cout<<"\033[43;31m+\033[0m";break;      //��Ѫ��"+"��ʾ 
	        		case 4:
		        	case 5: 
		        	cout<<"\033[43;31mo\033[0m";break;      //������"o"��ʾ 
		        	case 6:
		        	cout<<"\033[43;34m/\033[0m";break;      //��¥����"/"��ʾ 
		        	case 7:      
		        	cout<<"\033[43;34m\\\033[0m";break;     //��¥����"\"��ʾ 
		        	case 8: 
		        	cout<<"\033[43;36;5m!\033[0m";break;    //Կ����"!"��ʾ
					case 9: 
		        	cout<<"\033[43;36mD\033[0m";break;      //����"D"��ʾ 
		         	case 10:
		        	cout<<"\033[43;32m%\033[0m";break;     //����"%"��ʾ 
		        	case 11:
		        	cout<<"\033[43;33m&\033[0m";break;      //����"&"��ʾ 
		        	case 12:
		        	cout<<"\033[43;31m~\033[0m";break;      //����"~"��ʾ
                    case 13:
		        	cout<<"\033[43;35mB\033[0m";break;      //ħ����"B"��ʾ 
		            }
		        }
			    else 
			    {
	    	    	cout<<" ";
		        }
			}
			cout<<("\033[0;100m \033[0m");
			cout<<("\033[100;34m#\033[0m\n"); 
		}
	    for(int w=0;w<50;w++)
		{
		    cout<<"\033[100;34m#\033[0m"; 	
		}
		cout<<endl;
	} 
	gotoxy(0,0);
}


void drawmap_1(int *p) //��ͨ�ĸı��ͼ 
{
	switch(*p)
	{
	    case 0:
	    cout<<"\033[100;34m#\033[0m";break;     //��ͼ�߽���"#"��ʾ 
	  	case 1:
	    case 22: 
	   	cout<<"\033[;100m \033[0m";break;       //ǽ��"*"��ʾ 
	    case 2:
	   	cout<<"\033[47;37m \033[0m";break;      //·��" "��ʾ 
	  	case 3:
		cout<<"\033[47;31m+\033[0m";break;      //��Ѫ��"+"��ʾ 
		case 4:
		case 5:
	   	cout<<"\033[47;31mo\033[0m";break;      //������"o"��ʾ 
	   	case 6:
	 	cout<<"\033[47;34m/\033[0m";break;      //��¥����"/"��ʾ 
		case 7:      
	 	cout<<"\033[47;34m\\\033[0m";break;     //��¥����"\"��ʾ 
		case 8: 
	   	cout<<"\033[47;36;5m!\033[0m";break;    //Կ����"!"��ʾ
		case 9: 
	 	cout<<"\033[47;36mD\033[0m";break;      //����"D"��ʾ 
	 	case 10:
	 	cout<<"\033[47;32m%\033[0m";break;     //����"%"��ʾ 
	   	case 11:
	   	cout<<"\033[47;33m&\033[0m";break;      //����"&"��ʾ 
	    case 12:
	   	cout<<"\033[47;31m~\033[0m";break;      //����"~"��ʾ
	    case 13:
	   	cout<<"\033[47;35mB\033[0m";break;      //ħ����"B"��ʾ 
	}
}


void drawmap_2() //����ɭ���еĸı��ͼ 
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
				        cout<<"\033[100;34m#\033[0m";break;     //��ͼ�߽���"#"��ʾ 
				    	case 1:
				    	cout<<"\033[43;32m*\033[0m";break;      //ǽ��"*"��ʾ 
				        case 2:
				    	cout<<"\033[43;33m \033[0m";break;      //·��" "��ʾ 
				    	case 3:
						cout<<"\033[43;31m+\033[0m";break;      //��Ѫ��"+"��ʾ 
						case 4:
				    	case 5: 
				    	cout<<"\033[43;31mo\033[0m";break;      //������"o"��ʾ 
				    	case 6:
				    	cout<<"\033[43;34m/\033[0m";break;      //��¥����"/"��ʾ 
				    	case 7:      
				    	cout<<"\033[43;34m\\\033[0m";break;     //��¥����"\"��ʾ 
				    	case 8: 
				    	cout<<"\033[43;36;5m!\033[0m";break;    //Կ����"!"��ʾ
						case 9: 
				    	cout<<"\033[43;36mD\033[0m";break;      //����"D"��ʾ 
				     	case 10:
				    	cout<<"\033[43;32m%\033[0m";break;     //����"%"��ʾ 
				    	case 11:
				    	cout<<"\033[43;33m&\033[0m";break;      //����"&"��ʾ 
				    	case 12:
				    	cout<<"\033[43;31m~\033[0m";break;      //����"~"��ʾ
				        case 13:
				    	cout<<"\033[43;35mB\033[0m";break;      //ħ����"B"��ʾ 
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

void drawmap_3() //�ƶ��Թ��еĸı��ͼ 
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
		    	"\033[47;31mo\033[0m";
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
		    	"\033[47;31mo\033[0m";
			}
		}	
	}		
} 


void search() //Ѱ�����ߵĺ��� 
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
	}  //�ҳ�����
}


void type() //�ܱ߹�������� 
{
	int typefind=0;
	if(map[cas][fighter.i-1][fighter.j-1]==10||map[cas][fighter.i][fighter.j-1]==10||map[cas][fighter.i+1][fighter.j-1]==10||map[cas][fighter.i-1][fighter.j]==10||
	map[cas][fighter.i+1][fighter.j]==10||map[cas][fighter.i-1][fighter.j+1]==10||map[cas][fighter.i][fighter.j+1]==10||map[cas][fighter.i+1][fighter.j+1]==10)
	{
	    cout<<"�Ա�����ɫ�ġ�ʷ��ķ��(С��)   \nѪ����"<<monster[0].h<<" ��������"<<monster[0].a<<" ��������"<<monster[0].d<<endl;
		typefind=1; 
	}
	else if(map[cas][fighter.i-1][fighter.j-1]==11||map[cas][fighter.i][fighter.j-1]==11||map[cas][fighter.i+1][fighter.j-1]==11||map[cas][fighter.i-1][fighter.j]==11||
	map[cas][fighter.i+1][fighter.j]==11||map[cas][fighter.i-1][fighter.j+1]==11||map[cas][fighter.i][fighter.j+1]==11||map[cas][fighter.i+1][fighter.j+1]==11)
	{
		cout<<"�Ա��л�ɫ�ġ��ҽ��ޡ�(С��)  \nѪ����"<<monster[1].h<<" ��������"<<monster[1].a<<" ��������"<<monster[1].d<<endl;
		typefind=1;
	}
	else if(map[cas][fighter.i-1][fighter.j-1]==12||map[cas][fighter.i][fighter.j-1]==12||map[cas][fighter.i+1][fighter.j-1]==12||map[cas][fighter.i-1][fighter.j]==12||
	map[cas][fighter.i+1][fighter.j]==12||map[cas][fighter.i-1][fighter.j+1]==12||map[cas][fighter.i][fighter.j+1]==12||map[cas][fighter.i+1][fighter.j+1]==12)
	{
		cout<<"�Ա��к�ɫ�ġ�������ʿ��(С��)\nѪ����"<<monster[1].h<<" ��������"<<monster[1].a<<" ��������"<<monster[1].d<<endl;
		typefind=1;
	}
	else if(map[cas][fighter.i-1][fighter.j-1]==13||map[cas][fighter.i][fighter.j-1]==13||map[cas][fighter.i+1][fighter.j-1]==13||map[cas][fighter.i-1][fighter.j]==13||
	map[cas][fighter.i+1][fighter.j]==13||map[cas][fighter.i-1][fighter.j+1]==13||map[cas][fighter.i][fighter.j+1]==13||map[cas][fighter.i+1][fighter.j+1]==13)
	{
		cout<<"�Ա�����ɫ�ġ�ħ������boss��  \nѪ����<<boss.h<< ��������<<boss.a<< ��������boss.d\n";
		typefind=1;
	}
	else if(!typefind)
	{
		cout<<"�Ա�û�й�                    \n                                                                              \n"; 
	}
	else
	{
		cout<<"                              \n                                                                              \n";
	}
}


void location() //��ҵ�ǰ��λ�� 
{
	if((fighter.i>1&&fighter.i<7)&&(fighter.j>2&&fighter.j<20))
	{
		cout<<"�����ڹ���Ļ���\n��ܹ��ﲢͨ������ȥ������Ĳر���ɣ�\n\033[40;31m���ر�������ͨ������ɭ�ֵ�Կ�ף�\033[0m       \n"; 
	}
	else if((fighter.i>7&&fighter.i<15)&&(fighter.j>2&fighter.j<16))
	{
		cout<<"�����ڲر���    \n��ȥ��ͨ������ɭ�ֵ�Կ�ף�            \n                                                           \n"; 
	}
	else if(cas==0&&(fighter.i>1&&fighter.i<7)&&(fighter.j>20&fighter.j<29))
	{
		cout<<"������ħ����    \n��ȥ���ħ���ɣ�                      \n                                                           \n";
	}
	else if(cas==0&&(fighter.i>16&&fighter.i<23)&&(fighter.j>2&fighter.j<16))
	{
		cout<<"�������ƶ��Թ�  \n������ٲ����ޣ��ɱ�ǽѹ���ˣ�      \n\033[40;31m���ƶ��Թ��ڲ������õ���������ص�Կ�ף�\033[0m \n"; 
	}
	else if(cas==1&&(fighter.i>12&&fighter.i<24)&&(fighter.j>0&&fighter.j<49))
	{
		cout<<"����������ɭ��  \nĨ��ǰ�в��ҵ�ͨ��ħ�����·�ɣ�      \n                                                           \n"; 
	}
	else
	{
        cout<<"                \n                                      \n                                                           \n";		
    }	 
}


int interaction(int num) //����ʱ�Ľ��� 
{
	switch(num)
    {
        case 6:
		cout<<"�Ƿ���¥��\n����f��ȷ�ϣ���������ȡ��\n";break; 
		case 7:
		cout<<"�Ƿ���¥��\n����f��ȷ�ϣ���������ȡ��\n";break; 
		case 9:
		if(fighter.key)
		{
    		cout<<"����"<<fighter.key<<"��Կ��,�Ƿ�ʹ��һ�ѿ���\n����f����ȷ�ϣ���������ȡ��\n";break;
        }
		else
    	{
		    cout<<"������û��Կ��\n����f������\n";break; 
	    }
		case 10:
    	case 11:
    	case 12:
    	cout<<"�Ƿ�͹��ｻս\n����f��ȷ�ϣ���������ȡ��\n";break; 	
		case 13:
		cout<<"�Ƿ��ħ����ս\n����f��ȷ�ϣ���������ȡ��\n";break;        
	}
	char one=getch();
	gotoxy(0,47);
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


void addhp() //��Ѫ�ĺ��� 
{
	fighter.hp+=999;
	if(fighter.hp>fighter.max)
	{
	fighter.hp=fighter.max;
    }
}


void upgrade() //�����ĺ���
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


void battle(int *p) //ս���ĺ��� 
{   //x�ǹ̶��˺�,y�ǻ����˺�,z�����˺� 
    int h_1=monster[0].h;
    int h_2=monster[1].h;
    int h_3=monster[2].h;
    int h_4=boss.h;
	int x1,y1,z1; //�������ߵ����� 
	int x2,y2,z2; //����ֵ����� 
    switch(*p)
    {
        case 10:
		x1=20; y1=fighter.atk-monster[0].d; z1=x1+y1; //���ߵĹ������� 
        x2=20; y2=monster[0].a-fighter.def; z2=x2+y2; //һ�ŹֵĹ�������
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
		x1=20;y1=fighter.atk-monster[1].d;z1=x1+y1; //���ߵĹ�������
		x2=20;y2=monster[1].a-fighter.def;z2=x2+y2; //���ŹֵĹ�������
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
		x1=20; y1=fighter.atk-monster[2].d; z1=x1+y1; //���ߵĹ������� 
        x2=20; y2=monster[2].a-fighter.def; z2=x2+y2; //���ŹֵĹ�������
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
		x1=20; y1=fighter.atk-boss.d; z1=x1+y1; //���ߵĹ������� 
        x2=20; y2=boss.a-fighter.def; z2=x2+y2; //ħ���Ĺ�������
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


void keydown() //�ٿ������ƶ� 
{
	
    int keydown=getch();
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
	        if(map[cas][fighter.i-1][fighter.j]==2||map[cas][fighter.i-1][fighter.j]==3) //�ж�ǰ���Ƿ�Ϊ·���Ѫ�� 
		    { 
	
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i-1][fighter.j]+=2;
		        if(map[cas][fighter.i-1][fighter.j]==5)
		        {
		            addhp();
		        }
	        }
	        else
			if(map[cas][fighter.i-1][fighter.j]==6||map[cas][fighter.i-1][fighter.j]==7) //�ж�ǰ���Ƿ�Ϊ¥�� 
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
			if(map[cas][fighter.i-1][fighter.j]==8) //�ж�ǰ���Ƿ���Կ�� 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i-1][fighter.j]-=4;
		        fighter.key+=1;
			} 
			else 
			if(map[cas][fighter.i-1][fighter.j]==9) //�ж�ǰ���Ƿ����� 
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
			if(map[cas][fighter.i-1][fighter.j]==22) //�ж�ǰ���Ƿ�Ϊ�ƶ���ǽ 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i-1][fighter.j]==10||map[cas][fighter.i-1][fighter.j]==11||map[cas][fighter.i-1][fighter.j]==12||map[cas][fighter.i-1][fighter.j]==13) //�ж�ǰ���Ƿ�Ϊ�ֻ�ħ��
			{
	            if(interaction(map[cas][fighter.i-1][fighter.j])==1)
	            {
			        battle(&map[cas][fighter.i-1][fighter.j]);
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i-1>12&&fighter.i-1<24&&fighter.j>0&&fighter.j<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 
			{
				gotoxy(fighter.j,fighter.i+10);
			    drawmap_1(&map[cas][fighter.i-1][fighter.j]);
			}		
			break;
	        case 'S':
	        case 's':
	        if(map[cas][fighter.i+1][fighter.j]==2||map[cas][fighter.i+1][fighter.j]==3) //�жϺ����Ƿ�Ϊ·���Ѫ�� 
	        {
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i+1][fighter.j]+=2;
		        if(map[cas][fighter.i+1][fighter.j]==5)
		        {
		            addhp();
		        }
	        }
			else
			if(map[cas][fighter.i+1][fighter.j]==6||map[cas][fighter.i+1][fighter.j]==7) //�жϺ����Ƿ�Ϊ¥�� 
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
			if(map[cas][fighter.i+1][fighter.j]==8) //�жϺ����Ƿ���Կ�� 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i+1][fighter.j]-=4;
		        fighter.key+=1;
			} 
			else 
			if(map[cas][fighter.i+1][fighter.j]==9) //�жϺ����Ƿ����� 
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
			if(map[cas][fighter.i+1][fighter.j]==22) //�жϺ����Ƿ�Ϊ�ƶ���ǽ 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i+1][fighter.j]==10||map[cas][fighter.i+1][fighter.j]==11||map[cas][fighter.i+1][fighter.j]==12||map[cas][fighter.i+1][fighter.j]==13) //�жϺ����Ƿ�Ϊ�ֻ�ħ�� 
		    {
		    	if(interaction(map[cas][fighter.i+1][fighter.j])==1)
		    	{
			        battle(&map[cas][fighter.i+1][fighter.j]); 
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i+1>12&&fighter.i+1<24&&fighter.j>0&&fighter.j<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 
			{
				gotoxy(fighter.j,fighter.i+12);
			    drawmap_1(&map[cas][fighter.i+1][fighter.j]);
			}
			break;
	        case 'A':
	        case 'a':
	        if(map[cas][fighter.i][fighter.j-1]==2||map[cas][fighter.i][fighter.j-1]==3) //�ж�����Ƿ�Ϊ·���Ѫ�� 
	        {
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j-1]+=2;
		        if(map[cas][fighter.i][fighter.j-1]==5)
		        {
		            addhp();
		        }
	        }
			else
			if(map[cas][fighter.i][fighter.j-1]==6||map[cas][fighter.i][fighter.j-1]==7) //�ж�����Ƿ�Ϊ¥�� 
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
			if(map[cas][fighter.i][fighter.j-1]==8) //�ж�����Ƿ���Կ�� 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j-1]-=4;
		        fighter.key+=1;
			} 
			else 
			if(map[cas][fighter.i][fighter.j-1]==9) //�ж�����Ƿ����� 
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
			if(map[cas][fighter.i][fighter.j-1]==22) //�ж�����Ƿ�Ϊ�ƶ���ǽ 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i][fighter.j-1]==10||map[cas][fighter.i][fighter.j-1]==11||map[cas][fighter.i][fighter.j-1]==12||map[cas][fighter.i][fighter.j-1]==13) //�ж�����Ƿ�Ϊ�ֻ�ħ��
			{ 
			    if(interaction(map[cas][fighter.i][fighter.j-1])==1)
			    {
			    	battle(&map[cas][fighter.i][fighter.j-1]); 
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j-1>0&&fighter.j-1<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 
			{
				gotoxy(fighter.j-1,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j-1]);
			}
			break;
	        case 'D':
	        case 'd':
	        if(map[cas][fighter.i][fighter.j+1]==2||map[cas][fighter.i][fighter.j+1]==3) //�ж��ұ��Ƿ�Ϊ·���Ѫ�� 
	        {
		        map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j+1]+=2;
		        if(map[cas][fighter.i][fighter.j+1]==5) 
		        {
		            addhp();
		        }
	        }
			else
			if(map[cas][fighter.i][fighter.j+1]==6||map[cas][fighter.i][fighter.j+1]==7) //�ж��ұ��Ƿ�Ϊ¥�� 
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
			if(map[cas][fighter.i][fighter.j+1]==8) //�ж��ұ��Ƿ���Կ�� 
			{
				map[cas][fighter.i][fighter.j]-=2;
		        map[cas][fighter.i][fighter.j+1]-=4;
		        fighter.key+=1;
			} 
			else
			if(map[cas][fighter.i][fighter.j+1]==9) //�ж��ұ��Ƿ����� 
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
			if(map[cas][fighter.i][fighter.j+1]==22) //�ж��ұ��Ƿ�Ϊ�ƶ���ǽ 
			{
				gameover=3;
			}
	        else 
			if(map[cas][fighter.i][fighter.j+1]==10||map[cas][fighter.i][fighter.j+1]==11||map[cas][fighter.i][fighter.j+1]==12||map[cas][fighter.i][fighter.j+1]==13) //�ж��ұ��Ƿ�Ϊ�ֻ�ħ��
			{
				if(interaction(map[cas][fighter.i][fighter.j+1])==1)
				{
			    	battle(&map[cas][fighter.i][fighter.j+1]); 
			    }
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j>0&&fighter.j<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 		
			{
			    gotoxy(fighter.j,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j]);
			}
	        if(!(cas==1&&fighter.i>12&&fighter.i<24&&fighter.j+1>0&&fighter.j+1<49)) //���ڡ�����ɭ�֡�ʱ�ĵ�ͼˢ�� 
			{
				gotoxy(fighter.j+1,fighter.i+11);
			    drawmap_1(&map[cas][fighter.i][fighter.j+1]);
			}
			break;
	    }
    }
}


void changemap() //�ı��ͼ���ƶ��Թ����ĺ��� 
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


void judge() //�ж������Ƿ��ƶ��Թ��е�ǽѹ��ĺ��� 
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
	system("mode con cols=100 lines=100");
	foreword(); 
	Sleep(2000);  
    cout<<"��Ϸ��ʼ��\n\n";   
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
		    cout<<"������'w''s''a''d'�������߽����������ҵ��ƶ�\n";          
		    cout<<"--------------------\n";                                          
		    cout<<"��ͼ:\n"; 
		    drawmap_3();
			changemap();                                                       
			gotoxy(0,36);
			cout<<"ע��ͼ���½�Ϊԭ�㣬��Ϊ x ����������Ϊ y ��������\n\n";
			cout<<"HUD��\n\n";
			type(); 
			cout<<endl; 
			location();
			cout<<endl; 
			keydown();                                                       
			judge();                                                         
			upgrade();  			                                                     
			gotoxy(0,0);
		}
		system("cls");
		initmap();
		while(cas==1&&gameover==0) 
	   	{
			search();                                                          
		    drawstate();                                                        
		    cout<<"������Ļ������'w''s''a''d'�������߽����������ҵ��ƶ�\n";          
		    cout<<"--------------------\n";                                          
		    cout<<"��ͼ:\n"; 
		    drawmap_2();
			changemap();                                                      
			gotoxy(0,36);
			cout<<"ע��ͼ���½�Ϊԭ�㣬��Ϊ x ����������Ϊ y ��������\n\n";
			cout<<"HUD��\n\n";
			type(); 
			cout<<endl; 
			location();
			cout<<endl; 
			keydown();                                                                                                              
		 	upgrade(); 		                                                     
			gotoxy(0,0);
		}
		system("cls");
	}
	if(gameover==1)
	{ 
	    cout<<"�㱻��ɱ���ˣ�������Ҫ���٣�����һ�ΰ�";
    }
	else if(gameover==2)
	{
	    cout<<"W I N !!!\n��ϲ���������ս\n��Ϸ�����ˣ������Ҫ�����������Ǽ����ԡ����ߡ�����ݿ˷�ÿһ����ս��\n\n\n�Ӿ�������������\n\n\n��Ϸ������������\n��Ϸ���⣺������";	
    }
    else if(gameover==3)
    {
    	cout<<"�㱻ǽѹ���ˣ������´�ҪС��Ŷ";
	}
	
	return 0;
}
