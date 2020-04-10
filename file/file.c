#include <stdio.h>

#define STR_LENGTH 15

typedef struct 
{
	char el[STR_LENGTH];
	int len;
}string;

void smb_cond (string* pcstr, int pos, int len);
void ins_smb (string* pcstr, int pos, char smb);
void correct (string* pstr, string* pcstr);
void spaces (string* pstr, string* pcstr);
void del_smb (string* pcstr, int pos);
short leng_check (string* pname);
void lett_size (string* pcstr);
void prnt_str (string* pname);
void file_inp (string* pstr);
void smbls (string* pcstr);

void main(void)
{
	fprintf(stdout, "\n\twe will correct your string\n");
	fprintf(stdout, "\tremember that this prog. work only with first %d symbols!\n\n", (int)STR_LENGTH/2 + 1);

	string str, cstr;
	file_inp(&str);
	correct(&str, &cstr);

	fprintf(stdout, "\tyour string: %s\n", str.el); //prnt_str(str);
	if (leng_check(&cstr) == 1) fprintf(stdout, "\tcorrect string: %s\n", cstr.el); prnt_str(&cstr);

	return;
}

void file_inp (string* pstr)
{
	FILE *pfl;
	if ((pfl = fopen("d:\\c\\codec\\mes\\file\\fileinput.txt", "r")) == NULL)
	{
		printf("\tERROR! somethig goes wrong with opening your file. \n");
		return;
	}

	rewind(pfl);
	int i = -1;
	do
	{
		i++;
		pstr->el[i] = getc(pfl);
	}
	while ((i < STR_LENGTH)&&(pstr->el[i] != EOF));

	pstr->len = i;
	fclose(pfl);

	return;
}

void correct (string* pstr, string* pcstr)
{
	//printf("original:(%3.d)           _ ", pcstr->len); prnt_str(pstr);
	spaces(pstr, pcstr);
	//printf("spaces(pstr, pcstr):(%3.d)_ ", pcstr->len); prnt_str(pcstr);
	smbls (pcstr);
	//printf("smbls(pcstr):(%3.d)       _ ", pcstr->len); prnt_str(pcstr);
	lett_size (pcstr);
	//printf("lett_size(pcstr):(%3.d)   _ ", pcstr->len); prnt_str(pcstr);

	return;
}

//проходит по строке и оставляет по одному пробелу между словами и знаками
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

//перед использованием этой части мы оставили по одному пробелу перед символами
void smbls (string* pcstr) 
{
	unsigned int j = 1; // чтобы предостеречь ошибки связанные с тем что на первом месте могут стоять знаки
	while(j < pcstr->len)
	{
		if ((pcstr->el[j] == '.')||(pcstr->el[j] == '?')||(pcstr->el[j] == '!')||(pcstr->el[j] == ',')||(pcstr->el[j] == ';')||(pcstr->el[j] == ':')||(pcstr->el[j] == ')'))
		smb_cond(pcstr, j, 1);

		if  ((pcstr->el[j] == '.')&&(pcstr->el[j + 1] == '.')&&(pcstr->el[j + 3] == '.'))
		smb_cond(pcstr, j, 3);

		if ((pcstr->el[j] == ' ') && ((j + 1) == pcstr->len)) // такая ситуация может возникнуть если в конце текста, после слов стоят пробелы
		pcstr->len--;

		j++;
	}

	return;
}

//вообще эта функция должна позволить выделять любую последовательность символов из текста
void smb_cond (string* pcstr, int pos, int len)
{
	if ((pcstr->el[pos - 1] != ' ')&&(pcstr->el[pos + len] != ' '))
	{
		if (pcstr->len + 1 > STR_LENGTH)
		{	pcstr->len = - 1; return;	}

		ins_smb(pcstr, (pos + len), ' ');
		pcstr->len++;
	}
	else if ((pcstr->el[pos + len] != ' '))
	{
		//это мы переносим нашу последовательность на один символ назад
		for (int i = pos; i < pos + len; ++i)
		pcstr->el[i - 1] = pcstr->el[i];

		del_smb(pcstr, (pos + len - 1)); 
		ins_smb(pcstr, (pos + len - 1), ' ');
	}
	else if ((pcstr->el[pos - 1] == ' '))
	{
		for (int i = pos; i < pos + len; ++i)
		pcstr->el[i - 1] = pcstr->el[i];

		del_smb(pcstr, (pos + len - 1));
		pcstr->len--;
	}

	return;
}

//это не то чтобы удаление, мы просто сдвигаем всю строку к элементу с известным номером
void del_smb (string* pcstr, int pos)
{
	for (int i = pos; i < pcstr->len; i++)
	pcstr->el[i] = pcstr->el[i + 1];

	return;
}

void ins_smb (string* pcstr, int pos, char smb)
{
	for (int i = pcstr->len + 1; pos < i; i--)
	{
		pcstr->el[i] = pcstr->el[i - 1];
	}
	pcstr->el[pos] = smb;

	return;
}

void lett_size (string* pcstr)
{
	if ((pcstr->el[0] >= 'a') && (pcstr->el[0] <= 'z'))
	{
		pcstr->el[0] = pcstr->el[0] - 32;
	}

	for (int i = 1; i < pcstr->len; i++)
	{
		if ( ((pcstr->el[i] == '.')||(pcstr->el[i] == '!')||(pcstr->el[i] == '?')) && ((pcstr->el[i + 2] >= 'a') && (pcstr->el[i + 2] <= 'z')) ) 
		pcstr->el[i + 2] = pcstr->el[i + 2] - 32;

		if ( ((pcstr->el[i - 1] != '.')&&(pcstr->el[i - 1] != '!')&&(pcstr->el[i - 1] != '?')) && ((pcstr->el[i + 1] >= 'A') && (pcstr->el[i + 1] <= 'Z')) )
		pcstr->el[i + 1] = pcstr->el[i + 1] + 32;
	}

	return;
}


void prnt_str (string* pname)
{
	if (leng_check(pname) == 1)
	{
		for (int i = 0; i < pname->len ; i++)
		{
			fprintf(stdout, "%c", pname->el[i]);
		}
		fprintf(stdout, "\n");
		return;
	}
	else return;
}


short leng_check (string* pname)
{
	if (pname->len <= 0) {	printf("\tERROR! overflow.\n");	return 0;	}
	else return 1;
}