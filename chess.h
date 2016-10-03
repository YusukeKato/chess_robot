/**
 * chess.h
 */

/**
 * 9.26.2016
 * 10.3.2016
 * Chess Robot
 * Yusuke Kato
 */
 
/**
 * 1.人対人で対戦できるチェス作成 -> 完成
 * （できれば：チェックメイト表示、キャッスリング、アンパッサン）
 * 2.chessAI作成
 * 3.現実の座標を取り入れて、
 *   ロボットハンドで駒を動かせるようにする
 *   生体工学 逆運動学
 * 4.上にカメラをつけて画像処理で
 *   プレイヤーの駒の動きを読み取る
 */
 
/**
 * 重要
 * ・配列の長さは正しいか -> 問題なさそう
 * ・配列の初期化は必要か（0はだめ） -> 問題なさそう
 * ・例外処理
 *   ・配列の文字数超えたとき -> 問題なさそう
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK 10	/* 行 */
#define FILE 10	/* 列 */
#define ARRAY 4	/* 配列 */
 
/* 盤面配列 */
char board[RANK][FILE] = {
	'r','n','b','q','k','b','n','r','|','0',
	'p','p','p','p','p','p','p','p','|','1',
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
char before;	/* 移動前の駒 */
char after;		/* 移動後の駒 */
int turn_p1 = 1;	/* ターンフラグ player1 */
int turn_p2 = 1;	/* ターンフラグ player2 */
int flag_turn = 1;	/* player1: 1  player2: 2 */

/**
 * やったこと
 * (2016)
 * 9.26 初日、board設置
 * 9.27 駒移動実装
 * 9.28 例外処理
 * 9.29 駒 player1:大文字 player2:小文字
 * 		駒の動きのルール実装
 * 9.30 駒の動きのルール実装
 * 		ターン制実装
 * 10.3 ファイルを分けた（モジュール化？）
 */
