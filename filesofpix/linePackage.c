/*
 *      LinePackage.c
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      LinePackage is a container that stores a list of bytes
 *      along with the accessible size
 *      
 */

#include <stdlib.h>
#include <mem.h>
#include <assert.h>

typedef struct LinePackage 
{
        char *byteList;  /* The pointer to the first byte */
	size_t size;     /* The amount of bytes in use */
	size_t capacity; /* The amount of bytes that can be stored */
} *LinePackage;

/**********LinePackage_new********
 *
 * Creates a new linepackage struct
 * Inputs:
 *      char *bytes: list of bytes to store      
 *      size_t length: the size of the byte list to store
 * Return: A linepackage struct furnished with the given data
 * Expects
 *      *bytes to not be NULL. length to correctly indicate the size of *bytes
 *      *bytes is allocated on the Heap; the LinePackage_free will free
 *              the data stored at *bytes
 * Notes:
 *      Will CRE if allocation fails for the LinePackage
 *
 ************************/
LinePackage LinePackage_new(char *bytes, size_t length);

/**********LinePackage_free********
 *
 *      FREE's memory LinePackage allocates.
 * Inputs:
 *      LinePackage byteListStruct: The line package that needs to be freed
 * Return: nothing
 * Expects
 *      The data in the byteListStruct to be on the heap
 * Notes:
 *      Throws a CRE if the byteListStruct is NULL;
 *      Will cause a double free if byteList data is on the stack
 *      Will free up the data at the pointer to the LinePackage, 
 *              but will not set it to NULL
 *
 ************************/
void LinePackage_free(LinePackage byteListStruct);

/**********LinePackage_byteList********
 *
 * Creates a new linepackage struct
 * Inputs:
 *      LinePackage byteListStruct: The LinePackage to retrieve the data from
 * Return: The pointer to the first byte in the data array
 * Expects
 *      byteListStruct is not NULL
 * Notes:
 *      Will CRE if byteListStruct is NULL
 *
 ************************/
char *LinePackage_byteList(LinePackage byteListStruct);

/**********LinePackage_size********
 *
 * Outputs the size of the byte list in the given linepackage struct.
 * Inputs:
 *      LinePackage byteListStruct: the linepackage to check size of
 * Return: The size_t of the given linepackage's byte list.
 * Expects
 *      byteListStruct to be a valid linepackage
 *      The client used LinePackage_set_size if size was changed
 * Notes:
 *      Will CRE if byteListStruct is NULL
 *
 ************************/
size_t LinePackage_size(LinePackage byteListStruct);

/**********LinePackage_set_size********
 *
 * Sets the capacity of given linepackage struct to new size.
 * Inputs:
 *      LinePackage byteListStruct: the linepackage to modify capacity of
 *      size_t new_size: the new size to set the linepackage's size to
 * Return: nothing
 * Expects
 *      byteListStruct to be a valid linepackage.
 *      new_size to be larger than the current linepackage capacity
 * Notes:
 *      CRE if byteList is NULL
 *      CRE if new_size < current capacity
 *
 ************************/
void LinePackage_set_size(LinePackage byteListStruct, size_t new_size);


LinePackage LinePackage_new(char *bytes, size_t length) 
{
        LinePackage linepackage_p = ALLOC(sizeof(*linepackage_p));
        assert(linepackage_p != NULL);

        linepackage_p -> byteList = bytes;
        linepackage_p -> size = length;
        linepackage_p -> capacity = length;

        return linepackage_p;
}

void LinePackage_free(LinePackage byteListStruct) 
{
        assert(byteListStruct != NULL);

        FREE(byteListStruct -> byteList); 
        FREE(byteListStruct);

}

char *LinePackage_byteList(LinePackage byteListStruct) 
{
        assert(byteListStruct != NULL);
        return byteListStruct -> byteList;
}

size_t LinePackage_size(LinePackage byteListStruct) 
{
        assert(byteListStruct != NULL);
        return byteListStruct -> size;
}

void LinePackage_set_size(LinePackage byteListStruct, size_t new_size) 
{
        assert(byteListStruct)
        assert(new_size < byteListStruct -> capacity);

        byteListStruct -> size = new_size;
}