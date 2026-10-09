/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
 * 
 * A single blank should be given preference.
 */

#include <stdio.h>
#define COLUMNS 7
#define BLANK ' '
#define MAXLINE 1000

char line [MAXLINE];
char entabbed_line [MAXLINE];

int len;
int get_line (void);
void entab (void);
int count_blanks (int start_index);

int main ()
{
	while ((len=get_line())>0) {
		entab ();

		printf ("%s\n", entabbed_line);
	}

	return 0;
}

int get_line (void)
{
	int c, i;

	for (i=0; i<MAXLINE && (c=getchar())!=EOF && c!='\n'; ++i)
		line[i]=c;

	if (c=='\n')
		line[i++]=c;

	line[i]='\0';

	return i;
}

void entab (void)
{
	int i, k;
	int nblanks, remainder, difference, fewer_blanks;
	
	nblanks=0;
	for (i=0, k=0; i<len; ++i, ++k) {
		if (line[i]==BLANK)
			nblanks = count_blanks (i);

		if (nblanks>=COLUMNS) {
			remainder = nblanks % COLUMNS;
			
			difference = nblanks;
			while (difference != remainder) {
				entabbed_line[k++]='\t';
				difference = difference - COLUMNS;
			}

			while (remainder>0) {
				entabbed_line[k++] = BLANK;
				--remainder;
			}
			
		} else if (nblanks>0 && nblanks<COLUMNS) {
			// blanks were fewer than number of tab columns
			fewer_blanks = nblanks;
			while (fewer_blanks>0) {
				entabbed_line[k++]=BLANK;
				--fewer_blanks;
			}
		}

		i = i + nblanks;
		entabbed_line[k] = line[i];
		nblanks = 0;
	}
}

int count_blanks (int start_index)
{
	int j, i;

	j=0;
	// stop when line[i] is no longer a blank
	for (i=start_index; line[i]==BLANK; ++i)
		++j;

	return j;
}
