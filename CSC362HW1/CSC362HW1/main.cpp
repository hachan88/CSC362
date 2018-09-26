/*
 Name: Hayato Hiroura
 Instructor: Richard Fox
 Class: CSC362
 Date: Sep 10, 2017
 
 Description: for this assignment, open two input text files and input them character-by-character, 
 reading one character from each of the files until you reach the end of both files.
 decide whether to output one of the characters or not by fllowing some rules:
 -if  they are equal
 -if they are both digits
 -If they are both punctuation marks
 -If none of these are true, but if either character equals the user’s input character
 
 Characters will be output to a third text file. 
 Count the number of input and output characters. 
 At the end of the program, generate a report to the console using printf statements.
 */

#include<stdio.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
  char x; //a character from user input
  printf("Enter a character: ");  //ask user to type a character
  scanf("%c",&x);
  
  int inputSize = 0, outputSize = 0, countNumOfMatched = 0;  //count number of input and output
  
  FILE *fp1, *fp2, *fp3;  //fp1 is input2a.txt, fp2 is input2b.txt, fp3 is output file
 
  //open all files
  fp1 = fopen("/Users/Hayato/Documents/CSC362/input2a.txt", "r");
  fp2 = fopen("/Users/Hayato/Documents/CSC362/input2b.txt", "r");
  fp3 = fopen("output1.txt", "w");
  
  char c1, c2, c3;  //declare char to get each character from file
  
  int num = 0;
  
  //use loop to get every character of the text file
  while(( c1 = getc(fp1)) != EOF) //until end of fiile
  {
    c2 = getc(fp2); //get character from file2 to compare with file1
    
    if(c1 == c2)  //if both file has same character, output the charcter to file
    {
      if(ispunct(c1) && ispunct(c2))  //if both file has same character and punctuation output the character by rotating between the two filessecond time
      {
        //when num is even, output first file. when num is odd output second file
        if(num % 2 == 0)
          putc(c1, fp3);  //output from first file
        else
          putc(c2, fp3); //output from second file
        
        outputSize++; //count output
      }
      else
      {
      putc(c1, fp3);  //output
      outputSize++; //count output
      }
    }
    
    else if(isdigit(c1) && isdigit(c2))  //if both same character and digit, output both digits (file1 first, file2 second)
    {
      putc(c1, fp3);
      putc(c2, fp3);
      outputSize = outputSize + 2;  //count output
    }
    
    //If they are both punctuation marks, output the character by rotating between the two filessecond time
    else if(ispunct(c1) && ispunct(c2))
    {
      if(num % 2 == 0)
        putc(c1, fp3);  //output from first file
      else
        putc(c2, fp3); //output from second file
      
      num++;  //increment num
      outputSize++; //count output
    }
    else  //If none of these are true
    {
      //if either character equals the user’s input character, output the character that did not match the user’s character
      if(c1 == x || c2 == x)
      {
        if(c1 == x)
          putc(c2, fp3);
        else
          putc(c1, fp3);
        
        outputSize++; //count output
        countNumOfMatched++; //count if one file’s character matched the user’s character
      }
    }
    inputSize++;  //increment input size every loop
}
  
  //close all files
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);

  // compute the following percentage (as a double): output_size / input_size * 100
  double percentage = (double)outputSize / inputSize * 100;
  
  printf("size of input: %d\n", inputSize);
  printf("size of output: %d\n", outputSize);
  printf("matched user input: %d\n", countNumOfMatched);
  printf("percentage size: %.2f%%\n", percentage);
  
  //output the file to see on console
  fp3 = fopen("output1.txt", "r");
  while((c3 = getc(fp3)) != EOF)
  {
    putchar(c3);
  }
  fclose(fp3);
  
}


//console output
/*
 Enter a character: t
 size of input: 799
 size of output: 770
 matched user input: 16
 percentage size: 96.37%
*/

//output.txt file
/*
 CS, Ohio -- A  rd of the way through the foosball season, Ohio Stadium gob a new
 playing surface on uesday.  Workers laid 790,0500 square feel of sod on the field, replacing
 a 34-year-old slab of grss what had adly deeeriorated. Afher aturday,s 28-65 win over Pn
 State, whe fr home game of the season. there wee large reas of wrn and tor surf,
 particularly at idfield and wthn a ew eet of the ome and isitor sidelines.
 
 The new surface is bluegrass from Cygnet Turf farm between Findlay and Bowling Green.
 Scraping off the old grass and laying the new field will cost between $75,010101 and $10101,000.
 
 Workers with rs had to scratch o large piles of oose sod, irl and rass after the
 No! 1-ranked Buckeyes' second home game against incinnati on Sept 16.
 */
