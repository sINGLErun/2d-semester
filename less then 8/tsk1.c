#include <stdio.h>

void main()
{
	float a=1.23;
	int b=1;
	double c=1.3554;
	printf("my numbers: %f, %d, %f\n", a,b,c);
	printf("Say me your numbers a= ");
	scanf("%f", &a);
	c=(double)(a+b);
	printf("your numbers:%f, %d, %f\n", a,b,c);
	return;
}