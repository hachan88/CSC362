/*
 Name: Hayato Hiroura
 Class: CSC362
 Instructor: Richard Fox
 Date: October 1
 
 This program will compute city ratings based on various statistics. The input will come from a disk file.
 Input one city’s information at one time using fscanf. After input, call various functions
 to perform computations on that city and assign the city a rating. An output function will output some of
 the computed values including the rating for the city. Keep track of the number of cities evaluated and the
 sum of their ratings along with the highest rated city (both its rating and city name). After evaluating all of
 the cities in the file, the program will end by outputting the number of cities evaluated, the average rating
 of all cities, and the most highly rated city’s name and rating.
 
 There are 4 files with functions split between various files:
 1, file which has main function
 2, file which has input/output functions
 3, file whcih has computation/update functions
 4, header file
 */

#include "header.h" //include header file

//main function will open an input file and loop on each city until the end of the file, calling the six functions
//after loop, call 7th function  to output a summary of the number of input, the average livability, and the city’s name and rating found to be the most livable
int main(){
  FILE *fp1;
  fp1 = fopen("/Users/Hayato/Documents/CSC362/cities2.txt", "r"); //open file
  
  char name[20], bestCityName[20];
  int population, squareMileage, pollution, crime, expense, numOfHighway, count = 0;
  double density, pollutionRate, trafficRate, crimePerCapita, expensePerCapita, livability, bestLivability, totalLivability;
  
  printf("City \t\t Population dens \t\t Livability score \n");
  
  //call getInput() in loop until end of file
  while(getInput(fp1, name, &population, &squareMileage, &pollution, &crime, &expense, &numOfHighway) != EOF){
 
    //call getDensity and pass city’s population and square mileage
    density = getDensity(population, squareMileage);
    
    //call computeRate
    computeRate(&pollutionRate, &trafficRate, &crimePerCapita, &expensePerCapita, density, population, pollution, crime, expense, numOfHighway);
    
    //call getLivability
    livability = getLivability(pollutionRate, trafficRate, crimePerCapita, expensePerCapita);
    
    //call update
    update(&bestLivability, &totalLivability, &count, bestCityName, name, livability);
    
    //call output
    output(name, density, livability);
  }

  //call outputSummary
  double averageLivability = (double)totalLivability / count;
  outputSummary(count, bestLivability, bestCityName, averageLivability);
  fclose(fp1);
}

