/*
	プレイヤーからの文字入力を受け付ける
*/
#include "GLOBAL.h"

int searchStrings(char sourceStr[STRING_ARRAY_MAX][STRING_MAX], const int len);

/* ユーザーから入力を受け付ける */
int getInputString( const char *askInputNumber , const char *errorInputNumber , char sourceStr[STRING_ARRAY_MAX][STRING_MAX] ) {
	char inputStr[STRING_MAX] = { 0 };
	char *temp;
	char *ctx;
	int i = 0;
	int result = 0;
	memset(sourceStr, '\0', sizeof(sourceStr));
	while (1) {
		// 初期化
		for (int i = 0; i < STRING_ARRAY_MAX; i++)
			for (int j = 0; j < STRING_MAX; j++)
				sourceStr[i][j] = '\0';
		// 入力を促す文章を表示
		printf("%s", askInputNumber);
		fflush(stdout);
		// 入力(120文字まで、改行は削除する、最大文字数は125文字まで)
		scanf_s("%120[^\n]s", inputStr, STRING_MAX - 3 );
		int c;
		// 空読みをして次回の文字入力を正常にさせる
		while ( ( c = getchar() ) != '\n');
		/* 分割 */
		temp = strtok_s(inputStr, " " , &ctx );
		/* 分割後NULLになるまでコピーする*/
		for( i = 0 ; temp != NULL ; i++ ){
			strcpy_s(sourceStr[i] , STRING_MAX - 3 , temp );
			temp = strtok_s(NULL, " " , &ctx );
		}
		/* 空文字入力 or 検索してエラーだったら初期化して終了 */
		if ( i == 0 || ( result = searchStrings(sourceStr , i ) ) == EXIT_FAILURE) {
			printf(errorInputNumber);
			fflush(stdout);
			return EXIT_FAILURE;
		}
		break;
	}
	return EXIT_SUCCESS;
}
/* 文字列を検索していく */
int searchStrings(char sourceStr[STRING_ARRAY_MAX][STRING_MAX] , const int len ) {
	int i;
	long long int temp = -1;
	char *endptr;
	char *temp2;
	// 整数に変換後変換できなかった部分を検査していく
	for (i = 0; i < len; i++) {
		temp = strtoll(sourceStr[i], &endptr, 0);
		// 数値がオーバーフローしていたら
		if (errno == ERANGE && ( temp == LLONG_MAX || temp == LLONG_MIN ) ) {
			return EXIT_FAILURE;
		}
		// 数値に変換できなかったら
		if ( endptr[0] != '\0' ) {
			// 文字数があっていなかったら or 指定文字が入っていなかったら
			if (strlen(sourceStr[i]) != 1 || (temp2 = strpbrk(sourceStr[i], "+-*/")) == NULL) {
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}