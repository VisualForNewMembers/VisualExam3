#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#define num1 2
#define num2 13
#define num3 13
void drawmap(void);  //绘制地图
void keydown(void);  //进行按键交付
void start(void);    //游戏前进行提示
void shengji(void);  //进行升级处理
void fight(struct monster s);  //战斗处理
struct gamerole 
{
    int HP;                //生命值
    int Grade;             //等级
    int Defensivepower;    //防御力
    int aggressivity;      //攻击力
    int key;               //钥匙
    int experience;        //经验

};
struct monster 
{
    int HP;
    int Grade;
    int Defensivepower;
    int aggressivity;
    int experience;

};
struct gamerole uers = { 100,1,20,30,0,0};   //主角
struct monster Archmage={200,2,50,50,100};   //大魔王
struct monster Smallsoldier={40,1,10,20,50}; //小兵
struct monster dog={20,1,0,5,10};  //狗
struct monster bigsoldier{50,1,20,30,60};   //大兵

int k = 0;

int map[num1][num2][num3] =           //利用3维数组存储地图
{
    {
        {1,1,1,1,1,1,9,1,1,1,1,1,1},            
        {1,0,0,0,0,0,0,0,0,0,0,0,1},              
        {1,0,4,0,5,0,7,0,0,0,0,0,1},              
        {1,0,0,0,6,0,0,0,1,1,1,0,1},              
        {1,0,0,0,0,0,0,0,0,0,1,0,1},             
        {1,1,1,1,1,1,0,0,0,0,1,0,1},              
        {1,0,0,0,0,1,0,0,1,1,1,0,1},
        {1,7,0,5,0,1,0,0,6,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,1,1,1,3,1,0,1,1,1,1,1,1},
        {1,0,10,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,2,1,1,1,1,1,1},
    } ,

    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,11,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,0,0,1},
        {1,1,1,1,1,1,9,1,1,1,1,1,1},
    }
    
};

int main(void)
{
    start();
    system("CLS");
    while (1) {
        drawmap();
        keydown();
        shengji();
        system("CLS");
        if(map[1][5][6]!=11)
        {
            printf("恭喜你以通过");
            break;
        }
        
    }
    return 0;
}
               


void drawmap(void)      //绘制地图
{
    int i, j;
    printf("--------------------生命值：%d-----------------\n",uers.HP);
    printf("---------------------等级:%d-------------------\n", uers.Grade);
    printf("---------------------经验:%d-------------------\n", uers.experience);
    printf("--------------------防御力：%d------------------\n", uers.Defensivepower);
    printf("--------------------攻击力：%d------------------\n", uers.aggressivity);
    printf("--------------------钥匙数：%d------------------\n", uers.key);
    for(i=0;i<num2;i++)
    {
        for(j=0;j<num3;j++)
        {
            switch (map[k][i][j])
            {
            case 1:
                printf("*");
                break;
            case 0:
                printf(" ");
                break;
            case 2:
                printf("o");
                break;
            case 3:
                printf("D");
                break;
            case 4:
                printf("+");
                break;
            case 5:
                printf("`");
                break;
            case 6:
                printf("%%");
                break;
            case 7:
                printf("&");
                break;
            case 8:
                printf("/");
                break;
            case 9:
                printf("\\");
                break;
            case 10:
                printf("!");
                break;
            case 11:
                printf("B");
                break;

            }
            
        }
        printf("\n");


    }



}  
void keydown(void)    //处理按键输入
{
    int i, j;
    char uerkey;
    for(i=0;i<num2;i++)
    {
        for(j=0;j<num3;j++)
        {
            if (map[k][i][j] == 2)
                break;
        }
        if (map[k][i][j] == 2)
            break;
    }
    uerkey = _getch();
    switch (uerkey)
    {
    case 'W':
    case 'w':
        if (map[k][i - 1][j] == 0)  //在空地上行走
        {
            map[k][i][j] = 0;
            map[k][i - 1][j] = 2;
            
        }
        else if(map[k][i-1][j]==1)
        {
            map[k][i - 1][j] = map[k][i - 1][j];
            map[k][i][j] = map[k][i][j];
        }
        else if(map[k][i-1][j]==10)   //捡到钥匙
        {
            map[k][i - 1][j] = 2;
            map[k][i][j] = 0;
            uers.key++;
        }
        else if(map[k][i-1][j]==4) //捡到血包
        {
            map[k][i - 1][j] = 2;
            map[k][i][j] = 0;
            if (uers.HP < 100)
                uers.HP += 20;
        }
        else if(map[k][i-1][j]==6) //碰到敌人
        {
            fight(Smallsoldier);
            map[k][i - 1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i - 1][j] == 5) //碰到敌人
        {
            fight(dog);
            map[k][i - 1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i - 1][j] == 11) //碰到敌人
        {
            fight(Archmage);
            map[k][i - 1][j] = 2;
            map[k][i][j] = 0;
        }
        else if(map[k][i-1][j]==3)  //进门
        {
            if(uers.key>0)
            {
                map[k][i - 1][j] = 2;
                map[k][i][j] = 0;
                uers.key -= 1;
            }
        }
        else if(map[k][i-1][j]==7)
        {
            fight(bigsoldier);
            map[k][i - 1][j] = 2;
            map[k][i][j] = 0;
        }
        else if(map[k][i-1][j]=8)
        {
            k = 1;
        }
        break;

    case 'A':
    case 'a':
        if (map[k][i][j - 1] == 0)
        {
            map[k][i][j - 1] = 2;
            map[k][i][j] = 0;
            
        }
        else if (map[k][i][j-1] == 10)   //捡到钥匙
        {
            map[k][i][j-1] = 2;
            map[k][i][j] = 0;
            uers.key++;
        }
        else if (map[k][i][j-1] == 4) //捡到血包
        {
            map[k][i][j-1] = 2;
            map[k][i][j] = 0;
            if (uers.HP < 100)
                uers.HP += 20;
        }
        else if (map[k][i][j-1] == 6) //碰到敌人
        {
            fight(Smallsoldier);
            map[k][i][j-1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j-1] == 5) //碰到敌人
        {
            fight(dog);
            map[k][i][j-1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j-1] == 11) //碰到敌人
        {
            fight(Archmage);
            map[k][i][j-1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j-1] == 3)  //进门
        {
            if (uers.key > 0)
            {
                map[k][i][j-1] = 2;
                map[k][i][j] = 0;
                uers.key -= 1;
            }
        }
        else if (map[k][i][j-1] == 7)
        {
            fight(bigsoldier);
            map[k][i][j-1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j-1] == 1)
        {
            map[k][i][j-1] = map[k][i][j-1];
            map[k][i][j] = map[k][i][j];
        }
        break;
    case 'S':
    case 's':
        if(map[k][i+1][j] == 0)
        {
            map[k][i + 1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i + 1][j] == 1)
        {
            map[k][i + 1][j] = map[k][i+1][j];
            map[k][i][j] = map[k][i][j];
        }
        else if (map[k][i+1][j] == 10)   //捡到钥匙
        {
            map[k][i+1][j] = 2;
            map[k][i][j] = 0;
            uers.key++;
        }
        else if (map[k][i+1][j] == 4) //捡到血包
        {
            map[k][i+1][j] = 2;
            map[k][i][j] = 0;
            if (uers.HP < 100)
                uers.HP += 20;
        }
        else if (map[k][i+1][j] == 6) //碰到敌人
        {
            fight(Smallsoldier);
            map[k][i+1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i+1][j] == 5) //碰到敌人
        {
            fight(dog);
            map[k][i+1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i+1][j] == 11) //碰到敌人
        {
            fight(Archmage);
            map[k][i+1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i+1][j] == 3)  //进门
        {
            if (uers.key > 0)
            {
                map[k][i+1][j] = 2;
                map[k][i][j] = 0;
                uers.key -= 1;
            }
        }
        else if (map[k][i+1][j] == 7)
        {
            fight(bigsoldier);
            map[k][i+1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i+1][j] = 9)
        {
            k = 0;
            break;
        }
        break;
    case 'D':
    case 'd':
        if(map[k][i][j+1] == 0)
        {
            map[k][i][j + 1] = 2;
            map[k][i][j] = 0;
           
        }
        else if (map[k][i][j+1] == 10)   //捡到钥匙
        {
            map[k][i][j + 1] = 2;
            map[k][i][j] = 0;
            uers.key++;
        }
        else if (map[k][i][j+1] == 4) //捡到血包
        {
            map[k][i][j+1] = 2;
            map[k][i][j] = 0;
            if (uers.HP < 100)
                uers.HP += 20;
        }
        else if (map[k][i][j+1] == 6) //碰到敌人
        {
            fight(Smallsoldier);
            map[k][i][j+1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j+1] == 5) //碰到敌人
        {
            fight(dog);
            map[k][i][j+1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j+1] == 11) //碰到敌人
        {
            fight(Archmage);
            map[k][i + 1][j] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j+1] == 3)  //进门
        {
            if (uers.key > 0)
            {
                map[k][i + 1][j] = 2;
                map[k][i][j] = 0;
                uers.key -= 1;
            }
        }
        else if (map[k][i][j+1] == 7)
        {
            fight(bigsoldier);
            map[k][i][j+1] = 2;
            map[k][i][j] = 0;
        }
        else if (map[k][i][j+1] == 1)
        {
            map[k][i+1][j] = map[k][i+1][j];
            map[k][i][j] = map[k][i][j];
        }
        break;

    }

} //处理按键输入
void inputmonster(void)   //初始化怪物
{

}
void start(void)
{
    printf("欢迎来到魔塔\n");
    printf("使用wasd进行移动\n");
    system("pause");
}
void shengji(void)
{
    int y;
    while (1) {
        if (uers.experience >= 50)
        {
            uers.Grade += 1;
            uers.HP += 20;
            uers.aggressivity += 10;
            uers.Defensivepower += 5;
            uers.experience -= 50;
        }
        else if(uers.experience<50)
        {
            break;
        }
    }
}
void fight(struct monster s)
{
    int zhong1 = 0;  //怪物的总攻击
    int zhong = 0;   //主角的总攻击
    int guding= 20;  //主角的基础伤害
    int guding1 = 5; //怪物的基础伤害
    int jichu1 = s.aggressivity - uers.HP;
    int jichu = uers.aggressivity - s.Defensivepower;
    while (1) {
        if (jichu <= 0)
        {
            zhong = guding;
            s.HP -= zhong;
        }
        else if (jichu > 0)
        {
            zhong = guding + jichu;
            s.HP -= zhong;
        }
        if (s.HP < 0)
        {
            uers.experience += s.experience;
            break;
        }
        if(jichu1<0)
        {
            zhong1 = guding1;
            uers.HP -= zhong1;
        }
        if(jichu1>0)
        {
            zhong1 = guding1 + jichu1;
            uers.HP -= zhong1;
        }
        if(uers.HP<10)
        {
            printf("菜");
            break;
        }

    }








}