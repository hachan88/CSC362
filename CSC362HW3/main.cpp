/*
 Name: Hayato Hiroura
 Instructor: Richard Fox
 Date: 10/19/2017
 Class: CSC362
 
 Description: In this assignment, program will implement a variation of the game Chutes and Ladders.
 In this game, two players take turns rolling a 6-sided die, moving their piece on the game board.
 the program uses array[100] for board of the game ans use pointer for each players so that pointer access into the array and
 output their current location and movement.
 the player's movement is depending on the character in array:
   ‘ ’: a normal square, a player who lands here does not move again in this turn (unless the other player is on the same square)
   ‘B’: move backward to the nearest preceding safe haven, stop at 0 if no more havens exist
   ‘F’: move forward to the next safe haven, stay here if no more havens exist
   ‘H’: a haven which a player might move to when landing on a ‘B’ or ‘F’; once moved to because of a ‘B’ or ‘F’, change the ‘H’ to a ‘*’ (do not change the ‘H’ if the player lands on this square normally, that is, without reaching here because of ‘B’ or ‘F’)
   ‘a’ – ‘m’: a chute, move backward (see below), change this square to ‘-’
   ‘o’ – ‘z’: a ladder, move forward (see below), change this square to ‘-’
   ‘n’ – is not used
 
 Use loop until either player win, and output player's movement on console and each character into text file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

//output the current game board to file; this function receives the board, player pointers, and FILE *
//use putc to output each character and the location of player1 and player2
void output(FILE *, char [], char *, char *);

//this function receives both player pointers, the board, the player number (1 or 2)
//determine the player's movement and output it on console
//this function calls other functions depending on the player's position: findHaven(), chuteLadder(), or collision()
char *move(char *, char *, int, char []);

//this function is called if the player lands on a ‘B’ or ‘F’. search forward/backward for the next ‘H’
//output the player's movement
char *findHaven(char *, char []);

//this function returns the new location of the player moving from a chute or ladder
char *chuteLadder(char *, char []);

//this function is called if two players are on same square
//If a player lands on a square that the other player is currently on, the player who just moved is moved back 1 square
char *collision(char *, char []);

int main(){
  
  int turn = 1;
  char board[100]="  mHk nH l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";
  
  //p1 and p2 points to the beginning of the array
  char *p1, *p2;
  p1 = &board[0];
  p2 = &board[0];
  
  //generate random time
  srand(time(NULL));
  
  //create a file
  FILE *file;
  file = fopen("/Users/Hayato/Documents/CSC362/output.txt", "w");
  
  //loop until a player wins;
  while((p1 >= board && p1 < board + 100) && (p2 >= board && p2 < board + 100)){
    printf("\ncurrent turn is %d\n", turn);  //output the current turn
    
    //call move function for each player. pass player's pointer, number and array
    p1 = move(p1, p2, 1, board); // player 1’s turn
    p2 = move(p2, p1, 2, board); // player 2’s turn
    
    //call output function to output text file. pass file and array and player's pointers
    output(file, board, p1, p2);
    
    turn++; //increment turn
  }
  
  //determine who won the game
  if((p1 >= board + 100) && (p2 >= board + 100))  //if both reach 100 in same turn
    printf("Drow");
  else if(p1 >= board + 100)  //if player "You" reches 100
    printf("You win!");
  else  //if player "Me" reaches 100
    printf("Me win!");
  
  fclose(file);
  
  printf("\n");
}

/*outputs the current game board to file; this function receives the board, player
 pointers, and FILE *; use a pointer to iterate through each character in the board and output
 either ‘1’, ‘2’ or the character at that board position depending on whether p1 is pointing
 at that location, p2 is pointing at that location, or otherwise; use putc to output each
 character (do not use printf(“%s”, board);); the loop will exist once you have reached \0.
 */
void output(FILE *file, char board[], char *p1, char *p2){
  //c is currently pointing the begining of array. and will increment the pointer to point at the next array element every loop
  char *c = &board[0];

  //loop until end of the array
  while(*c != '\0'){
    if(c == p1 || c == p2){ //if c points either p1 or p2
      if(c == p1) //if c (pointer) points where p1 is on, put '1' in file
        putc('1', file);
      else //if c (pointer) points where p2 is on, put '2' in file
        putc('2', file);
    }
    else
      putc(*c, file); //output each character
    c++;  //increment pointer
  }
  
  putc('\n', file);
}


/*
 this function receives both player pointers, the board, the player number (1 or 2)
 and the size of the board; output the player number; randomly generate a move from 1-6;
 move the player by that amount; determine if the player has landed on a chute/ladder or
 ‘B’/’F’, if so, call the appropriate function.
 if not or if the player has moved because of it, see if the player has landed on the other player (p1==p2) and if so, move this
 player back 1 square indicating a collision occurred; output the amount the player moved and where the player is now
 */
char *move(char *player, char *anotherPlayer, int num, char board[]){
  
  //create dice
  int dice;
  dice = rand() % 6 + 1;
  
  //move the player by that amount
  player = player + dice;
  
  //if num is 1 player "you" turn, if 2 player "me" turn
  if(num == 1){
    printf("You: rolled %d  ", dice);
  }
  else{
    printf("Me: rolled %d  ", dice);
  }
  
  //if pointer points any of those arphabet
  if(*player == 'a' || *player == 'b' || *player == 'c' || *player == 'd' || *player == 'e' || *player == 'f' || *player == 'g' || *player == 'h' ||
     *player == 'i' || *player == 'j' || *player == 'k' || *player == 'l' || *player == 'm' ||
     *player == 'o' || *player == 'p' || *player == 'q' || *player == 'r' || *player == 's' || *player == 't' || *player == 'u' || *player == 'v' ||
     *player == 'w' || *player == 'x' || *player == 'y' || *player == 'z'){
    
    //call chuteLadder
    player = chuteLadder(player, board);
    
    //if a player moves forward/backward because of a chute or ladder or haven and lands on the other player, this player moves back 1 additional square
    //no collision on square 0
    if(player == anotherPlayer && player != board){
      player = collision(player, board);
    }
  }
  //if pointer points F or B
  else if(*player == 'F' || *player == 'B'){
    
    //call findHaven
    player = findHaven(player, board);
    
    //if a player moves forward/backward because of a chute or ladder or haven and lands on the other player, this player moves back 1 additional square
    //no collision on square 0
    if(player == anotherPlayer && player != board){
      player = collision(player, board);
    }
  }
  //If a player lands on a square that the other player is currently on, the player who just moved is moved back 1 square
  else if(player == anotherPlayer && player != board){
    player = collision(player, board);
  }
  
  //output current position of player
  printf("now at %d\n", player - board);
  
  return player;
}

/*
 this function is called if the player lands on a ‘B’ or ‘F’; search
 forward/backward for the next ‘H’; if you reach board moving backward, stop searching
 and move the player here; if you reach board+100 moving forward, stop searching and do
 not move the player; reset the square landed on from ‘H’ to ‘*’. Output the result of this
 operation (moved forward, moved backward, did not move)
 */
char *findHaven(char *player, char board[]){
  
  //original square where currently player is on
  char *temp = player;
  
  //if player landed on F
  if(*player == 'F'){
    
    printf("moving forward to haven...  ");
    
    //loop until pointer finds H
    while(*player != 'H'){
      *(player++);  //increments the pointer to point at the next array element
      
      //If a player is to move forward to the next haven and there are none left, the player does not move.
      if(player == board + 100){
        printf("but there are none haven left, so player did not move...  ");
        player = temp;  //bring player back to where it was originally on
        return player;
      }
    }
    *player = '*';  //once moved to because of a ‘B’ or ‘F’, change the ‘H’ to a ‘*’
  }
  //if player landed on B
  else if(*player == 'B'){
    printf("moving backward to haven... ");
    
    //loop until pointer finds H
    while(*player != 'H'){
      *(player--);  //decrement the pointer to point at the before array element
      
      //If a player is to move backward to a haven and there are none left on the board, the player moves back to square 0
      if(player == &board[0]){
        printf("but there are none heaven left, so player moves back to square 0... ");
        return player;
      }
    }
     *player = '*';  //once moved to because of a ‘B’ or ‘F’, change the ‘H’ to a ‘*’
  }
  return player;
}

/*
 this function returns the new location of the player moving from a chute or
 ladder; the distance moved is p1+(int)(*p1-110); (or p2 for player 2); change the
 original square (the chute/ladder square) to ‘-’ and return the new computed value; the
 (int) ensures that (*p-110) is cast as an int rather than a char. For instance, if p1 is at
 board+2 then p1 is on an ‘m’. This operation computes p1 + (109-110) which is p1 – 1.
 This function should be called as p1=chuteLadder(p1, board); (or p2) This
 function is called from move, not main
 */
char *chuteLadder(char *player, char board[]){
  
  //the original square where currently player is on
  char* temp = player;
  
  //the distance moved is player + (int)(*player-110)
  int move = (*player - 110);
  
  //player landed on ladder
  if(*player == 'a' || *player == 'b' || *player == 'c' || *player == 'd' || *player == 'e' || *player == 'f' || *player == 'g' || *player == 'h' ||
     *player == 'i' || *player == 'j' || *player == 'k' || *player == 'l' || *player == 'm'){
    printf("landed on chute...moving %d...  ", move);
  }
  //player landed on chute
  else if(*player == 'o' || *player == 'p' || *player == 'q' || *player == 'r' || *player == 's' || *player == 't' || *player == 'u' || *player == 'v' ||
          *player == 'w' || *player == 'x' || *player == 'y' || *player == 'z'){
    printf("landed on ladder...moving %d...  ", move);
  }
  
  player = player + move; //move player
  
  *temp = '-';  //change the original square to "-"
  
  return player;
}


/*
 this function return the new location of the player moving from a collision.
 If a player lands on a square that the other player is currently on, the player who just moved is moved back 1 square
 */
char *collision(char *player, char board[]){
  printf("collision! ... moving back one square ...  ");
  player = player - 1;  //move one aquare back
  return player;
}

//output on console
/*
 
 current turn is 1
 You: rolled 2  landed on chute...moving -1...  now at 1
 Me: rolled 6  now at 6
 
 current turn is 2
 You: rolled 2  now at 3
 Me: rolled 2  now at 8
 
 current turn is 3
 You: rolled 5  collision! ... moving back one square ...  now at 7
 Me: rolled 5  now at 13
 
 current turn is 4
 You: rolled 4  moving backward to haven... now at 7
 Me: rolled 3  moving forward to haven...  now at 22
 
 current turn is 5
 You: rolled 1  now at 8
 Me: rolled 2  now at 24
 
 current turn is 6
 You: rolled 6  landed on chute...moving -9...  now at 5
 Me: rolled 1  landed on chute...moving -6...  now at 19
 
 current turn is 7
 You: rolled 4  landed on chute...moving -2...  now at 7
 Me: rolled 2  now at 21
 
 current turn is 8
 You: rolled 4  moving backward to haven... now at 3
 Me: rolled 4  now at 25
 
 current turn is 9
 You: rolled 1  landed on chute...moving -3...  now at 1
 Me: rolled 3  now at 28
 
 current turn is 10
 You: rolled 5  now at 6
 Me: rolled 4  now at 32
 
 current turn is 11
 You: rolled 2  now at 8
 Me: rolled 6  landed on chute...moving -4...  now at 34
 
 current turn is 12
 You: rolled 5  now at 13
 Me: rolled 6  now at 40
 
 current turn is 13
 You: rolled 2  now at 15
 Me: rolled 4  now at 44
 
 current turn is 14
 You: rolled 5  landed on ladder...moving 2...  now at 22
 Me: rolled 6  now at 50
 
 current turn is 15
 You: rolled 4  moving backward to haven... now at 13
 Me: rolled 4  now at 54
 
 current turn is 16
 You: rolled 6  now at 19
 Me: rolled 4  landed on chute...moving -7...  now at 51
 
 current turn is 17
 You: rolled 6  now at 25
 Me: rolled 2  moving forward to haven...  now at 62
 
 current turn is 18
 You: rolled 2  landed on ladder...moving 11...  now at 38
 Me: rolled 4  moving backward to haven... now at 50
 
 current turn is 19
 You: rolled 4  moving forward to haven...  now at 69
 Me: rolled 2  now at 52
 
 current turn is 20
 You: rolled 2  landed on ladder...moving 10...  now at 81
 Me: rolled 4  landed on ladder...moving 7...  now at 63
 
 current turn is 21
 You: rolled 6  now at 87
 Me: rolled 5  landed on chute...moving -1...  now at 67
 
 current turn is 22
 You: rolled 2  now at 89
 Me: rolled 1  now at 68
 
 current turn is 23
 You: rolled 5  now at 94
 Me: rolled 6  moving backward to haven... now at 41
 
 current turn is 24
 You: rolled 3  moving backward to haven... now at 94
 Me: rolled 5  landed on ladder...moving 4...  now at 50
 
 current turn is 25
 You: rolled 6  now at 100
 Me: rolled 3  moving forward to haven...  now at 79
 You win!
 */

//text file output
/*
 1-Hk 2H l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -1k nH2l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -Hk n1 l B 2e Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -Hk n1 l B He Flq p 2  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -Hk n*1l B He Flq p * 2hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -Hk1n* l B H- Flq2p *  -ByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -Hk n1 - B H- Flq p2*  -ByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -1k n* - B H- Flq p *  2ByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 1-*- n* - B H- Flq p *  -By2lho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- 1* - B H- Flq p *  -ByHlho2H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n*1- B H- Flq p *  -ByHlho H2B  -r HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B 1- Flq p *  -ByHlho H B  -r2HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B H-1Flq p *  -ByHlho H B  -r HFB2ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B H- Flq - 1  -ByHlho H B  -r HFB ir j 2  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B 1- Flq - *  -ByHlho H B  -r HFB ir j H  F2ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B *- Flq1- *  -ByHlho H B  -r HFB ir j H2 F ku -d  H pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B *- Flq - *  1ByHlho H B  -r HFB ir j H  F ku -d  2 pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B *- Flq - *  -B-Hlho H B  1r HFB ir j 2  F ku -d  * pjB mH x  BF i H  m oB HlHFBhoH BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r HFB ir j * 2F ku -d  * pjB m1 x  BF i H  m oB HlHFBhoH BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r HFB ir j *  F k- -d  *2pjB m* -  BF i H 1m oB HlHFBhoH BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r HFB ir j *  F k- -d  * pjB2-* -  BF i H  m oB 1lHFBhoH BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r HFB ir j *  F k- -d  * pjB 2* -  BF i H  m oB Hl1FBhoH BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r 2FB ir j *  F k- -d  * pjB -* -  BF i H  m oB HlHFBho1 BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r *FB i- j 2  F k- -d  * pjB -* -  BF i H  m oB HlHFBho1 BB
 -*- n* - B *- Flq - *  -B-Hlho H B  -r *FB i- j *  F k- -d  * pjB -* -  BF i 2  m oB HlHFBho* BB
 */


