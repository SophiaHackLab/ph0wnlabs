#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "levels.h"

int main() {
    // Welcome message
    printf("Welcome to Ph0wn Labs!\n");
    printf(" ____  _      ___                   _          _ \n");
    printf("|  _ \\| |__  / _ \\__      ___ __   | |    __ _| |__  ___ \n");
    printf("| |_) | '_ \\| | | \\ \\ /\\ / / '_ \\  | |   / _` | '_ \\/ __|\n");
    printf("|  __/| | | | |_| |\\ V  V /| | | | | |__| (_| | |_) \\__\\ \n");
    printf("|_|   |_| |_|\\___/  \\_/\\_/ |_| |_| |_____\\__,_|_.__/|___/ \n");
    printf("\n");

    printf("You will face Pico le Croco - the hacking star from Monaco!\n\n");
    
    // Start the levels
    if (level1()) {
      if (level2()) {
	level3();
      }
    }

    return 0;
}
