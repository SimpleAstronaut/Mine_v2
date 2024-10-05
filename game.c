#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

struct games cache;


int firstInput = 1;    //�Ƿ����״���������
int firstx = 0;    //��¼�״������x
int firsty = 0;    //��¼�״������y


/*************************************************
Function: menu
Description: ���ڴ�ӡ���˵�
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
	printf("******** 1.��ʼ��Ϸ      0.�˳�   ********\n");
	printf("*****************************************\n");
}


/*************************************************
Function: setting
Description: ���ڴ�ӡѡ��˵�
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
	printf("***********   �����׵�����   *************\n");
	printf("*****************************************\n");
}


/*************************************************
Function: start
Description: ��������
Calls: meun(),setting(),game()
Called By: main()
Input: null
Output: nill;
Return: null
Others: ��������game()������������Ϸ
*************************************************/
void start()
{

	//���̳����Լ�����������
	int mine_count = 0;

	int input = 0;
	do
	{
		int status;			
		menu();//���˵�
		//firstInput = 1;
		//printf("��ѡ��: ");
		//status = scanf("%d", &input);
		while (1) 
		{   
			printf("��ѡ��: ");
			status = scanf("%d", &input);
 
			if (status == 1) 
			{
				printf("������������: %d\n", input);  
				break; 
			}
			else 
			{ 
				int c;
				while ((c = getchar()) != '\n' && c != EOF);

				printf("�������������һ��������\n");
			}
		}
		switch (input)
		{
		case 1:
			do
			{
				system("cls");
				setting();

				//printf("������: ");
				//scanf("%d",  &mine_count);
				while (1) 
				{ 
					printf("������: ");
					status = scanf("%d", &mine_count);

					// ���scanf�ķ���ֵ  
					if (status == 1) 
					{
						// ����ɹ���������  
						printf("������������: %d\n", input); 
						break; 
					}
					else 
					{
						// ����ʧ�ܣ���������  
						// ������뻺�����еķǷ��ַ�  
						int c;
						while ((c = getchar()) != '\n' && c != EOF);

						printf("�������������һ��������\n");
					}
				}
				if (mine_count >= ROW * COL)
				{
					printf("�׵��������࣬����������");
					system("pause");
				}
			} while (mine_count >= ROW * COL);	

			//д��games cache�ṹ
			cache.rows = ROWS;
			cache.cols = COLS;
			cache.mine_count = mine_count;

			//void game(int game_row, int game_col, int game_mine_count);
			game(cache);
			break;
		case 0:
			printf("�˳���Ϸ!\n");
			printf("%d", status);
			break;
		default:
			printf("�����������������!\n");
			break;
		}
	} while (input);
}


/*************************************************
Function: game
Description: ��Ϸ������
Calls: BoardInit;SetMine;PrintBoard;Mark
Called By: start
Input: struct games cache ����ṹ��games,����rows,cols��mine_count��������
Output:null
Return: null
Others: ��Ϸ���ɺ���,������������Ϸģ��
*************************************************/
void game(struct games cache)
{
	char mine[ROWS][COLS];
	char show[ROWS][COLS];

	//�����ʼ��
	do
	{
		BoardInit(mine, ROWS, COLS, '0');
		BoardInit(show, ROWS, COLS, '*');

		SetMine(mine, cache);
		system("cls");

		PrintBoard(show, cache);
		//PrintBoard(mine, cache);//������
		//printf("%s", mine);
		//��ӡ���� show��ӡ��������, mine��ӡ��������


		FindMine(mine, show, cache);
	} while (firstInput);
}


/*************************************************
Function: SetMine
Description: ���׺���,������1��ʾ,��֮��0��
Calls: null
Called By: game
Input: ��ά����
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

			//���״������׵�����ʱ������������
			x = randExclude(ROW, firstx);
			y = randExclude(COL, firsty);
		}
		else
		{
			x = rand() % ROW + 1;      //��������׵�����
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
Description: ��ʼ������
Calls: null
Called By: game()
Input: boardΪ��Ҫ��ʼ�������飬rows clos��setΪ�����ʼ������
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
			board[i][j] = set;   //set��ʾҪ��ʶ�����ַ�
		}
	}
}



/*************************************************
Function: PrintBoard
Description: ��ӡ����
Calls: null
Called By: game()
Input: boardΪ��Ҫ��ӡ������,�ڱ�ը������Ҫ��ӡ��������
Return: null
Others: null
*************************************************/
void PrintBoard(char board[ROWS][COLS], struct games cache)
{
	int i, j = 0;
	printf("------ɨ����Ϸ------\n");
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
	printf("------ɨ����Ϸ------\n");
}




/*************************************************
Function: Mark
Description: ����׵�λ��
Calls: null
Called By: game()
Input: boardΪλ�ö�ά����,games cacheΪ������Ϸ������Ϣ
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
		printf("����������Ҫ���λ�õ�����->");
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
					// ����ֱ�����з���EOF�������ַ�  
				} 
				printf("������������������������ÿո�ָ�����\n");
				printf("����������Ҫ���λ�õ�����->");
			}
		}
		if (x >= 1 && x <= cache.rows - 2 && y >= 1 && y <= cache.cols - 2)    //�жϸ������Ƿ�Ϸ�
		{
			if (board[x][y] == '*')        //�жϸ������Ƿ��Ų�
			{
				board[x][y] = '!';
				break;
			}
			else
			{
				printf("��λ�ò��ܱ���ǣ�����������!\n");
			}
		}
		else
		{
			printf("�����������������!\n");
		}
	}
}



/*************************************************
Function: GetMineCount
Description: ��ȡ��Χ�׵ĸ���
Calls: NULL
Called By: ExplosionSpread
Input: board������λ�ö�ά����,xyΪ��Ҫ��ѯ������
Output: ���int�������ݷ�����Χ�׵ĸ���
Return: int
Others: null
*************************************************/
int GetMineCount(char board[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	int count = 0;    //��������������
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
Description: �ݹ�չ����Χ�޵�������
Calls: GetMineCount
Called By: ExplosionSpread
Input: mineΪ�������� showΪ�������� cacheΪ������Ϸ����,xyΪ����,*pwָ��洢������ֹ���
Output: null
Return: null
Others: null
*************************************************/
void ExplosionSpread(char mine[ROWS][COLS], char show[ROWS][COLS], struct games cache, int x, int y, int* pw)
{
	if (x >= 1 && x <= cache.rows - 2 && y >= 1 && y <= cache.cols - 2)  //�ж������Ƿ�Ϊ�Ų鷶Χ��
	{
		int num = GetMineCount(mine, x, y);   //��ȡ������Χ�׵ĸ���
		if (num == 0)
		{
			(*pw)++;
			show[x][y] = ' ';   //�����������Χû���ף��ͰѸ������óɿո񣬲�����Χ�˸�����չ��
			int i = 0;
			int j = 0;
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (show[i][j] == '*')    //���Ƶݹ���������ֹ�Ѿ��Ų���������ٴεݹ飬�Ӷ�������ݹ�
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
Description: ����
Calls: ExplosionSpread
Called By: game()
Input: mine��ά����洢��������,show�洢��������,cache�洢��Ϸ����
Output: null
Return: null
Others: null
*************************************************/
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], struct games cache)
{
	//printf("test");
	int x = 0;
	int y = 0;
	int win = 0;  //��������Ƿ�ȡ��ʤ��
	int* pw = &win;
	char ch = 0;   //���������Ƿ���Ҫ�����
	int row = cache.rows - 2;
	int col = cache.cols - 2;
	while (win < row * col - cache.mine_count)
	{
		printf("����������Ҫ�Ų������->");
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
				// ʧ�ܣ�������뻺�����е�ʣ������  
				int c;
				while ((c = getchar()) != '\n' && c != EOF) 
				{
					// ����ֱ�����з���EOF�������ַ�  
				} 
				printf("������������������������ÿո�ָ�����\n");
				printf("����������Ҫ�Ų������->");
			}
		}
		if (x >= 1 && x <= row && y >= 1 && y <= col)   //�ж�����Ϸ���
		{
			if (mine[x][y] == '1')
			{
				//�ж��Ƿ�Ϊ�״�����
				if (firstInput)
				{
					//printf("���״�ѡ������ף��㻹��һ�λ���");
					//BoardInit(mine, ROWS, COLS, '0');
					//BoardInit(show, ROWS, COLS, '*');
					//SetMine(mine, cache);
					firstx = x;
					firsty = y;
					printf("test\n");
					break;
				}

				system("cls");
				printf("���ź����㱻ը����!\n");
				PrintBoard(mine, cache);   //��ը���˾ʹ�ӡmine���飬���û�֪���Լ���ô����
				break;
			}
			else
			{
				if (show[x][y] != '*')   //�ж��Ƿ��ظ��Ų�
				{
					printf("�������ѱ��Ų飬����������!\n");
					continue;  //ֱ�ӽ�����һ��ѭ��
				}
				else
				{
					firstInput = 0;
					ExplosionSpread(mine, show, cache, x, y, pw);  //��ըչ��һƬ
					system("cls");  //�����Ļ
					PrintBoard(show, cache);  //��ӡ����
					printf("��Ҫ����׵�λ��������y/Y,�����밴�����->");
					while ((ch = getchar()) != '\n');  //��������
					scanf("%c", &ch);
					if (ch == 'Y' || ch == 'y')
					{
						Mark(show, cache);  //�����
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
			printf("�����������������!\n");
		}
	}
	if (win == row * col - cache.mine_count)
	{
		system("cls");
		printf("��ϲ�㣬���׳ɹ�!\n");
		PrintBoard(show, cache);
		return;
	}
}



/*************************************************
Function: randExclude
Description: ����һ���ų�ĳ�����������
Calls: null
Called By: SetMine
Input: max: ���ֵ, exclude: �ų�������
Output: ֱ�����int��������
Return: null
Others: null
*************************************************/
int randExclude(int max, int exclude) {
	int min = 0;
	int num;
	do {
		num = rand() % (max - min + 1) + min;   // ����[min, max]��Χ�ڵ������  
	} while (num == exclude);   // ������ɵ������ų�����������������  
	return num;
}