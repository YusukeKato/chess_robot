/**
 * chess_main.c
 */

#include "chess.h"

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
	if(flag_turn == 1) {
		printf("\n (player1)入力 : ");
	} else if(flag_turn == 2) {
		printf("\n (player2)入力 : ");
	}
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
	
	if(flag_turn == 1) {
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
	} else if(flag_turn == 2) {
		/* 駒以外を指定したら無効 */
		if(!(before == 'p' ||
		 	before == 'k' ||
		 	before == 'q' ||
		 	before == 'b' ||
		 	before == 'n' ||
		 	before == 'r' )) {
		 	printf(" 駒を指定できていません\n");
		 	return 2;	/* 例外終了 */
		}
	}
	
	if(flag_turn == 1) {
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
	} else if(flag_turn == 2) {
		/* 移動先に自分の駒があったら無効 */
		if( after == 'p' ||
			after == 'k' ||
			after == 'q' ||
			after == 'b' ||
			after == 'n' ||
			after == 'r' ) {
			printf( " 駒の移動先に自分の駒があります\n");
			return 2;	/* 例外終了 */
		}
	}
	
	/*player2の駒を判定の時だけ大文字にする */
	switch(before){
		case 'p':
			before = 'P';
			break;
		case 'k':
			before = 'K';
			break;
		case 'q':
			before = 'Q';
			break;
		case 'b':
			before = 'B';
			break;
		case 'n':
			before = 'N';
			break;
		case 'r':
			before = 'R';
			break;
		default:
			break;
	}
	
	return 0;	/* 正常終了 */
}

/* 駒の移動が正しいかチェック */
int move_check(void)
{
	int i, j;	/* for文用 */
	
	switch (before) {
		/* ポーン 一つ進む（始め二つ進む） */
		case 'P':
			/* 列が等しくない場合 */
			if(input_int[1] != input_int[3]) {
				printf(" 列の入力が不正です\n");
				return 2;	/* 例外終了 */
			}
			if(flag_turn == 1) {
				if(turn_p1 == 1 && (input_int[2] == (input_int[0] - 2))) {
					return 0;	/* 正常終了 */
				} else if(input_int[2] != (input_int[0] - 1)) {
					printf(" 行の入力が不正です\n");
					return 2;	/* 例外終了 */
				}
			} else if(flag_turn == 2) {
				if(turn_p2 == 1 && (input_int[2] == (input_int[0] + 2))) {
					return 0;	/* 正常終了 */
				} else if(input_int[2] != (input_int[0] + 1)) {
					printf(" 行の入力が不正です\n");
					return 2;	/* 例外終了 */
				}
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
				for(i = (input_int[0] - 1); i > input_int[2]; i--) {
					if(board[i][input_int[1]] != '*') {//移動先までの間が'*'だったらOK
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 下に行く */
			else if((input_int[0] < input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] + 1); i < input_int[2]; i++) {
					if(board[i][input_int[1]] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 左に行く */
			else if((input_int[1] > input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] - 1); j > input_int[3]; j--) {
					if(board[input_int[0]][j] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 右に行く */
			else if((input_int[1] < input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] + 1); j < input_int[3]; j++) {
					if(board[input_int[0]][j] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 左上に行く */
			else if((input_int[0] > input_int[2]) && (input_int[1] > input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[0] - input_int[2]) != (input_int[1] - input_int[3])) {
					printf(" クイーンの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] - 1), j = (input_int[1] - 1); (i > input_int[2]) && (j > input_int[3]); i--, j--) {//i:行 j:列
					if(board[i][j] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 左下に行く */
			else if((input_int[0] < input_int[2]) && (input_int[1] > input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[2] - input_int[0]) != (input_int[1] - input_int[3])) {
					printf(" クイーンの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] + 1), j = (input_int[1] - 1); (i < input_int[2]) && (j > input_int[3]); i++, j--) {
					if(board[i][j] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 右上に行く */
			else if((input_int[0] > input_int[2]) && (input_int[1] < input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[0] - input_int[2]) != (input_int[3] - input_int[1])) {
					printf(" クイーンの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] - 1), j = (input_int[1] + 1); (i > input_int[2]) && (j < input_int[3]); i--, j++) {
					if(board[i][j] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 右下に行く */
			else if((input_int[0] < input_int[2]) && (input_int[1] < input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[2] - input_int[0]) != (input_int[3] - input_int[1])) {
					printf(" クイーンの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] + 1), j = (input_int[1] + 1); (i < input_int[2]) && (j < input_int[3]); i++, j++) {
					if(board[i][j] != '*') {
						printf(" クイーンの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			break;
		/* ビショップ 斜め方向どこまでも（駒は越せない） */	
		case 'B':
			/* 左上に行く */
			if((input_int[0] > input_int[2]) && (input_int[1] > input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[0] - input_int[2]) != (input_int[1] - input_int[3])) {
					printf(" ビショップの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか i:行 j:列 ループ条件は一つでいいが一応書いておく */
				for(i = (input_int[0] - 1), j = (input_int[1] - 1); (i > input_int[2]) && (j > input_int[3]); i--, j--) {
					if(board[i][j] != '*') {
						printf(" ビショップの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 左下に行く */
			else if((input_int[0] < input_int[2]) && (input_int[1] > input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[2] - input_int[0]) != (input_int[1] - input_int[3])) {
					printf(" ビショップの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] + 1), j = (input_int[1] - 1); (i < input_int[2]) && (j > input_int[3]); i++, j--) {
					if(board[i][j] != '*') {
						printf(" ビショップの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 右上に行く */
			else if((input_int[0] > input_int[2]) && (input_int[1] < input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[0] - input_int[2]) != (input_int[3] - input_int[1])) {
					printf(" ビショップの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] - 1), j = (input_int[1] + 1); (i > input_int[2]) && (j < input_int[3]); i--, j++) {
					if(board[i][j] != '*') {
						printf(" ビショップの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 右下に行く */
			else if((input_int[0] < input_int[2]) && (input_int[1] < input_int[3])) {
				/* 斜め移動では 移動後 - 移動前 が等しかったら正しい */
				if((input_int[2] - input_int[0]) != (input_int[3] - input_int[1])) {
					printf(" ビショップの移動先が不正です（ルート外）\n");
					return 2;	/* 例外終了 */
				}
				/* 移動先まで駒にぶつからないかどうか */
				for(i = (input_int[0] + 1), j = (input_int[1] + 1); (i < input_int[2]) && (j < input_int[3]); i++, j++) {
					if(board[i][j] != '*') {
						printf(" ビショップの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			break;
		/* ナイト 全方向桂馬（駒を越せる） */	
		case 'N':
			/* 上左 */
			if((input_int[2] == (input_int[0] - 2)) && (input_int[3] == input_int[1] - 1)) {
				return 0;	/* 正常終了 */
			}
			/* 上右 */
			else if((input_int[2] == (input_int[0] - 2)) && (input_int[3] == input_int[1] + 1)) {
				return 0;	/* 正常終了 */
			}
			/* 下左 */
			else if((input_int[2] == (input_int[0] + 2)) && (input_int[3] == input_int[1] - 1)) {
				return 0;	/* 正常終了 */
			}
			/* 下右 */
			else if((input_int[2] == (input_int[0] + 2)) && (input_int[3] == input_int[1] + 1)) {
				return 0;	/* 正常終了 */
			}
			/* 左上 */
			else if((input_int[2] == (input_int[0] - 1)) && (input_int[3] == input_int[1] - 2)) {
				return 0;	/* 正常終了 */
			}
			/* 左下 */
			else if((input_int[2] == (input_int[0] + 1)) && (input_int[3] == input_int[1] - 2)) {
				return 0;	/* 正常終了 */
			}
			/* 右上 */
			else if((input_int[2] == (input_int[0] - 1)) && (input_int[3] == input_int[1] + 2)) {
				return 0;	/* 正常終了 */
			}
			/* 右下 */
			else if((input_int[2] == (input_int[0] + 1)) && (input_int[3] == input_int[1] + 2)) {
				return 0;	/* 正常終了 */
			}
			/* それ以外は無効 */
			else {
				printf(" ナイトの移動先が不正です\n");
				return 2;	/* 例外終了 */
			}
			//break;
		/* ルーク 縦横どこまでも（駒は越せない） */	
		case 'R':
			/* 上に行く iに前行代入 後行まで探索 列は固定 */
			if((input_int[0] > input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] - 1); i > input_int[2]; i--) {
					if(board[i][input_int[1]] != '*') {//移動先までの間が'*'だったらOK
						printf(" ルークの移動先が不正です\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 下に行く */
			else if((input_int[0] < input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] + 1); i < input_int[2]; i++) {
					if(board[i][input_int[1]] != '*') {
						printf(" ルークの移動先が不正です\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 左に行く */
			else if((input_int[1] > input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] - 1); j > input_int[3]; j--) {
					if(board[input_int[0]][j] != '*') {
						printf(" ルークの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
			/* 右に行く */
			else if((input_int[1] < input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] + 1); j < input_int[3]; j++) {
					if(board[input_int[0]][j] != '*') {
						printf(" ルークの移動先が不正です（衝突）\n");
						return 2;	/* 例外終了 */
					}
				}
			}
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
	/* 大文字に変えていた駒を小文字に戻す */
	if(flag_turn == 2) {
		switch(before) {
			case 'P':
				before = 'p';
				break;
			case 'K':
				before = 'k';
				break;
			case 'Q':
				before = 'q';
				break;
			case 'B':
				before = 'b';
				break;
			case 'N':
				before = 'n';
				break;
			case 'R':
				before = 'r';
				break;
		}
	}

	/*指定した駒を移動させる */
	board[input_int[2]][input_int[3]] = before;
	
	/* 前の駒を消す */
	board[input_int[0]][input_int[1]] = '*';
	
	/* 勝ち 終了条件 */
	if(after == 'k') {
		printf("\n\n player1の勝利です\n\n");
		return 1;	/* player1勝利 */
	} else if(after == 'K') {
		printf("\n\n player2の勝利です\n\n");
		return 1;	/* player2勝利 */
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
	printf( " 開始します\n"
			" 'h':ヘルプ\n");
	
	/* 'q'を押すか、対局終了までループ */
	for(;flag != 1;) {
		
		/* ターン決定 */
		if(turn_p1 == turn_p2) {
			flag_turn = 1;	/* 先手player1 */
		} else {
			flag_turn = 2;	/* 後手player2 */
		}
		
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
			/* ターン数経過 */
			if(flag_turn == 1) {
				turn_p1++;
			} else if(flag_turn == 2) {
				turn_p2++;
			}
		} else if(flag == 3) {
			/* ヘルプ */
			help();
		}
		
		/* ターン数表示 */
		printf(" player1 : %d ターン目\n", turn_p1);
		printf(" player2 : %d ターン目\n", turn_p2);
	}
	
	/* 終了コメント */
	printf(" 終了します\n");
	
	return 0;
}
