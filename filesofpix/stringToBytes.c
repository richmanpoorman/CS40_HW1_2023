/*
 *      stringToBytes.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Converts string data into single byte data.
 *      
 *      TODO: write file description for stringToBytes.c
 */

#include <seq.h>
#include <stdbool.h>

#include "LinePackage.h"

/* TODO: Finish this function */
/**********convertSingleLine********
 *
 * Converts a single line of digit bytes to character bytes
 * Inputs:
 *      LinePackage line: the line to convert
 * Return: a linepackage with the converted line
 * Expects
 *      line to be a valid linepackage. TODO: improve this
 * Notes:
 *      will always end line WITHOUT \n character
 *
 ************************/
LinePackage convertSingleLine(LinePackage line);

/* TODO: Finish this function */
/**********stringToBytes********
 *
 * Converts data of digit bytes to character bytes
 * Inputs:
 *      Seq_T cleanedLines: the lines to convert to character bytes
 * Return: The converted lines
 * Expects
 *      cleanedLines to be now uncorrupted with only digit and space ASCII characters TODO: Check this
 * Notes:
 *      TODO: Finish notes
 *
 ************************/
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
                
                if (byte >= '0' && byte <= '9') { /* If the value if a digit, then accumulate */ /* TODO: WTF does this comment mean? */
                        hasPushed = false;
                        value *= 10;
                        value += byte - '0';   
                }
                else { /* Otherwise, put it into the string */
                        hasPushed = true;
                        byteList[writeHead] = (char) value;
                        writeHead++;
                        value = 0;
                        if (byte == '\n') { /* If it is an endline, put the endline on as well */
                                byteList[writeHead] = '\n';
                                writeHead++;
                        }
                }
        }
        if (!hasPushed) {
                byteList[writeHead] = (char) value;
                writeHead++;
        }
        /* writeHead always points to one after the last written place, which is the size */
        LinePackage_set_size(line, writeHead);

        return line;
}