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
	//���ֽ��ַ���ת���ֽ��ַ���
	wchar_t* CharToWchar(char* c_str);
	//���ֽ��ַ���ת���ֽ��ַ���
	char* WcharToChar(wchar_t* wc_str); 
	//��ȡ�û������ַ���
	char* stringBuild();
	//���ֽ��ַ���ת�����ַ���
	int* chsToInt(wchar_t* chs);
	void chsToInt(wchar_t*, int* num_buff);
	//��ȡ���鳤��
	unsigned getLength(char* c_str);
	unsigned getLength(wchar_t* wc_str);
	unsigned getLength(int* int_arr);
	//��������ת��Ϊ����RGBֵ����
	int** chsToRGB(int* int_arr, int** &RGB_Arr);
	//�ͷ���Դ
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
	//���캯��
}

intArrBuild::~intArrBuild()
{
	release();
}

/********************************
*���ܣ����ֽ��ַ���ת���ֽ��ַ���
*������char�ַ���
*����ֵ��wchar_t�ַ���
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
*���ܣ����ֽ��ַ���ת���ֽ��ַ���
*������wchar_t�ַ���
*����ֵ��char�ַ���
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
*���ܣ���ȡ�û������ַ���
*��������
*����ֵ��wchar_t* �û������ַ���
*********************************/
char* intArrBuild::stringBuild() 
{
	char ch;
	int count = 0;
	get_str = (char*)malloc(sizeof(char));
	//����ʧ��
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
*���ܣ����ֽ��ַ���ת�����ַ���
*������wchar_t�ַ���
*		(�ڶ�������ֵΪ���������׵�ַ)
*����ֵ�������ַ���
*		(�޷���ֵ)
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
*���ܣ���ȡ���鳤��
*�����������׵�ַ
*����ֵ���޷�������
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
//����
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
//����
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
*���ܣ��ͷ���Դ
*��������
*����ֵ����
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
*���ܣ�����һά����ת��Ϊ����RGBֵ��ά����
*����������һά����,���ζ�ά����
*����ֵ��RGB��ά���鳤��
*********************************/
int** intArrBuild::chsToRGB(int* int_arr, int** &RGB_Arr)
{
	unsigned int_length = getLength(int_arr) + 1;
	//��̬�����ά���鳤��
	RGB_Arr = (int**)malloc(sizeof(int*) * int_length);
	RGB_Arr[0] = (int *)malloc(int_length * RGB_COUNT * sizeof(int));
	for (unsigned i = 1; i < int_length; i++)
	{
		RGB_Arr[i] = RGB_Arr[i - 1] + RGB_COUNT;
	}
	//����Կ(******)�����һ��������(** ** **)

	for (unsigned i = 1; i < int_length; i++)
	{
		//Ӣ�Ĵ���Ӣ���ַ�С��127(ASCII)
		if (*int_arr < 127)
		{
			RGB_Arr[i][0] = *int_arr;			
			RGB_Arr[i][1] = 0;
			RGB_Arr[i][2] = 0;
			int_arr++;
		}
		//���Ĵ��������ַ���������Ϊ5λ�����Ϊ��λ��ǧλ�Ͱ�λ��ʮλ�͸�λ
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