#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<Windows.h>
#include<deque>
#define LENGTH 20        //迷宫长
#define WIDTH 20         //迷宫宽
#define DIR 8            //上下左右四个方向
#define HASWALK 2		 //标记走过的点

bool findpathflag = false;				//是否找到路径

using namespace std;

char CMG[LENGTH][WIDTH];				//字符表示的迷宫

int MG[LENGTH][WIDTH] = {				//数字表示的迷宫
				1, 1 ,1, 1 ,1 ,1 ,1 ,1 ,1, 1,
				1, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1,
				1, 0 ,1 ,0 ,1 ,0 ,0 ,1 ,1 ,1,
				1, 1 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,1,
				1, 0 ,1 ,1 ,0 ,1 ,1 ,0 ,1 ,1,
				1, 0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1,
				1, 1 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,1,
				1, 1 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,1,
				1, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1,
				1, 1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1
};

int Dir[DIR][2] = {			//八个方向
				0, 1,       //右
			    1, 1,		//右下
				1, 0,		//下
			    1,-1,		//左下
				0,-1,		//左
			   -1,-1,		//左上
			   -1, 0		//上
			   -1, 1		//右上
};

char InttoChar[3] = { '0','1','2' };      //数字迷宫变换成字符迷宫

struct point {				//记录路径
	int x;
	int y;
	int dir;				//记录方向
};

void setCMG()				//数字迷宫变换成字符迷宫
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			CMG[i][j] = InttoChar[MG[i][j]];
		}
	}
	CMG[1][1] = 'S';		//设置起点
	CMG[LENGTH-2][WIDTH-2] = 'E';		//设置终点

}

deque<point> mgdeque;		//存储路径的栈

void Inicial(int length,int width)			//产生随机数生成迷宫
{
	srand((int)time(0));
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0|| i == 0|| i == length - 1||j==width-1)
			{
				MG[i][j] = 1;
			}
			else 
			{
				MG[i][j] = rand() % 2;		//0表示可走，1表示墙
			}
		}
	}
	MG[1][1] = 0;
	MG[LENGTH - 2][WIDTH - 2] = 0;

}

void show(int x,int y)
{
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);				//设置CMD初始点
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cout << CMG[i][j] << " ";
		}
		cout << endl;
	}
}

void dshow()		//动态显示路径
{
	if (findpathflag)
	{
		for (auto mgd = mgdeque.begin() + 1; mgd != mgdeque.end(); mgd++)
		{
			show(0, LENGTH + 2);
			CMG[mgd->x][mgd->y] = '#';
			Sleep(1000);
		}
	}
	else
	{
		cout << "not find path!" << endl;
	}
}



void findpath()				//寻找路径
{
	point st;
	st.x = 1;
	st.y = 1;
	st.dir = 0;
	mgdeque.push_back(st);
	int nextx = 0;
	int nexty = 0;
	int i;

	while (!mgdeque.empty() && !findpathflag)
	{
		st = mgdeque.back();
		if (st.x == LENGTH - 2 && st.y == WIDTH - 2)
		{
			findpathflag = true;
			break;
		}
		for (i = 0; i < DIR; i++)			//八个方向寻找可行的点
		{
			st.x += Dir[i][0];
			st.y += Dir[i][1];
			st.dir = i;						//标记路径方向
			if (MG[st.x][st.y] == 0)
			{
				mgdeque.push_back(st);
				MG[st.x][st.y] = HASWALK;	//标记已经走过的点
				break;
			}
			st = mgdeque.back();
		}
		if (i >= DIR)
		{
			mgdeque.pop_back();
		}		
	}
}


int main()
{
	while (!findpathflag)
	{
		Inicial(LENGTH, WIDTH);
		setCMG();
		findpath();
		dshow();
	}

	/*Inicial(LENGTH, WIDTH);
	setCMG();
	findpath();
	show(0, 0);
	dshow();*/
	system("pause");
}