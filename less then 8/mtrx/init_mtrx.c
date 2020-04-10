#include "mtrx.h"

void initmtr (mtrx *pmtr)
{
		printf("\tprint 1-for input random matrix or 2-for input matrix from file: ");

		float putst=0;

	while(scanf("%f",&putst)!=1||(putst-(int)putst>0)||((putst!=1)&&(putst!=2))||(getchar()!='\n'))
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	
	if (putst == 1) { rndinit(pmtr); return; }
	if (putst == 2) { flread(pmtr); return; }

}

void flread (mtrx *pmtr)
{
	FILE *pfl = NULL;

	while (pfl == NULL)
	{
		pfl = fopen("fileforinputmtrx.txt", "r");
		if ( pfl == NULL ) printf("\tI can't open this file ( fileforinputmtrx.txt )\n");
		else printf("good\n");
	}

	pmtr->n = 0; pmtr->m = 0;
	char ch; 

	do
	{
		ch = getc(pfl);
		if ((ch == ' ')||(ch == '\n')) (pmtr->m)++;
		if (ch == '\n') (pmtr->n)++;
	}
	while (getc(pfl) != EOF);
	pmtr->n++;

//	rewind(pfl);

	printf("%d %d", pmtr->m, pmtr->n);

	fclose(pfl);
	return;
}

void flwrte (mtrx *pmtr)
{
	FILE *pfl = NULL;

	while (pfl == NULL)
	{
		pfl = fopen("fileformtrxres.txt", "w");
		if ( pfl == NULL ) printf("\tI can't write to this file ( fileformtrxres.txt )\n");
	}

	fclose(pfl);
	return ;
}

void rndinit (mtrx *pmtr)
{
	printf("\tlet's choose measurements of matrix %s (n): ", pmtr->name);
	pmtr->n = putpositiveprime();
	printf("\t                                      (m): ");
	pmtr->m = putpositiveprime();

	(pmtr->s)=malloc(sizeof(float)*(pmtr->n)*(pmtr->m));

	for (int i = 0; i < (pmtr->n); i++)
	{
		for (int j = 0; j < (pmtr->m); j++)
		{
			*( (pmtr->s) + i*(pmtr->m) + j ) = 0;
			*( (pmtr->s) + i*(pmtr->m) + j ) = rand()%21-10;
		}
	}
}

void prntmtr (mtrx *pmtr)
{
	if ( isnan( *(pmtr->s) ) != 0 )
	{
		printf("\t%s\n", pmtr->name);
		return;
	}
	else
	{
		printf("\n%s (%dx%d):\n", pmtr->name, pmtr->n, pmtr->m);
		for (int i = 0; i < (pmtr->n); ++i)
		{
			for (int j = 0; j < (pmtr->m); ++j)
			{
				printf("[%d%d] %8.3lf ", i, j, *( (pmtr->s) + i*(pmtr->m) + j) );
			}
			printf("\n");
		}
		printf("\n");
	}
}