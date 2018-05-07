/******************************************
 * File Name: testme.c
 * CS362_S2019: Random_Testing_Quiz Assignment
 * Modified by Chieko Duncans (duncansc)
 * Last Updated on 2018-05-04
 * Requirement: Need to find error within 5 minutes
 * ***************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
/*  try 1
char inputChar()
{
    // TODO: rewrite this function
    int randInt;
    char testC;
    
    randInt = (rand() % (126 - 32)) + 32;
    testC = randInt;
    return testC;
}
*/
// try2
char inputChar()
{
    // TODO: rewrite this function
    int randInt;
    char testC;
    char listC[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};    

    return listC[rand() % 9 ];
}

char *inputString()
{
    // TODO: rewrite this function
    int randInt;
    char randC;
    static char randString[6];
    char* testString;
    int i; // iterator
 
 // try 4 : all lower case alphabet test -- 7minutes +
 //  char* alphabetLow = "abcdefghijklmnopqrstuvwxyz";
   char* resetLow = "rest";

    for(i=0; i<5; i++){
       // randInt = (rand() % (126 - 32)) + 32;
       // randC = randInt;
       // randString[i] = randC;
       // try 4
       // randString[i] = alphabetLow[rand() % 26];
        randString[i] = resetLow[rand() % 4];
    }
    
    randString[5] = '\0';

    return randString;
  // try3: changed to "reset" to return all the time
  // return "reset";
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
//  while (tcCount < 100)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    //srand(time(NULL));
    srand(100);
    testme();
    return 0;
}
