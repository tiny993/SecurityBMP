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
	//����key
	void set_key();
	//��ȡkey
	char* get_key();
	//��keyת��Ϊ����
	unsigned keyToNum(char* key);
	//���key.lic�ļ�
	int checkKey();
	//����key.lic�ļ�,��д��key
	int licOpeartion();
	//��ȡlicense�ļ��е�key
	char* readKey();
	//�ͷ���Դ
	void release();
private:
	char* input_key;
	int sec_arr[6] = { 15,10,13,16,11,10 };
};

myKey::myKey():input_key(NULL)
{
	//���캯��
}

myKey::~myKey()
{
	release();
}
/********************************
*���ܣ�����key
*��������
*����ֵ����
*********************************/
void myKey::set_key() 
{
	cout << "������6λ���ּ���key:" << endl;
	while (true) 
	{
		input_key = intArrBuild::stringBuild();
		if (intArrBuild::getLength(input_key) > 5 && intArrBuild::getLength(input_key) < 7)
		{
			break;
		}
		if (intArrBuild::getLength(input_key) <= 5)
		{
			cout << "key���ȹ���" << endl;
		}
		else
		{
			cout << "key���ȹ���" << endl;
		}
	}
}

/********************************
*���ܣ���ȡkey
*��������
*����ֵ��keyֵ
*********************************/
char* myKey::get_key() 
{
	return input_key;
}

/********************************
*���ܣ���keyת��Ϊ�޷�������
*������key
*����ֵ���޷�������
*********************************/
unsigned myKey::keyToNum(char* key) 
{
	//��keyװ��Ϊ��������key��һ��ֵΪ�㣬��������100000
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
*���ܣ����key.lic�ļ��Ƿ����
*��������
*����ֵ��0���ڣ�-1������
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
*���ܣ����������key.lic�ļ�����д��key
*��������
*����ֵ��0�ɹ���-1ʧ��
*********************************/
int myKey::licOpeartion()
{
	ofstream file;
	int check_num = checkKey();
	//����license�ļ�
	if (check_num == -1)
	{
		file.open(".\\key.lic", ios::app);
		if (!file)
		{
			return -1;
		}
	}
	//����license�ļ�
	else
	{
		remove(".\\key.lic");
		file.open(".\\key.lic", ios::app);
		if (!file)
		{
			return -1;
		}
	}
	//��ֹ�û�δ����key�ͽ�keyд��
	if (input_key == NULL)
	{
		set_key();
	}
	int secu_index = 0;
	//����key��keyд���ļ�
	while (*input_key != NULL)
	{
		char temp = NULL;
		//�ַ�ֵͨ��ƫ�����м���
		temp = *input_key - sec_arr[secu_index];
		file << temp;
		secu_index++;
		input_key++;
	}
	return 0;
}

/********************************
*���ܣ��ͷ���Դ
*��������
*����ֵ����
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
*���ܣ���ȡlicense�ļ��е�Key
*��������
*����ֵ��key�ַ���
*********************************/
char* myKey::readKey()
{
	ifstream read_file(".\\key.lic", ios::in);;
	char ret[7] = {};
	int index = 0;

	if (!read_file.good())
	{
		cout << "ERROR:�ļ���ʧ��" << endl;
		exit(0);
	}
	//ͨ��ƫ�����н���key�ļ�
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