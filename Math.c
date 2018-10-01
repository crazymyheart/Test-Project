/*
	計算を行う関数
*/
#include "GLOBAL.h"

/* 数値の場合 */
int caseNumber(Stack_t *stack , long long int source ) {
	// プッシュしてエラーが起きたらエラーを返す
	if (stack_push(source, stack) == EXIT_FAILURE) {
		printf(DISPLAY_STACK_PUSH_ERROR);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
/* 足し算の演算 */
long long int operatorPlus(long long int data1, long long int data2, int *calcResult ) {
	long long int result = 0;
#ifdef ENABLE_DEBUG
	printf("data1 = %lld , data2 = %lld\n", data1, data2);
#endif
	/* オーバーフローしていたらエラー */
	if ((data2 > 0 && data1 > (LLONG_MAX - data2) ) ||
		(data2 < 0 && data1 < (LLONG_MIN - data2) ) ) {
		printf(DISPLAY_PLUS_OVERFLOW_ERROR);
		fflush(stdout);
		*calcResult = EXIT_FAILURE;
	}
	result = data1 + data2;
	return result;
}
/* 引き算の演算 */
long long int operatorMinus(long long int data1, long long int data2 , int *calcResult ) {
	long long int result = 0;
	/* 最小値を超える計算だったらエラー */
	if ( ( data2 > 0 && data1 < LLONG_MIN + data2 ) ||
			( data2 < 0 && data1 > LLONG_MAX + data2 ) ) {
		printf(DISPLAY_MINUS_OVERFLOW_ERROR);
		fflush(stdout);
		*calcResult = EXIT_FAILURE;
	}
	result = data1 - data2;
	return result;
}
/* 掛け算の演算 */
long long int operatorMP(long long int data1, long long int data2, int *calcResult ) {
	long long int result = 0;
#ifdef ENABLE_DEBUG
	printf("data1 = %lld , data2 = %lld\n", data1, data2);
#endif
	/* オーバーフロー検知 */
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
/* 割り算の演算 */
long long int operatorDivision(long long int data1, long long int data2 , int *calcResult ) {
#ifdef ENABLE_DEBUG
	printf("data1 = %lld , data2 = %lld\n", data1, data2);
#endif
	/* 0割 or -9223372036854775808 / -1 だったらオーバーフローにする*/
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

/* 演算の場合 */
int caseOperator(Stack_t *stack , char operatorChr ) {
	char *endptr , *endptr2;
	long long int data[2] = {0};			// スタック内の数値受け取り用
	long long int result = 0;				// 演算結果格納用
	char tempData[2][STRING_MAX] = { 0 };	// 文字列受け取り用
	int calcResult = 0;						// 計算結果(不正な計算だったらエラーを返す)
	// 値1と値2を受け取る
	strcpy_s(tempData[1], STRING_MAX - 3 , stack_pop(stack));
	strcpy_s(tempData[0], STRING_MAX - 3 , stack_pop(stack));
	data[0] = strtoll( tempData[0] , &endptr  , 10 );
	data[1] = strtoll( tempData[1] , &endptr2 , 10 );
	// 変換に失敗していたら
	if ( *endptr != '\0' || *endptr2 != '\0' ) {
		printf(DISPLAY_STACK_POP_ERROR);
		return EXIT_FAILURE;
	}
	// 計算を行う
	switch (operatorChr) {
		// 足し算の場合
		case '+':
			result = operatorPlus(data[0], data[1], &calcResult );
			break;
		// 引き算の場合
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
			printf("なにかプログラムがおかしい気がする\n");
			break;
	}
	// 計算結果がエラーだったらエラーを返す
	if (calcResult == EXIT_FAILURE) {
		printf( DISPLAY_PROGRAM_SHUTDOWN );
		return EXIT_FAILURE;
	}
	// プッシュしようとしてエラーだったらエラーを返す
	if (stack_push(result, stack) == EXIT_FAILURE) {
		printf(DISPLAY_STACK_PUSH_ERROR);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/* 式の展開 */
int explicateOperator(Stack_t *stack , const char *sourceStr) {
	char *endptr;
	long long int temp = -1;
	/* 数値だったらプッシュする */
	temp = strtoll(sourceStr , &endptr, 0);
	if (endptr[0] == '\0') {
		return caseNumber(stack, temp);
	}
	else {
		/* 演算子だったら */
		if (caseOperator(stack, sourceStr[0]) == EXIT_FAILURE) {
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}