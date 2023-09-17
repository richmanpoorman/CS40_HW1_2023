/*
 *      readaline.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      Reads a single line which ends at either a 
 *              \n character or end of file flag
 *      
 */

#include <stdio.h>
#include <stdlib.h>

#include <mem.h>
#include <assert.h>

#include "readaline.h"

/**********resizeReadLine********
 *
 * Resizes the data buffer size
 * Inputs:
 *	char **data: pointer to buffer to resize
 *      size_t *capacity: pointer to the buffer current capacity
 * Return: nothing (void)
 * Expects
 *      **data and *capacity to not be null. Expects capacity to not be 0.
 * Notes:
 *      Doubles the capacity of the buffer.
 *      CRE if memory could not be ALLOC'd
 *
 ************************/
void resizeReadLine(char **data, size_t *capacity);

/**********readaline********
 *
 * reads in a single line from input file and stores the data to datapp
 * Inputs:
 *      FILE *inputfd: pointer to input file
 *      char **datapp: pointer to array of chars (the string of data)
 * Return: size of the read line (size_t)
 * Expects
 *      Expects the file to be open, and that datapp is the location
 *      that can be read;
 *      Expects the string allocated by readaline to be freed elsewhere
 * Notes:
 *      CRE if *inputfd or **datapp is NULL.
 *      CRE if *inputfd is eof.
 *      CRE if buffer memory could not be ALLOC'd
 *      CRE if readaline encounters error reading in from input file
 *
 ************************/
size_t readaline(FILE *inputfd, char **datapp);

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

        /* If error when reading, cre */
        assert(ferror(inputfd) == 0);

        while (feof(inputfd) == 0 && currentByte != endLineCharacter) {
                /* If trying to write past the line size, expand */
                if (writerHead >= capacity) { 
                        resizeReadLine(&buffer, &capacity);
                }

                buffer[writerHead] = (char)currentByte;

                currentByte = fgetc(inputfd); // Go to the next character
                writerHead++;
                
                /* If error when reading, cre */
                assert(ferror(inputfd) == 0);
        }

        /* Adds the endLineCharacter if it is what the line ended on */
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

void resizeReadLine(char **data, size_t *capacity) {
        size_t  size     = *capacity;
        char   *currData = *data;
        
        size_t  newSize  = size * 2;
        char   *newSpace = ALLOC(newSize * sizeof(*newSpace));
        
        assert(newSpace != NULL);
        
        for (size_t writerHead = 0; writerHead < size; writerHead++) {
                newSpace[writerHead] = currData[writerHead];
        }

        FREE(currData);
        *data     = newSpace;
        *capacity = newSize;
}