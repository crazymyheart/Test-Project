/*
	�v�Z���s���֐�
*/
#include "GLOBAL.h"

/* ���l�̏ꍇ */
int caseNumber(Stack_t *stack , long long int source ) {
	// �v�b�V�����ăG���[���N������G���[��Ԃ�
	if (stack_push(source, stack) == EXIT_FAILURE) {
		printf(DISPLAY_STACK_PUSH_ERROR);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
/* �����Z�̉��Z */
long long int operatorPlus(long long int data1, long long int data2, int *calcResult ) {
	long long int result = 0;
#ifdef ENABLE_DEBUG
	printf("data1 = %lld , data2 = %lld\n", data1, data2);
#endif
	/* �I�[�o�[�t���[���Ă�����G���[ */
	if ((data2 > 0 && data1 > (LLONG_MAX - data2) ) ||
		(data2 < 0 && data1 < (LLONG_MIN - data2) ) ) {
		printf(DISPLAY_PLUS_OVERFLOW_ERROR);
		fflush(stdout);
		*calcResult = EXIT_FAILURE;
	}
	result = data1 + data2;
	return result;
}
/* �����Z�̉��Z */
long long int operatorMinus(long long int data1, long long int data2 , int *calcResult ) {
	long long int result = 0;
	/* �ŏ��l�𒴂���v�Z��������G���[ */
	if ( ( data2 > 0 && data1 < LLONG_MIN + data2 ) ||
			( data2 < 0 && data1 > LLONG_MAX + data2 ) ) {
		printf(DISPLAY_MINUS_OVERFLOW_ERROR);
		fflush(stdout);
		*calcResult = EXIT_FAILURE;
	}
	result = data1 - data2;
	return result;
}
/* �|���Z�̉��Z */
long long int operatorMP(long long int data1, long long int data2, int *calcResult ) {
	long long int result = 0;
#ifdef ENABLE_DEBUG
	printf("data1 = %lld , data2 = %lld\n", data1, data2);
#endif
	/* �I�[�o�[�t���[���m */
	if ( ( ( data1 >  0 && data2 >  0 ) && data1 > (LLONG_MAX / data2 ) ) ||
		 ( ( data1 >  0 && data2 < 0 ) && data2 < (LLONG_MIN / data1 ) ) ||
		 ( ( data1 < 0 && data2 >  0 ) && data1 < (LLONG_MIN / data2 ) ) ||
		 ( ( data1 < 0 && data2 < 0 ) && data2 < (LLONG_MAX / data1 ) ) ){
		printf(DISPLAY_MULTIPLICATION_OVERFLOW_ERROR);
		fflush(stdout);
		*calcResult = EXIT_FAILURE;
	}
	result = data1 * data2;
	return result;
}
/* ����Z�̉��Z */
long long int operatorDivision(long long int data1, long long int data2 , int *calcResult ) {
#ifdef ENABLE_DEBUG
	printf("data1 = %lld , data2 = %lld\n", data1, data2);
#endif
	/* 0�� or -9223372036854775808 / -1 ��������I�[�o�[�t���[�ɂ���*/
	if ( ( data2 == 0 ) || ( data1 == LLONG_MIN && data2 == -1 ) ) {
		printf(DISPLAY_DIVISION_OVERFLOW_ERROR);
		fflush(stdout);
		*calcResult = EXIT_FAILURE;
		return 0;
	}
	long long int result = 0;
	result = ((double)data1 / (double)data2) + 0.5;
	return result;
}

/* ���Z�̏ꍇ */
int caseOperator(Stack_t *stack , char operatorChr ) {
	char *endptr , *endptr2;
	long long int data[2] = {0};			// �X�^�b�N���̐��l�󂯎��p
	long long int result = 0;				// ���Z���ʊi�[�p
	char tempData[2][STRING_MAX] = { 0 };	// ������󂯎��p
	int calcResult = 0;						// �v�Z����(�s���Ȍv�Z��������G���[��Ԃ�)
	// �l1�ƒl2���󂯎��
	strcpy_s(tempData[1], STRING_MAX - 3 , stack_pop(stack));
	strcpy_s(tempData[0], STRING_MAX - 3 , stack_pop(stack));
	data[0] = strtoll( tempData[0] , &endptr  , 10 );
	data[1] = strtoll( tempData[1] , &endptr2 , 10 );
	// �ϊ��Ɏ��s���Ă�����
	if ( *endptr != '\0' || *endptr2 != '\0' ) {
		printf(DISPLAY_STACK_POP_ERROR);
		return EXIT_FAILURE;
	}
	// �v�Z���s��
	switch (operatorChr) {
		// �����Z�̏ꍇ
		case '+':
			result = operatorPlus(data[0], data[1], &calcResult );
			break;
		// �����Z�̏ꍇ
		case '-':
			result = operatorMinus(data[0], data[1], &calcResult );
			break;
		case '*':
			result = operatorMP(data[0], data[1], &calcResult );
			break;
		case '/':
			result = operatorDivision(data[0], data[1] , &calcResult );
			break;
		default:
			printf("�Ȃɂ��v���O���������������C������\n");
			break;
	}
	// �v�Z���ʂ��G���[��������G���[��Ԃ�
	if (calcResult == EXIT_FAILURE) {
		printf( DISPLAY_PROGRAM_SHUTDOWN );
		return EXIT_FAILURE;
	}
	// �v�b�V�����悤�Ƃ��ăG���[��������G���[��Ԃ�
	if (stack_push(result, stack) == EXIT_FAILURE) {
		printf(DISPLAY_STACK_PUSH_ERROR);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/* ���̓W�J */
int explicateOperator(Stack_t *stack , const char *sourceStr) {
	char *endptr;
	long long int temp = -1;
	/* ���l��������v�b�V������ */
	temp = strtoll(sourceStr , &endptr, 0);
	if (endptr[0] == '\0') {
		return caseNumber(stack, temp);
	}
	else {
		/* ���Z�q�������� */
		if (caseOperator(stack, sourceStr[0]) == EXIT_FAILURE) {
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}