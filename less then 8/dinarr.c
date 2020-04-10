#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// double avrg (double arr[], int sz);
// void rms (double x, double arr[], int sz);
double* pavrg (double* parr, int* psz);		//указательная часть
void prms (double* x, double* parr, int* sz);

int putprime (void);
int ending();

void main()
{
	while (1)
	{
		int sz;
		double* parr;

		printf("\n\tWe will calculate parameters of you array\n");
		printf("\ttell me the size: ");
		sz=putprime();
		parr = malloc(sizeof(double)*sz);
		if (parr == NULL) printf("\tCan't allocate memory!\n");

		for (int i = 0; i < sz; i++)
		{
			printf("\t  arr[%d]= ", i); 
			scanf("%lf", (parr+i));
		}

		// rms(avrg(parr, sz), parr, sz); //проходим по массиву 2 разa
		prms(pavrg(parr, &sz), parr, &sz);
		free(parr);
		if (ending()==0) return;
	}
}


double* pavrg (double* parr, int* psz)
{
	double min, max;
	double avrg=0;
	double* pavrg;

	for (int j = 0; j < *psz; j++)
	{
		if (j==0)
		{
			min= *parr; 
			max= *parr;
		}
		if (*parr<min) min= *parr;
		if (*parr>max) max= *parr;
		avrg+= *parr;
		parr++;		
	}
	avrg=avrg/(*psz);
	pavrg=&avrg;
	printf("\tminimal element: %f\n", min);
	printf("\tmaximum element: %f\n", max);
	printf("\taverage: %f\n", *pavrg);
	return pavrg;
}

void prms (double* x, double* parr, int* psz)
{
	double rms=0;

	for (int k = 0; k < *psz; ++k)
	{
		rms+=(*parr - *x)*(*parr - *x);
		parr++;
	}
	printf("\tstandard deviation: %f\n", sqrt(rms/(*psz)));
	return;
}


int ending()
{
// цикл обработки ввода для выхода из программы
	float tfc=0;
	printf("\n\twant to try again? (1-for yes, 0-for no): ");
	while(scanf("%f",&tfc)!=1||(tfc-(int)tfc>0)||((tfc!=1)&&(tfc!=0))||(getchar()!='\n'))
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	if (tfc==0) return 0;
}

int putprime ()
{
	float sz=0;
	while (scanf("%f", &sz)!=1||(sz-(int)sz>0)||sz<=0||getchar()!='\n')
	{
		while (getchar()!='\n');
		printf("\tnot enough space, try again: ");
	}
	return sz;
}