#pragma once
/* マクロ */
#define ENABLE_DEBUG				// デバッグ機能を有効化する
#define STACK_CAPACITY_MAX 5		// スタックの最大容量
#define CALC_NUM_MAX LLONG_MAX		// 計算の最大値
#define CALC_NUM_MIN LLONG_MIN		// 計算の最小値
#define STRING_ARRAY_MAX 64			// 文字列1種類の配列の最大個数
#define STRING_MAX 128				// 1配列の文字列の最大値
#define EXIT_USEREXIT 2				// ユーザーが自らエンドにしたいときのマクロ
#define STACK_POP_ERROR	"PopError"	// スタックのポップエラー
#define INPUT_ERROR "InputError"	// 入力エラー
#define DISPLAY_STACK_POP_ERROR					"スタックが0の状態でポップしようとしていました。\n"
#define DISPLAY_STACK_PUSH_ERROR				"スタック最大容量を超えてプッシュしようとしていました。\n"
#define DISPLAY_ZERO_DIVISION_ERROR				"0で割ろうとしていました。\n"
#define DISPLAY_DIVISION_OVERFLOW_ERROR			"割り算の計算結果がオーバーフローしました。\n"
#define DISPLAY_MULTIPLICATION_OVERFLOW_ERROR	"掛け算の計算結果がオーバーフローしました。\n"
#define DISPLAY_MINUS_OVERFLOW_ERROR			"引き算の計算結果がオーバーフローしました。\n"
#define DISPLAY_PLUS_OVERFLOW_ERROR				"足し算の計算結果がオーバーフローしました。\n"
#define DISPLAY_PROGRAM_SHUTDOWN				"プログラムを終了します。\n"