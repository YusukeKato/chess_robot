/**
 * 9.26.2016
 * 9.27.2016
 * Chess Robot Arm
 * Yusuke Kato
 */
 
/**
 * 1.人対人で対戦できるチェス作成
 * 2.chessAI作成
 * 3.現実の座標を取り入れて、
 *   ロボットアームで駒を動かせるようにする
 */
 
/**
 * 重要
 * ・例外処理
 *   ・配列の文字数超えたとき
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK 10	/* 行 */
#define FILE 10	/* 列 */
#define ARRAY 5

/* 盤面配列 */
char board[RANK][FILE] = {
	'R','N','B','Q','K','B','N','R','|','0',
	'P','P','P','P','P','P','P','P','|','1',
	'*','*','*','*','*','*','*','*','|','2',
	'*','*','*','*','*','*','*','*','|','3',
	'*','*','*','*','*','*','*','*','|','4',
	'*','*','*','*','*','*','*','*','|','5',
	'P','P','P','P','P','P','P','P','|','6',
	'R','N','B','Q','K','B','N','R','|','7',
	'-','-','-','-','-','-','-','-','+',' ',
	'0','1','2','3','4','5','6','7',' ',' ',
};

char input_char[ARRAY];	/* 文字列格納 */
int input_int[ARRAY];	/* 文字列をint型に変換して格納 */

/* 盤面を出力 */
void print_board(void)
{
	int i, j;
	
	/* 盤面出力 */
	for(i = 0; i < RANK; i++) {
		printf("\n");
		for(j = 0; j < FILE; j++) {
			printf(" %c",board[i][j]);
		}
	}
}

/* 入力 */
int input(void)
{
	int i;
	
	/* 駒の移動を指定する文字列入力 */
	printf("\n 入力 : ");
	gets(input_char);
	
	/* 終了コマンド */
	if(input_char[0] == 'q') {
		return 1;
	}
	
	/* 駒以外を指定したら無効 */
	if(!(board[input_int[0]][input_int[1]] == 'P' ||
		 board[input_int[0]][input_int[1]] == 'K' ||
		 board[input_int[0]][input_int[1]] == 'Q' ||
		 board[input_int[0]][input_int[1]] == 'B' ||
		 board[input_int[0]][input_int[1]] == 'N' ||
		 board[input_int[0]][input_int[1]] == 'R' )) {
		 return 2;
	}
	
	/* 文字列をint型に変換（配列番号に対応させる） */
	for(i = 0; i < strlen(input_char); i++) {
		input_int[i] = input_char[i] - '0';
		printf(" %d\n", input_int[i]);
	}
	
	return 0;
}

/* 駒移動 */
void move_chess(void)
{	
	/*行列指定->次の行列へ */
	board[input_int[2]][input_int[3]] = board[input_int[0]][input_int[1]];
	
	/* 前の駒を消す */
	board[input_int[0]][input_int[1]] = '*';
}

/* main関数 */
int main(void)
{
	int exit_val = 0;
	
	/* 'q'を押すか、対局終了までループ */
	for(;exit_val != 1;) {
		
		/* 盤面を出力 */
		print_board();
	
		/* 入力 */
		exit_val = input();
		
		/* 駒の指定が不正だったらスルー */
		if(!(exit_val == 1 || exit_val == 2)) {
			/* 駒移動 */
			move_chess();
		}
	}
	
	return 0;
}
