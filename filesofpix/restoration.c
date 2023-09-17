/*
 *      restoration.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      The program takes in a corrupted P2 PGM, uncorrupts, and writes an uncorrupted P5 PGM to a given file
 *      TODO: Fix this summary potentially.
 */

#include <stdio.h>

// #include "readaline.h"       /* TODO: Check if we need this */
#include "LinePackage.h"     
#include "reader.h"             // TODO: check if we need these .h files
#include "cleaner.h"
#include "stringToBytes.h"
#include "writer.h"
#include <seq.h>
#include <assert.h>

// TODO: make sure all chars are unsigned chars—This might not be necessary

/* TODO: replace all exit(1) with asserts */

/* TODO: rename linePackage.c and .h to LinePackage.c */

/* TODO: check that makefile is all good and proper */

int main(int argc, char *argv[]) 
{
        assert(argc <= 2);

        FILE *inputFile  = stdin;
        FILE *outputFile = stdout;
        
        /* open file */
        if (argc == 2) {         
                inputFile = fopen(argv[1], "r");
                assert(inputFile != NULL);
        }

        /* read in data */
        Seq_T dirtyData   = reader(inputFile);

        /* clean data */
        Seq_T cleanedData = cleaner(dirtyData);

        /* convert cleaned data to bytes */
        Seq_T rawData     = stringToBytes(cleanedData);

        /* output the raw P5 PGM */
        writer(outputFile, rawData);

        /* free seq memory */
        Seq_free(&dirtyData);
        Seq_free(&cleanedData);
        Seq_free(&rawData);

        /* close file */
        if (inputFile != NULL) { /* This closes the file when we reach the 
                                    end */
                fclose(inputFile);
        }

        exit(EXIT_SUCCESS);
}