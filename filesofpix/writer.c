/*
 *      writer.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Writes byte data to given output file.
 *      
 */

#include <stdio.h>
#include <seq.h>
#include <stddef.h>
#include "LinePackage.h"
#include "writer.h"


/**********writer********
 *
 * Writes data to given output file
 * Inputs:
 *      FILE *outputFile: pointer to output file
 *      Seq_T rawlines: the raw P5 PGM lines to output in the correct format
 * Return: nothing
 * Expects
 *      *outputFile to be nonnull
 *      rawLines to be uncorrupted P5 PGM lines
 * Notes:
 *      writer automatically generates and writes the P5 PGM header
 *
 ************************/
void writer(FILE *outputFile, Seq_T rawLines);

void writer(FILE *outputFile, Seq_T rawLines) 
{
        /* create header */
        /* Second newline character to skip comment line */
        fprintf(outputFile, "P5\n\n"); 

        /* determine width and height */
        size_t width, height;
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
                for (size_t i = 0; i < size; i++) {
                        fprintf(outputFile, "%c", byteList[i]);
                }

                LinePackage_free(line);
        }

}