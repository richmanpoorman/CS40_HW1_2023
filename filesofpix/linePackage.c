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
LinePackage LinePackage_new(char *bytes, size_t length) 
{
        LinePackage linepackage_p = ALLOC(sizeof(*linepackage_p));
        // printf("ALLOC'd new LinePackage at %p\n", (void*) linepackage_p);


        linepackage_p -> byteList = bytes;
        linepackage_p -> size = length;
        linepackage_p -> capacity = length;

        return linepackage_p;
}

void LinePackage_free(LinePackage byteListStruct) 
{
        // TODO: Put memory all on heap and make sure to free
        FREE(byteListStruct -> byteList);    // TODO: Check why this fixes double free error
        FREE(byteListStruct);
        // TODO: Check that this doesn't memory leak

}

// TODO: fix function formatting

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