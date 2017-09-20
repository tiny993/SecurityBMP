#pragma once
#include "headLib.h"
#include "IntArrBuild.h"

class BMP : intArrBuild
{
public:
	BMP();
	~BMP();
	//读取图像数据并存放于指定位置
	bool readBmp(char* bmpName);
	//将图像处理后存入指定文件中
	bool saveBmp(char *bmpName, unsigned char *imgBuf,
				int width, int height, int biBitCount,
				RGBQUAD *pColorTable);
	//封装数据到图片
	bool packgeBMP(int** RGB_arr);
	//输入图片名称，并检查输入是否合法
	char* getFileName();
private:
	//读入BMP图片的指针
	unsigned char* pBmpBuf;
	//图像宽
	int bmpWidth;
	//图像高
	int bmpHeight;
	//颜色表指针
	RGBQUAD* pColorTable;
	//每像素占用字节数
	int biBitCount;
};
BMP::BMP()
{
	//构造函数
}
BMP::~BMP()
{
	//析构函数
}
/**********************************
*功能：读取图像数据并存放于指定位置
*参数：图片名称，字符串
*返回值：操作结果bool类型
***********************************/
bool BMP::readBmp(char* bmpName) 
{
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0)
	{
		return 0;
	}
	//跳过头结构
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//定义头结构变量，读取位图信息头进内存并存放在变量head中  
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;  

	//每行像素所占的字节数（4的倍数）
	//由于需要先除以4保证长度为4的倍数
	//需要加上3（可为1、2、3任意数字）保证四舍五入后大小空间不会太小
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	
	//灰度图像（biBitCount为8）有颜色表，且颜色表表项为256，彩色图像无颜色表不需申请  
	if (biBitCount == 8)
	{
		//申请颜色表空间  
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//申请位图数据空间
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	fclose(fp); 
	return 1;
}

/**********************************
*功能：将图像处理后存入指定文件中
*参数：	bmpName：图像名称（字符串）
*	imgBuf：读取的图像数据源（字符串）
*	width：图像宽度（整形）
*	height：图像高度（整形）
*	biBitCount：像素字节数（整形）
*	pColorTable：颜色表（RGBQUAD类型指针）
*返回值：操作结果bool类型
***********************************/
bool BMP::saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable)
{
	if (!imgBuf)
	{
		return 0;
	}

	//灰度图像颜色表大小为1024字节，彩色图像（默认）大小为0字节  
	int colorTablesize = 0;
	if (biBitCount == 8)
	{
		colorTablesize = 1024;
	}

	//每行像素所占的字节数 
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//二进制写  
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0)
	{
		return 0;
	}

	//申请位图头结构空间
	BITMAPFILEHEADER fileHead;
	//bmp类型
	fileHead.bfType = 0x4D42; 
	//图像大小由四部分组成 
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;

	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	//图像文件前3个部分所需空间大小由前三部分构成  
	fileHead.bfOffBits = 54 + colorTablesize;

	//写文件头结构写进文件  
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//申请位图信息头结构  
	BITMAPINFOHEADER head;

	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte*height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;

	//写位图信息头进内存  
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//如果灰度图像，有颜色表，写入文件   
	if (biBitCount == 8)
	{
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//写位图数据进文件  
	fwrite(imgBuf, height*lineByte, 1, fp); 
	fclose(fp);
	return 1;
}

/**********************************
*功能：输入图片名称，并检查输入是否合法
*参数：无
*返回值：输入文件名
***********************************/
char* BMP::getFileName()
{
	//输入图像文件名
	cout << "请输入图像文件名，文件格式为.bmp" << endl;
	char* ret = NULL;
	while (true)
	{
		ret = intArrBuild::stringBuild();
		unsigned length = intArrBuild::getLength(ret);
		//判断后缀是否为".bmp"
		if (ret[length - 4] == '.' && ret[length - 3] == 'b' && ret[length - 2] == 'm' && ret[length - 1] == 'p' && length > 4)
		{
			break;
		}
		cout << "\n********输入格式错误，请重新输入！********\n" << endl;
	}
	return ret;
}

/**********************************
*功能：封装数据到图片
*参数：数据像素数组
*返回值：操作结果bool类型
***********************************/
bool BMP::packgeBMP(int** RGB_arr)
{
	char* readPath = getFileName();
	if (!readBmp(readPath))
	{
		cout << "\n********打开文件失败，请检查是否有"<<readPath<<"文件！********\n" << endl;
		return 0;
	}

	//完成文件打开，以下需要读取图片数据和改变像素值

	return 1;
}