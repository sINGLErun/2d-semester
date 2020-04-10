#include <stdio.h>
#include <math.h>

int putpositiveprime (void);
double fnc (double x)
{
	return log(x);
}
int ending ();

void main ()
{
	while (1)
	{
		unsigned int i=2,N;
		double x=0, a=0, b=0, s=0, h=0;
		printf("\n\tLet's calculate integral from a to b of the function f(x)\n");

		printf("\tset the limits of integration [a,b]: [");
		scanf("%lf,%lf]",&a,&b); //в консольку надо будет ввести два числа через запятую и поставить ] (!)
		printf("\thow many parts do we divide the segment?: ");
	  	N=putpositiveprime();

		h=(b-a)/N; x=a+h; 
		if (isinf(fnc(x-h))!=0) a=fnc(x-0.25*h);
		else a=fnc(x-h);
		if (isinf(fnc(x-h))!=0) b=fnc(x-0.75*h);//используем уже бесполезные переменныe
		else b=fnc(x);

		while (i<N)
		{
			s+=(h/2)*(a+b); 
			x+=h;			//в вычислении мы делаем шаг
			a=b;			//подтягиваем за шагом а
			if (isinf(fnc(x))!=0) b=fnc(x-0.5*h);
			else b=fnc(x); 	//вычисляем следующее значение функции
			i++; 
		}
		
		printf("\tanswer is: %lf\n", s);
		
		if (ending()==0) return;
	}
}

int putpositiveprime (void)
{
    float N=0;
    while (scanf("%f", &N)!=1||(N-(int)N>0)||N<=0||getchar()!='\n')
    {
        while (getchar()!='\n');
        printf("\ti can't divide the segment like that! try again: ");
    }
    return N;
}

int ending()
{
// цикл обработки ввода для выхода из программы
	float tfc=0;
	printf("\n\twant to try again? (1-for yes, 0-for no): ");
	while(scanf("%f",&tfc)!=1||(tfc-(int)tfc>0)||((tfc!=1)&&(tfc!=0))||(getchar()!='\n'))
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	if (tfc==0) return 0;
}