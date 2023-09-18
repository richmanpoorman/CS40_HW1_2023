/*
 *      cleaner.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Takes in corrupted data and uncorrupts it.
 *      
 */

#include <seq.h>
#include <mem.h>
#include <table.h>
#include <atom.h>
#include "LinePackage.h"
#include <stdbool.h>
#include <assert.h>

#include <stdio.h>  //TODO:: REMOVE THIS AFTER TESTING

/* TODO: Finish this function description */
/**********cleanSingleLine********
 *
 * Remove corrupted characters from a single line
 * Inputs:
 *      LinePackage line: the line to clean
 *      LinePackage *injected: pointer to linepackage to store corrupted data to
 * Return: A linepackage without any corrupted characters
 * Expects
 *      line to be a valid linepackage. TODO: improve this
 *      *injected to be nonnull
 * Notes:
 *      Will store all the digits characters in line, and all the
 *      corrupted characters in *injected
 *
 ************************/
LinePackage cleanSingleLine(LinePackage line, LinePackage *injected);

/* TODO: Finish this function description */
/**********freeTablePackages********
 *
 * FREE's all allocated memory of table TODO: Improve this
 * Inputs:
 *      const void *key: TODO: Explain key
 *      void **value: TODO: explain this variable
 *      void *cl: TODO: explain this variable
 * Return: nothing
 * Expects
 *      *key, **value, *cl to be nonnull. TODO: check that this is true
 * Notes:
 *      TODO: Finish notes
 *
 ************************/
void freeTablePackages(const void *key, void **value, void *cl);

Seq_T cleaner(Seq_T corruptedLines);

// TODO: Write function descriptions
Seq_T cleaner(Seq_T corruptedLines)
{
        

        size_t defaultSize = Seq_length(corruptedLines) / 2;

        /* make new Seq_T to store cleaned lines */
        Seq_T cleanedLines = Seq_new(defaultSize);

        /* Stores what the injected line of real rows is */
        LinePackage original = NULL;

        /*  The stores the first instance of each injection sequence,
         *  which connects to it's cleaned line in order to retrieve
         *  the line value of the first non-injected line when the 
         *  same line injection is found the second time 
         */
        Table_T injectionTable = Table_new(defaultSize, NULL, NULL);
        

        /*  clean every line sequentially 
         *  Note that it is hard to break up the function as it is part of 
         *  an algorithm to clean the sequence, with most of the lines
         *  just being assigning variables.
         */
        while (Seq_length(corruptedLines) > 0) {
                /* Get the line, as well as what is the 'duplicated' key */
                LinePackage line = Seq_remlo(corruptedLines);

                /* Gets the cleaned line, and the injected sequence */
                LinePackage injected;
                line = cleanSingleLine(line, &injected); 

                /* Gets the data of the injected string */
                char   *injectedCharacters = LinePackage_byteList(injected);
                size_t  injectedSize       = LinePackage_size(injected);

                /*  Turns the injected character into a table key, 
                 *  and retrieves the value in the table, if it exists
                 */
                const char  *injectedAtom = Atom_new(injectedCharacters, 
                                                     injectedSize);
                LinePackage  inTable      = Table_get(injectionTable, 
                                                      injectedAtom);

                /*   If it is in the table, then it is a real string 
                 *   as only the real strings have duplicates,
                 *   otherwise put it in the table as it has the potential
                 *   for a duplicate
                 */
                if (inTable != NULL) {
                        /*  If it is the first time seeing the repeated key,
                         *  Push the key on the table before adding 
                         *  the key just found
                         */
                        if (original == NULL) {
                                Seq_addhi(cleanedLines, inTable);
                                original = inTable;
                        }
                        Seq_addhi(cleanedLines, line);
                }
                else {
                        Table_put(injectionTable, injectedAtom, line);
                }

                /* Update seenInTable with the key */
                LinePackage_free(injected); 
        }

        /* Frees up the table */
        Table_map(injectionTable, freeTablePackages, original);
        Table_free(&injectionTable);
        
        return cleanedLines;
}


LinePackage cleanSingleLine(LinePackage line, LinePackage *injected)
{
        bool    hasNum      = false;    /* true if there is even a single digit 
                                           in a line */
        bool    placedSpace = false;
        size_t  writeHead   = 0;
        char   *byteList    = LinePackage_byteList(line);
        size_t  size        = LinePackage_size(line);

        char   *injectedCharacters = ALLOC(size * sizeof(*injectedCharacters));
        size_t  injectedWriteHead  = 0;

        /* Throw Checked Runtime Error if ALLOC returned NULL */
        assert(injectedCharacters != NULL);

        for (size_t readHead = 0; readHead < size; readHead++) {
                char byte = byteList[readHead];
                if (byte >= '0' && byte <= '9') {
                        hasNum = true;
                        placedSpace = false;
                        byteList[writeHead] = byte;
                        writeHead++;
                } else {
                        if (byte != '\n') {
                                injectedCharacters[injectedWriteHead] = byte;
                                injectedWriteHead++;
                        }

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

void freeTablePackages(const void *key, void **value, void *cl) {

        /*   Free the LinePackage in the table if it is
         *   an injected string; only one string in the 
         *   table is not the injected, which is passed 
         *   through cl
         */
        LinePackage original = cl;
        LinePackage inTable  = *value;
        if (inTable != original) {
                FREE(inTable);
        }
        (void) key; /* Don't need the key value */
}
