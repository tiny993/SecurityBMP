#pragma once
#ifndef LOG_H_
#define LOG_H_
#endif // !LOG_H_

#include "headLib.h"
#include <direct.h>
#include <io.h>

class Log 
{
private:
	//ʱ���ʽ����
	SYSTEMTIME sys_time;
public:
	Log();
	//��ȡ��ǰʱ��
	SYSTEMTIME getTime();
	//����Log�ļ���
	bool buildDir();
	//����־д�뵽�ı���
	bool writeLog(string log_str);
	//�����־�ļ�
	bool clearLog();
	//��ʾ��־�ļ���С
	void LogSize();
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
	bool flag = buildDir();
	if (!flag)
	{
		return false;
	}
	fstream file;
	file.open(".\\Log\\Log.txt", ios::app);
	if (!file)
	{
		file.close();
		return false;
	}
	getTime();
	//��ӡ��ǰʱ��
	string time_str = to_string(sys_time.wYear) + "-" + to_string(sys_time.wMonth) + "-" +
		to_string(sys_time.wDay) + " " + to_string(sys_time.wHour) + ":" +
		to_string(sys_time.wMinute) + ":" + to_string(sys_time.wSecond) + "    ";
	file << time_str;
	file << log_str + "\n";
	file.close();
	return true;
}

/**********************************
*���ܣ������־�ļ�
*��������
*����ֵ���������
***********************************/
bool Log::clearLog()
{
	ofstream file;
	remove(".\\Log\\Log.txt");
	file.open(".\\Log\\Log.txt", ios::app);
	if (!file)
	{
		file.close();
		return false;
	}
	file.close();
 	return true;
}

/**********************************
*���ܣ���ʾ��־�ļ���С
*��������
*����ֵ����
***********************************/
inline void Log::LogSize()
{
	FILE* file = fopen(".\\Log\\Log.txt", "r");
	if (!file)
	{
		return;
	}
	fseek(file, 0, SEEK_END);
	int log_size = ftell(file);
	int tmp = log_size;
	log_size /= 1024;
	log_size++;
	cout << "��־��СΪ��" << log_size << "KB��" << tmp << "B)" << endl;
	//����ر��ļ�����������������޷�����ļ���־
	fclose(file);
}

/**********************************
*���ܣ�����Log�ı�
*��������
*����ֵ���������
***********************************/
bool Log::buildDir()
{
	//�ж�Ŀ¼�Ƿ����
	int access_ret = access(".\\Log", 00);
	if (access_ret == -1)
	{
		access_ret = _mkdir(".\\Log");
	}
	if (access_ret == 0)
	{
		return true;
	}
	return false;
}