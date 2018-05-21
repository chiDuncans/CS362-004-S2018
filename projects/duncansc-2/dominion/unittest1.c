/***********************************************
 * File Name: unittest1.c
 * File Created Date: 2018-04-22
 * Last Updated: 2018-04-25
 * CS362-004-S2018
 * Assignment 3
 * Author: Chieko Duncans (duncansc@oregonstate.edu)
 * File Description: unit test 1 program for getCost test
 * ********************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int getCostTest(int cardNum){
  int ret; // return value of int getCost(int cardNumber)
  int costList[] = {
    0, // 0:curse
    2, // 1:estate
    5, // 2:duchy
    8, // 3:province
    0, // 4:copper
    3, // 5:silver
    6, // 6:gold
    6, // 7:adventurer
    5, // 8:council_room
    4, // 9:feast
    4, // 10:garden
    5, // 11:mine
    4, // 12:remodel
    4, // 13:smithy
    3, // 14:village
    4, // 15:baron
    3, // 16:great_hall
    5, // 17:minion
    3, // 18:steward
    5, // 19:tribute
    3, // 20:abnassador
    4, // 21:cutpurse
    2, // 22:embargo
    5, // 23:outpost
    4, // 24:salvager
    4, // 25:sea_hag
    4  // 26:treasure_map
    };

    ret = getCost(cardNum);
    if(cardNum < 0 || cardNum > 26){
      assert(ret == -1); // check return value is -1 or not
    }
    else{  
      assert(ret == costList[cardNum]); // check return value is 0 or above, compare
    }
}

int main (int argc, char** argv) {

  int i; // loop counter
 
  printf ("-------- Card numbers are 0 - 26 \n");
  

  printf ("-------- Test 1: card number 0 - 26 \n");
  for(i=0; i < 27; i++){
    getCostTest(i);
  }

  printf ("-------- PASSED on all InRange card getCost test \n");
    
  printf ("-------- Test 2: card number -1 \n");
  getCostTest(-1);

  printf ("-------- PASSED Test 2 on out ranged card number: -1 \n");
 
  printf ("-------- Test 3: card number 27 \n");
  getCostTest(27);

  printf ("-------- PASSED Test 3 on out ranged card number, 27\n");
  return 0;
}
