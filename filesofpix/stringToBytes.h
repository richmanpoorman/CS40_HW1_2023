/*
 *      stringToBytes.h
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      Converts the plain text cleaned digits and turns them
 *      into raw format strings
 */

#include <seq.h>
#include "LinePackage.h"

#ifndef STRINGTOBYTES_H_
#define STRINGTOBYTES_H_

Seq_T stringToBytes(Seq_T cleanedLines);

LinePackage convertSingleLine(LinePackage line);

#endif