#pragma once
#ifndef MYKEY_H_
#define MYKEY_H_
#endif // !MYKEY_H_

#include "IntArrBuild.h"

class myKey : intArrBuild
{
public:
 	myKey();
 	~myKey();
	//输入key
	void set_key();
	//读取key
	char* get_key();
	//将key转换为整数
	unsigned keyToNum(char* key);
	//检查key.lic文件
	int checkKey();
	//创建key.lic文件,并写入key
	int licOpeartion();
	//读取license文件中的key
	char* readKey();
	//释放资源
	void release();
private:
	char* input_key;
	int sec_arr[6] = { 15,10,13,16,11,10 };
};

myKey::myKey():input_key(NULL)
{
	//构造函数
}

myKey::~myKey()
{
	release();
}
/********************************
*功能：输入key
*参数：无
*返回值：无
*********************************/
void myKey::set_key() 
{
	cout << "请输入6位数字加密key:" << endl;
	while (true) 
	{
		input_key = intArrBuild::stringBuild();
		if (intArrBuild::getLength(input_key) > 5 && intArrBuild::getLength(input_key) < 7)
		{
			break;
		}
		if (intArrBuild::getLength(input_key) <= 5)
		{
			cout << "key长度过短" << endl;
		}
		else
		{
			cout << "key长度过长" << endl;
		}
	}
}

/********************************
*功能：获取key
*参数：无
*返回值：key值
*********************************/
char* myKey::get_key() 
{
	return input_key;
}

/********************************
*功能：将key转换为无符号整数
*参数：key
*返回值：无符号整数
*********************************/
unsigned myKey::keyToNum(char* key) 
{
	//将key装换为整数，若key第一个值为零，则将整数加100000
	unsigned num_key = 0;
	if (key[0] == '0')
	{
		key[0] = '1';
	}
	for (unsigned i = 0; i < intArrBuild::getLength(key); i++)
	{
		num_key += key[i] - '0';
		num_key *= 10;
	}
	num_key /= 10;
	return num_key;
}

/********************************
*功能：检查key.lic文件是否存在
*参数：无
*返回值：0存在，-1不存在
*********************************/
int myKey::checkKey()
{
	fstream file;
	file.open("key.lic", ios::in);
	if (!file)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/********************************
*功能：创建或更新key.lic文件，并写入key
*参数：无
*返回值：0成功，-1失败
*********************************/
int myKey::licOpeartion()
{
	ofstream file;
	int check_num = checkKey();
	//创建license文件
	if (check_num == -1)
	{
		file.open(".\\key.lic", ios::app);
		if (!file)
		{
			return -1;
		}
	}
	//更新license文件
	else
	{
		remove(".\\key.lic");
		file.open(".\\key.lic", ios::app);
		if (!file)
		{
			return -1;
		}
	}
	//防止用户未输入key就将key写入
	if (input_key == NULL)
	{
		set_key();
	}
	int secu_index = 0;
	//加密key后将key写入文件
	while (*input_key != NULL)
	{
		char temp = NULL;
		//字符值通过偏移序列加密
		temp = *input_key - sec_arr[secu_index];
		file << temp;
		secu_index++;
		input_key++;
	}
	return 0;
}

/********************************
*功能：释放资源
*参数：无
*返回值：无
*********************************/
void myKey::release()
{
// 	if (input_key)
// 	{
// 		delete input_key;
// 		input_key = NULL;
// 	}
// 	if (sec_arr)
// 	{
// 		delete[] sec_arr;
// 	}
}

/********************************
*功能：读取license文件中的Key
*参数：无
*返回值：key字符串
*********************************/
char* myKey::readKey()
{
	ifstream read_file(".\\key.lic", ios::in);;
	char ret[7] = {};
	int index = 0;

	if (!read_file.good())
	{
		cout << "ERROR:文件打开失败" << endl;
		exit(0);
	}
	//通过偏移序列解密key文件
	int secu_index = 0;
	while (!read_file.eof())
	{
		char tmp = NULL;
		read_file >> tmp;
		tmp += sec_arr[secu_index];
		ret[index] = tmp;
		index++;
		secu_index++;
	}
	ret[6] = '\0';
	return ret;
}