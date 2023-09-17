/*
 *      LinePackage.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for LinePackage.c
 *      
 */

#include <stdlib.h>
#include <mem.h>
#include <stdio.h>      // TODO: Remove
#include <assert.h>

typedef struct LinePackage 
{
        char *byteList;  // The pointer to the first byte
	size_t size;     // The amount of bytes in use
	size_t capacity; // The amount of bytes that can be stored
} *LinePackage;

// TODO: Explain what each function does

/* TODO: move these descriptions to where the function contracts will be located */
/* TODO: Finish LinePackage_new function description */

/**********LinePackage_new********
 *
 * Creates a new linepackage struct
 * Inputs:
 *      char *bytes: list of bytes to store      TODO: Improve this
 *      size_t length: the size of the byte list to store
 * Return: A linepackage struct furnished with the given data
 * Expects
 *      *bytes to not be NULL. length to correctly indicate the size of *bytes
 * Notes:
 *      TODO: finish notes
 *
 ************************/
LinePackage LinePackage_new(char *bytes, size_t length) 
{
        LinePackage linepackage_p = ALLOC(sizeof(*linepackage_p));
        /* POTENTIAL TODO: make assert that checks that memory ALLOC'd okay */

        linepackage_p -> byteList = bytes;
        linepackage_p -> size = length;
        linepackage_p -> capacity = length;

        return linepackage_p;
}

/* TODO: finish LinePackage_free function description */
/**********LinePackage_free********
 *
 *      FREE's memory LinePackage allocates.
 * Inputs:
 *      LinePackage byteListStruct: TODO: Finish this
 * Return: nothing
 * Expects
 *      TODO: Finish expects
 * Notes:
 *      TODO: finish notes
 *      Should only be called when the linepackage is no longer needed.
 *
 ************************/
void LinePackage_free(LinePackage byteListStruct) 
{
        // TODO: Put memory all on heap and make sure to free
        FREE(byteListStruct -> byteList);    // TODO: Check why this fixes double free error
        FREE(byteListStruct);
        // TODO: Check that this doesn't memory leak

}

// TODO: fix function formatting
/* TODO: finish LinePackage_byteList description */
/**********LinePackage_new********
 *
 * Creates a new linepackage struct
 * Inputs:
 *      char *bytes: list of bytes to store      TODO: Improve this
 *      size_t length: the size of the byte list to store
 * Return: A linepackage struct furnished with the given data
 * Expects
 *      *bytes to not be NULL. length to correctly indicate the size of *bytes
 * Notes:
 *      TODO: finish notes
 *
 ************************/
char *LinePackage_byteList(LinePackage byteListStruct) 
{
        return byteListStruct -> byteList;
}

size_t LinePackage_size(LinePackage byteListStruct) 
{
        return byteListStruct -> size;
}

void LinePackage_set_size(LinePackage byteListStruct, size_t new_size) 
{
        assert(new_size < byteListStruct -> capacity);
        // if (new_size > byteListStruct -> capacity) {
        //         exit(1);        // TODO: Check what error code this should output
        // }

        byteListStruct -> size = new_size;
}