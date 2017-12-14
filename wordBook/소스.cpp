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
};//�ܾ� ����ü

FILE* write = NULL;//���� ���� ��Ʈ��(�ʱ�ȭ)
FILE* add = NULL;//���� ���� ��Ʈ��(�߰�)
FILE* read = NULL;//�б� ���� ��Ʈ��
FILE* find = NULL;//�б� ���� ��Ʈ��(�ܾ�ã��)


void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}//�Է��� ��ǥ�� Ŀ���� �̵����� �ִ� �Լ�

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
};//���� ���� �Լ� ����

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
}//Ŀ�� ����� �Լ� ����

void main_screen() {
	system("mode con cols=80 lines=25");
	int x = 23, y = 17;
	gotoxy(x, y);     printf("+--------------------------------+");
	gotoxy(x, y + 1); printf("|           �ʵ� �ܾ���          |");
	gotoxy(x, y + 2); printf("+--------------------------------+");//���� ����
	for (int i = 1; i <= 25; ++i) {
		SetColor(GRAY);
		gotoxy(1, i);
		printf("��");
		Sleep(20);
	}//���� ȭ��ǥ ������
	for (int i = 25; i >= 1; --i) {
		SetColor(GRAY);
		gotoxy(78, i);
		printf("��");
		Sleep(20);
	}//������ ȭ��ǥ �ö��
	SetColor(YELLOW);
	int a = 30, b = 5;
	gotoxy(a, b + 11); printf("        ���"); Sleep(50);
	gotoxy(a, b + 10); printf("        ���"); Sleep(50);
	gotoxy(a, b + 8); printf("         ��"); Sleep(50);
	gotoxy(a, b + 7); printf("        ���"); Sleep(50);
	gotoxy(a, b + 6); printf("       ����"); Sleep(50);
	gotoxy(a, b + 5); printf("      �����"); Sleep(50);
	gotoxy(a, b + 4); printf("     ������"); Sleep(50);
	gotoxy(a, b + 3); printf("     ������"); Sleep(50);
	gotoxy(a, b + 2); printf("     ������"); Sleep(50);
	gotoxy(a, b + 1); printf("      �����"); Sleep(50);
	gotoxy(a, b); printf("        ���"); Sleep(50);//����ǥ �׸���
	for (int i = 25; i >= 1; --i) {
		SetColor(BLACK);
		gotoxy(78, i);
		printf("��");
		Sleep(10);
	}//������ ȭ��ǥ ����
	for (int i = 1; i <= 25; ++i) {
		SetColor(BLACK);
		gotoxy(1, i);
		printf("��");
		Sleep(10);
	}//���� ȭ��ǥ ����
	for (int i = 1; i <= 8; ++i) {
		if (i == i) {
			SetColor(BLACK);
			gotoxy(x, y + 3);
			printf("����������������������");
		}
		Sleep(60);
		SetColor(RED);
		gotoxy(x, y + 3);
		printf("     <PRESS ANY KEY TO START>");
		Sleep(60);
	}//���ӽ��۹� �ȳ�
	getch();
}


void first() {
	char buffer[30];//���� ����
	write = fopen("word.txt", "w");//���� ����
	add = fopen("word.txt", "a");//���� ����

	if (write == NULL || add == NULL) puts("���� ���� ����(first)\n");
	else {
		for (int i = 0; i < 2; ++i) {
			fgets(buffer, sizeof(buffer), stdin);
			fputs(buffer, add);
		}
	}//���� ���� ������ �Է� �ޱ�

	fclose(write);
	fclose(add);
}//�ܾ� �Է¹ޱ�(�ʱ�ȭ)

int findWord(char* word) {
	char buffer[30];
	find = fopen("word.txt", "r");

	strlwr(word);

	if (find == NULL)puts("���� ���� ����(find)\n");
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
	char buffer[30];//���� ����
	char tmp[30];
	add = fopen("word.txt", "a");//���� ����

	if (add == NULL) puts("���� ���� ����(add)\n");
	else {
		for (int i = 0; i < 2; ++i) {
			fgets(buffer, sizeof(buffer), stdin);
			strcpy(tmp, buffer);
			tmp[strlen(tmp) - 1] = '\0';
			if (findWord(tmp)) {
				printf("�̹� ��� �Ǿ��ִ� �ܾ� �Դϴ�.\n");
				return;
			}
			fputs(buffer, add);
		}
	}

	fclose(add);
}//�ܾ� �Է¹ޱ�(�߰�)

void readWord(struct Word* word, int start, int end) {
	read = fopen("word.txt", "r");
	int j = 0;//word�迭�� ��������

	if (read == NULL) puts("���� ���� ����(read)\n");
	for (int i = start; i <= end; ++i) {
		fgets((*(word + j)).En, sizeof((*(word + j)).En), read);
		fgets((*(word + j)).Ko, sizeof((*(word + j)).Ko), read);
	}

	fclose(read);
}//�ܾ� �о����


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