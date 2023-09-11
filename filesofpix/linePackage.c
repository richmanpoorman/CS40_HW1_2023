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

typedef struct LinePackage 
{
        char *byteList;  // The pointer to the first byte
	size_t size;     // The amount of bytes in use
	size_t capacity; // The amount of bytes that can be stored
} *LinePackage;

// TODO: Explain what each function does
LinePackage LinePackage_new(char *bytes, size_t length) 
{
        LinePackage linepackage_p = ALLOC(sizeof(LinePackage));

        linepackage_p -> byteList = bytes;
        linepackage_p -> size = length;
        linepackage_p -> capacity = length;

        return linepackage_p;
}

void LinePackage_free(LinePackage byteListStruct) 
{
        FREE(byteListStruct -> byteList);
        FREE(byteListStruct);
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
        if (new_size > byteListStruct -> capacity) {
                exit(1);        // TODO: Check what error code this should output
        }

        byteListStruct -> size = new_size;
}

// TODO: write free function