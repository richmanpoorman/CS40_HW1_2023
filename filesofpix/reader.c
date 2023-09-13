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

Seq_T reader(FILE *inputFile)
{
        if (inputFile == NULL) {
                exit(1);        // TODO: Check if this exits with a checked runtime error
        }

        char **datapp = ALLOC(sizeof(char*));
        // printf("ALLOC'd datapp at %p\n", (void*) datapp);

        size_t size = readaline(inputFile, datapp);

        Seq_T lines = Seq_new(1);

        // TODO: Check if we can use do while loops
        while (size != 0) {
                LinePackage tempLine = LinePackage_new(*datapp, size);

                Seq_addhi(lines, tempLine);
                size = readaline(inputFile, datapp);
        }

        // Deallocate datapp memory;
        // printf("FREE'd datapp at %p\n", (void*) datapp);
        FREE(datapp);   // TODO: Check why this stops leak
        // FREE(lines);

        return lines;
}