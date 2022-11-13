#define _CRT_SECURE_NO_WARNINGS 2
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <fstream>
//创建地图，使用三维数组方便关卡的转换
void dd();
void cd();
char map[2][13][13]= {
                        { 42,42,42,42,42,42,43,42,42,42,42,42,42,
                          42,47,32,32,32,32,68,32,32,32,43,33,42,
                          42,42,42,68,42,42,126,42,42,42,68,42,42,
                          42,33,38,32,32,42,32,42,126,32,32,32,42,
                          42,37,32,32,32,68,32,68,32,32,32,38,42,
                          42,32,32,32,37,42,32,42,32,32,126,43,42,
                          42,42,42,68,42,42,32,42,42,42,68,42,42,
                          42,32,32,32,32,42,32,42,32,37,32,32,42,
                          42,32,32,32,32,42,32,42,32,126,32,38,42,
                          42,37,32,32,32,42,32,42,126,33,37,37,42,
                          42,33,38,32,32,42,68,42,37,32,32,32,42,
                          42,42,42,42,42,33,32,33,42,42,42,42,42,
                          42,42,42,42,42,32,79,32,42,42,42,42,42
                        },
                        { 42,42,42,42,42,42,42,42,42,42,42,42,42,
                          42,92,42,33,32,37,32,33,42,32,38,32,42,
                          42,32,42,32,126,32,32,37,42,32,33,32,42,
                          42,32,42,42,42,68,42,42,42,32,32,32,42,
                          42,37,42,32,126,32,32,32,32,32,32,32,42,
                          42,32,68,32,32,42,42,42,42,42,32,32,42,
                          42,32,42,32,32,42,43,66,43,42,32,32,42,
                          42,126,42,42,42,42,38,38,38,42,42,68,42,
                          42,32,42,126,32,42,32,32,32,42,32,32,42,
                          42,38,68,32,32,32,37,33,32,42,126,38,42,
                          42,32,42,126,32,32,33,32,32,42,33,43,42,
                          42,42,42,42,42,42,42,42,42,42,42,42,42, }
};
//定义勇者与怪物
struct Role
{
    int xue;
    int gj;
    int fy;
    int ys;
    int jy;
    int dj;
};
struct Role role = { 100,30,20,0,0,1 };
typedef struct GW
{
    int xue;
    int gj;
    int fy;
    int jy;
}gw;
gw xg = { 50,30,10,30 };
gw zg = { 70,40,25,40 };
gw dg = { 160,50,70,60 };
gw boss = { 210,70,85,100 };
//加载地图
void jzmap(int n)
{
    int i, j;
    printf("请使用WASD或者2468来控制勇者的移动\n!为钥匙，D为门，+为血瓶，/\\为楼梯  只有按下Esc才能保存游戏进度\n");
    for (i = 0; i < 13; i++)
    {
        for (j = 0; j < 13; j++)
        {
            printf("%c", map[n][i][j]);
        }
        printf("\n");
    }
}
//加载勇者实时信息和怪物图鉴
void jzxx()
{
    printf("\n血量：%d\t", role.xue);
    printf("等级：%d\n", role.dj);
    printf("攻击力：%d\t", role.gj);
    printf("防御力：%d\n", role.fy);
    printf("经验：%d\t", role.jy);
    printf("钥匙：%d\n\n", role.ys);
    printf("怪物属性  血量 攻击力 防御力 经验\n");
    printf("%c-        50    30     10    30\n", 37);
    printf("~-        70    40     25    40\n");
    printf("&-        160   50     70    60\n");
    printf("B-        210   70     85    100\n\n\n\n");
}
//与怪物PK的函数
int pk(char a)
{
    switch (a)
    {
    case 37:
        while (role.xue > 0 && xg.xue > 0)
        {
            if (role.gj > xg.fy)
            {
                xg.xue -= (role.gj - xg.fy);
            }
            if (xg.gj > role.fy)
            {
                role.xue -= (xg.gj - role.fy);
            }
        }
        if (role.xue > 0)
            return 1;
        else
            return 0;
        break;
    case 126:
        while (role.xue > 0 && zg.xue > 0)
        {
            if (role.gj > zg.fy)
            {
                zg.xue -= (role.gj - zg.fy);
            }
            if (zg.gj > role.fy)
            {
                role.xue -= (zg.gj - role.fy);
            }
        }
        if (role.xue > 0)
            return 1;
        else
            return 0;
        break;
    case 38:
        while (role.xue > 0 && dg.xue > 0)
        {
            if (role.gj > dg.fy)
            {
                dg.xue -= (role.gj - dg.fy);
            }
            if (dg.gj > role.fy)
            {
                role.xue -= (dg.gj - role.fy);
            }
        }
        if (role.xue > 0)
            return 1;
        else
            return 0;
        break;
    case 66:
        while (role.xue > 0 && boss.xue > 0)
        {
            if (role.gj > boss.fy)
            {
                boss.xue -= (role.gj - boss.fy);
            }
            if (boss.gj > role.fy)
            {
                role.xue -= (boss.gj - role.fy);
            }
        }
        if (role.xue > 0)
        {
            printf("恭喜你，勇者，你打败了魔王！");
            map[1][6][8];
                exit(1);
        }
        else
            return 0;
        break;
    }
}
//经验等级判断的函数
void jydj()
{
    if (role.jy >= 50)
    {
        role.jy -= 50;
        role.dj++;
        role.gj += 10;
        role.fy += 5;
        role.xue += 20;
    }
}
//控制勇者的函数
int keyrole(int n)
{
    int i, j,a;
    for (i = 1; i < 13; i++)//在地图上找到勇者
    {
        for (j = 1; j < 13; j++)
        {
            if (map[n][i][j] == 79)
                break;
        }
        if (map[n][i][j] == 79)
            break;
    }
    a = _getch();
    switch (a)
    {
    case 'W':
    case 'w':
    case '8':
        if (map[n][i - 1][j] == 32)//方向上为空地
        {
            map[n][i - 1][j] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i - 1][j] == 33)//方向上为钥匙
        {
            map[n][i - 1][j] = 79;
            map[n][i][j] = 32;
            role.ys++;
        }
        else if (map[n][i - 1][j] == 68)//方向上为门
        {
            if (role.ys > 0)
            {
                map[n][i - 1][j] = 32;
                role.ys--;
            }
        }
        else if (map[n][i - 1][j] == 43)//方向上为血瓶
        {
            role.xue += 80;
            map[n][i - 1][j] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i - 1][j] == 47)//方向上为楼梯,下一关
        {
            map[1][2][1] = 79;
            map[n][i][j] = 32;
            jzmap(1);
            jzxx();
            return 1;
        }
        else if (map[n][i - 1][j] == 92)//方向上为楼梯，上一关
        {
            map[0][1][2] = 79;
            map[n][i][j] = 32;
            jzmap(0);
            jzxx();
            return 0;
        }
        else if (map[n][i - 1][j] == 37 || map[n][i - 1][j] == 126 || map[n][i - 1][j] == 38 || map[n][i - 1][j] == 66)//打怪
        {
            int k;
            a = map[n][i - 1][j];
            switch (a)
            {
            case 37:
                k=pk(a);
                if (k == 1)
                {
                    map[n][i - 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 126:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i - 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 38:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i - 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 66:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i - 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            }
        }
        break;
    case 'S':
    case 's':
    case '2':
        if (map[n][i + 1][j] == 32)//方向上为空地
        {
            map[n][i + 1][j] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i + 1][j] == 33)//方向上为钥匙
        {
            map[n][i + 1][j] = 79;
            map[n][i][j] = 32;
            role.ys++;
        }
        else if (map[n][i + 1][j] == 68)//方向上为门
        {
            if (role.ys > 0)
            {
                map[n][i + 1][j] = 32;
                role.ys--;
            }
        }
        else if (map[n][i + 1][j] == 43)//方向上为血瓶
        {
            role.xue += 80;
            map[n][i + 1][j] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i + 1][j] == 47)//方向上为楼梯,下一关
        {
            map[1][2][1] = 79;
            map[n][i][j] = 32;
            jzmap(1);
            jzxx();
            return 1;
        }
        else if (map[n][i + 1][j] == 92)//方向上为楼梯，上一关
        {
            map[0][1][2] = 79;
            map[n][i][j] = 32;
            jzmap(0);
            jzxx();
            return 0;
        }
        else if (map[n][i + 1][j] == 37 || map[n][i + 1][j] == 126 || map[n][i + 1][j] == 38 || map[n][i + 1][j] == 66)//打怪
        {
            int k;
            a = map[n][i + 1][j];
            switch (a)
            {
            case 37:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i + 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 126:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i + 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 38:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i + 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 66:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i + 1][j] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            }
        }
        break;
    case 'A':
    case 'a':
    case '4':
        if (map[n][i][j-1] == 32)//方向上为空地
        {
            map[n][i][j-1] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i][j-1] == 33)//方向上为钥匙
        {
            map[n][i][j-1] = 79;
            map[n][i][j] = 32;
            role.ys++;
        }
        else if (map[n][i][j-1] == 68)//方向上为门
        {
            if (role.ys > 0)
            {
                map[n][i][j-1] = 32;
                role.ys--;
            }
        }
        else if (map[n][i][j-1] == 43)//方向上为血瓶
        {
            role.xue += 80;
            map[n][i][j-1] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i][j-1] == 47)//方向上为楼梯,下一关
        {
            map[1][2][1] = 79;
            map[n][i][j] = 32;
            jzmap(1);
            jzxx();
            return 1;
        }
        else if (map[n][i][j-1] == 92)//方向上为楼梯，上一关
        {
            map[0][1][2] = 79;
            map[n][i][j] = 32;
            jzmap(0);
            jzxx();
            return 0;
        }
        else if (map[n][i][j-1] == 37 || map[n][i][j-1] == 126 || map[n][i][j-1] == 38 || map[n][i][j-1] == 66)//打怪
        {
            int k;
            a = map[n][i][j-1];
            switch (a)
            {
            case 37:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j-1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 126:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j-1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 38:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j-1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 66:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j-1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            }
        }
        break;
    case 'D':
    case 'd':
    case '6':
        if (map[n][i][j+1] == 32)//方向上为空地
        {
            map[n][i][j + 1] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i][j + 1] == 33)//方向上为钥匙
        {
            map[n][i][j + 1] = 79;
            map[n][i][j] = 32;
            role.ys++;
        }
        else if (map[n][i][j + 1] == 68)//方向上为门
        {
            if (role.ys > 0)
            {
                map[n][i][j + 1] = 32;
                role.ys--;
            }
        }
        else if (map[n][i][j + 1] == 43)//方向上为血瓶
        {
            role.xue += 80;
            map[n][i][j + 1] = 79;
            map[n][i][j] = 32;
        }
        else if (map[n][i][j + 1] == 47)//方向上为楼梯,下一关
        {
            map[1][2][1] = 79;
            map[n][i][j] = 32;
            jzmap(1);
            jzxx();
            return 1;
        }
        else if (map[n][i][j + 1] == 92)//方向上为楼梯，上一关
        {
            map[0][1][2] = 79;
            map[n][i][j] = 32;
            jzmap(0);
            jzxx();
            return 0;
        }
        else if (map[n][i][j + 1] == 37 || map[n][i][j + 1] == 126 || map[n][i][j + 1] == 38 || map[n][i][j + 1] == 66)//打怪
        {
            int k;
            a = map[n][i][j + 1];
            switch (a)
            {
            case 37:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j + 1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 126:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j + 1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 38:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j + 1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            case 66:
                k = pk(a);
                if (k == 1)
                {
                    map[n][i][j + 1] = 32;
                    role.jy += 30;
                    jydj();
                }
                else
                {
                    printf("恭喜你！挑战失败");
                    exit(0);
                }
                break;
            }
        }
        break;
    case 27:
        cd();
        printf("保存成功");
        break;
        }
    jzmap(n);
    jzxx();
    return n;
}
//存档
void cd()
{
    int i, j, n;
    FILE* pf = fopen("cd.txt", "w");
    if (pf == NULL)
    {
        perror("fopen");
        exit(0);
    }
    fprintf(pf, "%d %d %d %d %d %d", role.xue, role.gj, role.fy, role.ys, role.jy, role.dj);
    for (n = 0; n < 2; n++)
    {
        for (i = 0; i < 13; i++)
        {
            for (j = 0; j < 13; j++)
            {
                fprintf(pf, "%c", map[n][i][j]);
            }
        }
    }
    fclose(pf);
    pf = NULL;
}
//读档
void dd()
{
    int n, i, j, k;
    FILE* pf = fopen("cd.txt", "r");
    if (pf == NULL)
    {
        perror("fopen");
        exit(0);
    }
    fscanf(pf, "%d %d %d %d %d %d", &role.xue, &role.gj, &role.fy, &role.ys, &role.jy, &role.dj);
    for (n = 0; n < 2; n++)
    {
        for (i = 0; i < 13; i++)
        {
            for (j = 0; j < 13; j++)
            {
                map[n][i][j] = fgetc(pf);
            }
        }
    }
    fclose(pf);
    pf = NULL;
}

int main()
{   
    int b;
    printf("开始新游戏请输1 继续游戏请输2  ");
    scanf("%d", &b);
    if (b == 1)
    {
        int n = 0;
        jzmap(0);
        jzxx();
        while (1)
        {
            n = keyrole(n);
        }
    }
   else
    {   
       int n,i,j,k=0;
       dd();
       for (n = 0; n < 2; n++)
       {
           for (i = 0; i < 13; i++)
           {
               for (j = 0; j < 13; j++)
               {
                   if (map[n][i][j] == 79)
                   {
                       k = n;
                   }
                   break;
               }
               if (map[n][i][j] == 79)
                   break;
           }
           if (map[n][i][j] == 79)
               break;
       }
       jzmap(k);
       jzxx();
        while (1)
        {

            k = keyrole(k);
        }
    }
	return 0;
}