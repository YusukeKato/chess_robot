/**
 * 9.26.2016
 * 9.26.2016
 * Chess Robot Arm
 * Yusuke Kato
 */
 
/**
 * 1.�l�ΐl�őΐ�ł���`�F�X�쐬
 * 2.chessAI�쐬
 * 3.�����̍��W��������āA
 *   ���{�b�g�A�[���ŋ�𓮂�����悤�ɂ���
 */

#include <stdio.h>

#define RANK 10
#define FILE 10

char chess[RANK][FILE] = {
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

int main(void)
{
	int i, j;
	
	for(i = 0; i < RANK; i++) {
		printf("\n");
		for(j = 0; j < FILE; j++) {
			printf(" %c",chess[i][j]);
		}
	}
	return 0;
}