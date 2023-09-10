/*
 *      readaline.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for readaline.c
 *      
 */

#include <stdio.h>
#include <stdlib.h>
// #include <seq.h>
#include "mem.h"

#include "readaline.h"



size_t readaline(FILE *inputfd, char **datapp) {
        // (void) inputfd;

        char *buffer = ALLOC(1000);
        int currentByte = fgetc(inputfd); // Get the first character
        
        int endLineCharacter = '\n'; // POSSIBLE TODO:: Change \n to 10 (ASCII Code for new line)

        // While we haven't reached the end of file and the character is not at the end of line
        int i = 0;
        while (feof(inputfd) == 0 && currentByte != endLineCharacter) {
                if (i >= 1000) {
                        fprintf(stderr, "readaline: input line too long\n");
                        exit(4);
                }
                // If there is some error, break the loop
                if (ferror(inputfd) != 0) {
                        break;
                }
                // Seq_addhi(buffer, &currentByte);
                // printf("%i\n", currentByte);
                buffer[i] = (char)currentByte;

                currentByte = fgetc(inputfd); // Go to the next character
                i++;
                
        }

        // TODO: write a comment explaining what this if statement does
        if (currentByte == endLineCharacter) {
                buffer[i] = (char)currentByte;
        }

        // printf("Made it to here\n");
        // // TODO:: Check through the sequence; remove in real 
        // for (int j = 0; j < i; j++) {
        //         printf("%i ", buffer[j]);
        // }

        // printf("\n");
        *datapp = buffer;
        
        return i;
}