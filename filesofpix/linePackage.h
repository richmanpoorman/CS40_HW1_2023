/*
 *      LinePackage.h
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for LinePackage.h
 *      
 */

// #include <stdlib.h>

#ifndef LINEPACKAGE_H_
#define LINEPACKAGE_H_

typedef struct LinePackage *LinePackage;

LinePackage LinePackage_new(char *bytes, size_t length);

void LinePackage_free(LinePackage byteListStruct);

char *LinePackage_byteList(LinePackage byteListStruct);

size_t LinePackage_size(LinePackage byteListStruct);

void LinePackage_set_size(LinePackage byteListStruct, size_t new_size);

#endif