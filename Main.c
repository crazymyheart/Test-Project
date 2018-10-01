#include "GLOBAL.h"

void main() {
	Stack_t stack;											// スタック
	char operatorStr[STRING_ARRAY_MAX][STRING_MAX] = { 0 };	// 入力した式
	int endFlag = 0;										// プログラム終了フラグ
	/* スタックの初期化 */
	stack_init(&stack);
	printf("start\n");
	while (!endFlag) {
		/* もし入力が失敗していたら初期化して最初に戻す */
		if ( getInputString("式を入力してください=>", "入力エラーです。何もなかったことにします。\n", operatorStr ) == EXIT_FAILURE) {
			continue;
		}
		/* 式の計算 */
		for (int i = 0; operatorStr[i][0] != '\0'; i++) {
			// もし計算やスタックへの格納と取り出しが失敗していればエラーを返す
			if (explicateOperator(&stack, operatorStr[i]) == EXIT_FAILURE) {
				endFlag = 1;
				break;
			}
		}
		/* エラーがあったら終了 */
		if (!endFlag)
			stack_display(&stack);	// スタック内の表示
	}
	printf("end\n");
}