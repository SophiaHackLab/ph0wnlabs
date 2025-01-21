#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 8  // Each line corresponds to one byte (8 bits)
#define MAX_STRING 64

// Function to convert a string of '#' and ' ' to an integer
unsigned char convert_to_integer(const char *input) {
    unsigned char result = 0;
    for (int i = 0; i < 8; i++) {
        result |= (input[i] == '#') << (7 - i);  // Set the bit if the character is '#'
    }
    return result;
}


// Function to process the QR code file and decode it
char *process_file(const char *filename) {
  char *decoded_string;
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Error: Unable to open the QR code file %s\n", filename);
    return NULL;
  }

  char line[LINE_LENGTH + 1];  // Store each line of the QR code (8 characters + null terminator)
  int index = 0;
  decoded_string = (char *)calloc(MAX_STRING, sizeof(char));
  if (decoded_string == NULL) {
    fclose(file);
    perror("malloc issue");
    return NULL;
  }
  
  while (fgets(line, sizeof(line), file) && index < MAX_STRING-1 ) {
    // Remove trailing newline, if any
    line[strcspn(line, "\n")] = '\0';
    // Skip empty lines
    if (strlen(line) == 0) {
      continue;
    }

    if (strlen(line) != LINE_LENGTH) {
      printf("Error: invalid QR code line length\n");
      fclose(file);
      free(decoded_string);
      return NULL;
    }

    // Decode the binary string to an ASCII character
    char decoded_char = convert_to_integer(line);
    decoded_string[index] = decoded_char;
    index++;
  }

  fclose(file);
  return decoded_string;
}


int level4() {
  char filename[40];
  printf("\nLevel 4 --------------- \n");
  printf("You are on the golden penthouse floor and at the end of the corridor\n");
  printf("you stand before the video doorbell to his exclusive apartment.\n");
  printf("The only way to access Pico's lair is by using the correct QR code, one that will hack his high-tech security system.\n");
  printf("If you want to meet Pico, enter the filename of the QR code image that will allow you to bypass the doorbell...\n");

  // Ask the user to supply the filename of the QR code
  printf("Enter the filename of the QR code (e.g., qr_code.txt)\n");
  printf("Filename: ");
  scanf("%39s", filename);
  printf("\n");

  // Call the level4 function to process the QR code file
  char * decoded = process_file(filename);
  int ret = 0;
  if (decoded != NULL && strcmp(decoded, "p1coEl1te") == 0) {
    printf("Congratulations!\n");
    printf("The door opens, and Pico le Croco is standing in front of you\n");
    printf("with his charming smile. He says: \n");
    printf("'Hi! Come in! It's so nice to meet new hackers!\n");
    printf("\n");
    printf("How about some CTF now? Head to https://ph0wn.shl.contact\n");
    printf("Enjoy the rest of Ph0wn Labs!\n");
    printf("Ph0wn CTF 2026 - March 13-14, 2026 | Visit us at ph0wn.org\n");
    printf("======================== END =============================\n");
    ret = 1;
  } else {
    printf("%s\n", decoded);
    printf("Oops, that's not correct...\n");
  }

  return ret;
}
