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

// #include "readaline.h"
#include "LinePackage.h"     
#include "reader.h"             // TODO: check if we need these .h files
#include "cleaner.h"
#include "stringToBytes.h"
#include "writer.h"
#include <seq.h>

// size_t readaline(FILE *inputfd, char **datapp); //TODO :: Remove this

/* TODO: Fix comment formatting */

// TODO: fix function formatting

int main(int argc, char *argv[]) 
{
        // TODO:: Read the file names and open the appropriate file
        // (void) argc; 
        // (void) argv;
        
        // printf("Hello World!\n"); // RESULT: WORKED
        
        FILE *inputFile  = NULL;
        FILE *outputFile = stdout;
        
        char *defaultOutputFileName = "uncorrputed.pgm";
        // TODO :: Put in the error codes for no input file
        if (argc < 2) {
                printf("No input file was given!\n");   /* TODO: Check if this is needed */
                return 0;
        }

        /* open file */
        if (argc < 3) {
                // printf("File given! Opening file...\n");
                inputFile = fopen(argv[1], "r");
                if (inputFile == NULL) {
                        printf("File opening failed! %s\n", argv[1]);   /* TODO: Check if this is meant to be printed */
                        return 0;
                }
                /* else {
                        // printf("File opening success! %s\n", argv[1]);
                } */
        }

        /* read in data */
        Seq_T dirtyData   = reader(inputFile);

        /* clean data */
        Seq_T cleanedData = cleaner(dirtyData);

        /* convert cleaned data to bytes */
        Seq_T rawData     = stringToBytes(cleanedData);

        /* print the raw P5 PGM */
        writer(outputFile, rawData);

        /* free seq memory */
        Seq_free(&dirtyData);
        Seq_free(&cleanedData);
        Seq_free(&rawData);

        // close file
        if (inputFile != NULL) { // This closes the file when we reach the end
                /* printf("Closed the file\n"); */
                fclose(inputFile);
        }
        else {
                printf("No File\n");    /* TODO: Check if this is needed */
        }
        
        // (void) test;
        // (void) datapp;
        // (void) readalineSize;
        (void) defaultOutputFileName;
        (void) outputFile;
}