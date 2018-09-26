/*
 Name: Hayato Hiroura
 Class: CSC362
 Instructor: Richard Fox
 Date: 11/14/2017
 
 Program5: Implement the Selection Sort algorithm for an array of int values in assembly language.
 The selection sort makes n-1 passes through an array of n elements locating the smallest element and swapping it with the ith element.
 For the array part like array[i], I set ebx which is offset to 4 and multiply to index.
 For example if i = 2 and array[i], then i * ebx = 8, and it equals to array[2].
 
 The part I write in assembly is like this program in C:
  for(i = 0; i < n - 1; i++) {
    min = a[i];
    minposition = i;
    for(j = i + 1; j < n; j++) {
      if(a[j] < a[minposition]) {
        min = a[j];
        minposition = j;
    }
  //swap a[i] and a[minposition]
    temp = a[i];
    a[i] = a[minposition];
    a[minposition] = temp;
    }
  }
 */

#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
  int a[] = { 100, 99, 97, 95, 90, 87, 86, 83, 81, 77, 74, 69, 63, 50, 44, 43, 39, 31, 29, 12 };
  //int a[] = { 8, -1, 7, -8, 6, 3, -4, 4, 1, -2, 9, -5, 0, 2 };
  int i, j, min, minposition, temp;
  int n = sizeof(a) / sizeof(a[0]); //n is size of array
  
  __asm {
    mov eax, 0
    mov i, eax  //intialize i to 0
  loop1: mov ebx, 4  //ebx is offset
    mov eax, n
    sub eax, 1  //n - 1
    cmp i, eax //compare if i < n - 1
    jge xout  //if(i >= n - 1) then finish loop
    mov eax, i
    mul ebx //eax = i * 4
    mov ecx, a[eax] //ecx = a[i]
    mov min, ecx //min = a[i]
    mov eax, i
    mov minposition, eax  //minposition = i
    mov ecx, i
    add ecx, 1
    mov j, ecx  //j = i + 1
  loop2: mov eax, n //initialize eax to size of array
    cmp j, eax  //compare if j < n
    jge then2  //if(j >= n) jump to then2
    mov eax, j
    mul ebx //To calculate offset, j * 4
    mov ecx, a[eax] //ecx = a[j]
    mov eax, minposition
    mul ebx //To calculate offset, minposition * 4
    mov eax, a[eax] //eax = a[minposition]
    cmp ecx, eax  //compare a[j] and a[minposition]
    jge then //if(a[j] >= a[minposition], jump to then
    mov min, ecx //min = a[j]
    mov eax, j
    mov minposition, eax  //minposition = j
  
    //swap part
    //1, temp = a[i] part
  then: mov eax, i
    mul ebx //offset = i * 4
    mov ecx, a[eax]
    mov temp, ecx //temp = a[i]
    
    //2, a[i] = a[minposition] part
    mov eax, minposition
    mul ebx //offset = minposition * 4
    mov ecx, a[eax] //ecx = a[minposition]
    mov eax, i
    mul ebx //offset = i * 4
    mov a[eax], ecx //a[i] = a[minposition]
    
    //3, a[minposition] = temp part
    mov ecx, temp
    mov eax, minposition
    mul ebx //offset = minposition * 4
    mov a[eax], ecx //a[minposition] = temp
    
    //now swap is done
    inc j //increment j
    jmp loop2
    
  then2: inc i  //increment i
    jmp loop1
    
  xout: nop
  }
  
  for (i = 0; i < n; i++)
    printf("%d, ", a[i]);
  
}

//output1
//12, 29, 31, 39, 43, 44, 50, 63, 69, 74, 77, 81, 83, 86, 87, 90, 95, 97, 99, 100, Press any key to continue . . .

//output2
//-8, -5, -4, -2, -1, 1, 2, 0, 3, 4, 6, 7, 8, 9, Press any key to continue . . .


