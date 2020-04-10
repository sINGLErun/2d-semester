#include <stdio.h>
#include <math.h>
#define cntlim 100

//функции

double fnc (double x)
// {return (tan(0.5*x+0.2)-x*x);}
{
	return 2*x*x - 2*x + 1;
}

double dfnc (double x)
// {return (0.5/(pow((cos(0.5*x+0.2)),2))-2*x);}
{
    return 4*x-2; 
}

void slve (double x, int acc);
int ending ();

void main()
{
	printf("\n\tWe will solve equation f(x)=0 with your accuracy\n");

	while (1)
	{
		double x=0;
		int acc;
		printf("\n\tGive me an initial approximation: ");
		scanf("%lf",&x);
		printf("\tHow many numbers do you want to see after the point?: " );
		scanf("%d",&acc);

		slve(x, acc);
		if (ending()==0) return;
		//printf ("\tYour root is: %.*f\n", (int)acc, slve(x,acc)); //надо чтоб когда корней не было корень и не писало
		//а давайте просто сделаем ф-ю войд и выписывать будем там
	}
}

void slve (double x, int acc)
{
	int cnt=0;	//счетчик застоя (если у нас будет колеблющаяся функция и мы попадем между горбами и застрянем там)
	double dlt, eps;	//разница по х между следующим и текущим шагом
	eps=pow(10,(-1)*acc);	//порог точности

	do
	{
		if (dfnc(x)==0) { printf("\tYou have found an extremum, try to take a point more left or right\n"); return; }
		else dlt=fnc(x)/dfnc(x);	//следует из равенства (стр. 72)
		
		
		if ((((dfnc(x)<0)&&(fnc(x)>0))||((dfnc(x)>0)&&(fnc(x)<0)))&&(fabs(dlt)>1)) x+=0.1; //маленький шаг может быть плох для быстро (медленно) меняющихся ф-й
		else 
		{
			if (((dfnc(x)!=0)||(fnc(x)!=0))&&(fabs(dlt)>1)) x-=0.1; // -((A*B)+(C*D))=(A+B)*(C+D)=A*C+A*D+B*C+B*D, где A,B,C,D - последовательно отрицания логических выражений (А=dfnc>=0)из стр. выше. Здесь мы отсекли A*C и B*D
			else 
			{
				if (fnc(x)==0)
				{
					printf ("\tYour root is: %.*f\n", acc, x); return;
				}
			}
		}
		++cnt;
		if (cnt>cntlim)
		{
			printf("\tBad approach!\n", cnt); return;
		}

		if (fabs(dlt)<=1) x=x-fnc(x)/dfnc(x);
	}
	while (fabs(dlt)>eps);
	printf ("\tYour root is: %.*f\n", acc, x);
	return;
}

int ending()
{
// цикл обработки ввода для выхода из программы //это можно сделать в отдельной ф-и если ретернать ноль и ломать уже в теле мэйн
	float tfc=0;
	printf("\n\twant to try again? (1-for yes, 0-for no): ");
	while(scanf("%f",&tfc)!=1||(tfc-(int)tfc>0)||((tfc!=1)&&(tfc!=0))||(getchar()!='\n'))
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	if (tfc==0) return 0;
}