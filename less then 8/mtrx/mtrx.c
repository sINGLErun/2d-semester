#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define RNUM 3

typedef struct
{
	float* s;
	unsigned int n, m;
	char name[50];
} mtrx;

void initmtr (mtrx *pmtr);

short flinit (mtrx *pmtr);
short flprnt (mtrx *pmtr, FILE* pfl);
short rndinit (mtrx *pmtr);
void prntmtr (mtrx *pmtr);

mtrx sumAB (mtrx A, mtrx B);
mtrx prodAB (mtrx A, mtrx B);
void mnrM (mtrx M, mtrx mM, int k, int l);
double detM (mtrx M);
mtrx invrsM (mtrx M, double dM);

short twonumtest (int num1, int num2);
unsigned int putpositivenum (void);
void memrls (mtrx *pmtr);
FILE* AorWtest (void);
void dMtest (double x, FILE* pfl);
short ending (void);

void main (void)
{
	while (1)
	{
		mtrx A, B;
		mtrx res[RNUM];
		double dM;
		FILE* pfl;
		short ans;

		printf("\n\twe will calculate operation with matrix\n");

		srand(time(NULL));
		strcpy(A.name,"A"); initmtr(&A);
		strcpy(B.name,"B"); initmtr(&B);

		prntmtr(&A);
		prntmtr(&B);

		res[0] = sumAB(A, B);
		res[1] = prodAB(A, B);

		printf("\tdeterminant of which matrix to calc.? (1 - for A, 2 - for B): ");
		ans = twonumtest(1, 2);
		if (ans == 1) dM = detM(A);
		else dM = detM(B);

		printf("\tfor which matrix do we calc. inverse? (1 - for A, 2 - for B): ");
		ans = twonumtest(1, 2);
		if (ans == 1) res[2] = invrsM(A, detM(A));
		else res[2] = invrsM(B, detM(B));


		printf("\n");
		pfl = AorWtest();
		dMtest(dM, pfl);
		for (int i = 0; i < RNUM ; ++i)
		{
			flprnt( &res[i], pfl );
			prntmtr( &res[i] );
			memrls( &res[i] );
		}
		fclose(pfl);

		memrls(&A);
		memrls(&B);

		if (ending()==0) return;
	}
}


void initmtr (mtrx *pmtr)
{
	printf("\tprint 1 - for input random matrix or 2 - for input matrix from file: ");
	float ans=0;
	do
	{
		ans = twonumtest(1, 2);

		if ((ans == 1)&&(rndinit(pmtr) != 0)) return;
		if ((ans == 2)&&(flinit(pmtr) != 0)) return;
	}
	while (1);
}

short flinit (mtrx *pmtr)
{
	FILE *pfl = NULL;

	pfl = fopen("fileforinputmtrx.txt", "r");
	if ( pfl == NULL )
	{
		printf("\tI can't open this file ( fileforinputmtrx.txt ) try to choose once more!\n");
		return 0;
	}

	pmtr->n = 0; pmtr->m = 0;
	char ch; 
	do //находим размеры матрицы
	{
		ch = getc(pfl);
		if ((ch == ' ')||(ch == '\n')) pmtr->m++;
		if (ch == '\n') pmtr->n++;
	}
	while (ch != EOF);
	pmtr->n++; pmtr->m++;
	pmtr->m = (unsigned int)((float)(pmtr->m)/pmtr->n);
	rewind(pfl);

	(pmtr->s)=malloc(sizeof(float)*(pmtr->n)*(pmtr->m));
	if (pmtr->s == NULL)
	{
		printf("\tCan't allocate memory! try to choose once more!\n");
		return 0;
	}

	else
	{
		{
		for (int i = 0; i < (pmtr->n); i++)
			for (int j = 0; j < (pmtr->m); j++)
			{
				*((pmtr->s) + i*(pmtr->m) + j)=0;
				fscanf(pfl, "%f", ((pmtr->s) + i*(pmtr->m) + j));
			}
		}
	}

	fclose(pfl);
	return 1;
}

short flprnt (mtrx *pmtr, FILE* pfl)
{
	if ( pfl == NULL )
	{
		printf("\tI can't write to this file ( fileformtrxres.txt )\n");
		return 0;
	}

	if ( isnan( *(pmtr->s) ) != 0 )
	{
		fprintf(pfl, "\t%s\n", pmtr->name);
		return 1;
	}
	else
	{
		fprintf(pfl, "\n%s (%dx%d):\n", pmtr->name, pmtr->n, pmtr->m);
		for (int i = 0; i < (pmtr->n); ++i)
		{
			for (int j = 0; j < (pmtr->m); ++j)
			{
				fprintf(pfl, "[%d%d] %8.3lf ", i, j, *( (pmtr->s) + i*(pmtr->m) + j) );
			}
			fprintf(pfl, "\n");
		}
		fprintf(pfl, "\n");
	}

	return 1;
}

FILE* AorWtest (void)
{	
	short ans;
	printf("\tadd to file or rewrite it? (1 - for add, 2 - for rewrite): "); // так придется каждый раз отвечать и трудно подловить то что ты хочешь сохранить
	ans = twonumtest(1 , 2);
	if (ans == 1) return fopen("fileformtrxres.txt", "a");
	else return fopen("fileformtrxres.txt", "w");
}

short rndinit (mtrx *pmtr)
{
	printf("\tlet's choose measurements of matrix %s (n): ", pmtr->name);
	pmtr->n = putpositivenum();
	printf("\t                                      (m): ");
	pmtr->m = putpositivenum();

	(pmtr->s)=malloc(sizeof(float)*(pmtr->n)*(pmtr->m));
	if (pmtr->s == NULL)
	{
		printf("\tCan't allocate memory!\n");
		return 0;
	}

	else
	{
		for (int i = 0; i < (pmtr->n); i++)
		{
			for (int j = 0; j < (pmtr->m); j++)
			{
				*( (pmtr->s) + i*(pmtr->m) + j ) = 0;
				*( (pmtr->s) + i*(pmtr->m) + j ) = rand()%21-10;
			}
		}
	}
	return 1;
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

mtrx sumAB (mtrx A, mtrx B)
{
	mtrx C;
	C.n = A.n;
	C.m = A.m;
	C.s = malloc(sizeof(float)*(C.n)*(C.m));

	if ((A.n!=B.n)||(A.m!=B.m))
	{
		strcpy(C.name, "such matrices cannot be folded!");
		*C.s = sqrt(-1);
		return C;
	}
	else
	{	
		for (int i = 0; i < A.n; ++i)
		{
			for (int j = 0; j < A.m; ++j)
			{
				*(C.s + i*C.m + j)=(*(A.s + i*A.m + j)) + (*(B.s + i*B.m + j));
			}
		}

		strcpy(C.name, "summ of matrix A and B is C");
		return C;
	}
}

mtrx prodAB (mtrx A, mtrx B)
{
	mtrx C;
	C.n = A.n;
	C.m = B.m;
	C.s = malloc(sizeof(float)*(C.n)*(C.m));

	float pij=0;

	if (A.m!=B.n)
	{
		strcpy(C.name, "these matrices cannot be multiplied!");
		*C.s = sqrt(-1);
		return C;
	}

	for (int i = 0; i < A.n; ++i)
	{
		for (int j = 0; j < B.m; ++j)
		{
			for (int k = 0; k < A.m; ++k)
			{
				pij+=(*((A.s) + i*(A.m) + k))*(*((B.s) + k*(B.m) + j));
			}

			*(C.s + i*C.m + j) = 0;
			*(C.s + i*C.m + j) = pij;
			pij=0;
		}
	}

	strcpy(C.name, "product of matrix A and B is C");
	return C; 
}

double detM (mtrx M) // в этой функции будем считать определитель
{
	double det = 0;
	short id=1;
	mtrx mM;

	if (M.n!=M.m) return sqrt(-1);

	if (M.n==1) return *M.s;
	else if (M.n==2)
	{
		//     a[00]        a[11]                  a[01]          a[10]
		det= ( *M.s )*( *(M.s + M.n + 1) ) - ( *(M.s + 1) )*( *(M.s + M.n) );
		return det;
	}
	else
	{
		mM.n = M.n - 1;
		mM.m = mM.n;
		mM.s = malloc(sizeof(float)*(mM.n)*(mM.n));

		for (int j = 0; j < M.n; ++j)
		{
			mnrM(M,mM,0,j);	//раскладываем по любой строке (сейчас 1-ой)
			det = det + id*( *(M.s + 0*M.n + j) )*detM(mM);
			id*=(-1);
		}

		memrls(&mM);
		return det;
	}
}

void mnrM (mtrx M, mtrx mM, int k, int l) // подпрограмма выписывающая миноры
{
	for (int i = 0; i < M.n; ++i)
	{
		for (int j = 0; j < M.n; ++j)
		{
			if ((i!=k)&&(j!=l))
			{
				//разберись с условиями, где-то ошибка (при попытке посчитать определитель разложением по второй строке)
				//миноры считаются правильно, определитель теперь неправильный
				//это теорема работала о ложном определителе (!), теперь все хорошо

				if ((j<l)&&(i<k)) // чтобы записывать матрицу начиная с первой клетки
				{
					*(mM.s + i*mM.n + j)=*(M.s + i*M.n + j);
				}
				if ((j<l)&&(i>k))
				{
					*(mM.s + (i-1)*mM.n + j)=*(M.s + i*M.n + j);
				}
				if ((j>l)&&(i<k))
				{
					*(mM.s + i*mM.n + j-1)=*(M.s + i*M.n + j);
				}
				if ((j>l)&&(i>k))
				{
					*(mM.s + (i-1)*mM.n + j-1)=*(M.s + i*M.n + j);
				} 
			}
		}
	}
}

mtrx invrsM (mtrx M, double dM)
{
	mtrx iM;
	iM.n = M.n; iM.m = iM.n;
	iM.s = malloc(sizeof(float)*(iM.n)*(iM.n));


	if ((dM == 0)||(M.n!=M.m))
	{
		strcpy(iM.name, "matrix has no inverse!");
		*iM.s = sqrt(-1);
		return iM;
	}
	else
	{
		short id = 1;

		mtrx mM;

		mM.n = M.n - 1; mM.m = mM.n;
		mM.s = malloc(sizeof(float)*(mM.n)*(mM.n));

		for (int i = 0; i < M.n; ++i)
		{
			for (int j = 0; j < M.n; ++j)
			{
				mnrM(M, mM, i, j);
				*(iM.s + j*iM.n + i) = id*detM(mM)/dM;
				id*=(-1);
			}
			id*=(-1);
			if (M.n%2==1) id*=(-1); // в матрицах с нечетным размером на следующей строке знак дважды меняется
		}

		memrls(&mM);
		strcpy(iM.name, "inverse matrix for your matrix is M^(-1)");
		return iM;
	}
}

unsigned int putpositivenum (void)
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

void dMtest (double x, FILE* pfl)
{
	if ( isnan(x) != 0 )
	{
		printf("\tdeterminant for square matrices only!\n");
		fprintf(pfl, "\tdeterminant for square matrices only!\n");
		return;
	}
	else
	{
		printf("\tdeterminant of your matrix is: %.3lf\n", x);
		fprintf(pfl, "\tdeterminant of your matrix is: %.3lf\n", x);
	}
}

short twonumtest (int num1, int num2)
{
	float putst=0;
	while(scanf("%f",&putst)!=1||(putst-(int)putst>0)||((putst!=num1)&&(putst!=num2))||(getchar()!='\n'))
		{
			while (getchar()!='\n');
			printf("\twrong input! try again: ");
		}
	return putst;
}

short ending (void) // цикл обработки ввода для выхода из программы
{
	short tfc;
	printf("\n\twant to try again? (1-for yes, 0-for no): ");
	tfc = twonumtest(1, 0);
	if (tfc==0) return 0;
	if (tfc==1) return 1;
}