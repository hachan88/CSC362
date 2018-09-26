//this file includes all input/output functions

#include "header.h"

// this function gets one line of input file
int getInput(FILE *fp1, char *name, int *population, int *squareMileage, int *pollution, int *crime, int *expense, int *numOfHighway){
  return fscanf(fp1, "%s %d %d %d %d %d %d", name, population, squareMileage, pollution, crime, expense, numOfHighway);
}

//this function outputs a summary of this city (name, livability, population density)
void output(char *n, double d, double l){
  //printf("City \t Population dens \t Livability score \n %s \t %.2f \t %.2f", n, d, l);
  printf("%s \t\t\t %.2f \t\t\t %.2f\n", n, d, l);
}

//function to output a summary of the number of cities input, the average livability, and the city’s name and rating found to be the most livable
//parameters(count, best livability, best city, avrageLivability)
void outputSummary(int c, double bl, char *bc, double av){
  printf("Of the %d cities, the average livability was %.2f, and the most liveable was %s with a score of %.2f \n", c, av, bc, bl);
}
