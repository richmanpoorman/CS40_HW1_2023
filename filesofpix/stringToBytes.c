/*
 *      stringToBytes.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Converts the plain text cleaned digits and turns them
 *      into raw format strings
 */

#include <seq.h>
#include <stdbool.h>
#include <stddef.h>

#include "LinePackage.h"
#include "stringToBytes.h"

/**********convertSingleLine********
 *
 * Converts a single line of digit bytes to character bytes
 * Inputs:
 *      LinePackage line: The Linepackage with the data to convert
 * Return: a linepackage with the converted line (LinePackage)
 * Expects
 *      Expects the LinePackage to be in the format of:
 *              (numberDigits) (numberDigits) (numberDigits) ...
 * Notes:
 *      will always end line WITHOUT \n character
 *      will write to the line in-place
 *
 ************************/
LinePackage convertSingleLine(LinePackage line);

/*********stringToBytes*********
 *
 * Converts all of the LinePackages from plain to raw data, 
 *      maintaining the order the LinePackages were given in
 * Inputs:
 *      Seq_T cleanedLines: A sequence with the plain digit lines
 *                          in the correct order
 * Return: A sequence with all of the raw lines in order (Seq_T)
 * Expects
 *      There are no NULL in cleanedLines
 *      The lines don't have any "dirty" characters aka digits in the format:
 *              (numberDigits) (numberDigits) (numberDigits) ...
 * Notes:
 *      will always end line WITHOUT \n character
 *
 ************************/
Seq_T stringToBytes(Seq_T cleanedLines);

Seq_T stringToBytes(Seq_T cleanedLines)
{
        Seq_T rawLines = Seq_new(1);
        
        while (Seq_length(cleanedLines) > 0) {
                LinePackage clean = Seq_remlo(cleanedLines);
                LinePackage raw   = convertSingleLine(clean);
                
                Seq_addhi(rawLines, raw);
        }
        
        return rawLines;
}

LinePackage convertSingleLine(LinePackage line)
{
        int     value     = 0;
        char   *byteList  = LinePackage_byteList(line);
        size_t  size      = LinePackage_size(line);
        size_t  writeHead = 0;
        bool    hasPushed = false;

        for (size_t readHead = 0; readHead < size; readHead++) {
                char byte = byteList[readHead];
                
                /* If the value if a digit, then accumulate */
                if (byte >= '0' && byte <= '9') {
                        hasPushed = false;
                        value *= 10;
                        value += byte - '0';   
                }
                else { /* Otherwise, put it into the string */
                        hasPushed = true;
                        byteList[writeHead] = (char) value;
                        writeHead++;
                        value = 0;
                        if (byte == '\n') { /* If it is an endline, put the 
                                               endline on as well */
                                byteList[writeHead] = '\n';
                                writeHead++;
                        }
                }
        }
        if (!hasPushed) {
                byteList[writeHead] = (char) value;
                writeHead++;
        }
        /* writeHead always points to one after the last written place, which 
           is the size */
        LinePackage_set_size(line, writeHead);

        return line;
}