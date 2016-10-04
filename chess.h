#ifndef _CHESS_H_
#define _CHESS_H_

/**
 * chess.h
 */

/**
 * 9.26.2016
 * 10.4.2016
 * Chess Robot
 * Yusuke Kato
 */
 
/**
 * 1.�l�ΐl�őΐ�ł���`�F�X�쐬 -> ����
 * �i�ł���΁F�`�F�b�N���C�g�\���A�X�e�C�����C�g����A�A���p�b�T���j
 * 2.chessAI�쐬
 * 3.�����̍��W��������āA
 *   ���{�b�g�n���h�ŋ�𓮂�����悤�ɂ���
 *   ���̍H�w �t�^���w
 * 4.��ɃJ���������ĉ摜������
 *   �v���C���[�̋�̓�����ǂݎ��
 */
 
/**
 * �d�v
 * �E�z��̒����͐������� -> ���Ȃ�����
 * �E�z��̏������͕K�v���i0�͂��߁j -> ���Ȃ�����
 * �E��O����
 *   �E�z��̕������������Ƃ� -> ���Ȃ�����
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK 10	/* �s */
#define FILE 10	/* �� */
#define ARRAY 4	/* �z�� */
#define MAN_MAX 16 /* ��̍ő吔 */
//��ԍ�
#define KING 12
#define QUEEN 11
#define L_BISHOP 10
#define R_BISHOP 13
#define L_KNIGHT 9
#define R_KNIGHT 14
#define L_ROOK   8
#define R_ROOK   15

/* �֐���` */
/* chess_main */
void print_board(void);
int input(void);
int move_check(void);
int move_chess(void);
void pawn_up(void);
void state_check(void);
int castling(void);
void help(void);
int main(void);

 
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
int man_state_p1[MAN_MAX] = {0}; /* ��̏�Ԃ��L�^ */
int man_state_p2[MAN_MAX] = {0};
char before;	/* �ړ��O�̋� */
char after;		/* �ړ���̋� */
int turn_p1 = 1;	/* �^�[���t���O player1 */
int turn_p2 = 1;	/* �^�[���t���O player2 */
int flag_turn = 1;	/* player1: 1  player2: 2 */

/**
 * ���������
 * (2016)
 * 9.26 �����Aboard�ݒu
 * 9.27 ��ړ�����
 * 9.28 ��O����
 * 9.29 �� player1:�啶�� player2:������
 * 		��̓����̃��[������
 * 9.30 ��̓����̃��[������
 * 		�^�[��������
 * 10.3 �t�@�C���𕪂����i���W���[�����H�j
 * 10.4 �L���b�X�����O����
 * 		�|�[���̓����C��
 */
 
#endif	// _CHESS_H_
