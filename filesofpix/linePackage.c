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

typedef struct LinePackage {
        char *byteList;  // The pointer to the first byte
	size_t size;     // The amount of bytes in use
	size_t capacity; // The amount of bytes that can be stored
} *LinePackage;

LinePackage LinePackage_new(char *bytes, size_t length) {
        LinePackage linepackage_p = ALLOC(sizeof(LinePackage));

        linepackage_p -> byteList = bytes;
        linepackage_p -> size = length;
        linepackage_p -> capacity = length;

        return linepackage_p;
}

// TODO: make getters and setters