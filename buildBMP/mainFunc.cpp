#include "intArrBuild.h"
#include "myKey.h"
#include "BMP.h"
#include "Log.h"

int main()
{
// 	int bum[MAX] = {0};
// 	intArrBuild build;
// 	cout << "��������Ҫ���ܵ����ݣ�" << endl;
// 	build.chsToInt(build.CharToWchar(build.stringBuild()),bum);
// 	int count = 0;
// 	while (bum[count] != 0)
// 	{
// 		cout << bum[count] << endl;
// 		count++;
// 	}
// 	unsigned x = build.getLength(bum);
// 	cout << x << endl;
// 	int** tt;
// 	build.chsToRGB(bum, tt);
// 	for (unsigned i = 0; i < x; i++)
// 	{
// 		for (int j = 0; j < 3; j++)
// 		{
// 			cout << tt[i][j] << " ";
// 		}
// 		cout << "\n";
// 	}
// 	free(tt[0]);
// 	free(tt);


//	myKey mykey;
//	mykey.set_key();
// 	mykey.keyToNum(mykey.get_key());
 //	int flag = mykey.licOpeartion();
// 	cout << flag << endl;
//	char* x = mykey.readKey();
	BMP bmp;
	//char* x = bmp.getFileName();

// 	int** x = NULL;
// 	if (bmp.packgeBMP(x))
// 	{
// 		cout << "ok" << endl;
// 	}
// 	else
// 	{
// 		cout << "fail" << endl;
// 	}
	Log log_t;
	SYSTEMTIME sys = log_t.getTime();
	printf("%4d��%02d��%02d�� %02d:%02d:%02d\n",
		sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute,
		sys.wSecond);
//	log_t.writeLog("��־����");
	return 0;
}