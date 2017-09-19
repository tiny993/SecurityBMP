#pragma once
#ifndef INTARRBUILD_H_
#define INTARRBUILD_H_
#endif // !INTARRBUILD_H_

#include "headLib.h"

using namespace std;

class intArrBuild 
{
public:
	intArrBuild();
	virtual ~intArrBuild();
	//单字节字符串转宽字节字符串
	wchar_t* CharToWchar(char* c_str);
	//宽字节字符串转单字节字符串
	char* WcharToChar(wchar_t* wc_str); 
	//读取用户输入字符串
	char* stringBuild();
	//宽字节字符串转整形字符串
	int* chsToInt(wchar_t* chs);
	void chsToInt(wchar_t*, int* num_buff);
	//获取数组长度
	unsigned getLength(char* c_str);
	unsigned getLength(wchar_t* wc_str);
	unsigned getLength(int* int_arr);
	//整形数组转换为像素RGB值数组
	int** chsToRGB(int* int_arr, int** &RGB_Arr);
	//释放资源
	void release();

private:
	char* get_str;
	char* c_str;
	wchar_t* wc_str;
};

intArrBuild::intArrBuild()
		:get_str(NULL),
		wc_str(NULL),
		c_str(NULL)
{
	//构造函数
}

intArrBuild::~intArrBuild()
{
	release();
}

/********************************
*功能：单字节字符串转宽字节字符串
*参数：char字符串
*返回值：wchar_t字符串
*********************************/
wchar_t* intArrBuild::CharToWchar(char* c_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, c_str, strlen(c_str), NULL, 0);
	wc_str = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, c_str, strlen(c_str), wc_str, len);
	wc_str[len] = '\0';
	return wc_str;
}

/********************************
*功能：宽字节字符串转单字节字符串
*参数：wchar_t字符串
*返回值：char字符串
*********************************/
char* intArrBuild::WcharToChar(wchar_t* wc_str) 
{
	int len = WideCharToMultiByte(CP_ACP, 0, wc_str, wcslen(wc_str), NULL, 0, NULL, NULL);
	c_str = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wc_str, wcslen(wc_str), c_str, len, NULL, NULL);
	c_str[len] = '\0';
	return c_str;
}

/********************************
*功能：读取用户输入字符串
*参数：无
*返回值：wchar_t* 用户输入字符串
*********************************/
char* intArrBuild::stringBuild() 
{
	char ch;
	int count = 0;
	get_str = (char*)malloc(sizeof(char));
	//创建失败
	if (get_str == NULL)
	{
		printf("ERROR!\n");
		exit(1);
	}
	while ((ch = getchar()) != '\n')
	{
		get_str[count] = ch;
		count++;
		get_str = (char*)realloc(get_str, sizeof(char)*(count + 1));
	}
	get_str[count] = '\0';
	return get_str;
}

/**************************************
*功能：宽字节字符串转整形字符串
*参数：wchar_t字符串
*		(第二个参数值为整形数组首地址)
*返回值：整形字符串
*		(无返回值)
***************************************/
int* intArrBuild::chsToInt(wchar_t* wc_str) 
{
	int num_buff[MAX] = {};
	int index = 0;
	while (*wc_str != '\0')
	{
		num_buff[index] = *wc_str++;
		index++;
	}
	return num_buff;
}
void intArrBuild::chsToInt(wchar_t* wc_str, int* num_buff) 
{
	int index = 0;
	while (*wc_str != '\0')
	{
		num_buff[index] = *wc_str++;
		index++;
	}
}
/********************************
*功能：获取数组长度
*参数：数组首地址
*返回值：无符号整形
*********************************/
unsigned intArrBuild::getLength(char* c_str)
{
	unsigned ret = 0;
	while (*c_str != '\0')
	{
		ret++;
		c_str++;
	}
	return ret;
}
//重载
unsigned intArrBuild::getLength(wchar_t* wc_str)
{
	unsigned ret = 0;
	while (*wc_str != '\0')
	{
		ret++;
		wc_str++;
	}
	return ret;
}
//重载
unsigned intArrBuild::getLength(int* int_arr)
{
	unsigned ret = 0;
	int index = 0;
	while (int_arr[index] != 0)
	{
		ret++;
		index++;
	}
	return ret;
}

/********************************
*功能：释放资源
*参数：无
*返回值：无
*********************************/
void intArrBuild::release()
{
	if (get_str)
	{
		delete get_str;
		get_str = NULL;
	}
	if (c_str != NULL)
	{
		delete c_str;
		c_str = NULL;
	}
	if (wc_str)
	{
		delete wc_str;
		wc_str = NULL;
	}
}

/********************************
*功能：整形一维数组转换为像素RGB值二维数组
*参数：整形一维数组,整形二维数组
*返回值：RGB二维数组长度
*********************************/
int** intArrBuild::chsToRGB(int* int_arr, int** &RGB_Arr)
{
	unsigned int_length = getLength(int_arr) + 1;
	//动态申请二维数组长度
	RGB_Arr = (int**)malloc(sizeof(int*) * int_length);
	RGB_Arr[0] = (int *)malloc(int_length * RGB_COUNT * sizeof(int));
	for (unsigned i = 1; i < int_length; i++)
	{
		RGB_Arr[i] = RGB_Arr[i - 1] + RGB_COUNT;
	}
	//将秘钥(******)存入第一个像素中(** ** **)

	for (unsigned i = 1; i < int_length; i++)
	{
		//英文处理：英文字符小于127(ASCII)
		if (*int_arr < 127)
		{
			RGB_Arr[i][0] = *int_arr;			
			RGB_Arr[i][1] = 0;
			RGB_Arr[i][2] = 0;
			int_arr++;
		}
		//中文处理：中文字符整数长度为5位，拆分为万位，千位和百位，十位和个位
		else
		{
			int B_int = *int_arr % 100;
			*int_arr /= 100;
			int	G_int = *int_arr % 100;
			*int_arr /= 100;
			int R_int = *int_arr % 100;
			*int_arr /= 100;
			RGB_Arr[i][0] = R_int;
			RGB_Arr[i][1] = G_int;
			RGB_Arr[i][2] = B_int;
			int_arr++;
		}
	}
	return RGB_Arr;
}