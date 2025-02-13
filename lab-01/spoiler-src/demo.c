#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_quizz() {
 const char *questions[] = {
   "How can you base64 decode this string: UGljbyBpcyBhIHNtYXJ0IGNyb2NvZGlsZQ==?",
   "How to list files in the current directory from within r2 prompt?",
   "How to list all functions, excepted imports?",
   "How can you rename a function?",
   "How do you view the hexdump of the binary at a specific address?",
   "What command finds ROP gadgets in the binary?",
   "How do you debug a binary and break at the main function?"
 };

 const char *answers[][3] = {
   {"b64: UGljbyB...", "p6ds UGljbyB...", "!base64 -d UGljbyB..." }, /* "p6ds */
   {"!ls", "Ctrl-Z ls", "exec ls" }, /* !ls */
   {"afli", "afl-sym.imp", "afl~!sym.imp" }, /* afl~!sym.imp */
   {"afl/old_name/new_name", "afn new_name", "rename new_name" }, /* afn new_name */
   {"pd @ addr", "px @ addr", "iz"}, /* px @ addr */
   {"/R", "/rop", "/R | grep gadget"}, /* /R */
   {"oo+; s main", "ood; db main; dc", "/ main ; break; run"} /* ood; db main; dc */
 };

 const int correct_answers[] = {2, 1, 3, 2, 2, 1, 2};  // Indices of the correct answers (1-based)
 const int num_questions = sizeof(correct_answers) / sizeof(correct_answers[0]);

 int user_answer;
 int score = 0;

 printf("\nWelcome to the Quizz!\n");

 // Loop through all questions
 for (int i = 0; i < num_questions; i++) {
   printf("\nQuestion %d: %s\n", i + 1, questions[i]);
   for (int j = 0; j < 3; j++) {
     printf("%d. %s\n", j + 1, answers[i][j]);
   }

   printf("Your answer: ");
   if (scanf("%1d", &user_answer) != 1) {
     printf("Invalid input. Please enter a number.\n");
     // Clear input buffer
     while (getchar() != '\n');
     continue;
   }
   
   if (user_answer == correct_answers[i]) {
     printf("Correct!\n");
     score++;
   } else {
     printf("Wrong! The correct answer was: %s\n", answers[i][correct_answers[i] - 1]);
   }
 }

 printf("\nQuizz finished! Your score: %d/%d\n", score, num_questions);
}

void show_easter_egg() {
    printf("\n--- Easter Egg ---\n");
    printf("Congratulations! You found the hidden menu!\n");
    printf("Here's a fun fact: Did you know that the Eiffel Tower can be 15 cm taller during the summer?\n");
    printf("-------------------\n");
}

int main() {
    printf("Ph0wn Labs 01 - Radare2 Tutorial\n");
    int choice;

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Radare2 Quizz\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        if (scanf("%3d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                show_quizz();
                break;
            case 2:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
                break;
            case 99:
                show_easter_egg();
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

