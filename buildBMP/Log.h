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
	//时间格式变量
	SYSTEMTIME sys_time;
public:
	Log();
	//获取当前时间
	SYSTEMTIME getTime();
	//创建Log文件夹
	bool buildDir();
	//将日志写入到文本中
	bool writeLog(string log_str);
	//清空日志文件
	bool clearLog();
	//显示日志文件大小
	void LogSize();
};

Log::Log()
{
	//构造函数
}
/**********************************
*功能：获取当前时间
*参数：无
*返回值：时间结构体
***********************************/
SYSTEMTIME Log::getTime()
{
	GetLocalTime(&sys_time);
	return sys_time;
}

/**********************************
*功能：将日志写入文本中
*参数：string类型日志
*返回值：操作结果
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
	//打印当前时间
	string time_str = to_string(sys_time.wYear) + "-" + to_string(sys_time.wMonth) + "-" +
		to_string(sys_time.wDay) + " " + to_string(sys_time.wHour) + ":" +
		to_string(sys_time.wMinute) + ":" + to_string(sys_time.wSecond) + "    ";
	file << time_str;
	file << log_str + "\n";
	file.close();
	return true;
}

/**********************************
*功能：清空日志文件
*参数：无
*返回值：操作结果
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
*功能：显示日志文件大小
*参数：无
*返回值：无
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
	cout << "日志大小为：" << log_size << "KB（" << tmp << "B)" << endl;
	//必须关闭文件操作符，否则后面无法清除文件日志
	fclose(file);
}

/**********************************
*功能：创建Log文本
*参数：无
*返回值：操作结果
***********************************/
bool Log::buildDir()
{
	//判断目录是否存在
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