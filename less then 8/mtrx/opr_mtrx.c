#include "mtrx.h"

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
				*(C.s + i*C.m + j)=(*(A.s + i*A.m + j)) + (*(B.s + i*A.m + j));
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
				pij+=(*((A.s) + i*(A.m) + k))*(*((B.s) + k*(A.m) + j));
			}

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

		strcpy(iM.name, "inverse matrix for A is A^(-1)");
		return iM;
	}
}
