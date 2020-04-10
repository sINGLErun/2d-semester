#include <stdio.h>
#include <math.h>
#define SIZE 20

//void arprm (double arr[], int sz);
// void rms (double x, double arr[], int sz);
double* pavrg (double* parr, int* psz);		//указательная часть
//void prms (double* x, double* parr, int* sz);

int putprime (void);
int ending();

void main()
{
	while (1)
	{
		int sz;
		double arr[SIZE];

		printf("\n\tWe will calculate parameters of you array\n");
		printf("\ttell me the size (max: %d): ",SIZE);
		sz=putprime();

		for (int i = 0; i < sz; i++)
		{
			printf("\t  arr[%d]= ", i); 
			scanf("%lf", &arr[i]);
		}

	//	arprm(arr, sz); //проходим по массиву 2 разa// теперь нет
		pavrg(arr, &sz);
		if (ending()==0) return;
	}
}


/*void arprm (double arr[], int sz)
{
	double sm=0, sm2=0, xixj=0;
	double min=0, max=0;
// чтобы получилось надо массив в обратном порядке пройти
	for (int j = 1; j < sz+1; ++j)
	{
		//минимальные и максимальные значения
		if  (j==1) 
		{
			min=arr[sz-1]; max=arr[sz-1];
		}
		if (arr[sz-j]<min) min=arr[sz-j];
		if (arr[sz-j]>max) max=arr[sz-j];

		sm+=arr[sz-j];
		sm2+=arr[sz-j]*arr[sz-j];
	}
	printf("\tminimal element: %f\n", min);
	printf("\tmaximum element: %f\n", max);
	printf("\taverage: %f\n", sm/sz);
	printf("\tyour deviation: %f\n", sqrt(sm2/sz-(sm/sz)*(sm/sz)));
	printf("\n");//тут где-то в формуле наебка
	return;
}
*/
/*

void rms (double x, double arr[], int sz)
{
	double rms=0;

	for (int k = 0; k < sz; ++k)
	{
		rms+=(arr[k]-x)*(arr[k]-x);
	}
	printf("\tstandard deviation: %f\n", sqrt(rms/sz));
	return;
}

*/

double* pavrg (double* parr, int* psz)
{
	double min, max;
	double avrg=0;
	double* pavrg;

	for (int j = 0; j < *psz; j++)
	{
		if (j==0)
		{
			min= *(parr+j); 
			max= *(parr+j);
		}
		if (*(parr+j)<min) min= *(parr+j);
		if (*parr>max) max= *(parr+j);
		avrg+= *(parr+j);
			
	}
	avrg=avrg/(*psz);
	pavrg=&avrg;
	printf("\tminimal element: %f\n", min);
	printf("\tmaximum element: %f\n", max);
	printf("\taverage: %f\n", *pavrg);
	return pavrg;
}

/*void prms (double* x, double* parr, int* psz)
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
*/


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
	while (scanf("%f", &sz)!=1||(sz-(int)sz>0)||sz<=0||sz>SIZE||getchar()!='\n')
	{
		while (getchar()!='\n');
		printf("\tnot enough space, try again: ");
	}
	return sz;
}