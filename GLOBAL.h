#pragma once
/* �V�X�e���w�b�_�[ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

/* ����w�b�_�[ */
#include "Struct.h"

/* ����֐� */
extern void stack_init(Stack_t *stack);
extern int stack_push(long long int data, Stack_t *stack);
extern char *stack_pop(Stack_t *stack);
extern int getInputString(const char *askInputNumber, const char *errorInputNumber, char sourceStr[STRING_ARRAY_MAX][STRING_MAX]);
extern int explicateOperator(Stack_t *stack, const char *sourceStr);
extern void stack_display(Stack_t *stack);