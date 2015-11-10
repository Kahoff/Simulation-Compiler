#include "parseTable.h"


char *checkAndParseLine( char * currentLine, char * lineToWrite )
{
	char *token;
	int i = 0;
	for (i = 0; i < 16; i++)
	{
		lineToWrite[i] = '0';
	}
	for(i = 0; currentLine[i]; i++)
	{
  		currentLine[i] = tolower(currentLine[i]);
	}


	token = strtok( currentLine, " " );

	if( strcmp( token, "nop" ) == 0 )
	{
		token = strtok( NULL, " " );
		endLineCheck( token, lineToWrite );
		if ( lineToWrite[0] == 'f' )
		{
			return lineToWrite;
		}
		
	}
	else if ( strcmp( token, "\n" ) == 0 || ( token[0] == '/' && token[1] == '/' ) )
	{
		lineToWrite[0] = 's';

	}
	else
	{
		lineToWrite[0] = 'n';
	}
	return lineToWrite;
}

char * endLineCheck( char * restOfLine, char * lineToWrite )
{
	if ( !( restOfLine == NULL || ( restOfLine[0] == '/' && restOfLine[1] == '/' ) ) )
	{
		lineToWrite[0] = 'f';
	}
	
	return lineToWrite;

}

char * parseLineTable( char * currentLine, char * lineToWrite )
{
	char returnValue[] = "00000000";
	return lineToWrite;
}
