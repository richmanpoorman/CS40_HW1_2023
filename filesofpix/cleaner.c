/*
 *      cleaner.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for cleaner.c
 *      
 */

#include <seq.h>
#include "LinePackage.h"
#include <stdbool.h>

LinePackage clean_single_line(LinePackage line);

// TODO: Write function descriptions
Seq_T cleaner(Seq_T corruptedLines)
{
        // make new Seq_T to store cleaned lines
        Seq_T cleanedLines = Seq_new(1);

        // clean every line sequentially
        while (Seq_length(corruptedLines) > 0) {
                LinePackage line = Seq_remlo(corruptedLines);
                line = clean_single_line(line);

                if (line != NULL) {
                        Seq_addhi(cleanedLines, line);
                }
        }

        return cleanedLines;
}

// TODO: Test clean_single_line and test cleaner
// TODO: finish cleaner.

LinePackage clean_single_line(LinePackage line)
{
        bool hasNum = false;    // true if there is even a single digit in a line
        bool placedSpace = false;
        size_t writeHead = 0;
        char *byteList = LinePackage_byteList(line);
        size_t size = LinePackage_size(line);

        // TODO: reorganize this, make it more readable
        for (size_t readHead = 0; readHead < size; readHead++) {
                char byte = byteList[readHead];

                if (hasNum) {   // checks if seen a digit in this line
                        if (byte > 47 && byte < 58) {   // checks if digit
                                byteList[writeHead] = byte;
                                writeHead++;
                                placedSpace = false;
                        } else if (byte == 10) {        // check if \n
                                // gets rid of space before \n
                                if (placedSpace) {      // check if space was placed after digit
                                        byteList[writeHead - 1] = byte;
                                } else {        // adds \n after digit if no space
                                        byteList[writeHead] = byte;
                                        writeHead++;
                                }
                        } else if (!placedSpace) {      // place space after digit
                                byteList[writeHead] = ' ';
                                writeHead++;
                                placedSpace = true;
                        }
                } else {
                        if (byte > 47 && byte < 58) {   // places first digit at beginning of line
                                hasNum = true;
                                byteList[writeHead] = byte;
                                writeHead++;
                        }
                }
        }

        LinePackage_set_size(line, writeHead);

        // throw away injected line
        if (!hasNum) {
                LinePackage_free(line);
                return NULL;
        }

        return line;
}