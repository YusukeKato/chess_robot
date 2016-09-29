/**
 * 9.26.2016
 * 9.29.2016
 * Chess Robot
 * Yusuke Kato
 */
 
/**
 * 1.�l�ΐl�őΐ�ł���`�F�X�쐬	-> �ł���
 * 2.chessAI�쐬					-> ���[���ɏ]���ē������邭�炢�ł���
 * 3.�����̍��W��������āA
 *   ���{�b�g�n���h�ŋ�𓮂�����悤�ɂ���
 *   ���̍H�w �t�^���w				-> ���ƂŊw��
 * 4.��ɃJ���������ĉ摜������
 *   �v���C���[�̋�̓�����ǂݎ��	-> ���ƂŊw��
 */
 
/**
 * �d�v
 * �E�z��̒����͐�������
 * �E�z��̏������͕K�v���i0�͂��߁j
 * �E��O����
 *   �E�z��̕������������Ƃ�
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK 10	/* �s */
#define FILE 10	/* �� */
#define ARRAY 4	/* �z�� */

/* �Ֆʔz�� */
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

char input_char[ARRAY];	/* ������i�[ */
int input_int[ARRAY];	/* �������int�^�ɕϊ����Ċi�[ */
char before;	/* �ړ��O�̋� */
char after;		/* �ړ���̋� */
int turn_p1 = 1;	/* �^�[���t���O player1 */
int turn_p2 = 1;	/* �^�[���t���O player2 */

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
	printf("\n (h:help)���� : ");
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
	
	return 0;	/* ����I�� */
}

/* ��̈ړ������������`�F�b�N */
int move_check(void)
{
	int i;	/* for���p */
	
	switch (before) {
		/* �|�[�� ��i�ށi�n�ߓ�i�ށj */
		case 'P':
			if(input_int[1] != input_int[3]) {
				printf(" ��̓��͂��s���ł�\n");
				return 2;	/* ��O�I�� */
			}
			if(turn_p1 == 1 && (input_int[2] == (input_int[0] - 2))) {
				return 0;	/* ����I�� */
			} else if(input_int[2] != (input_int[0] - 1)) {
				printf(" �s�̓��͂��s���ł�\n");
				return 2;	/* ��O�I�� */
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
				for(i = input_int[0] - 1; i > input_int[2]; i--) {
					if(board[input_int[i]][input_int[1]] != '*') {//�ړ���܂ł̊Ԃ�'*'��������OK
						printf(" �N�C�[���̈ړ��悪�s���ł�\n");
						return 2;	/* ��O�I�� */
					}
				}
			}
			break;
		/* �r�V���b�v �΂ߕ����ǂ��܂ł��i��͉z���Ȃ��j */	
		case 'B':
		
			break;
		/* �i�C�g �S�����j�n�i����z����j */	
		case 'N':
			
			break;
		/* ���[�N �c���ǂ��܂ł��i��͉z���Ȃ��j */	
		case 'R':
		
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
	/*�w�肵������ړ������� */
	board[input_int[2]][input_int[3]] = before;
	
	/* �O�̋������ */
	board[input_int[0]][input_int[1]] = '*';
	
	/* ���� �I������ */
	if(after == 'k') {
		printf("\n\n ���Ȃ��̏����ł�\n\n");
		return 1;	/* ���� */
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
	printf(" �J�n���܂�\n");
	
	/* 'q'���������A�΋ǏI���܂Ń��[�v */
	for(;flag != 1;) {
		
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
			turn_p1++;	/* ���������^�[�����i�� */
		} else if(flag == 3) {
			/* �w���v */
			help();
		}
		
		/* �^�[�����\�� */
		printf(" �^�[�� : %d \n", turn_p1);
	}
	
	/* �I���R�����g */
	printf(" �I�����܂�\n");
	
	return 0;
}

/**
 * ���������
 * (2016)
 * 9.26 �����Aboard�ݒu
 * 9.27 ��ړ�����
 * 9.28 ��O����
 * 9.29 �� player1:�啶�� player2:������
 * 		��̓����̃��[������
 */
