#include <stdio.h>
#include <math.h>

int putprime ();

void main()
{
	int cnt, pr; 
    float N;
    int num = 0;
	printf("\n\tlet's print all prime numbers less then N\n");
    while (1)//цикл для замыкания програмы и возможности выбора в конце
    {
    	printf("\tgive me your N: ");

    	N=putprime();

    	for (int i=1; i<=N; i+=2) //внешний цикл для перебора простых чисел до Н, шаг через два числа
    	{
    		cnt=0;
    		for (int j=1; ((j<=sqrt(i))&&(cnt<2)); j+=2) //внутренний цикл, который проверяет остатки при делении на счетчик //добавили в условие cnt<2 и все хорошо
    		{//так, тут где-то ошибка // добавляются числа у которых 3 делитель на последнем шаге появляется (9, 25, 49)
                num++;
                if (i%j==0)
    			{
                    cnt++;
                    pr=j;
    			}
    		}
        if (pr==1) printf(" %d", i); //если добавить cnt!=3 то числа у которых появился 3 делитель на последнем шаге отсекаются
    	//if ((i==1)&&(N!=1)) printf(" 2");
    	}
        printf("\n");
        printf("num op = %d\n", num);


// цикл обработки ввода для выхода из программы//переделали на бесконечные циклы, переменные обьявляем внутри цикла чтоб не занимать так место
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

int putprime ()
{
    float N=0;
    while (scanf("%f", &N)!=1||(N-(int)N>0)||getchar()!='\n')
    {
        while (getchar()!='\n');
        printf("\tyour N isn't prime! try again: ");
    }
    return N;
}