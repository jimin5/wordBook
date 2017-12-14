#include<stdio.h>
#include<string.h>

struct Word {
	int no;
	char En[30];
	char Ko[30];
};//�ܾ� ����ü

FILE* write = NULL;//���� ���� ��Ʈ��(�ʱ�ȭ)
FILE* add = NULL;//���� ���� ��Ʈ��(�߰�)
FILE* read = NULL;//�б� ���� ��Ʈ��
//FILE* find = NULL;//�б� ���� ��Ʈ��(�ܾ�ã��)


void first() {
	char buffer[30];//���� ����
	write = fopen("word.txt", "w");//���� ����
	add = fopen("word.txt", "a");//���� ����

	if (write == NULL || add == NULL) puts("���� ���� ����(first)");
	else {
		fputc('1', write);//���° �ܾ����� �ʱ�ȭ
		for (int i = 0; i < 2; ++i) {
			fgets(buffer, sizeof(buffer), stdin);
			fputs(buffer, add);
		}
	}//���� ���� ������ �Է� �ޱ�

	fclose(write);
	fclose(add);
}//�ܾ� �Է¹ޱ�(�ʱ�ȭ)


int findWord(int no) {
	read = fopen("word.txt", "r");
	char number[30];
	char buffer[30];
	char num[30];
	sprintf(number, "%d", no);

	if (read == NULL)puts("���� ���� ����(find)");
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
	char buffer[30];//���� ����
	char number[30];
	add = fopen("word.txt", "a");//���� ����

	if (add == NULL) puts("���� ���� ����(add)");
	else {
		sprintf(number, "%d", no);
		fputs(number, add);//���° �ܾ����� �ʱ�ȭ
		if (findWord(no)) {
			for (int i = 0; i < 2; ++i) {
				fgets(buffer, sizeof(buffer), stdin);
				fputs(buffer, add);
			}
		}
		else printf("�̹� �ִ� �ĺ���ȣ �Դϴ�.");
	}

	fclose(add);
}//�ܾ� �Է¹ޱ�(�߰�)

void readWord(struct Word* word, int start, int end) {
	int j = 0;//word�迭�� ��������
	findWord(start);

	if (read == NULL) puts("���� ���� ����(read)");
	for (int i = start; i <= end; ++i) {
		fgets((*(word + j)).En, sizeof((*(word + j)).En), read);
		fgets((*(word + j)).Ko, sizeof((*(word + j)).Ko), read);
	}

	fclose(read);
}//�ܾ� �о����


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