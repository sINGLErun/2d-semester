#include <stdio.h>
#include <math.h>

//в этом пи попробуем сделать цикл фор с помощью остановки на 1/10^acc

void main ()

{
	int acc;
	double ampi,eps;
	printf(" We will write pi with your accuracy\n");

	while (1)
	{
		printf(" how much digits do you want to see after the point?: ");
		scanf("%d", &acc);
		//надо определиться до куда считать
		eps=pow(10,acc)+10;
		ampi=0;
//плохой для маленьуих чисел
		for (int i=1; i<eps; i+=2)
		{
			ampi+=(double)((pow((-1),(i-1)/2)*4)/i);
		}

		printf(" your pi is: %.*f\n", acc, ampi);


		do // цикл обработки ввода для выхода из программы//переделали на бесконечные циклы, переменные обьявляем внутри цикла чтоб не занимать так место
    		{
    			float tfc;
    			printf("\n Want to try again? (1-for yes, 0-for no): ");
    			scanf("%f", &tfc);
    			if (tfc==1||tfc==0)
    			{	
    				if (tfc==1) break;
    				else if (tfc==0) return;
    			}
    			 else printf(" wrong input! try again");
    		}
   		while (1); 
	}	
}