#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct
{
	float* s;
	unsigned int n, m;
	char name[50];
} mtrx;

int main()
{
	mtrx A, *pmtr = &A;	
	FILE *pfl = NULL;

	while (pfl == NULL)
	{
		pfl = fopen("fileforinputmtrx.txt", "r");
		if ( pfl == NULL ) printf("\tI can't open this file ( fileforinputmtrx.txt )\n");
		else printf("good\n");
	}

	pmtr->n = 0; pmtr->m = 0;
	char ch;
	rewind(pfl);

	do
	{
		ch=getc(pfl); //почему getc пропускает следующий за читаемым символо символ???????????? 
		printf("%c", ch);
		if ((ch == 32)||(ch == 10)) pmtr->m++;
		if (ch == 10) pmtr->n++;
	}
	while (ch != EOF); // нахуя ты тут гетс оставил, он тебе курсор и переводил, кретин
	pmtr->n++; pmtr->m++;

	printf("\n%d %d", pmtr->m, pmtr->n);

	fclose(pfl);
	return 0;
}

 