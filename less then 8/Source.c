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
	if (a == 0) //� ���������� ��������� ����������� � - ���������.
	{
		printf("\nThere int't square equation!"); //�����:"��� �� ���������� ���������!".
		return 0;
	}
	else
		D = (b*b) - (4 * a*c); //������������.
			if (D < 0) //�������� ������������� �� ���������������.
			{
				printf("\nNo real roots"); //�����: "��� ������������ ������".
			}
			else
				if (D == 0) //�������� �� ��������� ������������� ����.
				{
					x = (-1)*b / (2 * a); //������� ������������ ������.
					printf("\n1 root: x=%f", x); //������� ������������ ������.
				}
				else
					if (D > 0) //�������� ������������� �� ���������������
					{
						x = (-b - sqrt(D)) / (2 * a); //������� �����.
						y = (-b + sqrt(D)) / (2 * a);
						printf("\n2 roots: x1=%f\tx2=%f", x, y); //������� ��� �����.
					}
		return 0;
}