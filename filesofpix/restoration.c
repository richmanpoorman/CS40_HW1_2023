/*
 *      restoration.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      The program takes in a corrupted P2 PGM, uncorrupts, and writes uncorrupted P5 PGM to a given file
 */

#include <stdio.h>

#include "readaline.h"

size_t readaline(FILE *inputfd, char **datapp); //TODO :: Remove this

int main(int argc, char *argv[]) {
        // TODO:: Read the file names and open the appropriate file
        // (void) argc; 
        // (void) argv;
        
        printf("Hello World!\n"); // RESULT: WORKED
        
        FILE *inputFile  = NULL;
        FILE *outputFile = NULL;
        
        char *defaultOutputFileName = "uncorrputed.pgm";
        // TODO :: Put in the error codes for no input file
        if (argc < 2) {
                printf("No input file was given!\n");
                return 0;
        }

        if (argc < 3) {
                printf("File given! Opening file...\n");
                inputFile = fopen(argv[1], "r");
                if (inputFile == NULL) {
                        printf("File opening failed! %s\n", argv[1]);
                        return 0;
                }
                else {
                        printf("File opening success! %s\n", argv[1]);
                }
        }
        
        // (void) inputFile;
        
        char **datapp = NULL;
        
        size_t readalineSize = readaline(inputFile, datapp);

        printf("Made it to here\n");
        // TODO:: Check through the sequence; remove in real 
        for (size_t j = 0; j < readalineSize; j++) {
                printf("%i ", *datapp[j]);
        }

        if (inputFile != NULL) { // This closes the file when we reach the end
                printf("Closed the file\n");
                fclose(inputFile);
        }
        else {
                printf("No File\n");
        }
        
        (void) datapp;
        (void) readalineSize;
        (void) defaultOutputFileName;
        (void) outputFile;
}