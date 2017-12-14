#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define ESC 27
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13



struct Word {
	char En[30];
	char Ko[30];
};//단어 구조체

FILE* write = NULL;//쓰기 전용 스트림(초기화)
FILE* add = NULL;//쓰기 전용 스트림(추가)
FILE* read = NULL;//읽기 전용 스트림
FILE* find = NULL;//읽기 전용 스트림(단어찾기)


void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}//입력한 좌표로 커서를 이동시켜 주는 함수

void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

enum
{
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};//색깔 설정 함수 정의

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}//커서 숨기는 함수 정의

void main_screen() {
	system("mode con cols=80 lines=25");
	int x = 23, y = 17;
	gotoxy(x, y);     printf("+--------------------------------+");
	gotoxy(x, y + 1); printf("|           초등 단어장          |");
	gotoxy(x, y + 2); printf("+--------------------------------+");//게임 제목
	for (int i = 1; i <= 25; ++i) {
		SetColor(GRAY);
		gotoxy(1, i);
		printf("▼");
		Sleep(20);
	}//왼쪽 화살표 내려옴
	for (int i = 25; i >= 1; --i) {
		SetColor(GRAY);
		gotoxy(78, i);
		printf("▲");
		Sleep(20);
	}//오른쪽 화살표 올라옴
	SetColor(YELLOW);
	int a = 30, b = 5;
	gotoxy(a, b + 11); printf("        ■■"); Sleep(50);
	gotoxy(a, b + 10); printf("        ■■"); Sleep(50);
	gotoxy(a, b + 8); printf("         ■"); Sleep(50);
	gotoxy(a, b + 7); printf("        ■■"); Sleep(50);
	gotoxy(a, b + 6); printf("       ■■■"); Sleep(50);
	gotoxy(a, b + 5); printf("      ■■■■"); Sleep(50);
	gotoxy(a, b + 4); printf("     ■■■■■"); Sleep(50);
	gotoxy(a, b + 3); printf("     ■■■■■"); Sleep(50);
	gotoxy(a, b + 2); printf("     ■■■■■"); Sleep(50);
	gotoxy(a, b + 1); printf("      ■■■■"); Sleep(50);
	gotoxy(a, b); printf("        ■■"); Sleep(50);//느낌표 그리기
	for (int i = 25; i >= 1; --i) {
		SetColor(BLACK);
		gotoxy(78, i);
		printf("▲");
		Sleep(10);
	}//오른쪽 화살표 지움
	for (int i = 1; i <= 25; ++i) {
		SetColor(BLACK);
		gotoxy(1, i);
		printf("▼");
		Sleep(10);
	}//왼쪽 화살표 지움
	for (int i = 1; i <= 8; ++i) {
		if (i == i) {
			SetColor(BLACK);
			gotoxy(x, y + 3);
			printf("■■■■■■■■■■■■■■■■■■■■■");
		}
		Sleep(60);
		SetColor(RED);
		gotoxy(x, y + 3);
		printf("     <PRESS ANY KEY TO START>");
		Sleep(60);
	}//게임시작법 안내
	getch();
}


void first() {
	char buffer[30];//예비 버퍼
	write = fopen("word.txt", "w");//파일 열기
	add = fopen("word.txt", "a");//파일 열기

	if (write == NULL || add == NULL) puts("파일 열기 오류(first)\n");
	else {
		for (int i = 0; i < 2; ++i) {
			fgets(buffer, sizeof(buffer), stdin);
			fputs(buffer, add);
		}
	}//파일 열기 성공시 입력 받기

	fclose(write);
	fclose(add);
}//단어 입력받기(초기화)

int findWord(char* word) {
	char buffer[30];
	find = fopen("word.txt", "r");

	strlwr(word);

	if (find == NULL)puts("파일 열기 오류(find)\n");
	else {
		while (!feof(find)) {
			fgets(buffer, sizeof(buffer), find);
			buffer[strlen(buffer) - 1] = '\0';
			strlwr(buffer);
			if (!strcmp(buffer, word)) {
				fclose(find);
				return 1;
			}
		}
	}

	fclose(find);
	return 0;
}

void addWord(int no) {
	char buffer[30];//예비 버퍼
	char tmp[30];
	add = fopen("word.txt", "a");//파일 열기

	if (add == NULL) puts("파일 열기 오류(add)\n");
	else {
		for (int i = 0; i < 2; ++i) {
			fgets(buffer, sizeof(buffer), stdin);
			strcpy(tmp, buffer);
			tmp[strlen(tmp) - 1] = '\0';
			if (findWord(tmp)) {
				printf("이미 등록 되어있는 단어 입니다.\n");
				return;
			}
			fputs(buffer, add);
		}
	}

	fclose(add);
}//단어 입력받기(추가)

void readWord(struct Word* word, int start, int end) {
	read = fopen("word.txt", "r");
	int j = 0;//word배열의 원소접근

	if (read == NULL) puts("파일 열기 오류(read)\n");
	for (int i = start; i <= end; ++i) {
		fgets((*(word + j)).En, sizeof((*(word + j)).En), read);
		fgets((*(word + j)).Ko, sizeof((*(word + j)).Ko), read);
	}

	fclose(read);
}//단어 읽어오기


int main(void)
{
	struct Word word;
	char str[30] = "Banana";
	first();
	addWord(2);
	printf("%d\n", findWord(str));
	fcloseall();
	main_screen();
	return 0;
}