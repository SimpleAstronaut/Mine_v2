#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

struct games cache;


int firstInput = 1;    //是否是首次输入坐标
int firstx = 0;    //记录首次输入的x
int firsty = 0;    //记录首次输入的y


/*************************************************
Function: menu
Description: 用于打印主菜单
Calls: printf()
Called By: start()
Input: null
Output: null
Return: null
Others: null
*************************************************/
void menu()
{
	printf("*****************************************\n");
	printf("******** 1.开始游戏      0.退出   ********\n");
	printf("*****************************************\n");
}


/*************************************************
Function: setting
Description: 用于打印选项菜单
Calls: printf()
Called By: start()
Input: null
Output: null
Return: null
Others: null
*************************************************/
void setting()
{
	printf("*****************************************\n");
	printf("***********   输入雷的数量   *************\n");
	printf("*****************************************\n");
}


/*************************************************
Function: start
Description: 启动函数
Calls: meun(),setting(),game()
Called By: main()
Input: null
Output: nill;
Return: null
Others: 负责启动game()函数以启动游戏
*************************************************/
void start()
{

	//雷盘长宽以及雷数量变量
	int mine_count = 0;

	int input = 0;
	do
	{
		int status;			
		menu();//主菜单
		//firstInput = 1;
		//printf("请选择: ");
		//status = scanf("%d", &input);
		while (1) 
		{   
			printf("请选择: ");
			status = scanf("%d", &input);
 
			if (status == 1) 
			{
				printf("您输入了整数: %d\n", input);  
				break; 
			}
			else 
			{ 
				int c;
				while ((c = getchar()) != '\n' && c != EOF);

				printf("输入错误，请输入一个整数。\n");
			}
		}
		switch (input)
		{
		case 1:
			do
			{
				system("cls");
				setting();

				//printf("请输入: ");
				//scanf("%d",  &mine_count);
				while (1) 
				{ 
					printf("请输入: ");
					status = scanf("%d", &mine_count);

					// 检查scanf的返回值  
					if (status == 1) 
					{
						// 输入成功，是整数  
						printf("您输入了整数: %d\n", input); 
						break; 
					}
					else 
					{
						// 输入失败，不是整数  
						// 清除输入缓冲区中的非法字符  
						int c;
						while ((c = getchar()) != '\n' && c != EOF);

						printf("输入错误，请输入一个整数。\n");
					}
				}
				if (mine_count >= ROW * COL)
				{
					printf("雷的数量过多，请重新输入");
					system("pause");
				}
			} while (mine_count >= ROW * COL);	

			//写入games cache结构
			cache.rows = ROWS;
			cache.cols = COLS;
			cache.mine_count = mine_count;

			//void game(int game_row, int game_col, int game_mine_count);
			game(cache);
			break;
		case 0:
			printf("退出游戏!\n");
			printf("%d", status);
			break;
		default:
			printf("输入错误，请重新输入!\n");
			break;
		}
	} while (input);
}


/*************************************************
Function: game
Description: 游戏主函数
Calls: BoardInit;SetMine;PrintBoard;Mark
Called By: start
Input: struct games cache 输入结构体games,包含rows,cols和mine_count三个参数
Output:null
Return: null
Others: 游戏主干函数,负责启动各游戏模块
*************************************************/
void game(struct games cache)
{
	char mine[ROWS][COLS];
	char show[ROWS][COLS];

	//数组初始化
	do
	{
		BoardInit(mine, ROWS, COLS, '0');
		BoardInit(show, ROWS, COLS, '*');

		SetMine(mine, cache);
		system("cls");

		PrintBoard(show, cache);
		//PrintBoard(mine, cache);//测试用
		//printf("%s", mine);
		//打印雷盘 show打印密文雷盘, mine打印明文雷盘


		FindMine(mine, show, cache);
	} while (firstInput);
}


/*************************************************
Function: SetMine
Description: 埋雷函数,有雷用1表示,反之用0·
Calls: null
Called By: game
Input: 二维数组
Output: null
Return: null
Others: null
*************************************************/
void SetMine(char board[ROWS][COLS], struct games cache)
{
	printf("test1\n");
	int count = cache.mine_count;
	while (count)
	{
		int x, y;
		if (firstInput)
		{

			//当首次输入雷的坐标时重新生成雷盘
			x = randExclude(ROW, firstx);
			y = randExclude(COL, firsty);
		}
		else
		{
			x = rand() % ROW + 1;      //随机生成雷的坐标
			y = rand() % COL + 1;
		}
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			//printf("%d %d\n", x, y);
			count--;
		}
	}
	printf("test2\n");
	return;
}



/*************************************************
Function: BoardInit
Description: 初始化数组
Calls: null
Called By: game()
Input: board为需要初始化的数组，rows clos和set为数组初始化参数
Output: null
Return: null
Others: null
*************************************************/
void BoardInit(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;   //set表示要初识化的字符
		}
	}
}



/*************************************************
Function: PrintBoard
Description: 打印雷盘
Calls: null
Called By: game()
Input: board为需要打印的雷盘,在被炸死后需要打印明码雷盘
Return: null
Others: null
*************************************************/
void PrintBoard(char board[ROWS][COLS], struct games cache)
{
	int i, j = 0;
	printf("------扫雷游戏------\n");
	printf("  ");
    for (i = 1; i <= cache.rows - 2; i++)
	{
		printf("%d ", i);
		//printf("\n");
	}
	printf("\n");
	for (i = 1; i <= cache.rows - 2; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= cache.cols - 2; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("------扫雷游戏------\n");
}




/*************************************************
Function: Mark
Description: 标记雷的位置
Calls: null
Called By: game()
Input: board为位置二维数组,games cache为本局游戏缓存信息
Output: null
Return: null
Others: null
*************************************************/
void Mark(char board[ROWS][COLS], struct games cache)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("请输入你想要标记位置的坐标->");
	    int status;
		//scanf("%d %d", &x, &y);
		while (1) {
			status = scanf("%d %d", &x, &y); 
			if (status == 2) 
			{ 
				break;
			}
			else {
				int c;
				while ((c = getchar()) != '\n' && c != EOF) {
					// 忽略直到换行符或EOF的所有字符  
				} 
				printf("输入错误，请输入两个整数（用空格分隔）。\n");
				printf("请输入你想要标记位置的坐标->");
			}
		}
		if (x >= 1 && x <= cache.rows - 2 && y >= 1 && y <= cache.cols - 2)    //判断该坐标是否合法
		{
			if (board[x][y] == '*')        //判断该坐标是否被排查
			{
				board[x][y] = '!';
				break;
			}
			else
			{
				printf("该位置不能被标记，请重新输入!\n");
			}
		}
		else
		{
			printf("输入错误，请重新输入!\n");
		}
	}
}



/*************************************************
Function: GetMineCount
Description: 获取周围雷的个数
Calls: NULL
Called By: ExplosionSpread
Input: board储存雷位置二维数组,xy为需要查询的坐标
Output: 输出int类型数据返回周围雷的个数
Return: int
Others: null
*************************************************/
int GetMineCount(char board[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	int count = 0;    //储存雷数量变量
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (board[i][j] == '1')
			{
				count++;
			}
		}
	}
	return count;
}



/*************************************************
Function: ExplosionSpread
Description: 递归展开周围无地雷坐标
Calls: GetMineCount
Called By: ExplosionSpread
Input: mine为密文雷盘 show为明文雷盘 cache为本局游戏缓存,xy为坐标,*pw指针存储次数防止溢出
Output: null
Return: null
Others: null
*************************************************/
void ExplosionSpread(char mine[ROWS][COLS], char show[ROWS][COLS], struct games cache, int x, int y, int* pw)
{
	if (x >= 1 && x <= cache.rows - 2 && y >= 1 && y <= cache.cols - 2)  //判断坐标是否为排查范围内
	{
		int num = GetMineCount(mine, x, y);   //获取坐标周围雷的个数
		if (num == 0)
		{
			(*pw)++;
			show[x][y] = ' ';   //如果该坐标周围没有雷，就把该坐标置成空格，并向周围八个坐标展开
			int i = 0;
			int j = 0;
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (show[i][j] == '*')    //限制递归条件，防止已经排查过的坐标再次递归，从而造成死递归
						ExplosionSpread(mine, show, cache, i, j, pw);
				}
			}
		}
		else
		{
			(*pw)++;
			show[x][y] = num + '0';
		}
	}
}



/*************************************************
Function: FindMine
Description: 排雷
Calls: ExplosionSpread
Called By: game()
Input: mine二维数组存储密文雷盘,show存储明文雷盘,cache存储游戏缓存
Output: null
Return: null
Others: null
*************************************************/
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], struct games cache)
{
	//printf("test");
	int x = 0;
	int y = 0;
	int win = 0;  //用来标记是否取得胜利
	int* pw = &win;
	char ch = 0;   //用来接受是否需要标记雷
	int row = cache.rows - 2;
	int col = cache.cols - 2;
	while (win < row * col - cache.mine_count)
	{
		printf("请输入你想要排查的坐标->");
		scanf("%d %d", &x, &y);
		int status;
		while (1) 
		{ 
			status = scanf("%d %d", &x, &y);
			if (status == 2) 
			{
				break;
			}
			else 
			{
				// 失败，清除输入缓冲区中的剩余内容  
				int c;
				while ((c = getchar()) != '\n' && c != EOF) 
				{
					// 忽略直到换行符或EOF的所有字符  
				} 
				printf("输入错误，请输入两个整数（用空格分隔）。\n");
				printf("请输入你想要排查的坐标->");
			}
		}
		if (x >= 1 && x <= row && y >= 1 && y <= col)   //判断坐标合法性
		{
			if (mine[x][y] == '1')
			{
				//判断是否为首次输入
				if (firstInput)
				{
					//printf("你首次选择的是雷，你还有一次机会");
					//BoardInit(mine, ROWS, COLS, '0');
					//BoardInit(show, ROWS, COLS, '*');
					//SetMine(mine, cache);
					firstx = x;
					firsty = y;
					printf("test\n");
					break;
				}

				system("cls");
				printf("很遗憾，你被炸死了!\n");
				PrintBoard(mine, cache);   //被炸死了就打印mine数组，让用户知道自己怎么死的
				break;
			}
			else
			{
				if (show[x][y] != '*')   //判断是否重复排查
				{
					printf("该坐标已被排查，请重新输入!\n");
					continue;  //直接进入下一次循环
				}
				else
				{
					firstInput = 0;
					ExplosionSpread(mine, show, cache, x, y, pw);  //爆炸展开一片
					system("cls");  //清空屏幕
					PrintBoard(show, cache);  //打印棋盘
					printf("需要标记雷的位置请输入y/Y,否则请按任意键->");
					while ((ch = getchar()) != '\n');  //清理缓冲区
					scanf("%c", &ch);
					if (ch == 'Y' || ch == 'y')
					{
						Mark(show, cache);  //标记雷
						system("cls");
						PrintBoard(show, cache);
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			printf("输入错误，请重新输入!\n");
		}
	}
	if (win == row * col - cache.mine_count)
	{
		system("cls");
		printf("恭喜你，排雷成功!\n");
		PrintBoard(show, cache);
		return;
	}
}



/*************************************************
Function: randExclude
Description: 生成一个排除某个数的随机数
Calls: null
Called By: SetMine
Input: max: 最大值, exclude: 排除的数字
Output: 直接输出int类型数据
Return: null
Others: null
*************************************************/
int randExclude(int max, int exclude) {
	int min = 0;
	int num;
	do {
		num = rand() % (max - min + 1) + min;   // 生成[min, max]范围内的随机数  
	} while (num == exclude);   // 如果生成的数是排除的数，则重新生成  
	return num;
}