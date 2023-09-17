/*
 *      cleaner.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Takes in corrupted data and uncorrupts it.
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
#include <assert.h>

/**********cleanSingleLine********
 *
 * Remove corrupted characters from a single line
 * Inputs:
 *      LinePackage line     : The corrupted line to read
 *      LinePackage *injected: pointer to linepackage to store corrupted data
 * Return: A linepackage without any corrupted characters (LinePackage)
 * Expects
 *      line to be a valid linepackage. 
 *      *injected to be nonnull
 * Notes:
 *      Will store all the digits characters in line, and all the
 *      corrupted characters in *injected
 *      Will CRE if can't allocate space for injected line
 *
 ************************/
LinePackage cleanSingleLine(LinePackage line, LinePackage *injected);

/* TODO: Finish this function description */
/**********freeTablePackages********
 *
 * FREE's all of the injected lines in the table; used for 
 *      Table_T's Table_map function
 * Inputs:
 *      const void *key: Key of the table; just to match function contract
 *      void **value   : The pointer to the item at the key in the table;
 *                              only deletes if it is corrupted
 *      void *cl       : An accumulation variable; Stores the address
 *                              to the only original line in the table
 *                              so that the program knows not to delete
 * Return: nothing
 * Expects
 *      Only used for Table_map function, with cl being given the 
 *              LinePackage that is original in the table
 * Notes:
 *      Also need Table_free to get rid of the Hanson table
 *
 ************************/
void freeTablePackages(const void *key, void **value, void *cl);

Seq_T cleaner(Seq_T corruptedLines);

// TODO: Write function descriptions
Seq_T cleaner(Seq_T corruptedLines)
{
        
        /* make new Seq_T to store cleaned lines */
        size_t defaultSize = Seq_length(corruptedLines) / 2;
        Seq_T cleanedLines = Seq_new(defaultSize);

        /* Stores what the injected line of real rows is */
        LinePackage original = NULL;

        /*  
         *  The stores the first instance of each injection sequence,
         *  which connects to it's cleaned line in order to retrieve
         *  the line value of the first non-injected line when the 
         *  same line injection is found the second time 
         */
        Table_T injectionTable = Table_new(defaultSize, NULL, NULL);
        

        /*  
         *  clean every line sequentially 
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

                /*  
                 *  Turns the injected character into a table key, 
                 *  and retrieves the value in the table, if it exists
                 */
                const char  *injectedAtom = Atom_new(injectedCharacters, 
                                                     injectedSize);
                LinePackage  inTable      = Table_get(injectionTable, 
                                                      injectedAtom);

                /*   
                 *  If it is in the table, then it is a real string 
                 *  as only the real strings have duplicates,
                 *  otherwise put it in the table as it has the potential
                 *  for a duplicate
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

        bool    hasNum      = false; /* There is a number placed */
        bool    placedSpace = false; /* If a space was placed already */
        size_t  writeHead   = 0; 
        char   *byteList    = LinePackage_byteList(line);
        size_t  size        = LinePackage_size(line);

        char   *injectedCharacters = ALLOC(size * sizeof(*injectedCharacters));
        size_t  injectedWriteHead  = 0;

        /* Throw Checked Runtime Error if ALLOC returned NULL */
        assert(injectedCharacters != NULL);

        /*  
         *  Write the character to the cleaned line if it is a number
         *  Otherwise, write a space if it hasn't already and 
         *  add the character to the injected line (excluding \n)
         */
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
