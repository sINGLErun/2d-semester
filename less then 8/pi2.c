#include <stdio.h>
#include <math.h>

void main ()

{
	int acc;
	unsigned int i;
	double pip,pim,eps=1;
	printf("\tWe will write pi with your accuracy\n");
	while (1)
	{
		printf("\thow much digits do you want to see after the point?: ");
		scanf("%d", &acc);

		eps=pow(10,((-1)*acc));
		pip=0; pim=0; i=1;

		do
		{
			pip=pim+(double)4/i;
			i+=2;
			pim=pip-(double)4/i;
			i+=2;
		}
		while (pip-pim>eps);
		//pow занимает время

		printf("\tyour pi is: %.*f\n", acc, (pim+pip)/2);

		// цикл обработки ввода для выхода из программы
        float tfc=0;
        printf("\n\twant to try again? (1-for yes, 0-for no): ");
        while(scanf("%f",&tfc)!=1||(tfc-(int)tfc>0)||((tfc!=1)&&(tfc!=0))||(getchar()!='\n'))
        {
            while (getchar()!='\n');
            printf("\twrong input! try again: ");
        }
        if (tfc==0) return;
	}	
}