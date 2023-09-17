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
/**********LinePackage_byteList********
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

/* TODO: finish LinePackage_size description */
/**********LinePackage_size********
 *
 * Outputs the size of the byte list in the given linepackage struct.
 * Inputs:
 *      LinePackage byteListStruct: the linepackage to check size of
 * Return: The size_t of the given linepackage's byte list.
 * Expects
 *      byteListStruct to be a valid linepackage
 * Notes:
 *      TODO: finish notes
 *
 ************************/
size_t LinePackage_size(LinePackage byteListStruct) 
{
        return byteListStruct -> size;
}

/* TODO: finish LinePackage_set_size description */
/**********LinePackage_set_size********
 *
 * Sets the capacity of given linepackage struct to new size.
 * Inputs:
 *      LinePackage byteListStruct: the linepackage to modify capacity of
 *      size_t new_size: the new size to set the linepackage's capacity to
 * Return: nothing
 * Expects
 *      byteListStruct to be a valid linepackage.
 *      new_size to be larger than the current linepackage capacity
 * Notes:
 *      CRE if new_size < current capacity
 *
 ************************/
void LinePackage_set_size(LinePackage byteListStruct, size_t new_size) 
{
        assert(new_size < byteListStruct -> capacity);

        byteListStruct -> size = new_size;
}