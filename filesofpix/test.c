// test file

#include <stdio.h>

// #include "readaline.h"
#include "LinePackage.h"     
#include "reader.h"             // TODO: check if we need these .h files
#include <seq.h>
#include <mem.h>
#include "cleaner.h"
#include "readaline.h"
#include "stringToBytes.h"
#include "writer.h"
// size_t readaline(FILE *inputfd, char **datapp); //TODO :: Remove this

// TODO: fix function formatting

void printBytes(char *bytes, size_t size) {
        for (size_t i = 0; i < size; i++) {
                // Replace unseeable characters [that could mess with output if read as char] as a blank space instead
                char displayableCharacter = ' ';
                if (bytes[i] >= 32 && bytes[i] != 127) {
                        displayableCharacter = bytes[i];
                }
                printf("%i(%c) ", (unsigned char)bytes[i], displayableCharacter);
        }
        printf("\n");
}

void freeTestSequence(Seq_T testSequence) {
        printf("Number of lines: %i\n", Seq_length(testSequence));
        while (Seq_length(testSequence) > 0) {
                LinePackage package = Seq_remlo(testSequence);
                size_t size = LinePackage_size(package);

                printf("Line Size: %li\n", size);

                char *bytes = LinePackage_byteList(package);
                
                printBytes(bytes, size);
                
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
// TODO:: readaline is not adding the endline character
void testReadaline(FILE *inputFile) {
        char *datapp;

        size_t size = readaline(inputFile, &datapp);
        printf("size %li \n", size);
        printBytes(datapp, size);
        FREE(datapp);
}

void testReader(FILE *inputFile) {
        Seq_T data = reader(inputFile);
        freeTestSequence(data);
}

void testCleaner(FILE *inputFile) {
        Seq_T dirtyData = reader(inputFile);

        Seq_T cleanedData = cleaner(dirtyData);
        Seq_free(&dirtyData);

        freeTestSequence(cleanedData);
}
// TEST EDGE CASE: 10 IS A NUMBER IN THE FILE
void testStringToBytes(FILE *inputFile) 
{
        Seq_T dirtyData   = reader(inputFile);
        Seq_T cleanedData = cleaner(dirtyData);
        Seq_T rawData     = stringToBytes(cleanedData);

        Seq_free(&dirtyData);
        Seq_free(&cleanedData);

        freeTestSequence(rawData);
}

void testWriter(FILE *inputFile, FILE *outputFile)
{
        Seq_T dirtyData   = reader(inputFile);
        Seq_T cleanedData = cleaner(dirtyData);
        Seq_T rawData     = stringToBytes(cleanedData);
        writer(outputFile, rawData);

        Seq_free(&dirtyData);
        Seq_free(&cleanedData);
        Seq_free(&rawData);

        // freeTestSequence(rawData);
}

void test(FILE *inputFile, FILE *outputFile) 
{
        // testStringToBytes(inputFile);
        // testCleaner(inputFile);
        testReader(inputFile);
        // testLinePackageNew();
        // testReadaline(inputFile);
        // testWriter(inputFile, outputFile);
        (void) inputFile;
        (void) outputFile;
}

int main(int argc, char *argv[]) 
{
        // TODO:: Read the file names and open the appropriate file
        // (void) argc; 
        // (void) argv;
        
        // printf("Hello World!\n"); // RESULT: WORKED
        
        FILE *inputFile  = NULL;
        FILE *outputFile = stdout;        // TODO: Check if we free these pointers
        
        /* char *defaultOutputFileName = "uncorrputed.pgm"; */
        // TODO :: Put in the error codes for no input file
        if (argc < 2) {
                printf("No input file was given!\n");
                return 0;
        }

        /* TODO: write comments for this */
        // printf("File given! Opening file...\n");
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
                printf("File opening failed! %s\n", argv[1]);
                return 0;
        }
        else {
                // printf("File opening success! %s\n", argv[1]);
        }

        if (argc > 2) {
                // printf("File given! Opening %s file...\n", argv[2]);
                outputFile = fopen(argv[2], "w");
        }
        
        test(inputFile, outputFile);

        if (inputFile != NULL) { // This closes the file when we reach the end
                // printf("Closed the file\n");
                fclose(inputFile);
        }
        else {
                printf("No File\n");
        }
        
        if (outputFile != stdout) {
                fclose(outputFile);
        }
        (void) outputFile;
}