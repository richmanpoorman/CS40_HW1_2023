/*
 *      restoration.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      The program takes in a corrupted P2 PGM, uncorrupts the data, and writes
 *      an uncorrupted P5 PGM to stdout
 *      TODO: Fix this summary potentially.
 */

#include <stdio.h>

#include "LinePackage.h"     
#include "reader.h"
#include "cleaner.h"
#include "stringToBytes.h"
#include "writer.h"
#include <seq.h>
#include <assert.h>

/* TODO: rename linePackage.c and .h to LinePackage.c */

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