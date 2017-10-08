#include "intArrBuild.h"
#include "myKey.h"
#include "BMP.h"
#include "Log.h"

int main(int arg, char* args[])
{
	myKey key;
	key.licOpeartion();
	int key_num = key.keyToNum(key.readKey());
	int** x;
	intArrBuild arr;
	cout << "请输入需要加密的数据：" << endl;
	int l = arr.chsToRGB(arr.chsToInt(arr.CharToWchar(arr.stringBuild())), x, key_num);
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << x[i][j] << " ";
		}
		cout << "\n";
	}
	BMP bmp;
	bmp.packgeBMP(x, l);

	return 0;
}