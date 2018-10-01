/*
	�v���C���[����̕������͂��󂯕t����
*/
#include "GLOBAL.h"

int searchStrings(char sourceStr[STRING_ARRAY_MAX][STRING_MAX], const int len);

/* ���[�U�[������͂��󂯕t���� */
int getInputString( const char *askInputNumber , const char *errorInputNumber , char sourceStr[STRING_ARRAY_MAX][STRING_MAX] ) {
	char inputStr[STRING_MAX] = { 0 };
	char *temp;
	char *ctx;
	int i = 0;
	int result = 0;
	memset(sourceStr, '\0', sizeof(sourceStr));
	while (1) {
		// ������
		for (int i = 0; i < STRING_ARRAY_MAX; i++)
			for (int j = 0; j < STRING_MAX; j++)
				sourceStr[i][j] = '\0';
		// ���͂𑣂����͂�\��
		printf("%s", askInputNumber);
		fflush(stdout);
		// ����(120�����܂ŁA���s�͍폜����A�ő啶������125�����܂�)
		scanf_s("%120[^\n]s", inputStr, STRING_MAX - 3 );
		int c;
		// ��ǂ݂����Ď���̕������͂𐳏�ɂ�����
		while ( ( c = getchar() ) != '\n');
		/* ���� */
		temp = strtok_s(inputStr, " " , &ctx );
		/* ������NULL�ɂȂ�܂ŃR�s�[����*/
		for( i = 0 ; temp != NULL ; i++ ){
			strcpy_s(sourceStr[i] , STRING_MAX - 3 , temp );
			temp = strtok_s(NULL, " " , &ctx );
		}
		/* �󕶎����� or �������ăG���[�������珉�������ďI�� */
		if ( i == 0 || ( result = searchStrings(sourceStr , i ) ) == EXIT_FAILURE) {
			printf(errorInputNumber);
			fflush(stdout);
			return EXIT_FAILURE;
		}
		break;
	}
	return EXIT_SUCCESS;
}
/* ��������������Ă��� */
int searchStrings(char sourceStr[STRING_ARRAY_MAX][STRING_MAX] , const int len ) {
	int i;
	long long int temp = -1;
	char *endptr;
	char *temp2;
	// �����ɕϊ���ϊ��ł��Ȃ������������������Ă���
	for (i = 0; i < len; i++) {
		temp = strtoll(sourceStr[i], &endptr, 0);
		// ���l���I�[�o�[�t���[���Ă�����
		if (errno == ERANGE && ( temp == LLONG_MAX || temp == LLONG_MIN ) ) {
			return EXIT_FAILURE;
		}
		// ���l�ɕϊ��ł��Ȃ�������
		if ( endptr[0] != '\0' ) {
			// �������������Ă��Ȃ������� or �w�蕶���������Ă��Ȃ�������
			if (strlen(sourceStr[i]) != 1 || (temp2 = strpbrk(sourceStr[i], "+-*/")) == NULL) {
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}