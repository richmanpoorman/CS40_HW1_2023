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
#include <mem.h>
#include <table.h>
#include <atom.h>
#include "LinePackage.h"
#include <stdbool.h>

LinePackage cleanSingleLine(LinePackage line, LinePackage *injected);

// TODO: Write function descriptions
Seq_T cleaner(Seq_T corruptedLines)
{
        // make new Seq_T to store cleaned lines
        Seq_T cleanedLines = Seq_new(1);

        bool foundOriginal = false;

        // The stores the first instance of each injection sequence, connected to it's cleaned line
        Table_T injectionSequences = Table_new(Seq_length(corruptedLines) / 2, NULL, NULL);

        // clean every line sequentially
        while (Seq_length(corruptedLines) > 0) {
                
                LinePackage line = Seq_remlo(corruptedLines);

                LinePackage injected;
                line = cleanSingleLine(line, &injected); 

                const char *injectedAtom = Atom_new(LinePackage_byteList(injected), LinePackage_size(injected));
                
                LinePackage inTable = Table_get(injectionSequences, injectedAtom);

                if (inTable != NULL) {
                        if (!foundOriginal) {
                                Seq_addhi(cleanedLines, inTable);
                                foundOriginal = true;
                        }
                        Seq_addhi(cleanedLines, line);
                }
                else {
                        Table_put(injectionSequences, injectedAtom, line);
                }
                
                LinePackage_free(injected); // TODO:: May free up when atom references
        }

        return cleanedLines;
}

// TODO: Test clean_single_line and test cleaner
// TODO: finish cleaner.

LinePackage cleanSingleLine(LinePackage line, LinePackage *injected)
{
        bool    hasNum      = false;    // true if there is even a single digit in a line
        bool    placedSpace = false;
        size_t  writeHead   = 0;
        char   *byteList    = LinePackage_byteList(line);
        size_t  size        = LinePackage_size(line);

        char   *injectedCharacters = ALLOC(size * sizeof(char));
        size_t  injectedWriteHead  = 0;

        // TODO: reorganize this, make it more readable
        for (size_t readHead = 0; readHead < size; readHead++) {
                char byte = byteList[readHead];
                if (byte >= '0' && byte <= '9') {
                        hasNum = true;
                        placedSpace = false;
                        byteList[writeHead] = byte;
                        writeHead++;
                }
                else if (byte == '\n') {
                        if (placedSpace) {
                                writeHead--;
                        }
                        byteList[writeHead] = byte;
                        writeHead++;
                }
                else {
                        injectedCharacters[injectedWriteHead] = byte;
                        injectedWriteHead++;

                        if (hasNum && !placedSpace) {
                                byteList[writeHead] = ' ';
                                writeHead++;
                                placedSpace = true;
                        }
                }
                
        }

        LinePackage_set_size(line, writeHead);

        *injected = LinePackage_new(injectedCharacters, injectedWriteHead);

        return line;
}