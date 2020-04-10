#include "mtrx.h"

unsigned int putpositiveprime (void)
{
	float N=0;
	while (scanf("%f", &N)!=1||(N-(int)N>0)||N<=0||getchar()!='\n')
	{
		while (getchar()!='\n');
		printf("\tyou give unacceptable input! try again: ");
	}
	return N;
}

void memrls (mtrx *pmtr) // освобождение памяти
{
	free(pmtr->s);
	// ???
}

void NaNtest (double x)
{
	if ( isnan(x) != 0 )
	{
		printf("\tdeterminant for square matrices only!\n");
		return;
	}
	else printf("\tdeterminant of matrix A is: %.3lf\n", x);
}

short ending (void) // цикл обработки ввода для выхода из программы
{
	float tfc=0;
	printf("\n\twant to try again? (1-for yes, 0-for no): ");
	while(scanf("%f",&tfc)!=1||(tfc-(int)tfc>0)||((tfc!=1)&&(tfc!=0))||(getchar()!='\n'))
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	if (tfc==0) return 0;
}