#include <stdlib.h>
#include <stdio.h>

#define BUFF 10
#define OWER 100

typedef struct
{
	char* el;
	int len;
}string;

typedef struct
{
	unsigned int day;
	unsigned int mnth;
	unsigned int year;
}brth;

typedef struct cppl
{
	string srnm;	//фамилия
	string nm;		//имя
	double phne;	//телефон
	brth date;		//дата рождения
	struct cppl *next;
}cppl;

short cons_inp (string* pstr);
void rllc_buf (string* pstr, int i);
void trim_buf (string* pstr);
void get_text (string* pstr);

short str_cmpr (string str1, string str2);
short day_test (int mnth, int year);
short coincide (cppl *hed, cppl *r);
short end_free (cppl *hed);
void prnt_cpp (cppl *hed);
void add_cntc (cppl *hed);
void del_cntc (cppl *hed);
void inp_date (cppl *r);
void srt_cntc ();

void prnt_str (string *pname);
long long putprime (long long num1, long long num2);
short menu (cppl *hed);
cppl* new_head (cppl* hed, cppl* cur, int i);
cppl* el_bnum (cppl* hed, int j);

void main()
{
	fprintf(stdout, "\n\twe will work with a phone book\n");

	cppl *hed = NULL;
	while (menu(hed) == 1);
}

short menu (cppl *hed)
{
	fprintf(stdout, "\n\tMENU:\n\t1 - for add contact\n\t2 - for delete contact\n\t3 - for sort\n\t4 - for print\n\t5 - for exit\n\t");
	do
	{
		switch (putprime(1, 5))
		{
			case 1: add_cntc(hed); return 1;
			case 2: del_cntc(hed); return 1;
			case 3: srt_cntc(hed); return 1;
			case 4: prnt_cpp(hed); return 1;
			case 5: end_free(hed); return 0;
		}
	}
	while (1);
}

void add_cntc (cppl *hed)
{
	cppl *r = (cppl*)malloc(sizeof(cppl));
	if (r == NULL) fprintf(stdout, "\tERROR! (#2) can't allocate memory!\n"); //сделайте обработку ошибки
	else
	{
		fprintf(stdout, "\n\tPrint the name: "); get_text(&r->nm); prnt_str(&r->nm);
		fprintf(stdout, "\tPrint the surname: "); get_text(&r->srnm); prnt_str(&r->srnm);
		fprintf(stdout, "\tPrint the phone number: "); r->phne = putprime(10000000000, 1000000000000000);

		if (coincide(hed, r) == 0)
		{
			printf("hi fucker\n");
			fprintf(stdout, "\tPrint the date of birth:\n"); inp_date(r);
			r->next = hed;
			hed = r;
		}
	}
	return;
}

void get_text (string* pstr)
{
	pstr->el = malloc(sizeof(char)*BUFF);
	if (pstr->el == NULL) pstr->len = -1;
	else
	{
		if (cons_inp(pstr) == 1) trim_buf(pstr);
	}
	return;
}

short cons_inp (string* pstr)
{
	int i = -1;
	do
	{
		if (( (i + 1) % BUFF == 0) && (i > 0)) rllc_buf(pstr, i);
		if (pstr->len == -1) return 0;

		i++;
		pstr->el[i] = getchar();
	}
	while ((i < OWER) && (pstr->el[i - 1] != '\n') && (i - 1 >= 0));
	while (getchar() != '\n');
	
	if (pstr->el[0] == '\n') { pstr->len = -2; return 0; } //что тут с этим будем делать??
	else pstr->len = i;

	return 1;
}

void rllc_buf (string* pstr, int i)
{
	char* pnstr;

	pnstr = malloc(sizeof(char)*(i + BUFF + 1));
	if (pnstr == NULL)
	{
		pstr->len = -1;
		return;
	}

	for (int j = 0; j <= i; ++j)
	pnstr[j] = pstr->el[j];

	free(pstr->el);
	pstr->el = pnstr;

	return;
}

void trim_buf (string* pstr)
{
	char* pnstr;

	pnstr = malloc(sizeof(char)*(pstr->len));
	if (pnstr == NULL)
	{
		pstr->len = -1;
		return;
	}

	for (int i = 0; i < pstr->len; ++i)
	pnstr[i] = pstr->el[i];

	free(pstr->el);
	pstr->el = pnstr;

	return;
}

void inp_date (cppl *r)
{
	fprintf(stdout, "\t  Put the year: "); r->date.year = putprime(1900, 2019);
	fprintf(stdout, "\t  Put the month: "); r->date.mnth = putprime(1, 12);
	
	fprintf(stdout, "\t  Put the day: ");
	switch (day_test(r->date.mnth, r->date.year))
	{
		case 1: r->date.day = putprime(1, 31); return;
		case 2: r->date.day = putprime(1, 28); return;
		case 3: r->date.day = putprime(1, 29); return;
		case 4: r->date.day = putprime(1, 30); return;
	}
}

short day_test (int mnth, int year)
{
	if (mnth == 1 || mnth == 3 || mnth == 5 || mnth == 7 || mnth == 8 || mnth == 10 || mnth == 12) return 1;
	if (mnth == 2 && year % 4 != 0) return 2;
	if (mnth == 2 && year % 4 == 0) return 3;
	else return 4;
}

short coincide (cppl *hed, cppl *r)
{
	cppl* swch = hed;
	while (swch != NULL)
	{
		if (str_cmpr(swch->nm, r->nm) == 2 && str_cmpr(swch->srnm, r->srnm) == 2)
		{
			fprintf(stdout, "\tERROR (#4) contact with this name has already created\n");
			free(r->srnm.el);
			free(r->nm.el);
			free(r);
			return 1;
		}
		if (r->phne == swch->phne)
		{
			fprintf(stdout, "\tERROR (#5) contact with this phone number has already created\n");
			free(r->srnm.el);
			free(r->nm.el);
			free(r);
			return 1;
		}
		swch = swch->next;
	}
	return 0;
}

short str_cmpr (string str1, string str2)
{
	int i = 0;
	while (i < str1.len && i < str2.len)
	{
		if (str1.el[i] > str2.el[i]) return 1;
		if (str1.el[i] < str2.el[i]) return 0;
		if (str1.el[i] == str2.el[i]) i++;
	}
	if (str1.len == str2.len && str1.len == i) return 2;
	if (str1.len > str2.len) return 1;
	else return 0;
}

void del_cntc (cppl *hed)
{
	if (hed == NULL) fprintf(stdout, "\tERROR! (#3) empty list\n");
	else
	{
		int i = 0, j = 0;
		cppl *swch = hed;
		string del_nm, del_srnm;

		fprintf(stdout, "\tEnter the name: "); get_text(&del_nm);
		fprintf(stdout, "\tEnter the surname: "); get_text(&del_srnm);
		while (swch != NULL)
		{
			while (str_cmpr(swch->nm, del_nm) == 2 && str_cmpr(swch->srnm, del_srnm) == 2)
			{
				swch = new_head(hed, swch, i);
				j++;
				if (swch == NULL) break;
				i--;
			}
			if (swch == NULL) break;
			swch = swch->next;
			i++;
		}
		if (j == 0) fprintf(stdout, "\tThis contact didn't found\n");
		free(del_srnm.el);
		free(del_nm.el);
	}
}

cppl* new_head (cppl* hed, cppl* cur, int i)
{
	if (i == 0 && cur->next == NULL)
	{
		free(cur->srnm.el);
		free(cur->nm.el);
		free(cur);
		hed = NULL;
		return NULL;
	}
	if (i == 0)
	{
		cppl *elm = cur;
		hed = elm->next;
		free(cur->srnm.el);
		free(cur->nm.el);
		free(elm);
		return hed;
	}
	if (cur->next == NULL)
	{
		cppl *prv = el_bnum(hed, i - 1), *elm = cur;
		prv->next = NULL;
		free(cur->srnm.el);
		free(cur->nm.el);
		free(elm);
		return  prv;
	}
	else
	{
		cppl *prv = el_bnum(hed, i - 1), *elm = prv->next;
		prv->next = elm->next;
		free(cur->srnm.el);
		free(cur->nm.el);
		free(elm);
		return  prv;
	}
}

cppl* el_bnum (cppl* hed, int j)
{
	cppl* swch = hed;
	int cnt = 0;
	while (cnt < j && swch)
	{
		swch = swch->next;
		cnt++;
	}
	return swch;
}

void prnt_cpp (cppl *hed)
{
	cppl *r = hed;
	if (r == NULL) fprintf(stdout, "\tERROR! (#3) empty list\n");
	else
	{
		int i = 0;
		fprintf(stdout, "\tyour contacts:\n");
		while (r != NULL)
		{
			i++;
			fprintf(stdout, "\tcontact %d: ", i);
			prnt_str(&r->nm); fprintf(stdout, "\t");
			prnt_str(&r->srnm); fprintf(stdout, "\t");
			fprintf(stdout, "\t%.0lf\t", r->phne); fprintf(stdout, "\t");

			if (r->date.day <10) printf("0%d.", r->date.day);
			else printf("%d.", r->date.day);
			if (r->date.mnth < 10) printf("0%d.", r->date.mnth);
			else printf("%d.", r->date.mnth);
			printf("%d\n", r->date.year);

			r = r->next;
		}
	}
}

// цикл обработки ввода для освобождения памяти и выхода из программы
short end_free (cppl *hed)
{
	if (hed != NULL)
	{
		cppl* prv = NULL;
		while (hed->next != NULL)
		{
			prv = hed;
			hed = hed->next;
			free(hed->srnm.el);
			free(hed->nm.el);
			free(prv);
		}
		free(hed->srnm.el);
		free(hed->nm.el);
		free(hed);
	}
}

void prnt_str (string *pname)
{
	for (int i = 0; i < pname->len ; i++)
	fprintf(stdout, "%c", pname->el[i]);

	return;
}

long long putprime (long long num1, long long num2)
{
	long long ans = 0;
	while (fscanf(stdin, "%lld", &ans) != 1 || num2 < ans || ans < num1 || getchar()!='\n')
	{
		while (getchar()!='\n');
		fprintf(stdout, "\twrong input! try again: ");
	}
	return ans;
}