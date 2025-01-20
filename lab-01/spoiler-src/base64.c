#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"

// Base64 decoding table
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function to decode a base64 string
char* base64_decode(const char* input) {
    int len = strlen(input);
    int padding = 0;
    
    if (input[len - 1] == '=')
        padding++;
    if (input[len - 2] == '=')
        padding++;
    
    int decoded_len = (len * 3) / 4 - padding;
    char* decoded = (char*)malloc(decoded_len + 1);
    
    int i = 0, j = 0;
    unsigned char temp[4];
    while (len--) {
        if (*input == '=')
            break;
        temp[i++] = *input++;
        if (i == 4) {
            decoded[j++] = (temp[0] << 2) | (temp[1] >> 4);
            decoded[j++] = (temp[1] << 4) | (temp[2] >> 2);
            decoded[j++] = (temp[2] << 6) | temp[3];
            i = 0;
        }
    }
    if (i) {
        for (int k = i; k < 4; k++)
            temp[k] = 0;
        decoded[j++] = (temp[0] << 2) | (temp[1] >> 4);
        if (i > 2)
            decoded[j++] = (temp[1] << 4) | (temp[2] >> 2);
    }
    decoded[j] = '\0';
    return decoded;
}
