/*
 Name: Hayato Hiroura
 Class: CSC362
 Instructor: Richard Fox
 Date: 11/14/2017
 
 Program4:
 Write code in assembly to make an increasingly additive sequence which is a list of integer numbers
 such that the next number in the sequence is greater than the sum of the previous numbers.
 Ask user to input two integers (first number should be smaller than second number), then find prime numbers between the two integers.
 Once you find prime number, then check if it is increasingly additive prime sequence. If it is, output the number.
 
 The part I write in assembly is this program in C:
  for(i = num1; i <= num2; i++){
    divisor = 0;
    for(j = 1; j <= i; j++){
      if(i % j == 0)
        divisor++;
    }
    if(divisor == 2){
      if(i >= totalPrimeNum){
        totalPrimeNum = totalPrimeNum + i;
        printf("%d ", i);
      }
    }
  }
 */

#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
  
  int num1, num2, divisor, totalPrimeNum = 0, i, j;
  printf("Input two numbers. First number must be less then second number\n");
  
  //input two integers
  scanf_s("%d", &num1);
  scanf_s("%d", &num2);
 
  __asm {
    mov eax, num1
    mov i, eax //i is first integer
    mov ebx, num2 //num2 is second integer and store into ebx
  loop1 : cmp i, ebx   //loop lasts until i(num1) > num2.
    jg xout //if num1 > num2 then finish loop
    mov eax, 0
    mov  divisor, eax  //initialize divisor to 0
    mov eax, 1
    mov j, eax //initialize j to 0
    mov eax, i
  loop2 : cmp j, eax // inner loop lasts until j > i
    jg if1 //if j > i, out the inner loop and jump to if1 to check if i was prime number
    mov edx, 0  // edx is the left half of the numerator
    mov eax, i  // eax is the right half of the numerator
    idiv j // quotient is placed in eax, remainder in edx
    mov eax, i
    cmp edx, 0  // is i % j == 0 ????
    jne then2 //if(edx != 0) jump to then2 for next loop
    inc divisor //otherwise increment devisor
    jmp then2  //jump to then2 for next loop
  if1 : cmp divisor, 2  //if(divisor == 2)
    jne then  //if not, jump to then. if yes, it means the number is prime number, so move on next check
    mov eax, i
    cmp eax, totalPrimeNum //check if it's increasingly additive sequence (i > total of prime number in the list)
    jle then //if not, jump to then
    mov eax, i //if yes, add the prime number to the sum of the prime numbers
    add totalPrimeNum, eax  //totalPrimeNum = totalPrimeNum + i
  }
  
  //print it out before going on to the nextnumber
  printf("%d, ", i);
  
  __asm {
  then: inc i  //increment i
    jmp loop1
  then2 : inc j //increment j
    jmp loop2
  xout : nop
  }
}

/*
 output1
 Input two numbers. First number must be less then second number
 3
 1000
 3, 5, 11, 23, 43, 89, 179, 359, 719, Press any key to continue . . .
 
 output2
 Input two numbers. First number must be less then second number
 300
 5000
 307, 311, 619, 1249, 2503, 4993, Press any key to continue . . .
 */



