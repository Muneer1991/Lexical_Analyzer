/**************Documentation**************
Name          : Muneer Mohammad Ali
Date          : 20/05/2022
Description   : Lexical Analyzer
Sample Input  : gcc *.c
                ./a.out test.c
Sample Output : Lists all identifiers, keywords, operators, constants etc
******************************************/

#include <stdio.h>

#include "types.h"
#include "detect_tokens.h"

int main(int argc, char *argv[])
{   
    /* Declare file pointer */
    FILE *fptr;

    /* Declare a variable to store the character size of the file being passed */
    unsigned long int size;

    /* Read and validate the arguments */
    if(read_and_validate_args(argc, argv) == e_success)
    {
        /* Open the file in read only mode */
        fptr = fopen(argv[1], "r");

        /* Error if no such file present in current working directory */
        if (fptr == NULL)
        {
    	    perror("fopen");
    	    fprintf(stderr, "ERROR: Unable to open file %s\n", argv[1]);

    	    return 0;
        }

        /* Skip and place the file pointer to the end of file */
        fseek(fptr, 0, SEEK_END);

        /* The last position is nothing but the size of the file */
        size = ftell(fptr);

        /* Declare an array with the file size */
        char str[size];

        /* Place the pointer back to 1st position */
        fseek(fptr, 0, SEEK_SET);

        /* Store the characters of the file into the array */
        fread(str,size,1,fptr);

        /* Store a NULL character at the end of the array to represent a string */
        str[size] = '\0';

        /* Print the input file contents */
        printf("%s\n",str);

        /* Function call to recognize each tokens */
        detectTokens(str);    
    }

    /* Error statements for invalid arguments */
    else
    {
        printf("-----------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :./a.out test.c\n");
        printf("\n-----------------------------------------------------\n");
    }
             
}