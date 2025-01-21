#include <stdio.h>
#include <string.h>

// First level function
int level1() {
    char password[20];
    const char* secret = "ph0wn2026";

    printf("Level 1 --------------- \n");
    printf("You are standing in front of a sleek interphone panel in the heart of Monaco.\n");
    printf("The building is luxurious, the ocean breeze is gentle, and the sounds of the city hum in the background.\n");
    printf("A golden plaque reads: 'Pico le Croco - The Hacking Star'\n");
    printf("The interphone waits for the correct apartment tag, e.g 'Sweet Home'\n");
    printf("Apartment tag: ");

    scanf("%19s", password);

    if (strcmp(password, secret) == 0) {
        printf("Correct! Welcome to the next level.\n");
	return 1;
    } else {
        printf("Incorrect password. Try again!\n");
	return 0;
    }
}

