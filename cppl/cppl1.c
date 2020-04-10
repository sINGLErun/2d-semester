#include <stdlib.h>
#include <stdio.h>

#define BUFF 10
#define OWER 100

typedef struct
{
	char *el;
	int len;
}string;

typedef struct
{
	int day;
	int mnth;
	int year;
}brth;

typedef struct cppl
{
	string nm;
	string srnm;
	long long phne;
	brth date;
	struct cppl *next;
}cppl;

cppl* new_head (cppl** hed, cppl* r, int i);
cppl* el_bnum (cppl* hed, int i);
short date_cmpr (cppl* r, cppl* nx);
short srnm_cmpr (cppl* r, cppl* nx);
short phne_cmpr (cppl* r, cppl* nx);
short str_cmpr (string str1, string str2);
short day_test (int mnth, int year);
short coincide (cppl* hed, cppl *r);
short nm_cmpr (cppl* r, cppl* nx);
short menu (cppl** hed);
void prnt_cpp (cppl** hed);
void del_cntc (cppl** hed);
void add_cntc (cppl** hed);
void srt_cntc (cppl** hed);
void end_free (cppl** hed);
void inp_date (cppl* r);
void sorting (cppl** hed, short cmpr(cppl* r, cppl* nx));

short cons_inp (string* pstr);
short get_text (string* pstr);
void prnt_str(string pname);
void rllc_buf (string* pstr, int i);
void trim_buf (string* pstr);

long long putprime (long long num1, long long num2);

void main ()
{
	cppl* hed = NULL;
	while (menu(&hed) == 1);
}

short menu (cppl** hed)
{
	fprintf(stdout, "\n\tMENU:\n\t1 - for add contact\n\t2 - for delete contact\n\t3 - for sort\n\t4 - for print\n\t5 - for exit\n\t");	

	switch (putprime(1, 5))
	{
		case 1: add_cntc(hed); return 1;
		case 2: del_cntc(hed); return 1;
		case 3: srt_cntc(hed); return 1;
		case 4: prnt_cpp(hed); return 1;
		case 5: end_free(hed); return 0;
	}
}

void add_cntc (cppl** hed)
{
	cppl *r = (cppl*)malloc(sizeof(cppl));
	fprintf(stdout, "\n\tprint the name: "); if (get_text(&(r->nm)) == 0) return;
	fprintf(stdout, "\tprint the surname: "); if (get_text(&(r->srnm)) == 0) return;
	fprintf(stdout, "\tprint the phone number: "); r->phne = putprime(10000000000, 1000000000000000);

	if (coincide(*hed, r) == 0)
	{
		fprintf(stdout, "\tprint the date of birth:\n");
		inp_date(r);
		r->next = *hed;
		*hed = r;
	}
}

short get_text (string* pstr)
{
	pstr->el = malloc(sizeof(char)*BUFF);
	if (pstr->el == NULL)
	{
		fprintf(stdout, "\tERROR! (#1) can't allocate memory\n");
		return 0;
	}

	if (cons_inp(pstr) == 1) { trim_buf(pstr); return 1; }
	else return 0;
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
	while ((i < OWER) && (pstr->el[i] != '\n'));
	
	if (pstr->el[0] == '\n') { fprintf(stdout, "\tERROR! (#2) you have not even enter a string\n"); return 0; }
	else pstr->len = i;

	return 1;	
}

void rllc_buf (string* pstr, int i)
{
	char* pnstr;

	pnstr = malloc(sizeof(char)*(i + BUFF + 1));
	if (pnstr == NULL)
	{
		fprintf(stdout, "ERROR! (#1) can't allocate memory\n");
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
		fprintf(stdout, "ERROR! (#1) can't allocate memory\n");
		return;
	}

	for (int i = 0; i < pstr->len; ++i)
	pnstr[i] = pstr->el[i];

	free(pstr->el);
	pstr->el = pnstr;

	return;
}

short coincide (cppl* hed, cppl *r)
{
	cppl *nh = hed;
	while (nh != NULL)
	{
		if ((str_cmpr(nh->nm, r->nm) == 0) && (str_cmpr(nh->srnm, r->srnm) == 0))
		{
			fprintf(stdout, "\tERROR! (#3) contact with this name has already created\n");
			free(r->srnm.el);
			free(r->nm.el);
			free(r);
			return 1;
		}
		if (r->phne == nh->phne) {
			fprintf(stdout, "\tERROR! (#4) contact with this phone number has already created\n");
			free(r->srnm.el);
			free(r->nm.el);
			free(r);
			return 1;
		}
		nh = nh->next;
	}
	return 0;
}

short str_cmpr (string str1, string str2)
{
	int i = 0;
	while (i < str1.len && i < str2.len)
	{
		if (str1.el[i] > str2.el[i]) return 1;
		if (str1.el[i] < str2.el[i]) return 2;
		if (str1.el[i] == str2.el[i]) i++;
	}
	if (str1.len == str2.len && str1.len == i) return 0;
	if (str1.len > str2.len) return 1;
	else return 2;
}

void inp_date (cppl *r)
{
	fprintf(stdout, "\t  put the year: "); r->date.year = putprime(1900, 2019);
	fprintf(stdout, "\t  put the month: "); r->date.mnth = putprime(1, 12);
	
	fprintf(stdout, "\t  put the day: ");
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

void del_cntc (cppl** hed)
{
	if (*hed == NULL) fprintf(stdout, "\tERROR! (#5) empty list\n");
	else
	{
		int i = 0, j = 0;
		cppl* nh = *hed;
		string del_nm, del_srnm;
		fprintf(stdout, "\tenter the name: "); get_text(&del_nm);
		fprintf(stdout, "\tenter the surname: "); get_text(&del_srnm);
		while (nh != NULL)
		{
			while (str_cmpr(nh->nm, del_nm) == 0 && str_cmpr(nh->srnm, del_srnm) == 0)
			{
				nh = new_head(hed, nh, i);
				if (nh == NULL) break;
				j++;
				i--;
			}
			if (nh == NULL) break;
			nh = nh->next;
			i++;
		}
		if (j == 0) fprintf(stdout, "\tthis contact didn't found\n");
		free(del_srnm.el);
		free(del_nm.el);
	}
}

cppl* new_head (cppl** hed, cppl* r, int i)
{
	if (i == 0 && r->next == NULL)
	{
		free(r->srnm.el);
		free(r->nm.el);
		free(r);
		*hed = NULL;
		return NULL;
	}
	if (i == 0)
	{
		cppl* elm = r;
		*hed = elm->next;
		free(r->srnm.el);
		free(r->nm.el);
		free(elm);
		return *hed;
	}
	if (r->next == NULL)
	{
		cppl* prv = el_bnum(*hed, i - 1);
		cppl* elm = r;
		prv->next = NULL;
		free(r->srnm.el);
		free(r->nm.el);
		free(elm);
		return prv;
	}
	else
	{
		cppl *prv = el_bnum(*hed, i - 1);
		cppl *elm = prv->next;
		prv->next = elm->next;
		free(r->srnm.el);
		free(r->nm.el);
		free(elm);
		return prv;
	}
}

cppl* el_bnum (cppl* hed, int i)
{
	cppl* nh = hed;
	int cnt = 0;
	while (cnt < i && nh != NULL)
	{
		nh = nh->next;
		cnt++;
	}
	return nh;
}

void srt_cntc (cppl** hed)
{
	if (hed == NULL) fprintf(stdout, "\tERROR! (#5) empty list\n");
	else
	{
		fprintf(stdout, "\n\tselect type of sort:\n\t1 - by name\n\t2 - by surname\n\t3 - by phone number\n\t4 - by date of birth\n\t"); 
		switch (putprime(1, 4))
		{
			case 1: sorting(hed, nm_cmpr); break;
			case 2: sorting(hed, srnm_cmpr); break;
			case 3: sorting(hed, phne_cmpr); break;
			case 4: sorting(hed, date_cmpr); break;
		}
	}
}
	
void sorting (cppl** hed, short cmpr(cppl* tl, cppl* nx)) //при сортировке теряется один элемент //тот который самый хороший для сортировки//кажется все которые поднимаются
{
	cppl *nh = *hed, *a = NULL, *b = NULL, *c = NULL, *d = NULL, *tl = NULL;
	while (d != (*hed)->next)
	{
		c = *hed;
		a = *hed;
		b = a->next;
		while (a != d)
		{
			if (cmpr(a, b) == 1)
			{
				if (a == *hed)
				{
					*hed = b;
					tl = b->next;
					b->next = a;
					a->next = tl;	
					c = b;
				}
				else
				{
					tl = b->next;
					b->next = a;
					a->next = tl;
					c->next = b;
					c = b;
				}
			}
			else
			{
				c = a;
				a = a->next;
			}
			b = a->next;
			if (b == d) d = a;
		}
	}
}

short nm_cmpr (cppl* r, cppl* nx)
{
	if (str_cmpr(r->nm, nx->nm) == 1) return 1;
	else return 0;
}
	
short srnm_cmpr (cppl* r, cppl* nx)
{
	if (str_cmpr(r->srnm, nx->srnm) == 1) return 1;
	else return 0;
}
	
short phne_cmpr(cppl* r, cppl* nx)
{
	if (r->phne > nx->phne) return 1;
	else return 0;
}
	
short date_cmpr(cppl* r, cppl* nx)
{
	if (r->date.year > nx->date.year) return 1;
	if (r->date.year == nx->date.year)
	{
		if (r->date.mnth > nx->date.mnth) return 1;
		if (r->date.mnth == nx->date.mnth)
		{
			if (r->date.day > nx->date.day) return 1;
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

void prnt_cpp(cppl** hed)
{
	cppl* r = *hed;
	if (r == NULL) fprintf(stdout, "\tERROR! (#5) empty list\n");
	else
	{
		int i = 0;
		fprintf(stdout, "\n\tyour contacts:\n");
		while (r != NULL)
		{
			i++;
			fprintf(stdout, "\tcontact %d:\t", i);
			prnt_str(r->nm); fprintf(stdout, "\t");
			prnt_str(r->srnm); fprintf(stdout, "\t");
			fprintf(stdout, "%lld\t", r->phne); fprintf(stdout, "\t");

			if (r->date.day <10) fprintf(stdout, "0%d.", r->date.day);
			else fprintf(stdout, "%d.", r->date.day);
			if (r->date.mnth < 10)	fprintf(stdout, "0%d.", r->date.mnth);
			else fprintf(stdout, "%d.", r->date.mnth);
			fprintf(stdout, "%d\n", r->date.year);

			r = r->next;
		}
	}
}

void prnt_str (string pname)
{
	for (int i = 0; i < pname.len ; i++)
	fprintf(stdout, "%c", pname.el[i]);

	return;
}

void end_free(cppl** hed)
{
	if (*hed != NULL)
	{
		cppl* prv = NULL;
		while ((*hed)->next != NULL)
		{
			prv = *hed;
			*hed = (*hed)->next;
			free(&(prv->nm.el));
			free(&(prv->srnm.el));
			free(prv);
		}
		free(&((*hed)->nm.el));
		free(&((*hed)->srnm.el));
		free(*hed);
	}
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