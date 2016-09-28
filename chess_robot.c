/**
 * 9.26.2016
 * 9.28.2016
 * Chess Robot
 * Yusuke Kato
 */
 
/**
 * 1.�l�ΐl�őΐ�ł���`�F�X�쐬
 * 2.chessAI�쐬
 * 3.�����̍��W��������āA
 *   ���{�b�g�n���h�ŋ�𓮂�����悤�ɂ���
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

char input_char[ARRAY];	/* ������i�[ */
int input_int[ARRAY];	/* �������int�^�ɕϊ����Ċi�[ */

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

/* ���� */
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
		
		/* �z��̍ő�l�𒴂���l�̓��͂̓G���[ */
		if(input_int[i] < 0 || input_int[i] > 7) {
			printf( "\n ���͂��s���ł�\n"
					" ���͂��Ȃ����Ă�������\n\n");
			return 2;	/* ��O�I�� */
		}
	}
	
	/* ��ȊO���w�肵���疳�� */
	if(!(board[input_int[0]][input_int[1]] == 'P' ||
		 board[input_int[0]][input_int[1]] == 'K' ||
		 board[input_int[0]][input_int[1]] == 'Q' ||
		 board[input_int[0]][input_int[1]] == 'B' ||
		 board[input_int[0]][input_int[1]] == 'N' ||
		 board[input_int[0]][input_int[1]] == 'R' )) {
		 printf("\n ����w��ł��Ă��܂���\n"
		 		" ���͂��Ȃ����Ă�������\n");
		 return 2;	/* ��O�I�� */
	}
	
	return 0;	/* ����I�� */
}

/* ��ړ� */
void move_chess(void)
{	
	/*�s��w��->���̍s��� */
	board[input_int[2]][input_int[3]] = board[input_int[0]][input_int[1]];
	
	/* �O�̋������ */
	board[input_int[0]][input_int[1]] = '*';
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
	int exit_val = 0;
	
	/* �J�n�R�����g */
	printf("\n\n �J�n���܂�\n\n");
	
	/* 'q'���������A�΋ǏI���܂Ń��[�v */
	for(;exit_val != 1;) {
		
		/* �Ֆʂ��o�� */
		print_board();
	
		/* ���� */
		exit_val = input();
		
		/* ��̎w�肪�s����������X���[ */
		if(exit_val == 0) {
			/* ��ړ� */
			move_chess();
		} else if(exit_val == 3) {
			/* �w���v */
			help();
		}
	}
	
	/* �I���R�����g */
	printf("\n\n �I�����܂�\n\n");
	
	return 0;
}

/**
 * ���������
 * (2016)
 * 9.26 �����Aboard�ݒu
 * 9.27 ��ړ�����
 * 9.28 ��O����
 */
