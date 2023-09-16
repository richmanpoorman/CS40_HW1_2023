/*
 *      readaline.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for readaline.c
 *      
 */

#include <stdio.h>
#include <stdlib.h>

#include <mem.h>
#include <assert.h>

#include "readaline.h"

/* TODO: Finish this contract description */
/**********resizeReadLine********
 *
 * Resizes the data buffer size
 * Inputs:
 *	char **data: pointer to buffer to resize
 *      size_t *capacity: pointer to the buffer current capacity
 * Return: nothing
 * Expects
 *      **data and *capacity to not be null. Expects capacity to not be 0.
 * Notes:
 *      Doubles the capacity of the buffer.
 *
 ************************/
void resizeReadLine(char **data, size_t *capacity);

/* TODO: Finish this function contract */
/**********readaline********
 *
 * reads in a single line from input file and stores the data to datapp
 * Inputs:
 *      FILE *inputfd: pointer to input file
 *      char **datapp: pointer to array of chars (the string of data)
 * Return: size of the read line
 * Expects
 *      TODO: finish expects
 * Notes:
 *      CRE if *inputfd or **datapp is NULL.
 *      CRE if *inputfd is eof.
 *      CRE if buffer memory could not be ALLOC'd
 *      CRE if readaline encounters error reading in from input file
 *
 ************************/
size_t readaline(FILE *inputfd, char **datapp);

/* TODO: Check if we can have helper functions in readaline */

size_t readaline(FILE *inputfd, char **datapp) 
{
        /* If either inputfd is null or datapp is null, cre */
        assert(inputfd != NULL && datapp != NULL);

        /* If it starts with an empty file, cre */
        assert(feof(inputfd) == 0);

        size_t  capacity = 512;
        char   *buffer   = ALLOC(capacity * sizeof(*buffer));
        
        /* If buffer can't alloc */
        assert(buffer != NULL);

        size_t writerHead = 0;
        int    currentByte = fgetc(inputfd);
        int    endLineCharacter = '\n'; 

        while (feof(inputfd) == 0 && currentByte != endLineCharacter) {
                /* If trying to write past the line size, expand */
                if (writerHead >= capacity) { 
                        resizeReadLine(&buffer, &capacity);
                }

                /* If error when reading, cre */
                assert(ferror(inputfd) == 0);

                buffer[writerHead] = (char)currentByte;

                currentByte = fgetc(inputfd); // Go to the next character
                writerHead++;
        }

        // TODO: write a comment explaining what this if statement does
        if (currentByte == endLineCharacter) {
                /* If trying to write past the line size, expand */
                if (writerHead >= capacity) { 
                        resizeReadLine(&buffer, &capacity);
                }
                
                buffer[writerHead] = endLineCharacter;
                writerHead++;
        }

        *datapp = buffer;
        
        /* The writerHead is the same as the size of the string */
        return writerHead;
}

// TODO: fix the error throwers

void resizeReadLine(char **data, size_t *capacity) {
        size_t  size     = *capacity;
        char   *currData = *data;
        
        size_t  newSize  = size * 2;
        char   *newSpace = ALLOC(newSize * sizeof(*newSpace));
        
        // TODO: Check if the assert is correct
        assert(newSpace != NULL);
        
        for (size_t writerHead = 0; writerHead < size; writerHead++) {
                newSpace[writerHead] = currData[writerHead];
        }

        FREE(currData);
        *data     = newSpace;
        *capacity = newSize;
}