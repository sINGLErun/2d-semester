#include <stdio.h>
#include <math.h>
#define N 10000

int Scan_Text(char *pArr, FILE *f) {
	rewind(f);
	int n = 0;
	for (int i = 0; i < N; i++) {
		pArr[i] = getc(f);
		if (pArr[i] == EOF) {
			break;
		}
		n++;
	}
	/*int i = 0;
	do {
		pArr[i] = getc(f);
		n++;
		if (n+1 > N) {
			break;
		}
		i++;
	} while (pArr[i] != EOF);*/
	return n;
}


int Punctuation(char pArr) {
	if ((pArr == '.') || (pArr == ',') || (pArr == '?') || (pArr == '!') || (pArr == ';') || (pArr == ':') || (pArr == ')')) {
		return 1;
	}
		else return 0;
}

void Print_Text(char *pArr, int n) {
	FILE*f;
	fopen_s(&f, "correct_file.txt", "w");
		for (int i = 0; i < n; i++) {
			fprintf(f, "%c", pArr[i]);
		}
	fclose(f);
}

int Check_Overflow (int M) {
	if (M <= 0) {
		printf("Error. Overflow.\n");
		return 1;
	} else return 0;
}

void Delete(char *pArr, int M, int i) {//Ôóíêöèÿ óäàëåíèÿ ñèìâîëà
	for (int j = i; j < M; j++) {
		pArr[j] = pArr[j + 1];
	}
}

void Add(char *pArr, int M, int i) {//Ôóíêöèÿ äîáàâëåíèÿ ïðîáåëà.
	for (int j = M+1; j > i; j--) {
		pArr[j]= pArr[j-1];
	}
	pArr[i] = ' ';
}

int Correct_Spaces(char *pArr, int M) {
	while (pArr[0] == ' ') {
		Delete(pArr, M, 0);//Óäàëåíèå ïðîáåëîâ â íà÷àëå òåêñòà.
		M--;
	}
	int i = 0;
	do {
		while ((pArr[i] == ' ') && (pArr[i + 1] == ' ')) { //Óäàëåíèå íåñêîëüêèõ ïðîáåëîâ, èäóùèõ ïîäðÿä.
			Delete(pArr, M, i);
			M--;
		}
		while (((pArr[i] == ' ') && (Punctuation(pArr[i + 1]) == 1))) {
			Delete(pArr, M, i);//Óäàëåíèå ïðîáåëîâ ïåðåä çíàêàìè ïðåïèíàíèÿ.
			M--;
		}
		while (((Punctuation(pArr[i]) == 1) && (pArr[i + 1] != ' ') && (pArr[i + 1] != '.'))) {
			Add(pArr, M, i + 1); //Äîáàâëåíèå ïðîáåëîâ ïîñëå çíàêîâ ïðåïèíàíèÿ.
			M++;
			if (M > N) { M = 0; break; }
		}
		i++;
		if (M == 0){ break; }
	} while (pArr[i] != EOF);
	return M;
}

void Correct_Size_Letter(char *pArr, int M) {
	if ((pArr[0] >= 97) && (pArr[0] <= 122)) {
		pArr[0] = pArr[0] - 32;
	}
	int i = 0;
	do {
		while ((pArr[i] == '.') && ((pArr[i + 2] >= 97) && (pArr[i + 2] <= 122))) {
			pArr[i + 2] = pArr[i + 2] - 32; //Èçìåíåíèå ðàçìåðà áóêâû â íà÷àëå ïðåäëîæåíèÿ.
		}
		while (((pArr[i - 1] != '.') || ((pArr[i] >= 65) && (pArr[i] <= 122))) && ((pArr[i + 1] >= 65) && (pArr[i + 1] <= 90))) {
			pArr[i + 1] = pArr[i + 1] + 32; //Èçìåíåíèå ðàçìåðà áóêâû â ïðåäëîæåíèè (ñ áîëüøîé íà ìàëåíüêóþ).
		}
		i++;
	} while (pArr[i] != EOF);
}

int Correct_Text(char *pArr, int M) {
	M=Correct_Spaces(pArr, M);
	Correct_Size_Letter(pArr, M);
	return M;
}

int main(){
	FILE *fp; char Mas[N], *pMas; int M; pMas = &Mas;
	if ((fopen_s(&fp, "file.txt", "r") != 0) || (getc(fp) == EOF)) {
		printf("\nError: empty file/file wasn't open.\n");
		return 0;
	}
	else printf("\nSuccessful Nonempty File Opening.\nRemember, program work only with first %d symbols.\n", N);
		M = Scan_Text(pMas, fp);
		M = Correct_Text(pMas, M);
		if (Check_Overflow(M) == 0) { //Ïðîâåðêà íà ïåðåïîëíåíèå.
			Print_Text(pMas, M);
		}
		fclose(fp);
}