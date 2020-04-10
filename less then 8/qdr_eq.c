#include <stdio.h>
#include <math.h>

void main()
{
	printf("\n let's solve quadratic equation,\n");
	while (1)
	{//чтобы решать уравнения с большими коэффициентами надо привести все к даблу и использовать %lf для ввода %g для вывода
		double A=0,B=0,C=0;
		printf(" give me three coefficients for Ax^2+Bx+C=0\n");
		printf(" A= "); scanf("%lf",&A);
		printf(" B= "); scanf("%lf",&B);
		printf(" C= "); scanf("%lf",&C);


		if (A!=0)
		{//квадратичная часть
			double dscr=B*B-4*A*C;
			if (dscr<0)
			{
				printf(" there is no rational roots\n");
				//иррациональные корни (float)((-1)*B/(2*A)), (float)(sqrt(dscr)/(2*A)), (float)((-1)*B/(2*A)), (float)((-1)*sqrt(dscr)/(2*A)
			}
			else 
			{	
				if (dscr==0)
				{	
					double x1;
					x1=(double)((-1)*B/(2*A));
					printf(" x1(2)= %g\n", x1);
				}
				else
				{
					double x1,x2;
					x1=(double)(((-1)*B+sqrt(dscr))/(2*A));
					x2=(double)(((-1)*B-sqrt(dscr))/(2*A));
					printf("x1= %g, x2= %g", x1, x2);
				}
			}
		}
		else
		{	
			if (B!=0)
			{//линейная часть
				printf(" this is not a quadratic equation, but linear %lfx+%lf=0", B,C);
				
				float ans;
				do // цикл обработки ввода для выхода из программы//переделали на бесконечные циклы, переменные обьявляем внутри цикла чтоб не занимать так место
    			{	
    				printf("\n continue our solution? (1-yes, 0-no): ");
    				scanf("%d", &ans);
    				if (ans==1||ans==0)
    				{	
    					if (ans==1) 
    					{
    						double x1;
							x1=(double)((-1)*C)/B;
							printf(" x= %g\n", x1);
							break;
    					}
    					else if (ans==0) return;
    				}
    				else printf(" wrong input! try again");
    			}
   				while (1);
			}
			else //a=0 b=0 c=0
			{
				(C!=0)? printf(" there is no solutions\n"): printf(" there is infinitelly many solutions\n");
			} 
		}

	do // цикл обработки ввода для выхода из программы//переделали на бесконечные циклы, переменные обьявляем внутри цикла чтоб не занимать так место
    {
        float tfc;
        printf("\n Want to try again? (1-for yes, 0-for no): ");
        scanf("%f",&tfc);
        if (tfc==1||tfc==0)
        {   
            if (tfc==1) break;
            else return;
        }
        else printf(" wrong input! try again");
    }
    while (1); 

	}
	
}