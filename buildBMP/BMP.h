#pragma once
#ifndef BMP_H_
#define BMP_H_
#endif // !BMP_H_

#include "headLib.h"
#include "IntArrBuild.h"
#include "Log.h"

class BMP : intArrBuild
{
public:
	BMP();
	~BMP();
	//��ȡͼ�����ݲ������ָ��λ��
	bool readBmp(char* bmpName);
	//��ͼ��������ָ���ļ���
	bool saveBmp(char *bmpName, unsigned char *imgBuf,
				int width, int height, int biBitCount,
				RGBQUAD *pColorTable);
	//��װ���ݵ�ͼƬ
	bool packgeBMP(int** RGB_arr, int arr_length);
	//����ͼƬ���ƣ�����������Ƿ�Ϸ�
	char* getFileName();
private:
	//����BMPͼƬ��ָ��
	unsigned char* pBmpBuf;
	//ͼ���
	int bmpWidth;
	//ͼ���
	int bmpHeight;
	//��ɫ��ָ��
	RGBQUAD* pColorTable;
	//ÿ����ռ���ֽ���
	int biBitCount;
	Log log_t;
};
BMP::BMP()
{
	//���캯��
}
BMP::~BMP()
{
	//��������
}
/**********************************
*���ܣ���ȡͼ�����ݲ������ָ��λ��
*������ͼƬ���ƣ��ַ���
*����ֵ���������bool����
***********************************/
bool BMP::readBmp(char* bmpName) 
{
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0)
	{
		return 0;
	}
	//����ͷ�ṹ
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//����ͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ沢����ڱ���head��  
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;  

	//ÿ��������ռ���ֽ�����4�ı�����
	//������Ҫ�ȳ���4��֤����Ϊ4�ı���
	//��Ҫ����3����Ϊ1��2��3�������֣���֤����������С�ռ䲻��̫С
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	
	//�Ҷ�ͼ��biBitCountΪ8������ɫ������ɫ�����Ϊ256����ɫͼ������ɫ��������  
	if (biBitCount == 8)
	{
		//������ɫ��ռ�  
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//����λͼ���ݿռ�
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	fclose(fp); 
	return 1;
}

/**********************************
*���ܣ���ͼ��������ָ���ļ���
*������	bmpName��ͼ�����ƣ��ַ�����
*	imgBuf����ȡ��ͼ������Դ���ַ�����
*	width��ͼ���ȣ����Σ�
*	height��ͼ��߶ȣ����Σ�
*	biBitCount�������ֽ��������Σ�
*	pColorTable����ɫ��RGBQUAD����ָ�룩
*����ֵ���������bool����
***********************************/
bool BMP::saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable)
{
	if (!imgBuf)
	{
		return 0;
	}
	//�Ҷ�ͼ����ɫ���СΪ1024�ֽڣ���ɫͼ��Ĭ�ϣ���СΪ0�ֽ�  
	int colorTablesize = 0;
	if (biBitCount == 8)
	{
		colorTablesize = 1024;
	}

	//ÿ��������ռ���ֽ��� 
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//������д  
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0)
	{
		return 0;
	}

	//����λͼͷ�ṹ�ռ�
	BITMAPFILEHEADER fileHead;
	//bmp����
	fileHead.bfType = 0x4D42; 
	//ͼ���С���Ĳ������ 
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;

	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	//ͼ���ļ�ǰ3����������ռ��С��ǰ�����ֹ���  
	fileHead.bfOffBits = 54 + colorTablesize;

	//д�ļ�ͷ�ṹд���ļ�  
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//����λͼ��Ϣͷ�ṹ  
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

	//дλͼ��Ϣͷ���ڴ�  
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//����Ҷ�ͼ������ɫ��д���ļ�   
	if (biBitCount == 8)
	{
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//дλͼ���ݽ��ļ�  
	fwrite(imgBuf, height*lineByte, 1, fp); 
	fclose(fp);
	return 1;
}

/**********************************
*���ܣ�����ͼƬ���ƣ�����������Ƿ�Ϸ�
*��������
*����ֵ�������ļ���
***********************************/
char* BMP::getFileName()
{
	//����ͼ���ļ���
	cout << "������ͼ���ļ������ļ���ʽΪ.bmp" << endl;
	char* ret = NULL;
	while (true)
	{
		ret = intArrBuild::stringBuild();
		unsigned length = intArrBuild::getLength(ret);
		//�жϺ�׺�Ƿ�Ϊ".bmp"��ֻ�ܳ���һ��"."
		int point_count = 0;
		for (int i = 0; i < length; i++)
		{
			if (ret[i] == '.')
			{
				point_count++;
			}
		}
		if (length > 4 && ret[length - 4] == '.' && ret[length - 3] == 'b' && ret[length - 2] == 'm' 
			&& ret[length - 1] == 'p' && point_count == 1)
		{
			break;
		}
		cout << "\n********�����ʽ�������������룡********\n" << endl;
		log_t.writeLog("����ͼƬ����ʽ�������������룡");
	}
	return ret;
}

/**********************************
*���ܣ���װ���ݵ�ͼƬ
*������������������
*����ֵ���������bool����
***********************************/
bool BMP::packgeBMP(int** RGB_arr, int arr_length)
{
	int word_count = 0;
	char* readPath = getFileName();
	if (!readBmp(readPath))
	{
		cout << "\n********���ļ�ʧ�ܣ������Ƿ���"<<readPath<<"�ļ���********\n" << endl;
		log_t.writeLog("���ļ�ʧ�ܣ������Ƿ��������ļ���");
		return false;
	}

	//ÿ��������ռ���ֽ�����4�ı�����
	//������Ҫ�ȳ���4��֤����Ϊ4�ı���
	//��Ҫ����3����Ϊ1��2��3�������֣���֤����������С�ռ䲻��̫С
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	//����ļ��򿪣�������Ҫ��ȡͼƬ���ݺ͸ı�����ֵ
	//��ʮ��
	for (int i = 0; i < bmpHeight; i += 10)
	{
		//ÿ��99�����ظı�����ֵ
		for (int j = 0; j < bmpWidth; j += 99)
		{
			//�ı�ÿ�����ص�RGBֵ
			for (int k = 0; k < 3; k++)
			{
				*(pBmpBuf + i*lineByte + j * 3 + k) = RGB_arr[word_count][k];
			}
			word_count++;
		}
		if (word_count >= arr_length)
		{
			break;
		}
	}
	log_t.writeLog("����RGBֵ�޸ĳɹ���");
	cout << "\n********����RGBֵ�޸�ʧ�ܡ�********\n" << endl;
	cout << "��������ܺ��ͼ������" << endl;
	char* bmpName = getFileName();
	saveBmp(bmpName, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	delete[]pBmpBuf;
	return true;
}