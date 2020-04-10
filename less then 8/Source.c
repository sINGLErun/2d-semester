#include <stdio.h>
#include <math.h>
int main()
{
	float a, b, c, D, x, y;
	printf("a=");
	if (scanf_s("%f", &a) != 1)
	{
		printf("\nError input");
		return 0;
	}
		printf("\nb=");
		if (scanf_s("%f", &b) != 1)
		{
			printf("\nError input");
			return 0;
		}
		else
			printf("\nc=");
			if (scanf_s("%f", &c) != 1)
			{
				printf("\nError input");
				return 0;
			}
	if (a == 0) //В квадратном уравнении коэффициент а - ненулевой.
	{
		printf("\nThere int't square equation!"); //Вывод:"Это не квадратное уравнение!".
		return 0;
	}
	else
		D = (b*b) - (4 * a*c); //Дискриминант.
			if (D < 0) //Проверка дискриминанта на отрицательность.
			{
				printf("\nNo real roots"); //Вывод: "Нет вещественных корней".
			}
			else
				if (D == 0) //Проверка на равенство дискриминанта нулю.
				{
					x = (-1)*b / (2 * a); //Находим единственный корень.
					printf("\n1 root: x=%f", x); //Выводим единственный корень.
				}
				else
					if (D > 0) //Проверка дискриминанта на положительность
					{
						x = (-b - sqrt(D)) / (2 * a); //Находим корни.
						y = (-b + sqrt(D)) / (2 * a);
						printf("\n2 roots: x1=%f\tx2=%f", x, y); //Выводим оба корня.
					}
		return 0;
}