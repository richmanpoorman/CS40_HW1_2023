/*
 *      reader.h
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Reads in from given file and stores the information.
 *      
 */

#include <seq.h>
#include <stdio.h>

#ifndef READER_H_
#define READER_H_

Seq_T reader(FILE *inputFile);

#endif