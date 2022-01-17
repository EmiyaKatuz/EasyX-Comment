#undef UNICODE
#undef _UNICODE
#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#define width 1200//页面窗口宽度
#define height 700//页面窗口高度
#define munber 9999999//输出字符的数量
#define speed 16//弹幕的移动速度
#define n 5//弹幕种类的数量
void outtext(int text_x, int text_y, int color, int mun, struct house str_house[n]);//输出字符串函数
void movetext(int mun, int color);//移动字符串函数

//定义每个字符串的属性
struct string
{
	int x;
	int y;
	int color;
	int size;
}str[munber];

//用来输出字符串的字符串库
typedef struct house
{
	char str[100];
};
struct house str_house[n] = { "Hello World!","Happy New Year!","Hello 2022!","新年快乐!!","元旦快乐!!" };

//===========生成一串字符======================
void outtext(int text_x, int text_y, int color, int mun, struct house str_house[n])
{
	//输出文字的颜色
	settextcolor(color);

	//输出文字的背景为透明
	setbkmode(TRANSPARENT);

	//输出的文字样式
	settextstyle(str[mun].size, 0, _T("楷体"));

	//输出这串字符
	outtextxy(text_x, text_y, str_house[mun % n].str);
}
//==

//=============主函数！！======================
void main(void)
{
	//初始化窗口大小
	initgraph(width, height);

	//定义取随机数的方式
	srand((unsigned)time(NULL));

	//初始化每个字符
	int mun;
	for (mun = 0; mun < munber; mun++)
	{
		str[mun].x = -200;//定义初始x位置
		str[mun].y = (rand() % height);//定义初始y位置
		str[mun].color = (int)HSLtoRGB(rand() % 360, 1, 0.5f);//定义初始颜色
		int RAND = rand() % 30;//定义初始大小
		if (RAND > 10)
			str[mun].size = RAND;
		else
			str[mun].size = RAND + 30;
	}

	//逐个输出字符串
	for (mun = 0; mun < munber; mun++)
	{
		//生成一串字符(函数)
		outtext(str[mun].x, str[mun].y, str[mun].color, mun, str_house);

		//移动这个字符串
		int munmove, current = 0;
		for (munmove = current; munmove < mun; munmove++)
		{

			//如果这个字符串跑的太远了,那就停下来;
			if (str[munmove].x > width)
			{
				current++;
				continue;
			}

			//移动刚刚那串字符
			movetext(munmove, str[munmove].color);
		}
		Sleep(speed);
	}

	//==========任意键退出窗口============//
	getchar();
	closegraph();
}

//=======移动字符，但只移动一次================
void movetext(int mun, int color)
{
	//清除刚刚的字符
	outtext(str[mun].x, str[mun].y, 0x000000, mun, str_house);

	//根据字符大小给予相应的移动尺度
	if (str[mun].size > 30)
		str[mun].x = str[mun].x + 11;
	else if (str[mun].size <= 30 && str[mun].size > 25)
		str[mun].x = str[mun].x + 9;
	else if (str[mun].size <= 25 && str[mun].size > 20)
		str[mun].x = str[mun].x + 7;
	else if (str[mun].size <= 20 && str[mun].size > 15)
		str[mun].x = str[mun].x + 5;
	else if (str[mun].size <= 15 && str[mun].size > 10)
		str[mun].x = str[mun].x + 3;

	//在新的位置重新出现
	outtext(str[mun].x, str[mun].y, color, mun, str_house);
}
//==