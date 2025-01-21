#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "base64.h"

char *base64_decode(const char *input) {
    char command[256];
    FILE *pipe;
    char *output = NULL;
    size_t output_size = 0;

    // Prepare the command to decode base64
    snprintf(command, sizeof(command), "echo %s | base64 -d", input);

    // Open a pipe to the command
    pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run base64 -d command.\n");
        return NULL;
    }

    // Allocate initial memory for the output
    size_t buffer_size = 128; // Start with a reasonable buffer size
    output = malloc(buffer_size);
    if (!output) {
        fprintf(stderr, "Memory allocation failed.\n");
        pclose(pipe);
        exit(EXIT_FAILURE);
    }

    // Read the decoded output from the pipe
    size_t len = 0;
    while (fgets(output + len, buffer_size - len, pipe) != NULL) {
        len += strlen(output + len);
        // If the buffer is full, reallocate more space
        if (len >= buffer_size - 1) {
            buffer_size *= 2;
            char *new_output = realloc(output, buffer_size);
            if (!new_output) {
                fprintf(stderr, "Memory reallocation failed.\n");
                free(output);
                pclose(pipe);
                exit(EXIT_FAILURE);
            }
            output = new_output;
        }
    }

    // Close the pipe
    pclose(pipe);

    // Null-terminate the output
    output[len] = '\0';

    return output;
}
