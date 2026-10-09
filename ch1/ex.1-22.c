/* Exercise 1-22. Write a program to ``fold'' long input lines into two or more shorter lines after
 * the last non-blank character that occurs before the n-th column of input. Make sure your
 * program does something intelligent with very long lines, and if there are no blanks or tabs
 * before the specified column.
 */

#include <stdio.h>
#define MAXLINE 1000
#define MAXCOLUMNS 66
#define BLANK ' '

int len;
int buffer_len;
char line [MAXLINE];
char buffer [MAXLINE];
char folded_line [MAXLINE];

int get_line (void);
void fold (void);
int copy (int start_index, char line_buffer []);

int main ()
{
	while ((len=get_line())>0) {
		fold ();

		printf ("\n%s\n", folded_line);
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

void fold (void)
{
	int i, j;

	buffer_len = copy (0, line);
	for (i=0, j=0; i<buffer_len; ++i, ++j) {
		
		if ((i % MAXCOLUMNS)==0 && i!=0) {
				
				while (buffer[i]!=BLANK && i!=0) {
					--i;
					--j;
				}

				if (buffer[i]==BLANK) {
					folded_line[j]=BLANK;
					folded_line[++j]='\n';
					buffer_len = copy (++i, buffer);
					i = -1;
				} 
            else {
                    while (i<(MAXCOLUMNS)) {
                        folded_line[j]=buffer[i];
                        ++i;
                        ++j;
                    }

                    folded_line[j]='\n';
                    folded_line[++j]='-';
                    buffer_len = copy (i, buffer);
                    i=-1;
            }
		}
		else {
			folded_line[j]=buffer[i];
		}
	}
}

int copy (int start_index, char line_buffer [])
{
	int i;

	for (i=0; i<MAXLINE && line_buffer[start_index]!=EOF && line_buffer[start_index]!='\n'; ++i, ++start_index)
		buffer[i]=line_buffer[start_index];

	if (line_buffer[start_index]=='\n')
		buffer[i++]=line_buffer[start_index];

	buffer[i]='\0';

	return i;
}
