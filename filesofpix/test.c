// test file

#include <stdio.h>

// #include "readaline.h"
#include "LinePackage.h"     
#include "reader.h"             // TODO: check if we need these .h files
#include <seq.h>
#include <mem.h>
#include "cleaner.h"
#include "readaline.h"

// size_t readaline(FILE *inputfd, char **datapp); //TODO :: Remove this

// TODO: fix function formatting

void freeTestSequence(Seq_T testSequence) {
        while (Seq_length(testSequence) > 0) {
                LinePackage package = Seq_remlo(testSequence);
                size_t size = LinePackage_size(package);
                char *bytes = LinePackage_byteList(package);
                for (size_t i = 0; i < size; i++) {
                        printf("%i ", bytes[i]);
                }
                printf("\n");
                LinePackage_free(package);
        }
        Seq_free(&testSequence);
}

void testLinePackageNew() {
        char *testString = ALLOC(3);
        testString[0] = 'a';
        testString[1] = 'b';
        testString[2] = 'c';
        Seq_T test = Seq_new(1);
        LinePackage package = LinePackage_new(testString, 3);
        
        Seq_addhi(test, package);
        
        freeTestSequence(test);
        
}

void testReadaline(FILE *inputFile) {
        char *datapp;

        size_t size = readaline(inputFile, &datapp);
        printf("size %li \n", size);
        for (size_t i = 0; i < size; i++) {
                printf("%c", datapp[i]);
        }
        printf("\n");
        FREE(datapp);
}

void testReader(FILE *inputFile) {
        Seq_T data = reader(inputFile);
        freeTestSequence(data);
}

void test(FILE *inputFile) 
{
        testReader(inputFile);
        // testLinePackageNew();
        // testReadaline(inputFile);
        (void) inputFile;
}

int main(int argc, char *argv[]) 
{
        // TODO:: Read the file names and open the appropriate file
        // (void) argc; 
        // (void) argv;
        
        // printf("Hello World!\n"); // RESULT: WORKED
        
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