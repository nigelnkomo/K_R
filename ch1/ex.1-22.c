/* Exercise 1-22. Write a program to ``fold'' long input lines into two or more shorter lines after
 * the last non-blank character that occurs before the n-th column of input. Make sure your
 * program does something intelligent with very long lines, and if there are no blanks or tabs
 * before the specified column.
 */

#include <stdio.h>
#define MAXLINE 1000
#define MAXCOLUMNS 66
#define BLANK ' '
#define TAB '\t'
#define TABCOLUMNS 8

int len;
int buffer_len;
char line [MAXLINE];
char buffer [MAXLINE];
char folded_line [MAXLINE];

int get_line (void);
void fold (char line_to_fold []);
int copy (int start_index, char line_buffer []);
void reset_line (void);

int main ()
{
	while ((len=get_line())>0) {
		     fold (line);

		     printf ("\n%s\n", folded_line);
           reset_line ();
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

void fold (char line_to_fold [])
{
	int i, j, tmp, blanks_needed;

	buffer_len = copy (0, line_to_fold);
	for (i=0, j=0, tmp=0; i<buffer_len; ++i, ++j, ++tmp) {

      // the presence of tabs means we will arrive at the end of the line faster
      if (buffer[i]==TAB) {
              blanks_needed = TABCOLUMNS - (tmp%TABCOLUMNS);
              tmp = tmp + blanks_needed;
      }     
	
      /* don't break at index 0 since 0%MAXLINE is 0
       * trigger folding when tmp is big enough
       * tmp > MAXCOLUMNS-1 in situations where tmp overshoots   
       */ 
		if (((i % (MAXCOLUMNS-1))==0 && i!=0) || (tmp >= (MAXCOLUMNS-1))) {
            
            // trace back to find blank or tab or stop if you've reached the beginning of the buffer
				while (buffer[i]!=BLANK && buffer[i]!=TAB && i!=0) {
					--i;
					--j;
				}
            
            // store the blank or tab and fold after it
				if (buffer[i]==BLANK || buffer[i]==TAB) {
                    folded_line[j]=buffer[i];
                    folded_line[++j]='\n';
                    buffer_len = copy (++i, buffer); // update buffer to start after the blank or tab
                    i = -1; // i will be incremented to zero in the next iteration
                    tmp = -1; /* reset tmp */
				} 
            else {

                    // if there was no blank or tab, then word was longer than MAXCOLUMNS
                    // add word to whole line...
                    while (i<(MAXCOLUMNS)) {
                        folded_line[j]=buffer[i];
                        ++i;
                        ++j;
                    }
                     
                    //...and fold word when we reach the end of the line
                    folded_line[j]='\n';

                    // if the next character isn't a blank or a tab, then the word isn't finished yet. use - to show that.
                    // increments in array[++i] mutate the value of i
                    if ((buffer[i]!=BLANK || buffer[i]!=TAB) && (buffer[++i]!=BLANK || buffer[++i]!=TAB)) {
                            folded_line[++j]='-';
                            --i;
                    }
                    
                    buffer_len = copy (i, buffer);
                    i=-1; // i will be incremented to zero in the next iteration
                    tmp = -1; /* reset tmp */
            }
		}
		else {
              // copy to folded line if we haven't reached MAXCOLUMNS
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

void reset_line (void)
{
        int i;

        for (i=0; i<MAXLINE; ++i) {
                line[i]='\0';
                buffer[i]='\0';
                folded_line[i]='\0';
        }
}
