#pragma once
#ifndef LOG_H_
#define LOG_H_
#endif // !LOG_H_

#include "headLib.h"

class Log 
{
private:
	//时间格式变量
	SYSTEMTIME sys_time;
public:
	Log();
	//获取当前时间
	SYSTEMTIME getTime();
	//创建Log文本
	bool buildLog();
	//将日志写入到文本中
	bool writeLog(string log_str);
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
	fstream file;
	file.open(".\\Log.txt", ios::app);
	if (!file)
	{
		return false;
	}
	getTime();
	string time_str = to_string(sys_time.wYear) + "年" + to_string(sys_time.wMonth) + "月" +
		to_string(sys_time.wDay) + "日 " + to_string(sys_time.wHour) + ":" +
		to_string(sys_time.wMinute) + ":" + to_string(sys_time.wSecond) + ":\n";
	file << time_str;
	file << log_str + "\n";
	return true;
}

/**********************************
*功能：创建Log文本
*参数：无
*返回值：操作结果
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