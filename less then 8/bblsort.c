#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int putpositiveprime (void);
int putprime (void);

int* sort (int (*pcmp)(int, int), int* parr, int* pmch, int sz);
int dcmp (int aj, int ak);
int ucmp (int aj, int ak);
int acmp (int aj, int ak);

int ending();

void main ()
{
	while (1)
	{
		int (*pcmp)(int, int);
		int* parr=NULL; 
		int sz;
		int ls=1,rs=-1;
		int st;
		int truedo=0;
		int mch=0, *pmch=&mch;

		printf("\n\tWe'll sort your array\n");
		printf("\ttell me size of your array: ");

		while (parr==NULL)
		{
			sz=putpositiveprime();
			parr = malloc(sizeof(int)*sz);
			if (parr==NULL) printf("\ti can't allocate memory! try again: ");
		}

		while (ls>rs)
		{
			printf("\ttell me the scatter of random numbers (left): ");
			ls=putprime();
			printf("\t                               and right is?: ");
			rs=putprime();
			if (ls>rs) printf("\tyour left border is more than the right, are you not a mathematician?\n ");
		}

		printf("\thow we sort array? (1 - descending, 2 - ascending, 3 - by absolute value): ");
		
		do
		{	
			st=putprime();
			switch (st)
			{
				case 1:
					pcmp=&dcmp;
					truedo=1;
					break;
				case 2:
					pcmp=&ucmp;
					truedo=1;
					break;
				case 3:
					pcmp=&acmp;
					truedo=1;
					break;
				default:
					printf("\tchose from the list! " );
					continue;
			}
		}
		while (truedo==0);

		printf("\n");
		srand(time(NULL));
		for (int i = 0; i < sz; ++i)
		{
			*(parr+i)=rand()%(rs-ls+1) + ls; 
			printf("\t  arr[%d]=%d\n", i, *(parr+i));

			if (i==0) mch=*parr;
			if ((i!=0)&&(pcmp(mch,*(parr+i))==1)) *pmch=*(parr+i);//это мы ищем самый хороший из элементов сортировки (самый большой при убывании...)
		}

		sort (*pcmp, parr, pmch, sz);
		printf("\n");

		for (int i = 0; i < sz; ++i)
		{ 
			printf("\t  arr'[%d]=%d\n", i, *(parr+i));
		}
		free(parr);

		if (ending()==0) return;
	}
}

int* sort(int (*pcmp)(int, int), int* parr, int* pmch, int sz)
{
	int pte=0;
	for (int j = 0; j < sz; ++j)
	{
		for (int k = j+1; k < sz; ++k)
		{
			if (pcmp(*(parr+j),*(parr+k))==1)
			{
				*(parr+k)+=*(parr+j);
				*(parr+j)=*(parr+k)-*(parr+j);
				*(parr+k)-=*(parr+j);
				pte=1;
			}

			if (pcmp(*pmch,*(parr+k))==0) pte=1; //проверяем находятся ли при проходе элементы похуже (меньше чем самое большое...), если да то плохо
		}

		if (pte==0) break;
		else
		{
			pte=0;
			*pmch=*(parr+j); //т.к. в parr+j по убыванию собираются самые крутые элементы сортировки
		}
	}
	return parr;
}

int dcmp (int aj, int ak)
{
	if (aj<ak) return 1;
	else return 0;
}

int ucmp (int aj, int ak)
{
	if (aj>ak) return 1;
	else return 0;
}

int acmp (int aj, int ak)
{
	if (abs(aj)<abs(ak)) return 1;
	else return 0;
}


// цикл обработки ввода для выхода из программы
int ending()
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

int putpositiveprime (void)
{
    float N=0;
    while (scanf("%f", &N)!=1||(N-(int)N>0)||N<=0||getchar()!='\n')
    {
        while (getchar()!='\n');
        printf("\tyou give unacceptable input! try again: ");
    }
    return N;
}

int putprime ()
{
	float sz=0;
	while (scanf("%f", &sz)!=1||(sz-(int)sz>0)||getchar()!='\n')
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	return sz;
}