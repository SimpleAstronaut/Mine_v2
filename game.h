#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define MINE '*'  // 定义一个常量来表示雷  

void menu();
void setting();
void start();


void game(struct games cache);
void BoardInit(char board[ROWS][COLS], int rows, int cols, char set);
void SetMine(char board[ROWS][COLS], struct games cache);
void PrintBoard(char board[ROWS][COLS], struct games cache);
void Mark(char board[ROWS][COLS], struct games cache);


int GetMineCount(char board[ROWS][COLS], int x, int y);
void ExplosionSpread(char mine[ROWS][COLS], char show[ROWS][COLS], struct games cache, int x, int y, int* pw);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], struct games cache);

int randExclude(int max, int exclude);


struct games
{
	int rows;
	int cols;
	int mine_count;
};