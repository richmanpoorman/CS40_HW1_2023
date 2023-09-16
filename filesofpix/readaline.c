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
#include "mem.h"

#include "readaline.h"



size_t readaline(FILE *inputfd, char **datapp) 
{
        if (inputfd == NULL || datapp == NULL) {
                exit(1);        // TODO: Check if this exits with a checked runtime error
        }

        if (feof(inputfd) != 0) {
                *datapp = NULL;
                return 0;
        } 

        char *buffer = ALLOC(1000);
        
        if (buffer == NULL) {   // TODO: Do they want a try catch for this?
                exit(1);        // TODO: Check if this exits with a checked runtime error
        }

        int currentByte = fgetc(inputfd); // Get the first character
        /* TODO: potentially write an error thrower if it reads a character it doesn't know */
        
        int endLineCharacter = '\n'; // POSSIBLE TODO:: Change \n to 10 (ASCII Code for new line)

        // While we haven't reached the end of file and the character is not at the end of line
        size_t i = 0;
        while (feof(inputfd) == 0 && currentByte != endLineCharacter) {
                if (i >= 1000) {
                        fprintf(stderr, "readaline: input line too long\n");
                        exit(4);
                }
                // If there is some error, break the loop
                if (ferror(inputfd) != 0) {
                        exit(1);        // TODO: Check that this throws a Checked Runtime Error
                        // break;
                }
                // Seq_addhi(buffer, &currentByte);
                // printf("%i\n", currentByte);
                buffer[i] = (char)currentByte;

                currentByte = fgetc(inputfd); // Go to the next character
                i++;
                
        }

        // TODO: write a comment explaining what this if statement does
        if (currentByte == endLineCharacter) {
                if (i >= 1000) {
                        fprintf(stderr, "readaline: input line too long\n");
                        exit(4);
                }
                
                buffer[i] = endLineCharacter;
                i++;
                
        }

        *datapp = buffer;
        
        return i;
}

// TODO: fix the error throwers