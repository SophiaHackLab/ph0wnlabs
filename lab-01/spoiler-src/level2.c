#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"

// Second level function
int level2() {
  int ret = 0;
    char password[32];
    const char* secret_base64 = "c3RhcnBvcnQ=";  // Base64 for 'starport' (related to yacht ports and stars)

    printf("Level 2 --------------- \n");
    printf("You arrive at the entrance to a luxurious yacht in Monaco.\n");
    printf("A doorman steps forward, wearing a sharp suit. He gestures towards you with an air of exclusivity.\n");
    printf("\"Good evening,\" he says. \"I assume you're here to meet the star of the night: Pico le Croco.\"\n");
    printf("The doorman takes a glance at you, expecting a sign of your importance.\n");
    printf("Give him your business card. Pay attention to the words on your card...\n");
    printf("Business card: ");

    scanf("%31s", password);

    char *decoded = base64_decode(secret_base64);
    if (decoded == NULL) { perror("malloc error?"); }

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
