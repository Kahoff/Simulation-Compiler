#include <stdio.h>
#include <stdlib.h>
#include "parseTable.h"

#define MAX_LINE_LENGTH 256
#define MAX_COMPILER_OUTPUT 32768


void quit( FILE * fileToCompile, FILE * fileWrittenOver, char * lineToWrite )
{
	fclose(fileToCompile);
	fclose(fileWrittenOver);
	free(lineToWrite);
}

int main( int argc, char *argv[] )
{
	char lineInFile[ MAX_LINE_LENGTH ];
	char * nameOfCompiledFile = "a";
	int lineCount = 0;
	char *lineToWrite = malloc( 512 );
	char *dataToWriteToFile = malloc( MAX_COMPILER_OUTPUT );
	int nextFreeCharacter = 0;
	int i;
	FILE *fileWrittenOver;

	if ( argc == 1 )
	{
		printf( "user needs to specify file to compile\n" );
		free(lineToWrite);
		return -1;
	}
	else
	{
		FILE *fileToCompile = fopen( argv[1], "r" );

		if ( fileToCompile == NULL)
		{
			printf( "Could not compile %s \n", argv[1] );
		}
		else
		{
			if ( argc == 4 )
			{
				if ( strcmp(argv[ 2 ], "-o" ) )
				{
					printf( "Second entry must be \"-o\"\n" );
					quit( fileToCompile, fileWrittenOver, lineToWrite );
					return -1;
				}

				nameOfCompiledFile = argv[3];

			}
			else if (argc != 2)
			{
				printf( "Incorrect number of arguments were entered in command line.\n");
				quit( fileToCompile, fileWrittenOver, lineToWrite );
				return -1;
			}

			fileWrittenOver = fopen( nameOfCompiledFile, "w" );

			while ( fgets( lineInFile, MAX_LINE_LENGTH, fileToCompile) != NULL )
			{
				// call function to check each line for validity.
				lineCount++;
				if ( 1 )
				{
					
					lineToWrite = checkAndParseLine( lineInFile, lineToWrite );
					printf( "%s\n", lineToWrite );
					if( lineToWrite[0] == 'f' )
					{
						printf( "Error: Too Many Arguments.\n  Line - %d \n", lineCount );
						quit( fileToCompile, fileWrittenOver, lineToWrite );
						return -1;
					}
					else if( lineToWrite[0] == 'n' )
					{
						printf( "Error: Invalid Instruction.\n  Line - %d \n", lineCount );
						quit( fileToCompile, fileWrittenOver, lineToWrite );
						return -1;
					}
					else if( lineToWrite[0] != 's' )
					{
						if ( nextFreeCharacter == MAX_COMPILER_OUTPUT )
						{
							printf( "Error: Program too large.\n  Please reduce code. %d \n", lineCount );
							quit( fileToCompile, fileWrittenOver, lineToWrite );
							return -1;
						}

						for (i = 0; i < 16; i++ )
						{
							dataToWriteToFile[nextFreeCharacter++] = lineToWrite[i];
						}
						printf( "%s\n", lineToWrite );
					}

				}

			}

			printf( "%d\n", nextFreeCharacter );
			//printf( "%s\n", dataToWriteToFile );
			for (i = 0; i < MAX_COMPILER_OUTPUT; i++ ){
				if (i < nextFreeCharacter )
				{
					//fprintf( fileWrittenOver, &dataToWriteToFile[i] );
					fputc( dataToWriteToFile[i], fileWrittenOver );
				}
				else
				{
					fputc( '0', fileWrittenOver );
					//char * one = "1";
					//fprintf( fileWrittenOver, one );
				}
			}
			//printf( "File had %d lines.\n", lineCount );
			quit( fileToCompile, fileWrittenOver, lineToWrite );
		}
	}
	return 0;
}
