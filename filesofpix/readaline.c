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

void resizeReadLine(char **data, size_t *capacity);

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
        
        // Check if the assert is correct
        assert(newSpace != NULL);
        
        for (size_t writerHead = 0; writerHead < size; writerHead++) {
                newSpace[writerHead] = currData[writerHead];
        }

        FREE(currData);
        *data     = newSpace;
        *capacity = newSize;
}