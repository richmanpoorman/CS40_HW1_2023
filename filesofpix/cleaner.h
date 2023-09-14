/*
 *      cleaner.h
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      
 *      TODO: write summary for cleaner.h
 *      
 */

#include <seq.h>
#include "LinePackage.h"

#ifndef CLEANER_H_
#define CLEANER_H_

Seq_T cleaner(Seq_T corruptedLines);

LinePackage cleanSingleLine(LinePackage line, LinePackage *injected);        // TODO: Fix this to be camel case

#endif