//This file is header file that includes all function prototypes, #include and #define statements
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS
#define A 1.7
#define B 872.6
#define C 1217.1
#define D 13.81

//function prototype
int getInput(FILE *, char *, int *, int *, int *, int *, int *, int *); //input city's information
double getDensity(int, int);  //compute population density
void computeRate(double *, double *, double *, double *, double, int, int, int, int, int);  //compute the city’s amount of pollution rating, traffic rating, crime per capita, expense per capita
double getLivability(double, double, double, double); //compute the city’s livability
void update(double *, double *, int *, char *, char *, double); //update the most livable city’s name and score
void output(char *, double, double);  //ouput all citY's name and livability
void outputSummary(int, double, char *, double);  //output summary and best city
