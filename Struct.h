#pragma once
#include "Define.h"

typedef struct {
	char data[STACK_CAPACITY_MAX][STRING_MAX];	// �i�[����f�[�^
	int position;								// �i�[�����ʒu
}Stack_t;