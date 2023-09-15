/*
 *      writer.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for writer.c
 *      
 */

#include <stdio.h>
#include <seq.h>
#include "LinePackage.h"

/* TODO: Write function contracts */
/* POTENTIAL TODO: add parameter to writer that is what the maxVal is */
void writer(FILE *outputFile, Seq_T rawLines) 
{
        /* create header */
        /* Second newline character to skip comment line */
        fprintf(outputFile, "P5\n\n");  /* TODO: Check if we print anything in the comment line */

        /* determine width and height */
        size_t width, height;   /* TODO: Check if this is proper style */
        width = LinePackage_size(Seq_get(rawLines, 0));    /* -1 for \n */
        height = Seq_length(rawLines);

        /* print width and height */
        fprintf(outputFile, "%li %li\n", width, height);

        /* print maxVal value */
        fprintf(outputFile, "255\n");

        /* print every line */
        while (Seq_length(rawLines) > 0) {
                LinePackage line = Seq_remlo(rawLines);
                size_t size = LinePackage_size(line);
                char *byteList = LinePackage_byteList(line);

                /* print each char in byteList */
                /* TODO: check if there is a different var than i for size_t */
                for (size_t i = 0; i < size; i++) {
                        fprintf(outputFile, "%c", byteList[i]);
                }

                LinePackage_free(line);
        }

        // (void) outputFile;
        // (void) rawLines;
}