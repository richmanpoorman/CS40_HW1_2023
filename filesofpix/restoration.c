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
#include <seq.h>

// size_t readaline(FILE *inputfd, char **datapp); //TODO :: Remove this

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
        
        // char *datapp;
        
        // size_t readalineSize = readaline(inputFile, &datapp);

        // testing
        // printf("Made it to here\n");
        // // TODO:: Check through the sequence; remove in real 
        // for (size_t j = 0; j < readalineSize; j++) {
        //         printf("%i ", datapp[j]);
        // }

        // test that reader works
        Seq_T testReader = reader(inputFile);
        printf("testing reader\n");
        while (Seq_length(testReader) > 0) {
                LinePackage testPackage = Seq_remlo(testReader);
                for (size_t i = 0; i < LinePackage_size(testPackage); i++) {
                        printf("%i ", LinePackage_byteList(testPackage)[i]);
                }
                printf("\n");
        }

        if (inputFile != NULL) { // This closes the file when we reach the end
                printf("Closed the file\n");
                fclose(inputFile);
        }
        else {
                printf("No File\n");
        }

        // // tests
        // printf("running tests!\n");
        // char *ptr = "abc";
        // LinePackage test = LinePackage_new(ptr, 3);
        // size_t testLength = LinePackage_size(test);
        // printf("testLength is %li\n", testLength);
        // char *testByteList = LinePackage_byteList(test);
        // for (size_t i = 0; i < testLength; i++) {
        //         printf("%c", testByteList[i]);
        // }
        // printf("\n");

        // LinePackage_set_size(test, 2);
        // testLength = LinePackage_size(test);
        // printf("testLength is %li\n", testLength);
        // testByteList = LinePackage_byteList(test);
        // for (size_t i = 0; i < testLength; i++) {
        //         printf("%c", testByteList[i]);
        // }
        // printf("\n");

        // LinePackage_free(test);
        
        // (void) test;
        // (void) datapp;
        // (void) readalineSize;
        (void) defaultOutputFileName;
        (void) outputFile;
}