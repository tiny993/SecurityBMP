#pragma once
#ifndef LOG_H_
#define LOG_H_
#endif // !LOG_H_

#include "headLib.h"

class Log 
{
private:
	//ʱ���ʽ����
	SYSTEMTIME sys_time;
public:
	Log();
	//��ȡ��ǰʱ��
	SYSTEMTIME getTime();
	//����Log�ı�
	bool buildLog();
	//����־д�뵽�ı���
	bool writeLog(string log_str);
};

Log::Log()
{
	//���캯��
}
/**********************************
*���ܣ���ȡ��ǰʱ��
*��������
*����ֵ��ʱ��ṹ��
***********************************/
SYSTEMTIME Log::getTime()
{
	GetLocalTime(&sys_time);
	return sys_time;
}

/**********************************
*���ܣ�����־д���ı���
*������string������־
*����ֵ���������
***********************************/
bool Log::writeLog(string log_str)
{
	fstream file;
	file.open(".\\Log.txt", ios::app);
	if (!file)
	{
		return false;
	}
	getTime();
	string time_str = to_string(sys_time.wYear) + "��" + to_string(sys_time.wMonth) + "��" +
		to_string(sys_time.wDay) + "�� " + to_string(sys_time.wHour) + ":" +
		to_string(sys_time.wMinute) + ":" + to_string(sys_time.wSecond) + ":\n";
	file << time_str;
	file << log_str + "\n";
	return true;
}

/**********************************
*���ܣ�����Log�ı�
*��������
*����ֵ���������
***********************************/
bool Log::buildLog()
{
	fstream file;
	file.open(".\\Log\\Log.txt", ios::app);
	if (file)
	{
		return true;
	}
	return false;
}