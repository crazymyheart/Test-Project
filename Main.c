#include "GLOBAL.h"

void main() {
	Stack_t stack;											// �X�^�b�N
	char operatorStr[STRING_ARRAY_MAX][STRING_MAX] = { 0 };	// ���͂�����
	int endFlag = 0;										// �v���O�����I���t���O
	/* �X�^�b�N�̏����� */
	stack_init(&stack);
	printf("start\n");
	while (!endFlag) {
		/* �������͂����s���Ă����珉�������čŏ��ɖ߂� */
		if ( getInputString("������͂��Ă�������=>", "���̓G���[�ł��B�����Ȃ��������Ƃɂ��܂��B\n", operatorStr ) == EXIT_FAILURE) {
			continue;
		}
		/* ���̌v�Z */
		for (int i = 0; operatorStr[i][0] != '\0'; i++) {
			// �����v�Z��X�^�b�N�ւ̊i�[�Ǝ��o�������s���Ă���΃G���[��Ԃ�
			if (explicateOperator(&stack, operatorStr[i]) == EXIT_FAILURE) {
				endFlag = 1;
				break;
			}
		}
		/* �G���[����������I�� */
		if (!endFlag)
			stack_display(&stack);	// �X�^�b�N���̕\��
	}
	printf("end\n");
}