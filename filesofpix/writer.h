/*
 *      writer.h
 *      By Helena Simson, Matthew Wong, 9/9/2023
 *      hw1: filesofpix
 *
 *      Summary:
 *      Writes byte data to given output file.
 *      
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <stdio.h>
#include <seq.h>

void writer(FILE *outputFile, Seq_T rawLines);

#endif