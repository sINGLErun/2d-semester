#include "mtrx.h"

void main (void)
{
	while (1)
	{
		mtrx A, B;
		mtrx res[RNUM];
		double dM;

		printf("\n\twe will calculate operation with matrix\n");

//нужна возможность брать матрицы из файла
//считывать количество пробелов или до интера чтоб знать сколько размер массиваыы

		srand(time(NULL));
		strcpy(A.name,"A"); initmtr(&A);
		strcpy(B.name,"B"); initmtr(&B);

//стоит сделать более гибкий интерфейс

		prntmtr(&A);
		prntmtr(&B);

		res[0] = sumAB(A, B);
		res[1] = prodAB(A, B);
		dM = detM(A);
		res[2] = invrsM(A, dM);

//нужно записывать результаты в файл

//		pflw = flwrtetst();

		printf("\n");
		NaNtest(dM);
		for (int i = 0; i < RNUM ; ++i)
		{
			prntmtr( &res[i] );
			memrls( &res[i] );
		}

		memrls(&A);
		memrls(&B);

		if (ending()==0) return;
	}
}