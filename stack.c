/*  
 * �X�^�b�N�Ɋւ��鏈��  
 */
#include "GLOBAL.h"

/* �f�[�^�̏����� */
void stack_init(Stack_t *stack) {
	for (int i = 0; i < STACK_CAPACITY_MAX; i++) {
		for (int j = 0; j < STRING_MAX; j++) {
			stack->data[i][j] = '\0';
		}
	}
	stack->position = 0;
}

/* �f�[�^�̃v�b�V��(�i�[)*/
int stack_push(long long int data , Stack_t *stack ) {
	/* �X�^�b�N�̈���z���悤�Ƃ��Ă�����G���[*/
	if (stack->position >= 5 ) {
		return EXIT_FAILURE;
	}
	// �f�[�^���i�[
	sprintf_s(stack->data[stack->position], STRING_MAX, "%lld", data);
	stack->position++;		// �ʒu���X�V(0~4�܂�)
	return EXIT_SUCCESS;	// ����I��
}

/* �f�[�^�̃|�b�v(���o��)*/
char *stack_pop(Stack_t *stack) {
	static char temp[STRING_MAX] = { 0 };
	memset(temp, '\0', sizeof(temp));
	/* �̈�𒴂��ă|�b�v���悤�Ƃ�����G���[*/
	if (stack->position <= 0 ) {
		return STACK_POP_ERROR;
	}
	// �ʒu�����炷
	stack->position--;
	// �f�[�^�̎��o��
	strcpy_s(temp, STRING_MAX - 3 , stack->data[stack->position]);
	// ���������ꏊ��NULL�ɂ���
	for (int i = 0; i < STRING_MAX; i++)
		stack->data[stack->position][i] = '\0';
	return temp;
}

/* ���݂̃X�^�b�N�̕\�� */
void stack_display(Stack_t *stack) {
	for (int i = STACK_CAPACITY_MAX - 1; i >= 0 ; i-- ) {
		printf("stack[%d] = %s\n", i, stack->data[i]);
	}
}