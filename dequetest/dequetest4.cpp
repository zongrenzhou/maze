#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<Windows.h>
#include<deque>
#define LENGTH 20        //�Թ���
#define WIDTH 20         //�Թ���
#define DIR 8            //���������ĸ�����
#define HASWALK 2		 //����߹��ĵ�

bool findpathflag = false;				//�Ƿ��ҵ�·��

using namespace std;

char CMG[LENGTH][WIDTH];				//�ַ���ʾ���Թ�

int MG[LENGTH][WIDTH] = {				//���ֱ�ʾ���Թ�
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

int Dir[DIR][2] = {			//�˸�����
				0, 1,       //��
			    1, 1,		//����
				1, 0,		//��
			    1,-1,		//����
				0,-1,		//��
			   -1,-1,		//����
			   -1, 0		//��
			   -1, 1		//����
};

char InttoChar[3] = { '0','1','2' };      //�����Թ��任���ַ��Թ�

struct point {				//��¼·��
	int x;
	int y;
	int dir;				//��¼����
};

void setCMG()				//�����Թ��任���ַ��Թ�
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			CMG[i][j] = InttoChar[MG[i][j]];
		}
	}
	CMG[1][1] = 'S';		//�������
	CMG[LENGTH-2][WIDTH-2] = 'E';		//�����յ�

}

deque<point> mgdeque;		//�洢·����ջ

void Inicial(int length,int width)			//��������������Թ�
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
				MG[i][j] = rand() % 2;		//0��ʾ���ߣ�1��ʾǽ
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
	SetConsoleCursorPosition(hout, coord);				//����CMD��ʼ��
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cout << CMG[i][j] << " ";
		}
		cout << endl;
	}
}

void dshow()		//��̬��ʾ·��
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



void findpath()				//Ѱ��·��
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
		for (i = 0; i < DIR; i++)			//�˸�����Ѱ�ҿ��еĵ�
		{
			st.x += Dir[i][0];
			st.y += Dir[i][1];
			st.dir = i;						//���·������
			if (MG[st.x][st.y] == 0)
			{
				mgdeque.push_back(st);
				MG[st.x][st.y] = HASWALK;	//����Ѿ��߹��ĵ�
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