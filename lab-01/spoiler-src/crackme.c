#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"

// First level function
int level_one() {
    char password[64];
    const char* secret = "ph0wn2026";

    printf("Level 1 --------------- \n");
    printf("You are standing in front of a sleek interphone panel in the heart of Monaco.\n");
    printf("The building is luxurious, the ocean breeze is gentle, and the sounds of the city hum in the background.\n");
    printf("A golden plaque reads: 'Pico le Croco - The Hacking Star'\n");
    printf("The interphone waits for the correct apartment tag, e.g 'Sweet Home'\n");
    printf("Apartment tag: ");

    scanf("%s", password);

    if (strcmp(password, secret) == 0) {
      //      printf("Ph0wn CTF 2026 - March 13-14, 2026 | Visit us at ph0wn.org\n");
        printf("Correct! Welcome to the next level.\n");
	return 1;
    } else {
        printf("Incorrect password. Try again!\n");
	return 0;
    }
}

// Second level function
int level_two() {
  int ret = 0;
    char password[64];
    const char* secret_base64 = "c3RhcnBvcnQ=";  // Base64 for 'starport' (related to yacht ports and stars)
    
    printf("You arrive at the entrance to a luxurious yacht in Monaco.\n");
    printf("A doorman steps forward, wearing a sharp suit. He gestures towards you with an air of exclusivity.\n");
    printf("\"Good evening,\" he says. \"I assume you're here to meet the star of the night: Pico le Croco.\"\n");
    printf("The doorman takes a glance at you, expecting a sign of your importance.\n");
    printf("Give him your business card. Pay attention to the words on your card...\n");
    printf("Business card: ");

    scanf("%s", password);
    
    char* decoded = base64_decode(secret_base64);

    if (strcmp(password, decoded) == 0) {
      printf("The doorman nods approvingly.\n");
      printf("You've completed this level, and you’re one step closer to greatness.\n");
      ret = 1;
    } else {
      printf("The doorman examines your business card. He looks disappointed.\n");
      printf("I'm afraid Pico is not available. Try again later\n");
    }

    free(decoded);
    return ret;
}

int level_three() {
  return 0;
}

int main() {
    // Welcome message
    printf("Welcome to Ph0wn Labs!\n");
    printf(" ____  _      ___                   _          _ \n");
    printf("|  _ \| |__  / _ \__      ___ __   | |    __ _| |__  ___ \n");
    printf("| |_) | '_ \| | | \ \ /\ / / '_ \  | |   / _` | '_ \/ __|\n");
    printf("|  __/| | | | |_| |\ V  V /| | | | | |__| (_| | |_) \__	\ \n");
    printf("|_|   |_| |_|\___/  \_/\_/ |_| |_| |_____\__,_|_.__/|___/ \n");
    printf("\n");

    printf("You will face Pico le Croco - the hacking star from Monaco!\n\n");
    
    // Start the levels
    if (level_one()) {
      if (level_two()) {
	level_three();
      }
    }

    return 0;
}
