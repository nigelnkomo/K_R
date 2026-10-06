/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop.  
* Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?  
*/ 

#include <stdio.h>
#define COLUMNS 8
#define MAXLINE 1000

char line [MAXLINE];
char detabbed_line [MAXLINE];
int len;

int get_line (void);
void detab (void);

int main ()
{
	while ((len = get_line())>0) {
		detab ();
	
		printf ("%s\n", detabbed_line);
	}

	return 0;	
}

int get_line (void)
{
	int i, c;

	for (i=0; i<MAXLINE-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		line[i]=c;

	if (c=='\n')
		line[i++]=c;

	line[i]='\0';

	return i;
}

void detab (void)
{
	int i, j, k;
	int spaces_needed;

	for (i=0, k=0; i<len; ++i, ++k) {

		if (line[i] == '\t') {
			
			spaces_needed = COLUMNS - (k%COLUMNS);

			j=0;
			while (j<spaces_needed) {
				detabbed_line[k++] = ' ';
				++j;
			}
			--k;
		}
		else {
			detabbed_line[k]=line[i];
		}
	}


	if (i==len)
		detabbed_line[++k]='\0';
}
