/*  
 * スタックに関する処理  
 */
#include "GLOBAL.h"

/* データの初期化 */
void stack_init(Stack_t *stack) {
	for (int i = 0; i < STACK_CAPACITY_MAX; i++) {
		for (int j = 0; j < STRING_MAX; j++) {
			stack->data[i][j] = '\0';
		}
	}
	stack->position = 0;
}

/* データのプッシュ(格納)*/
int stack_push(long long int data , Stack_t *stack ) {
	/* スタック領域を越えようとしていたらエラー*/
	if (stack->position >= 5 ) {
		return EXIT_FAILURE;
	}
	// データを格納
	sprintf_s(stack->data[stack->position], STRING_MAX, "%lld", data);
	stack->position++;		// 位置を更新(0~4まで)
	return EXIT_SUCCESS;	// 正常終了
}

/* データのポップ(取り出し)*/
char *stack_pop(Stack_t *stack) {
	static char temp[STRING_MAX] = { 0 };
	memset(temp, '\0', sizeof(temp));
	/* 領域を超えてポップしようとしたらエラー*/
	if (stack->position <= 0 ) {
		return STACK_POP_ERROR;
	}
	// 位置をずらす
	stack->position--;
	// データの取り出し
	strcpy_s(temp, STRING_MAX - 3 , stack->data[stack->position]);
	// 元あった場所はNULLにする
	for (int i = 0; i < STRING_MAX; i++)
		stack->data[stack->position][i] = '\0';
	return temp;
}

/* 現在のスタックの表示 */
void stack_display(Stack_t *stack) {
	for (int i = STACK_CAPACITY_MAX - 1; i >= 0 ; i-- ) {
		printf("stack[%d] = %s\n", i, stack->data[i]);
	}
}