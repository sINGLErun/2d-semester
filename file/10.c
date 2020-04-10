#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#define N 10 //Кол-во символов, на которое будет увеличиваться массив при каждом дополнительном выделении памяти.
#define OWERFLOW 100000 //Максимальное кол-во символов, с которыми будет работать программа, в случае отсутствия терминатора.

typedef struct {
	char* pS;
	int n;
	char terminator;
}string;

void false_input() {//Функция, вызывающаяся при неправильном вводе.
	while (getchar() != '\n') {}
	printf("\nError input. Enter the correct value:\n");
}

void realloc_buffer(string *pstr, int i) { //Выделяет память под новые N элементов.
	if (((i+1) % N == 0)&&(i!=0)&&(pstr->pS[i] != pstr->terminator)) {
		char *newpS=NULL;
		newpS = malloc(sizeof(char)*(i + N + 1));
		for (int j = 0; j <= i; j++) {
			newpS[j] = pstr->pS[j];
		}
		free(pstr->pS);
		pstr->pS = newpS;
	}
}

void trim_buffer(string *pstr) { //Выделяет память под точное кол-во символов.
	char* newpS=NULL; 
	newpS = malloc(sizeof(char)*(pstr->n));
	for (int i = 0; i < pstr->n; i++) {
		newpS[i] = pstr->pS[i];
	}
	free(pstr->pS);
	pstr->pS=newpS;
}

void console_input(string *pstr) {
	int i = -1;
	printf("\nWrite your text:\n");
	do {
		i++;
		pstr->pS[i] = getchar();
		realloc_buffer(pstr, i);
	} while ((pstr->pS[i] != pstr->terminator) && (i != OWERFLOW));
	while (getchar()!='\n'){}
	if (pstr->pS[0] == pstr->terminator) {
		i = -1;
	}
	pstr->n = i;
}

void file_input(string *pstr) {
	int i = -1; FILE *fp;
	if ((fopen_s(&fp, "in.txt", "r") != 0) || (getc(fp) == EOF)) {
		printf("\nError: empty file/file wasn't open. Please, write text in console.\n");
		console_input(pstr);
	}
	rewind(fp);
	do {
		i++;
		pstr->pS[i] = getc(fp);
		realloc_buffer(pstr, i);
	} while ((pstr->pS[i] != pstr->terminator) && (i != OWERFLOW)&&(pstr->pS[i] != EOF));
	while (getc(fp) != EOF) {}
	pstr->n = i;
	fclose(fp);
}

void get_text(string *pstr) {
	int t;
	pstr->pS = malloc(sizeof(char)*N);
	printf("Select the source of the text:\n(1)From the console;\n(2)From the file.\n");
	while ((scanf_s("%d", &t) != 1) || ((t != 1) && (t != 2)) || (getchar() != '\n')) {
		false_input();
	}
	if (t == 1) {
		console_input(pstr);
	}
	if (t == 2) {
		file_input(pstr);
	}
	trim_buffer(pstr);
}

void delete(string *pstr, int i) {//Функция удаления символа
	char *newpS = NULL;
	newpS = malloc(sizeof(char)*(pstr->n - 1));
	for (int j = 0; j < i; j++) {
		newpS[j] = pstr->pS[j];
	}
	for (int j = i; j < pstr->n-1; j++) {
		newpS[j] = pstr->pS[j + 1];
	}
	free(pstr->pS);
	pstr->pS = newpS;
}

void add(string *pstr, int i) {//Функция добавления пробела.
	char *newpS = NULL;
	newpS = malloc(sizeof(char)*(pstr->n+1));
	for (int j = 0; j < i; j++) {
		newpS[j] = pstr->pS[j];
	}
	for (int j = pstr->n + 1; j > i; j--) {
		newpS[j] = pstr->pS[j - 1];
	}
	newpS[i] = ' ';
	free(pstr->pS);
	pstr->pS = newpS;
}

int punctuation(char pArr) {
	if ((pArr == '.') || (pArr == ',') || (pArr == '?') || (pArr == '!') || (pArr == ';') || (pArr == ':') || (pArr == ')')) {
		return 1;
	}
	else return 0;
}

int error(int M) {
	if (M == -1) {
		printf("Error. Overflow or no symbols.\n");
		return 1;
	}
	else return 0;
}

void correct_spaces(string *pstr) {
	while ((pstr->pS[0] == ' ')|| (pstr->pS[0] == '\n')) {
		delete(pstr, 0);//Удаление пробелов в начале текста.
		pstr->n--;
	}
	int i = 0;
	do{
		while ((pstr->pS[i] == ' ') && (pstr->pS[i + 1] == ' ')) { //Удаление нескольких пробелов, идущих подряд.
			delete(pstr, i);
			pstr->n--;
		}
		while (((pstr->pS[i] == ' ') && (punctuation(pstr->pS[i + 1]) == 1))) {
			delete(pstr, i);//Удаление пробелов перед знаками препинания.
			pstr->n--;
		}
		while (((punctuation(pstr->pS[i]) == 1) && (pstr->pS[i + 1] != ' ') && (pstr->pS[i + 1] != '.'))) {
			add(pstr, i + 1); //Добавление пробелов после знаков препинания.
			pstr->n++;
			if (pstr->n > OWERFLOW) {pstr->n = -1; break; }
		}
		i++;
		if (pstr->n == -1) { break; }
	} while ((int)i != (int)pstr->n);
}

void correct_size_letter(string *pstr) {
	if ((pstr->pS[0] >= 97) && (pstr->pS[0] <= 122)) {
		pstr->pS[0] = pstr->pS[0] - 32;
	}
	int i = 1;
	do {
		if ((pstr->pS[i] >= 65) && (pstr->pS[i] <= 90)) {
			pstr->pS[i] = pstr->pS[i] + 32; //Изменение размера буквы в предложении (с большой на маленькую).
		}
		i++;
	} while (i!=pstr->n);
	i = 2;
	do {
		if (((pstr->pS[i - 2] == '.') && ((pstr->pS[i] >= 97) && (pstr->pS[i] <= 122))) || ((pstr->pS[i - 3] == '.') && (pstr->pS[i - 1] == '\n') && ((pstr->pS[i] >= 97) && (pstr->pS[i] <= 122)))) {
			pstr->pS[i] = pstr->pS[i] - 32; //Изменение размера буквы в начале предложения.
		}
		i++;
	} while (i != pstr->n);
}

void correct_text(string *pstr) {
	if (pstr->n != -1){
		correct_spaces(pstr);
	if (pstr->n != -1){
		correct_size_letter(pstr);
	}
	}
}

void console_print(string *pstr) {
	printf("\nYour text:\n");
	for (int i = 0; i < pstr->n; i++) {
		printf("%c", pstr->pS[i]);
	}
}

void file_print(string *pstr) {
	FILE*fp;
	fopen_s(&fp, "out.txt", "w");
	fprintf(fp, "\nYour text:\n");
	for (int i = 0; i < pstr->n; i++) {
		fprintf(fp, "%c", pstr->pS[i]);
	}
	fclose(fp);
}

void print(string *pstr) {
	int t;
	printf("\nDo you want print text in console?\n(1)Yes;\n(2)No.\n"); 
	while ((scanf_s("%d", &t) != 1) || ((t != 1) && (t != 2))|| (getchar() != '\n')) {
		false_input();
	}
	if (t == 1) { console_print(pstr); }
	printf("\nDo you want print text in file?\n(1)Yes;\n(2)No.\n"); 
		while ((scanf_s("%d", &t) != 1) || ((t != 1) && (t != 2))|| (getchar() != '\n')) {
			false_input();
		}
		if (t == 1) { file_print(pstr); }
		free(pstr->pS);
}

void get_terminator(string *pstr) {
	printf("What symbol do you want to use as a terminator?\n");
	while ((pstr->terminator = getchar()) && (getchar() != '\n')) {
		false_input();
	}
}

int main ()
{
	string str, *pstr; pstr = &str; int t = 1;
	while (t == 1) {
		get_terminator(pstr);
		get_text(pstr);
		correct_text(pstr);
			if (error(pstr->n) != 1) {
				print(pstr);
			}
		printf("\nDo you want more? \n(1)Yes;\n(2)No.\n");
		while ((scanf_s("%d", &t) != 1) || ((t != 1) && (t != 2)) || (getchar() != '\n')) { false_input(); }
	}
	_CrtDumpMemoryLeaks();
}