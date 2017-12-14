#include<stdio.h>
#include<string.h>

struct Word {
	int no;
	char En[30];
	char Ko[30];
};//단어 구조체

FILE* write = NULL;//쓰기 전용 스트림(초기화)
FILE* add = NULL;//쓰기 전용 스트림(추가)
FILE* read = NULL;//읽기 전용 스트림
//FILE* find = NULL;//읽기 전용 스트림(단어찾기)


void first() {
	char buffer[30];//예비 버퍼
	write = fopen("word.txt", "w");//파일 열기
	add = fopen("word.txt", "a");//파일 열기

	if (write == NULL || add == NULL) puts("파일 열기 오류(first)");
	else {
		fputc('1', write);//몇번째 단어인지 초기화
		for (int i = 0; i < 2; ++i) {
			fgets(buffer, sizeof(buffer), stdin);
			fputs(buffer, add);
		}
	}//파일 열기 성공시 입력 받기

	fclose(write);
	fclose(add);
}//단어 입력받기(초기화)


int findWord(int no) {
	read = fopen("word.txt", "r");
	char number[30];
	char buffer[30];
	char num[30];
	sprintf(number, "%d", no);

	if (read == NULL)puts("파일 열기 오류(find)");
	else {
		while (!feof(read)) {
			fgets(buffer, sizeof(buffer), read);
			if (!strcmp(number, buffer)) {
				fseek(read, 0, SEEK_CUR);
				fclose(read);
				return 0;
			}
		}
	}

	fclose(read);
	return 1;
}

void addWord(int no) {
	char buffer[30];//예비 버퍼
	char number[30];
	add = fopen("word.txt", "a");//파일 열기

	if (add == NULL) puts("파일 열기 오류(add)");
	else {
		sprintf(number, "%d", no);
		fputs(number, add);//몇번째 단어인지 초기화
		if (findWord(no)) {
			for (int i = 0; i < 2; ++i) {
				fgets(buffer, sizeof(buffer), stdin);
				fputs(buffer, add);
			}
		}
		else printf("이미 있는 식별번호 입니다.");
	}

	fclose(add);
}//단어 입력받기(추가)

void readWord(struct Word* word, int start, int end) {
	int j = 0;//word배열의 원소접근
	findWord(start);

	if (read == NULL) puts("파일 열기 오류(read)");
	for (int i = start; i <= end; ++i) {
		fgets((*(word + j)).En, sizeof((*(word + j)).En), read);
		fgets((*(word + j)).Ko, sizeof((*(word + j)).Ko), read);
	}

	fclose(read);
}//단어 읽어오기


int main(void)
{
	struct Word word;
	first();
	addWord(2);
	readWord(&word, 1, 1);
	readWord(&word, 2, 2);
	printf("%s", word.En);
	printf("%s", word.Ko);
	fcloseall();
	return 0;
}