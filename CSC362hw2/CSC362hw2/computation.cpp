//this file includes all computation functions and update function

#include "header.h"

//this function returns single value which is population density, so use return statement.
double getDensity(int p, int s){ //p is population, s is square mileage
  double d = (double)p / s;
  return d;
}

//this function computes the city’s amount of pollution rating, traffic rating, crime per capita, expense per capita
//parameters are (pollution rating, traffic rating, crime per capita, expense per capita, density, population, pollution, crime, expense, number of highway
void computeRate(double *pr, double *tr, double *cpc, double *epc, double d, int pop, int pol, int c, int e, int n){
  
  //A, B, C are constants that declared in header file
  *pr = (double)pol * d / 1000; //Pollution = pollution amount * population density / 1000
  *tr = d * A / (double)n;  //Traffic rating = population density * 1.7 / major highways
  *cpc = (double)c * d / B; //Crime per capita = crime * population density / 872.6
  *epc = (double)e * d / C; //Expense per capita = expense * population density / 1217.1
}

//compute the city’s livability (this function returns a single value)
double getLivability(double pr, double tr, double cpc, double epc){
  //formula is Livability = 100 – (Pollution + Traffic rating + Crime per capita + Expense per capita) / 13.81
  double l = 100 - (pr + tr + cpc + epc) / D;
  return l;
}

//this function updates running totals for total livability, total number of cities processed,
//and determine if this city is more livable than the previous best and if so, update the most livable city’s name and score
//parameter(best city, best livability, total livability, count, name, livability)
void update(double *bl, double *tl, int *c, char *bc, char *n, double l){
  *tl = *tl + l;  //total livability
  *c = *c + 1;  //total number of cities processed
  if(*bl < l){  //if current livability is better than best livability, set the current one to the best
    *bl = l;
    strcpy(bc, n);
  }

}
