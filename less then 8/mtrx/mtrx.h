#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define RNUM 3

typedef struct
{
	float* s;
	unsigned int n, m;
	char name[50];
} mtrx;

void initmtr (mtrx *pmtr);

void flinit (FILE *pflr);
void flprnt (FILE *pflw);
void rndinit (mtrx *pmtr);
void prntmtr (mtrx *pmtr);

mtrx sumAB (mtrx A, mtrx B);
mtrx prodAB (mtrx A, mtrx B);
void mnrM (mtrx M, mtrx mM, int k, int l);
double detM (mtrx M);
mtrx invrsM (mtrx M, double dM);

unsigned int putpositiveprime (void);
void memrls (mtrx *pmtr);
void NaNtest (double x);
void flread(mtrx *pmtr);
void flwrte(mtrx *pmtr);
short ending (void);