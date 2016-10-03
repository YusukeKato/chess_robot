/**
 * chess_main.c
 */

#include "chess.h"

/* �Ֆʂ��o�� */
void print_board(void)
{
	int i, j;
	
	/* �Ֆʏo�� */
	for(i = 0; i < RANK; i++) {
		printf("\n");
		for(j = 0; j < FILE; j++) {
			printf(" %c",board[i][j]);
		}
	}
}

/* ���� + ���͕s������ */
int input(void)
{
	int i;
	
	/* ��̈ړ����w�肷�镶������� */
	if(flag_turn == 1) {
		printf("\n (player1)���� : ");
	} else if(flag_turn == 2) {
		printf("\n (player2)���� : ");
	}
	gets(input_char);
	
	/* �I���R�}���h */
	if(input_char[0] == 'q') {
		return 1;	/* �Q�[���I�� */
	} else if(input_char[0] == 'h') {
		return 3;	/* �w���v�� */
	}
	
	/* �������int�^�ɕϊ��i�z��ԍ��ɑΉ�������j */
	for(i = 0; i < ARRAY; i++) {
		input_int[i] = input_char[i] - '0';
		printf(" %d\n", input_int[i]);
		/* board�͈̔͂𒴂���l�̓��͂̓G���[ */
		if(input_int[i] < 0 || input_int[i] > 7) {
			printf( " ���͂��s���ł�\n");
			return 2;	/* ��O�I�� */
		}
	}
	
	/* �w�肵����������₷���悤�ɊȒP�ȕϐ��ɑ�� */
	before = board[input_int[0]][input_int[1]];	/* �ړ��O�̋� */
	after = board[input_int[2]][input_int[3]];	/* �ړ���̋� */
	
	if(flag_turn == 1) {
		/* ��ȊO���w�肵���疳�� */
		if(!(before == 'P' ||
		 	before == 'K' ||
		 	before == 'Q' ||
		 	before == 'B' ||
		 	before == 'N' ||
		 	before == 'R' )) {
		 	printf(" ����w��ł��Ă��܂���\n");
		 	return 2;	/* ��O�I�� */
		}
	} else if(flag_turn == 2) {
		/* ��ȊO���w�肵���疳�� */
		if(!(before == 'p' ||
		 	before == 'k' ||
		 	before == 'q' ||
		 	before == 'b' ||
		 	before == 'n' ||
		 	before == 'r' )) {
		 	printf(" ����w��ł��Ă��܂���\n");
		 	return 2;	/* ��O�I�� */
		}
	}
	
	if(flag_turn == 1) {
		/* �ړ���Ɏ����̋�������疳�� */
		if( after == 'P' ||
			after == 'K' ||
			after == 'Q' ||
			after == 'B' ||
			after == 'N' ||
			after == 'R' ) {
			printf( " ��̈ړ���Ɏ����̋����܂�\n");
			return 2;	/* ��O�I�� */
		}
	} else if(flag_turn == 2) {
		/* �ړ���Ɏ����̋�������疳�� */
		if( after == 'p' ||
			after == 'k' ||
			after == 'q' ||
			after == 'b' ||
			after == 'n' ||
			after == 'r' ) {
			printf( " ��̈ړ���Ɏ����̋����܂�\n");
			return 2;	/* ��O�I�� */
		}
	}
	
	/*player2�̋�𔻒�̎������啶���ɂ��� */
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
	
	return 0;	/* ����I�� */
}

/* ��̈ړ������������`�F�b�N */
int move_check(void)
{
	int i, j;	/* for���p */
	
	switch (before) {
		/* �|�[�� ��i�ށi�n�ߓ�i�ށj */
		case 'P':
			/* �񂪓������Ȃ��ꍇ */
			if(input_int[1] != input_int[3]) {
				printf(" ��̓��͂��s���ł�\n");
				return 2;	/* ��O�I�� */
			}
			if(flag_turn == 1) {
				if(turn_p1 == 1 && (input_int[2] == (input_int[0] - 2))) {
					return 0;	/* ����I�� */
				} else if(input_int[2] != (input_int[0] - 1)) {
					printf(" �s�̓��͂��s���ł�\n");
					return 2;	/* ��O�I�� */
				}
			} else if(flag_turn == 2) {
				if(turn_p2 == 1 && (input_int[2] == (input_int[0] + 2))) {
					return 0;	/* ����I�� */
				} else if(input_int[2] != (input_int[0] + 1)) {
					printf(" �s�̓��͂��s���ł�\n");
					return 2;	/* ��O�I�� */
				}
			}
			break;
		/* �L���O �S������� */	
		case 'K':
			/* �s�������ŗ񂪈��ɍs�����Ƃ� */
			if(input_int[0] == input_int[2] && input_int[3] == (input_int[1] - 1)) {
				return 0;	/* ����I�� */
			}
			/* �s�������ŗ񂪈���ɍs�����Ƃ��Ƃ� */
			else if(input_int[0] == input_int[2] && input_int[3] == (input_int[1] + 1)) {
				return 0;	/* ����I�� */
			}
			/* �񂪓����ōs������ɍs�����Ƃ� */
			else if(input_int[1] == input_int[3] && input_int[2] == (input_int[0] - 1)) {
				return 0;	/* ����I�� */
			}
			/* �񂪓����ōs����E�ɍs�����Ƃ� */
			else if(input_int[1] == input_int[3] && input_int[2] == (input_int[0] + 1)) {
				return 0;	/* ����I�� */
			}
			/* �΂ߍ��� */
			else if(input_int[2] == (input_int[0] - 1) && input_int[3] == (input_int[1] - 1)) {
				return 0;	/* ����I�� */
			}
			/* �΂ߍ��� */
			else if(input_int[2] == (input_int[0] - 1) && input_int[3] == (input_int[1] + 1)) {
				return 0;	/* ����I�� */
			}
			/* �΂߉E�� */
			else if(input_int[2] == (input_int[0] + 1) && input_int[3] == (input_int[1] - 1)) {
				return 0;	/* ����I�� */
			}
			/* �΂߉E�� */
			else if(input_int[2] == (input_int[0] + 1) && input_int[3] == (input_int[1] + 1)) {
				return 0;	/* ����I�� */
			}
			/* �s�� */
			else {
				printf(" �L���O�̈ړ��悪�s���ł�\n");
				return 2;	/* ��O�I�� */
			}
			//break;	/* return �ŏI�����邩��break����Ȃ� */
		/* �N�C�[�� �S�����ǂ��܂ł��i��͉z���Ȃ��j */	
		case 'Q':
			/* ��ɍs�� i�ɑO�s��� ��s�܂ŒT�� ��͌Œ� */
			if((input_int[0] > input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] - 1); i > input_int[2]; i--) {
					if(board[i][input_int[1]] != '*') {//�ړ���܂ł̊Ԃ�'*'��������OK
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* ���ɍs�� */
			else if((input_int[0] < input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] + 1); i < input_int[2]; i++) {
					if(board[i][input_int[1]] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* ���ɍs�� */
			else if((input_int[1] > input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] - 1); j > input_int[3]; j--) {
					if(board[input_int[0]][j] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �E�ɍs�� */
			else if((input_int[1] < input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] + 1); j < input_int[3]; j++) {
					if(board[input_int[0]][j] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* ����ɍs�� */
			else if((input_int[0] > input_int[2]) && (input_int[1] > input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[0] - input_int[2]) != (input_int[1] - input_int[3])) {
					printf(" �N�C�[���̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] - 1), j = (input_int[1] - 1); (i > input_int[2]) && (j > input_int[3]); i--, j--) {//i:�s j:��
					if(board[i][j] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �����ɍs�� */
			else if((input_int[0] < input_int[2]) && (input_int[1] > input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[2] - input_int[0]) != (input_int[1] - input_int[3])) {
					printf(" �N�C�[���̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] + 1), j = (input_int[1] - 1); (i < input_int[2]) && (j > input_int[3]); i++, j--) {
					if(board[i][j] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �E��ɍs�� */
			else if((input_int[0] > input_int[2]) && (input_int[1] < input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[0] - input_int[2]) != (input_int[3] - input_int[1])) {
					printf(" �N�C�[���̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] - 1), j = (input_int[1] + 1); (i > input_int[2]) && (j < input_int[3]); i--, j++) {
					if(board[i][j] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �E���ɍs�� */
			else if((input_int[0] < input_int[2]) && (input_int[1] < input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[2] - input_int[0]) != (input_int[3] - input_int[1])) {
					printf(" �N�C�[���̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] + 1), j = (input_int[1] + 1); (i < input_int[2]) && (j < input_int[3]); i++, j++) {
					if(board[i][j] != '*') {
						printf(" �N�C�[���̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			break;
		/* �r�V���b�v �΂ߕ����ǂ��܂ł��i��͉z���Ȃ��j */	
		case 'B':
			/* ����ɍs�� */
			if((input_int[0] > input_int[2]) && (input_int[1] > input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[0] - input_int[2]) != (input_int[1] - input_int[3])) {
					printf(" �r�V���b�v�̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� i:�s j:�� ���[�v�����͈�ł������ꉞ�����Ă��� */
				for(i = (input_int[0] - 1), j = (input_int[1] - 1); (i > input_int[2]) && (j > input_int[3]); i--, j--) {
					if(board[i][j] != '*') {
						printf(" �r�V���b�v�̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �����ɍs�� */
			else if((input_int[0] < input_int[2]) && (input_int[1] > input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[2] - input_int[0]) != (input_int[1] - input_int[3])) {
					printf(" �r�V���b�v�̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] + 1), j = (input_int[1] - 1); (i < input_int[2]) && (j > input_int[3]); i++, j--) {
					if(board[i][j] != '*') {
						printf(" �r�V���b�v�̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �E��ɍs�� */
			else if((input_int[0] > input_int[2]) && (input_int[1] < input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[0] - input_int[2]) != (input_int[3] - input_int[1])) {
					printf(" �r�V���b�v�̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] - 1), j = (input_int[1] + 1); (i > input_int[2]) && (j < input_int[3]); i--, j++) {
					if(board[i][j] != '*') {
						printf(" �r�V���b�v�̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �E���ɍs�� */
			else if((input_int[0] < input_int[2]) && (input_int[1] < input_int[3])) {
				/* �΂߈ړ��ł� �ړ��� - �ړ��O �������������琳���� */
				if((input_int[2] - input_int[0]) != (input_int[3] - input_int[1])) {
					printf(" �r�V���b�v�̈ړ��悪�s���ł��i���[�g�O�j\n");
					return 2;	/* ��O�I�� */
				}
				/* �ړ���܂ŋ�ɂԂ���Ȃ����ǂ��� */
				for(i = (input_int[0] + 1), j = (input_int[1] + 1); (i < input_int[2]) && (j < input_int[3]); i++, j++) {
					if(board[i][j] != '*') {
						printf(" �r�V���b�v�̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			break;
		/* �i�C�g �S�����j�n�i����z����j */	
		case 'N':
			/* �㍶ */
			if((input_int[2] == (input_int[0] - 2)) && (input_int[3] == input_int[1] - 1)) {
				return 0;	/* ����I�� */
			}
			/* ��E */
			else if((input_int[2] == (input_int[0] - 2)) && (input_int[3] == input_int[1] + 1)) {
				return 0;	/* ����I�� */
			}
			/* ���� */
			else if((input_int[2] == (input_int[0] + 2)) && (input_int[3] == input_int[1] - 1)) {
				return 0;	/* ����I�� */
			}
			/* ���E */
			else if((input_int[2] == (input_int[0] + 2)) && (input_int[3] == input_int[1] + 1)) {
				return 0;	/* ����I�� */
			}
			/* ���� */
			else if((input_int[2] == (input_int[0] - 1)) && (input_int[3] == input_int[1] - 2)) {
				return 0;	/* ����I�� */
			}
			/* ���� */
			else if((input_int[2] == (input_int[0] + 1)) && (input_int[3] == input_int[1] - 2)) {
				return 0;	/* ����I�� */
			}
			/* �E�� */
			else if((input_int[2] == (input_int[0] - 1)) && (input_int[3] == input_int[1] + 2)) {
				return 0;	/* ����I�� */
			}
			/* �E�� */
			else if((input_int[2] == (input_int[0] + 1)) && (input_int[3] == input_int[1] + 2)) {
				return 0;	/* ����I�� */
			}
			/* ����ȊO�͖��� */
			else {
				printf(" �i�C�g�̈ړ��悪�s���ł�\n");
				return 2;	/* ��O�I�� */
			}
			//break;
		/* ���[�N �c���ǂ��܂ł��i��͉z���Ȃ��j */	
		case 'R':
			/* ��ɍs�� i�ɑO�s��� ��s�܂ŒT�� ��͌Œ� */
			if((input_int[0] > input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] - 1); i > input_int[2]; i--) {
					if(board[i][input_int[1]] != '*') {//�ړ���܂ł̊Ԃ�'*'��������OK
						printf(" ���[�N�̈ړ��悪�s���ł�\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* ���ɍs�� */
			else if((input_int[0] < input_int[2]) && (input_int[1] == input_int[3])) {
				for(i = (input_int[0] + 1); i < input_int[2]; i++) {
					if(board[i][input_int[1]] != '*') {
						printf(" ���[�N�̈ړ��悪�s���ł�\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* ���ɍs�� */
			else if((input_int[1] > input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] - 1); j > input_int[3]; j--) {
					if(board[input_int[0]][j] != '*') {
						printf(" ���[�N�̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			/* �E�ɍs�� */
			else if((input_int[1] < input_int[3]) && (input_int[0] == input_int[2])) {
				for(j = (input_int[1] + 1); j < input_int[3]; j++) {
					if(board[input_int[0]][j] != '*') {
						printf(" ���[�N�̈ړ��悪�s���ł��i�Փˁj\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			break;
			
		default:
			printf(" �G���[ move_check\n");
			return 2;	/* ��O�I�� */
			//break	/* return �ŏI�����邩��break����Ȃ� */
	}
	
	return 0;	/* �d�v */
}

/* ��ړ� */
int move_chess(void)
{	
	/* �啶���ɕς��Ă�������������ɖ߂� */
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

	/*�w�肵������ړ������� */
	board[input_int[2]][input_int[3]] = before;
	
	/* �O�̋������ */
	board[input_int[0]][input_int[1]] = '*';
	
	/* ���� �I������ */
	if(after == 'k') {
		printf("\n\n player1�̏����ł�\n\n");
		return 1;	/* player1���� */
	} else if(after == 'K') {
		printf("\n\n player2�̏����ł�\n\n");
		return 1;	/* player2���� */
	}
	
	return 0;
}

/* �w���v */
void help(void)
{
	printf( "\n\n==============================\n"
			"������������̍s�Ɨ��\n"
			"�����������ꏊ�̍s�Ɨ��\n"
			"�����Ɏw�肵�Ă�������\n"
			"�i��j6454\n"
			" 64�̃|�[����54�֓�����\n"
			"==============================\n\n");
}

/* main�֐� */
int main(void)
{
	int flag = 0;	/* ���[�v�������O�����̌��� */

	//flag = 0 ����
	//flag = 1 �I��
	//flag = 2 ���͖���
	//flag = 3 �w���v
	
	/* �J�n�R�����g */
	printf( " �J�n���܂�\n"
			" 'h':�w���v\n");
	
	/* 'q'���������A�΋ǏI���܂Ń��[�v */
	for(;flag != 1;) {
		
		/* �^�[������ */
		if(turn_p1 == turn_p2) {
			flag_turn = 1;	/* ���player1 */
		} else {
			flag_turn = 2;	/* ���player2 */
		}
		
		/* �Ֆʂ��o�� */
		print_board();
	
		/* ���� + ���͕s������ */
		flag = input();
		
		/* ��̈ړ������������`�F�b�N */
		if(flag == 0) {
			flag = move_check();
		}
		
		/* ���͂��s�� */
		if(flag == 2) {
			printf(" ���͂��Ȃ����Ă�������\n");
		}
		
		/* ��̎w�肪�s����������X���[ */
		if(flag == 0) {
			/* ��ړ� */
			flag = move_chess();
			/* �^�[�����o�� */
			if(flag_turn == 1) {
				turn_p1++;
			} else if(flag_turn == 2) {
				turn_p2++;
			}
		} else if(flag == 3) {
			/* �w���v */
			help();
		}
		
		/* �^�[�����\�� */
		printf(" player1 : %d �^�[����\n", turn_p1);
		printf(" player2 : %d �^�[����\n", turn_p2);
	}
	
	/* �I���R�����g */
	printf(" �I�����܂�\n");
	
	return 0;
}
