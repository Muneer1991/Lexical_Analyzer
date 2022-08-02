#include "types.h"

/* Function to read and validate arguments */
Status read_and_validate_args(int argc, char *argv[]);

/* Functions to check for various delimiters */
Status isValidDelimiter(char ch);

/* Functions to check for various operators */
Status isValidOperator(char ch);

/* Functions to check for various identifiers */
Status isvalidIdentifier(char* str);

/* Functions to check for various keywords */
Status isValidKeyword(char* str);

/* Functions to check for constants*/
Status isValidInteger(char* str);

/* Functions to check for float numbers */
Status isRealNumber(char* str);

/* Function to store words into a buffer */
char *subString(char* str, int left, int right);

/* Function call to recognize each tokens */
void detectTokens(char* str);