/*  Program demonstrates file reading and writing.  It copies one line at a time, char by char
	into a temp array, and then prints that line backwards to the output file.  The output is
	also one character at a time, just backwards  */

#include <stdio.h>			// for file functions

int main()
{
  char x;				// current char from one file to other
  char line[80];			// the temp string to store each line
  int i = 0, j;			// i counts number of chars for current line, j is a loop variable
  
  FILE *fp1, *fp2;		// fp1 points to the input file, fp2 points to the output file
  fp1 = fopen("/Users/Hayato/Documents/CSC362/input1a.txt", "r");	// open input file, read-only
  fp2 = fopen("output.dat", "w");	// open output file, write-only
  while((x=getc(fp1))!=-1)	// get next char from input file, store in x, until we reach EOF
  {
    line[i++] = x;		// add latest char to the line
    if(x=='\n')		// if this char is end of line, then output line backwards
    {
      for(j=i-2;j>=0;j--)		// skip the last char ('\n') and output each char one at a time
        putc(line[j], fp2);	// to the output file
      putc('\n', fp2);		// now add the '\n'
      i=0;				// reset number of chars in line to 0 to start new line
    }
  }
  fclose(fp1);			// when done, close both files
  fclose(fp2);
}
