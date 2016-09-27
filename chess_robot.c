/**
 * 9.26.2016
 * 9.27.2016
 * Chess Robot Arm
 * Yusuke Kato
 */
 
/**
 * 1.�l�ΐl�őΐ�ł���`�F�X�쐬
 * 2.chessAI�쐬
 * 3.�����̍��W��������āA
 *   ���{�b�g�A�[���ŋ�𓮂�����悤�ɂ���
 */
 
/**
 * �d�v
 * �E��O����
 *   �E�z��̕������������Ƃ�
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK 10	/* �s */
#define FILE 10	/* �� */
#define ARRAY 5

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
	printf("\n ���� : ");
	gets(input_char);
	
	/* �I���R�}���h */
	if(input_char[0] == 'q') {
		return 1;
	}
	
	/* ��ȊO���w�肵���疳�� */
	if(!(board[input_int[0]][input_int[1]] == 'P' ||
		 board[input_int[0]][input_int[1]] == 'K' ||
		 board[input_int[0]][input_int[1]] == 'Q' ||
		 board[input_int[0]][input_int[1]] == 'B' ||
		 board[input_int[0]][input_int[1]] == 'N' ||
		 board[input_int[0]][input_int[1]] == 'R' )) {
		 return 2;
	}
	
	/* �������int�^�ɕϊ��i�z��ԍ��ɑΉ�������j */
	for(i = 0; i < strlen(input_char); i++) {
		input_int[i] = input_char[i] - '0';
		printf(" %d\n", input_int[i]);
	}
	
	return 0;
}

/* ��ړ� */
void move_chess(void)
{	
	/*�s��w��->���̍s��� */
	board[input_int[2]][input_int[3]] = board[input_int[0]][input_int[1]];
	
	/* �O�̋������ */
	board[input_int[0]][input_int[1]] = '*';
}

/* main�֐� */
int main(void)
{
	int exit_val = 0;
	
	/* 'q'���������A�΋ǏI���܂Ń��[�v */
	for(;exit_val != 1;) {
		
		/* �Ֆʂ��o�� */
		print_board();
	
		/* ���� */
		exit_val = input();
		
		/* ��̎w�肪�s����������X���[ */
		if(!(exit_val == 1 || exit_val == 2)) {
			/* ��ړ� */
			move_chess();
		}
	}
	
	return 0;
}
