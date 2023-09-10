/*
 *      readaline.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      Header file for readaline
 *      
 */

#include <stdio.h>
#include <seq.h>

#include "readaline.h"



size_t readaline(FILE *inputfd, char **datapp) {
    // (void) inputfd;
        (void) datapp;

        Seq_T buffer = Seq_new(1000);
        int currentByte = fgetc(inputfd); // Get the first character
        
        int endLineCharacter = '\n'; // POSSIBLE TODO:: Change \n to 10 (ASCII Code for new line)

        // While we haven't reached the end of file and the character is not at the end of line
        while (feof(inputfd) == 0 && currentByte != endLineCharacter) {

                // If there is some error, break the loop
                if (ferror(inputfd) != 0) {
                        break;
                }
                Seq_addhi(buffer, &currentByte);
                currentByte = fgetc(inputfd); // Go to the next character
        }
        if (currentByte == endLineCharacter) {
                Seq_addhi(buffer, &currentByte);
        }

        printf("Made it to here\n");
        // TODO:: Check through the sequence; remove in real 
        while (Seq_length(buffer) > 0) {
                char *byte = Seq_remlo(buffer);
                printf("%i ", *byte);
        }

        printf("\n");
        
    return 0;
}