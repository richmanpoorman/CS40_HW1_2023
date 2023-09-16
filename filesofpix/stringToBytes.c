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


LinePackage convertSingleLine(LinePackage line);

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
                
                if (byte >= '0' && byte <= '9') { // If the value if a digit, then accumulate
                        hasPushed = false;
                        value *= 10;
                        value += byte - '0';   
                }
                else { // Otherwise, put it into the string
                        hasPushed = true;
                        byteList[writeHead] = (char) value;
                        writeHead++;
                        value = 0;
                        if (byte == '\n') { // If it is an endline, put the endline on as well
                                byteList[writeHead] = '\n';
                                writeHead++;
                        }
                }
        }
        if (!hasPushed) {
                byteList[writeHead] = (char) value;
                writeHead++;
        }
        // writeHead always points to one after the last written place, which is the size
        LinePackage_set_size(line, writeHead);

        return line;
}