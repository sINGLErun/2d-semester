#include <stdio.h>
#include <math.h>

void main ()

{
	int acc,i;
	double ampi,eps=1,spe;
	printf(" We will write pi with your accuracy\n");
	while (1)
	{
		ampi=0; i=1; spe=0;

		printf(" how much digits do you want to see after the point?: ");
		scanf("%d", &acc);

		eps=pow(10,((-1)*acc));
		spe+=(double)((pow((-1),(i-1)/2)*4)/i);

		do
		{
			ampi=spe;
			i+=2;
			spe=ampi+(double)((pow((-1),(i-1)/2)*4)/i);
		}	
		while (fabs(spe-ampi)>eps);

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