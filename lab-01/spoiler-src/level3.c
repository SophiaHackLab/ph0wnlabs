#include <stdio.h>
#include <string.h>

int level3() {
    char key = 0x26;
    char encrypted[] = { 0x52,  0x49, 0x56, 0x79, 0x40, 0x4a, 0x49, 0x49, 0x54 };
    char input[64];

    printf("\nLevel 3 --------------- \n");
    printf("You stand inside the lift to Pico le Croco's luxurious apartment in Monaco.\n");
    printf("The lift's panel glows softly, but there's no indication of which floor you need.\n\n");
    printf("Floor: ");

    scanf("%63s", input);
    printf("\n");

    // XOR the user input with the key to check against the encrypted value
    int correct = 1;
    for (int i = 0; i < strlen(input); i++) {
        if ((input[i] ^ key) != encrypted[i]) {
            correct = 0;
            break;
        }
    }

    if (correct && strlen(input) == sizeof(encrypted)/sizeof(char)) {
        printf("\nThe lift dings softly, and the doors open to reveal a golden floor interior.\n");
        printf("Congratulations, you've completed this level!\n");
	printf("Ph0wn CTF 2026 - March 13-14, 2026 | Visit us at ph0wn.org\n");
	return 1;
    } else {
      printf("The lift closes its doors... and brings you down to the garbage level.\n");
      printf("For sure, that's not where Pico le Croco lives :(\n");
      printf("Looks like you need to figure out the correct floor code to proceed.\n");
      return 0;
    }
}
