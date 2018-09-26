/*
 Name: hayato Hiroura
 Class: CSC362
 Instructor: Richard Fox
 Date: 12/8/2017
 
 Description:
 Implement the first fit strategy. Use an array of Bins where each Bin is
 a struct that stores its current available capacity (initialized to 1.0) and a pointer to a linked list of
 items currently placed into that Bin. The linked list will consist of struct nodes that store the name of
 the item (a string), the weight of the item (a double) and a pointer to the next struct node in the list
 This program requires two structs (a node struct and a bin struct) and one array (of bins). You will
 have to implement these linked list functions: ordered insert to insert the new item into a node in
 its appropriate location using alphabetical ordering of item names, traverse the list to print the items
 of the list out along with the list’s capacity, destroy the list to deallocate the nodes of the list.
 
 I've been stuck in insert() part for a long time and couldn't figure out, so even though it's not completed yet I submit this assignment
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// defines a node in a linked list
//The linked list will consist of struct nodes that store the name of the item (a string),
//the weight of the item (a double) and a pointer to the next struct node in the list.
struct node{
  char name[20];  //item's name
  double weight;  //item's weight
  struct node *next;  //pointer to the next node
};

//bin struct
struct Bin{
  double capacity;  //bin capacity
  struct Bin *list; //a pointer to a linked list of items currently placed into that Bin
};

// prototypes
//struct node *insert(struct Bin *, char *, double );
struct Bin *insert(struct Bin *, char *, double);
void print(struct node *);
void destroy(struct node *);

int main(){
  int i, j;
  char name[20];
  double weight;
  
  /*  {"Vase", 0.5},
   {"Bowling_ball", 0.9},
   {"Book", 0.3},
   {"Umbrella", 0.4},
   {"Gold_medal", 0.7},
   {"Speaker_1", 0.4},
   {"Walkman", 0.2},
   {"Speaker_2", 0.4},
 */
  
  //For each bin b in the array of Bins, initialize b.capacity = 1.0 and b.list to NULL
  //array of bin(struct)
  struct Bin bins[10];
  for(i = 0; i < sizeof(bins); i++){
    bins[i].capacity = 1.0;
    bins[i].list = NULL;
  }
  
  int n;
  printf("Enter the number of items: ");  //ask user to know how many items to input
  scanf("%d", &n);
  
  //Input the item, i (from keyboard or a disk file, or it can be hard-coded into the program)
  
  for(i = 0; i < n; i++){
    printf("Enter item's name and weight: \n"); //ask user to input item's name and weight
    scanf("%s\n", name);
    scanf("%lf\n", &weight);
    
    int inserted = 0;
    j = 0;
    
    //While i is not placed in a Bin, iterate through each Bin, b, in the array of Bins
    while(!inserted){
      //If item i can be placed into b (that is, is b.capacity + weight(i) <= 1.0)
      if(bins[j].capacity >= weight){
        
        bins[j].list = insert(bins[j].list, name, weight);  //insert into bins[j]
        
        //modify b.capacity
        bins[j].capacity = bins[j].capacity - weight;
        inserted = 1; //inserted = true
      }
      else{
        j++;  //move in to next bin
      }
    }
  }
}

//The insert function then creates the new node containing name and size and inserts the new node in the linked list in the appropriate place
struct Bin *insert(struct Bin *list, char *n, double w){
  struct node *item;
  
  item = (struct node *)malloc(sizeof (struct node));      // allocate a node from heap
  
  // assign the new node its value
  strcpy(item->name, n);
  item->weight = w;
  
  item->next = NULL;    //the current wilast node, so make next NULL
  
  list = (struct Bin*)item;
  
  //return the head pointer
  return list;
};

// print the items of the list out along with the list’s capacity
void print(struct node *n){
  while(n != NULL)
  {
    printf("%s\n", n->name);
    printf("%lf\n", n->weight);
    n = n->next;                        // move n to next node in list
  }
}

// deallocate the nodes of the list
void destroy(struct node *n){
  struct node *temp = n;                   // need a temp pointer as one pointer will point to next
  while(n != NULL)                         // while we still have list nodes to deallocate
  {
    n = n->next;                        // n now points to the next node in the list
    free(temp);                       // so we can deallocate the current node
    temp = n;
  }
}
