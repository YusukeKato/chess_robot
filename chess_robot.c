/**
 * 9.26.2016
 * 9.29.2016
 * Chess Robot
 * Yusuke Kato
 */
 
/**
 * 1.人対人で対戦できるチェス作成	-> できる
 * 2.chessAI作成					-> ルールに従って動かせるくらいでいい
 * 3.現実の座標を取り入れて、
 *   ロボットハンドで駒を動かせるようにする
 *   生体工学 逆運動学				-> 授業で学ぶ
 * 4.上にカメラをつけて画像処理で
 *   プレイヤーの駒の動きを読み取る	-> 授業で学ぶ
 */
 
/**
 * 重要
 * ・配列の長さは正しいか
 * ・配列の初期化は必要か（0はだめ）
 * ・例外処理
 *   ・配列の文字数超えたとき
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

/* 入力 + 入力不正検査 */
int input(void)
{
	int i;
	
	/* 駒の移動を指定する文字列入力 */
	printf("\n (h:help)入力 : ");
	gets(input_char);
	
	/* 終了コマンド */
	if(input_char[0] == 'q') {
		return 1;	/* ゲーム終了 */
	} else if(input_char[0] == 'h') {
		return 3;	/* ヘルプへ */
	}
	
	/* 文字列をint型に変換（配列番号に対応させる） */
	for(i = 0; i < ARRAY; i++) {
		input_int[i] = input_char[i] - '0';
		printf(" %d\n", input_int[i]);
		/* boardの範囲を超える値の入力はエラー */
		if(input_int[i] < 0 || input_int[i] > 7) {
			printf( " 入力が不正です\n");
			return 2;	/* 例外終了 */
		}
	}
	
	/* 指定した駒を書きやすいように簡単な変数に代入 */
	before = board[input_int[0]][input_int[1]];	/* 移動前の駒 */
	after = board[input_int[2]][input_int[3]];	/* 移動後の駒 */
	
	/* 駒以外を指定したら無効 */
	if(!(before == 'P' ||
		 before == 'K' ||
		 before == 'Q' ||
		 before == 'B' ||
		 before == 'N' ||
		 before == 'R' )) {
		 printf(" 駒を指定できていません\n");
		 return 2;	/* 例外終了 */
	}
	
	/* 移動先に自分の駒があったら無効 */
	if( after == 'P' ||
		after == 'K' ||
		after == 'Q' ||
		after == 'B' ||
		after == 'N' ||
		after == 'R' ) {
		printf( " 駒の移動先に自分の駒があります\n");
		return 2;	/* 例外終了 */
	}
	
	return 0;	/* 正常終了 */
}

/* 駒の移動が正しいかチェック */
int move_check(void)
{
	int i;	/* for文用 */
	
	switch (before) {
		/* ポーン 一つ進む（始め二つ進む） */
		case 'P':
			if(input_int[1] != input_int[3]) {
				printf(" 列の入力が不正です\n");
				return 2;	/* 例外終了 */
			}
			if(turn_p1 == 1 && (input_int[2] == (input_int[0] - 2))) {
				return 0;	/* 正常終了 */
			} else if(input_int[2] != (input_int[0] - 1)) {
				printf(" 行の入力が不正です\n");
				return 2;	/* 例外終了 */
			}
			break;
		/* キング 全方向一つ */	
		case 'K':
			/* 行が同じで列が一つ上に行ったとき */
			if(input_int[0] == input_int[2] && input_int[3] == (input_int[1] - 1)) {
				return 0;	/* 正常終了 */
			}
			/* 行が同じで列が一つ下に行ったときとき */
			else if(input_int[0] == input_int[2] && input_int[3] == (input_int[1] + 1)) {
				return 0;	/* 正常終了 */
			}
			/* 列が同じで行が一つ左に行ったとき */
			else if(input_int[1] == input_int[3] && input_int[2] == (input_int[0] - 1)) {
				return 0;	/* 正常終了 */
			}
			/* 列が同じで行が一つ右に行ったとき */
			else if(input_int[1] == input_int[3] && input_int[2] == (input_int[0] + 1)) {
				return 0;	/* 正常終了 */
			}
			/* 斜め左上 */
			else if(input_int[2] == (input_int[0] - 1) && input_int[3] == (input_int[1] - 1)) {
				return 0;	/* 正常終了 */
			}
			/* 斜め左下 */
			else if(input_int[2] == (input_int[0] - 1) && input_int[3] == (input_int[1] + 1)) {
				return 0;	/* 正常終了 */
			}
			/* 斜め右上 */
			else if(input_int[2] == (input_int[0] + 1) && input_int[3] == (input_int[1] - 1)) {
				return 0;	/* 正常終了 */
			}
			/* 斜め右下 */
			else if(input_int[2] == (input_int[0] + 1) && input_int[3] == (input_int[1] + 1)) {
				return 0;	/* 正常終了 */
			}
			/* 不正 */
			else {
				printf(" キングの移動先が不正です\n");
				return 2;	/* 例外終了 */
			}
			//break;	/* return で終了するからbreakいらない */
		/* クイーン 全方向どこまでも（駒は越せない） */	
		case 'Q':
			/* 上に行く iに前行代入 後行まで探索 列は固定 */
			if((input_int[0] > input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = input_int[0] - 1; i > input_int[2]; i--) {
					if(board[input_int[i]][input_int[1]] != '*') {//移動先までの間が'*'だったらOK
						printf(" クイーンの移動先が不正です\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			break;
		/* ビショップ 斜め方向どこまでも（駒は越せない） */	
		case 'B':
		
			break;
		/* ナイト 全方向桂馬（駒を越せる） */	
		case 'N':
			
			break;
		/* ルーク 縦横どこまでも（駒は越せない） */	
		case 'R':
		
			break;
			
		default:
			printf(" エラー move_check\n");
			return 2;	/* 例外終了 */
			//break	/* return で終了するからbreakいらない */
	}
	
	return 0;	/* 重要 */
}

/* 駒移動 */
int move_chess(void)
{	
	/*指定した駒を移動させる */
	board[input_int[2]][input_int[3]] = before;
	
	/* 前の駒を消す */
	board[input_int[0]][input_int[1]] = '*';
	
	/* 勝ち 終了条件 */
	if(after == 'k') {
		printf("\n\n あなたの勝利です\n\n");
		return 1;	/* 勝利 */
	}
	
	return 0;
}

/* ヘルプ */
void help(void)
{
	printf( "\n\n==============================\n"
			"動かしたい駒の行と列と\n"
			"動かしたい場所の行と列を\n"
			"同時に指定してください\n"
			"（例）6454\n"
			" 64のポーンを54へ動かす\n"
			"==============================\n\n");
}

/* main関数 */
int main(void)
{
	int flag = 0;	/* ループ条件や例外処理の結果 */

	//flag = 0 正常
	//flag = 1 終了
	//flag = 2 入力無効
	//flag = 3 ヘルプ
	
	/* 開始コメント */
	printf(" 開始します\n");
	
	/* 'q'を押すか、対局終了までループ */
	for(;flag != 1;) {
		
		/* 盤面を出力 */
		print_board();
	
		/* 入力 + 入力不正検査 */
		flag = input();
		
		/* 駒の移動が正しいかチェック */
		if(flag == 0) {
			flag = move_check();
		}
		
		/* 入力が不正 */
		if(flag == 2) {
			printf(" 入力しなおしてください\n");
		}
		
		/* 駒の指定が不正だったらスルー */
		if(flag == 0) {
			/* 駒移動 */
			flag = move_chess();
			turn_p1++;	/* 駒が動いたらターンが進む */
		} else if(flag == 3) {
			/* ヘルプ */
			help();
		}
		
		/* ターン数表示 */
		printf(" ターン : %d \n", turn_p1);
	}
	
	/* 終了コメント */
	printf(" 終了します\n");
	
	return 0;
}

/**
 * やったこと
 * (2016)
 * 9.26 初日、board設置
 * 9.27 駒移動実装
 * 9.28 例外処理
 * 9.29 駒 player1:大文字 player2:小文字
 * 		駒の動きのルール実装
 */
