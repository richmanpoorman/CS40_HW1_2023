// test file

#include <stdio.h>

// #include "readaline.h"
#include "LinePackage.h"     
#include "reader.h"             // TODO: check if we need these .h files
#include <seq.h>
#include <mem.h>
#include "cleaner.h"

// size_t readaline(FILE *inputfd, char **datapp); //TODO :: Remove this

// TODO: fix function formatting

void test(FILE *inputFile) 
{
        // testing
        // printf("Made it to here\n");
        // // TODO:: Check through the sequence; remove in real 
        // for (size_t j = 0; j < readalineSize; j++) {
        //         printf("%i ", datapp[j]);
        // }

        // // TODO: This test is giving weird leaks—bad test???
        // // test that reader works
        // Seq_T testReader = reader(inputFile);
        // printf("testing reader\n");
        // while (Seq_length(testReader) > 0) {
        //         LinePackage testPackage = Seq_remlo(testReader);
        //         for (size_t i = 0; i < LinePackage_size(testPackage); i++) {
        //                 printf("%i ", LinePackage_byteList(testPackage)[i]);
        //         }
        //         printf("\n");
        //         LinePackage_free(testPackage);
        // }

        // (void) testReader;

        // // tests
        // printf("running tests!\n");
        // char *str = ALLOC(3);
        // str[0] = 'a';
        // str[1] = 'b';
        // str[2] = 'c';
        // // char *ptr = "abc";
        // LinePackage test = LinePackage_new(str, 3);
        // size_t testLength = LinePackage_size(test);
        // printf("testLength is %li\n", testLength);
        // char *testByteList = LinePackage_byteList(test);
        // for (size_t i = 0; i < testLength; i++) {
        //         printf("%c", testByteList[i]);
        // }
        // printf("\n");

        // printf("%c\n", str[1]);

        // str[1] = 'x';

        // LinePackage_set_size(test, 2);
        // testLength = LinePackage_size(test);
        // printf("testLength is %li\n", testLength);
        // testByteList = LinePackage_byteList(test);
        // for (size_t i = 0; i < testLength; i++) {
        //         printf("%c", testByteList[i]);
        // }
        // printf("\n");

        // LinePackage_free(test);

        // TODO: this test is likely a bad test with bad code
        // // test cleaner
        // Seq_T testReader = reader(inputFile);
        // Seq_T testCleaner = cleaner(testReader);
        // while (Seq_length(testCleaner) > 0) {
        //         LinePackage testPackage = Seq_remlo(testCleaner);
        //         for (size_t i = 0; i < LinePackage_size(testPackage); i++) {
        //                 printf("%c ", LinePackage_byteList(testPackage)[i]);
        //         }
        //         printf("\n");
        //         LinePackage_free(testPackage);
        // }

        (void) inputFile;
}

int main(int argc, char *argv[]) 
{
        // TODO:: Read the file names and open the appropriate file
        // (void) argc; 
        // (void) argv;
        
        printf("Hello World!\n"); // RESULT: WORKED
        
        FILE *inputFile  = NULL;
        FILE *outputFile = NULL;        // TODO: Check if we free these pointers
        
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
        
        test(inputFile);

        if (inputFile != NULL) { // This closes the file when we reach the end
                printf("Closed the file\n");
                fclose(inputFile);
        }
        else {
                printf("No File\n");
        }
        
        // (void) test;
        // (void) datapp;
        // (void) readalineSize;
        (void) defaultOutputFileName;
        (void) outputFile;
}