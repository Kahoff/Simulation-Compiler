#ifndef PARSE_TABLE
#define PARSE_TABLE
#include <string.h>
#include <stdio.h>

char *checkAndParseLine( char * currentLine, char * lineToWrite );

char * endLineCheck( char * restOfLine, char * lineToWrite );

char * parseLineTable( char * currentLine, char * lineToWrite );

#endif