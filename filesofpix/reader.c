/*
 *      reader.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for reader.c
 *      
 */

// TODO: write function descriptions

#include <seq.h>
#include <stdio.h>     // TODO: Check if include reader.h file
#include <stdlib.h>
#include <mem.h>
#include "LinePackage.h"
#include "readaline.h"

/* TODO: Check if reader needs a function contract to fulfil style guide */
/**********reader********
 *
 * Reads the contents of a given file
 * Inputs:
 *              FILE *inputFile: pointer to file to read from
 * Return: Hanson Sequence of LinePackage structs that represents a line
 * Expects
 *      inputFile to be opened
 * Notes:
 *      TODO: Finish summary
 ************************/
Seq_T reader(FILE *inputFile)
{
        if (inputFile == NULL) {
                exit(1);        // TODO: Check if this exits with a checked runtime error
        }

        char **datapp = ALLOC(sizeof(char*));
        printf("ALLOC'd datapp at %p\n", (void*) datapp);
        /* TODO: delete the printf statements */

        size_t size = readaline(inputFile, datapp);

        Seq_T lines = Seq_new(1);

        // TODO: Check if we can use do while loops
        while (size != 0) {
                LinePackage tempLine = LinePackage_new(*datapp, size);

                Seq_addhi(lines, tempLine);
                size = readaline(inputFile, datapp);
        }

        // Deallocate datapp memory;
        printf("FREE'd datapp at %p\n", (void*) datapp);
        FREE(datapp);

        return lines;
}