#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

int main()
{
	//设置随机数的种子
	srand((unsigned int)time(NULL));
	start();
	return 0;
}
