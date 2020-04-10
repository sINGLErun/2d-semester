#include <stdlib.h>
#include <stdio.h>

#define BUFF 10
#define OWER 1000000

typedef struct 
{
	char* el;
	int len;
}string;

short cons_inp (string* pstr);
short file_inp (string* pstr);
void rllc_buf (string* pstr, int i);
void trim_buf (string* pstr);
void get_text (string* pstr);

void ins_smbl (string* pcstr, int pos, char smb);
void smb_cond (string* pcstr, int pos, int len);
void del_smbl (string* pcstr, int pos);
void lett_sze (string* pcstr);
void prnt_str (string* pname);
void correct (string* pstr, string* pcstr);
void spaces (string* pstr, string* pcstr);
void smbls (string* pcstr);

short twonumtest (int num1, int num2);
short leng_check (string* pname);
short end_free (string* name1, string* name2);
void prnt_str (string* pname);

void main (void)
{
	fprintf(stdout, "\n\twe will read and correct your text\n");

	while (1)
	{
		string str, cstr;
		
		get_text(&str);
		if (leng_check(&str) > 0)
		{
			correct(&str, &cstr);
			if (leng_check(&cstr) > 0)
			{
				fprintf(stdout, "\tyour string: ");		prnt_str(&str);
				fprintf(stdout, "\tcorrect string: ");	prnt_str(&cstr);

				if (end_free(&str, &cstr) == 0) return;
			}
			else if (end_free(&str, &cstr) == 0) return;
		}
		else if (end_free(&str, &cstr) == 0) return;
	}
}

void get_text (string* pstr)
{
	short ans;
	pstr->el = malloc(sizeof(char)*BUFF);
	if (pstr->el == NULL)
	{
		pstr->len = -1;
		return;
	}

	fprintf(stdout, "\n\tchoose    1 - for input string from console\n\t       or 2 - for input from file: ");
	ans = twonumtest (1, 2);

	if ((ans == 1) && (cons_inp(pstr) == 1)) { trim_buf(pstr); return; } else return;
	if ((ans == 2) && (file_inp(pstr) == 1)) { trim_buf(pstr); return; } else return;
}

short cons_inp (string* pstr)
{
	fprintf(stdout, "\tprint some text (terminator is #): ");

	int i = -1;
	do
	{
		if (( (i + 1) % BUFF == 0) && (i > 0)) rllc_buf(pstr, i);
		if (pstr->len == -1) return 0;

		i++;
		pstr->el[i] = getchar();
	}
	while ((i < OWER) && (pstr->el[i] != '#'));
	while (getchar() != '\n');
	
	if (pstr->el[0] == '#') { pstr->len = -2; return 0; }
	else pstr->len = i;

	return 1;	
}

short file_inp (string* pstr)
{
	FILE *pfl;
	if ((pfl = fopen("d:\\c\\codec\\mes\\get_text\\get_textinput.txt", "r")) == NULL)
	{
		fprintf(stdout, "\tERROR! (#3) somethig goes wrong with opening your file.\n");
		fprintf(stdout, "\tare you want to input text from console? (1-for yes, 2-for no):");

		short ans;
		ans = twonumtest(1, 2);

		if ((ans == 1)&&(cons_inp(pstr)) == 1) return 1;
		if (ans == 2) { pstr->len = -3; return 0; }
	}

	rewind(pfl);
	int i = -1;
	do
	{
		i++;
		pstr->el[i] = getc(pfl);

		if ((i + 1) % BUFF == 0)
		rllc_buf(pstr, i);

		if (pstr->len == -1) return 0;
	}
	while ((i < OWER)&&(pstr->el[i] != '#')&&(pstr->el[i] != EOF));

	fprintf(stdout, "\twell, we got text from file (until #)");
	fclose(pfl);

	if (pstr->el[0] == '#') { pstr->len = -2; return 0; }
	else pstr->len = i;

	return 1;
}

void rllc_buf (string* pstr, int i)
{
	//printf("rllc_\n");

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
	//printf("trim_in: "); prnt_str(pstr);

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

	//printf("trim_out: "); prnt_str(pstr);
	return;
}

void correct (string* pstr, string* pcstr)
{
		pcstr->el = malloc(sizeof(char)*(pstr->len));
		if (pcstr->el == NULL)
		{
			pcstr->len = -1;
			return;
		}
		//pcstr->len = 1; //пойдёт любое число больше нуля

		spaces(pstr, pcstr);
		smbls(pcstr);
		lett_sze(pcstr);

		return;
}

void spaces (string* pstr, string* pcstr)
{
		unsigned int i = 0, j = 0;
		while (i < pstr->len)
		{	
			if (pstr->el[i] == ' ') i++;
			if (pstr->el[i] != ' ')
			{
				pcstr->el[j] = pstr->el[i];
				j++;
				if ((pstr->el[i + 1] == ' ') && ((i + 1) < pstr->len))
				{
					pcstr->el[j] = ' ';
					j++;
				}
			}
			i++;
		}
		pcstr->len = j;

		return;
}

void smbls (string* pcstr) 
{
	unsigned int j = 1;
	while(j < pcstr->len)
	{
		if ((pcstr->el[j] == '.')||(pcstr->el[j] == '?')||(pcstr->el[j] == '!')||(pcstr->el[j] == ',')||(pcstr->el[j] == ';')||(pcstr->el[j] == ':')||(pcstr->el[j] == ')'))
		smb_cond(pcstr, j, 1);

		if  ((pcstr->el[j] == '.')&&(pcstr->el[j + 1] == '.')&&(pcstr->el[j + 3] == '.'))
		smb_cond(pcstr, j, 3);

		if ((pcstr->el[j] == ' ') && ((j + 1) == pcstr->len) && (pcstr->len != 1))
		pcstr->len--;

		j++;
	}

	return;
}

void smb_cond (string* pcstr, int pos, int len)
{
	if ((pcstr->el[pos - 1] != ' ')&&(pcstr->el[pos + len] != ' '))
	{
		if (pcstr->len + 1 > OWER)
		{	pcstr->len = 0; return;	}

		ins_smbl(pcstr, (pos + len), ' ');
		pcstr->len++;
	}
	else if ((pcstr->el[pos + len] != ' '))
	{
		//это мы просто переносим нашу последовательность на один символ назад
		for (int i = pos; i < pos + len; ++i)
		pcstr->el[i - 1] = pcstr->el[i];

		del_smbl(pcstr, (pos + len - 1)); 
		ins_smbl(pcstr, (pos + len - 1), ' ');
	}
	else if ((pcstr->el[pos - 1] == ' '))
	{
		for (int i = pos; i < pos + len; ++i)
		pcstr->el[i - 1] = pcstr->el[i];

		del_smbl(pcstr, (pos + len - 1));
		pcstr->len--;
	}

	return;
}

//в этой программе мы можем себе позволить по настоящему удалять
void del_smbl (string* pcstr, int pos)
{
	//printf("del_in: "); prnt_str(pcstr);

	char* pnstr;

	pnstr = malloc(sizeof(char)*(pcstr->len - 1));
	if (pnstr == NULL)
	{
		pcstr->len = -1;
		return;
	}

	for (int i = 0; i < pos; i++)
	pnstr[i] = pcstr->el[i];

	for (int i = pos; i < pcstr->len - 1; i++)
	pnstr[i] = pcstr->el[i + 1];

	free(pcstr->el);
	pcstr->el = pnstr;

	//printf("del_out: "); prnt_str(pcstr);
	return;
}

void ins_smbl (string* pcstr, int pos, char smb)
{
	//printf("ins_in: ", pos); prnt_str(pcstr);
	
	char* pnstr;

	pnstr = malloc(sizeof(char)*(pcstr->len + 1));
	if (pnstr == NULL)
	{
		pcstr->len = -1;
		return;
	}

	for (int i = 0; i < pos; i++)
	pnstr[i] = pcstr->el[i];

	pnstr[pos] = smb;

	for (int i = pcstr->len + 1; pos < i; i--)
	pnstr[i] = pcstr->el[i - 1];

	free(pcstr->el);
	pcstr->el = pnstr;

	//printf("ins_out: "); prnt_str(pcstr);
	return;
}

void lett_sze (string* pcstr)
{
	if ((pcstr->el[0] >= 'a') && (pcstr->el[0] <= 'z'))
	{
		pcstr->el[0] = pcstr->el[0] - 32;
	}

	int i = 1;
	do
	{
		if ((pcstr->el[i] >= 'A') && (pcstr->el[i] <= 'Z'))
		pcstr->el[i] = pcstr->el[i] + 32;
		i++;
	} while (i!=pcstr->len);

	i = 2;
	do
	{
		if (((pcstr->el[i - 2] == '.') && ((pcstr->el[i] >= 'a') && (pcstr->el[i] <= 'z'))) || ((pcstr->el[i - 3] == '.') && (pcstr->el[i - 1] == '\n') && ((pcstr->el[i] >= 'a') && (pcstr->el[i] <= 'z'))))
		pcstr->el[i] = pcstr->el[i] - 32;
		i++;
	} while (i != pcstr->len);

	return;
}

short leng_check (string* pname)
{
	//printf("len: %d\n", pname->len);
	if (pname->len == -3) return 0; // ошибка минимального ранга: описана в программе
	if (pname->len == -2)	{	fprintf(stdout, "\tERROR! (#2) you have not even entered a string!\n"); return 0; }
	if (pname->len == -1)	{	fprintf(stdout, "\tERROR! (#1) can't allocate memory!\n"); return 0; }
	if (pname->len == 0)	{	fprintf(stdout, "\tERROR! (#0) overflow!\n"); return 0; }
	if (pname->len > 0) return pname->len;
}

short twonumtest (int num1, int num2)
{
	float ans = 0;
	while(scanf("%f", &ans)!=1 || (ans-(int)ans>0) || ((ans!=num1) && (ans!=num2)) || (getchar()!='\n'))
	{
		while (getchar()!='\n');
		printf("\twrong input! try again: ");
	}
	
	return ans;
}

// цикл обработки ввода для освобождения памяти и выхода из программы
short end_free (string* name1, string* name2)
{
	printf("\n\twant to try again? (1-for yes, 0-for no): ");

	short ans;
	ans = twonumtest(1, 0);

	if (ans == 0) { free(name1->el); free(name2->el); return 0; }
	if (ans == 1) { free(name1->el); free(name2->el); return 1; }
}

void prnt_str (string* pname)
{
	for (int i = 0; i < pname->len ; i++)
	{
		fprintf(stdout, "%c", pname->el[i]);
	}
	fprintf(stdout, "#\n"); //я использую зарезервированный символ просто чтоб показать, что там пробелов нет

	return;
}