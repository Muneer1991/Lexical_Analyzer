#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

/* Function to read and validate arguments */
Status read_and_validate_args(int argc, char *argv[])
{
    /* Check for .c file */
    if(argc == 2 && strcmp((strstr(argv[1],".")), ".c") == 0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

/* Functions to check for various delimiters mentioned in the if condition */
Status isValidDelimiter(char ch) 
{
   if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'|| ch == '\n' || ch == EOF)
   {
       return e_success;
   }
   return e_failure;
}

/* Functions to check for various operators mentioned in the if condition */
Status isValidOperator(char ch)
{
   if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=')
   {
       return e_success;
   }

   return e_failure;
}

/* Functions to check for various identifiers mentioned in the if condition */
Status isvalidIdentifier(char *str)
{
   if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || isValidDelimiter(str[0]) == e_success)
   {
       return e_failure;
   }

   return e_success;
}

/* Functions to check for various keywords mentioned in the if condition */
Status isValidKeyword(char *str) 
{
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||  !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "default") || !strcmp(str, "char") || !strcmp(str, "for") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto") || !strcmp(str, "const") || !strcmp(str, "volatile"))
    {
        return e_success;        
    }

   return e_failure;
}

/* Functions to check for constants*/
Status isValidInteger(char *str) 
{
    int len = strlen(str);
    
    /* Check if the string array is empty then return*/
    if (len == 0)
    {
        return e_failure;
    }

    /* else, checking if any one character is other than a integer or a '-' at start (for -ve value)  */
    for (int i = 0; i < len; i++) 
    {
        /* return if character other than integer found*/
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
        {
            
            return e_failure;
        }
    }
   return e_success;
}

/* Functions to check for float numbers */
Status isRealNumber(char *str) 
{
    int len = strlen(str);
    
    /* declaring a seperate variable of type Status to store the return status */
    /* This variable is necessary to differentiate between dot operator and decimal */
    Status hasDecimal = e_failure;
    
    if (len == 0)
    {
        return e_failure;        
    }

    
    for (int i = 0; i < len; i++) 
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
        {
            return e_failure;
        }

        /* if '.' found, then change the hasDecimal status */
        if (str[i] == '.')
        {
            hasDecimal = e_success;
        }
    }
    
    return hasDecimal;
}

/* Function to store words into a buffer */
char *subString(char *str, int left, int right) 
{
    /* Allocating memory dynamically */
    char *subStr = calloc( sizeof(char), (right - left + 2));

    /* left contains the string length */
    /* This loop will store the word in subStr buffer */
    for (int i = left; i <= right; i++)
    {
        subStr[i - left] = str[i];    
    }

    /* Store NULL at end to from a string */
    subStr[right - left + 1] = '\0';
    
    return subStr;
}

/* Function to dectect tokens */
void detectTokens(char *str) 
{
    /* Variables used as array index to move through the array */
    int left = 0, right = 0;
    /* store the array length to a variable*/
    int length = strlen(str);

    /* Loop until the length of array is reached by the index variables*/
    while (right <= length && left <= right) 
    {
        /* if the character from the array do not match any of the tokens mentioned in the function increment right */
        if (isValidDelimiter(str[right]) == e_failure)
        {
            right++;
        }

        /* if the charcter is a token mentioned in the delimiter function */
        /* But not a token in the operator function as there are operators also in the delimiter function */
        /* Also the token shouldn't be a space or next line */
        /* if all these conditions are met then its a special character */
        else if (isValidOperator(str[right]) == e_failure && isValidDelimiter(str[right]) == e_success && str[right] != '\n' && str[right] != ' ')
        {
            printf("'%c' : Special Character\n",str[right]);
        }

        /* Condition for priniting operator */
        if (isValidDelimiter(str[right]) == e_success && left == right) 
        {
            if (isValidOperator(str[right]) == e_success)
            {
                printf("'%c' : Operator\n", str[right]);
            }

            /* Assigning left with right so that the length of string is stored in left */
            right++;
            left = right;
        } 

        /* Condition to get keywords, constants, floating numbers and identifier */
        else if (isValidDelimiter(str[right]) == e_success && left != right || (right == length && left != right)) 
        {
            /* function to store strings */
            char *subStr = subString(str, left, right - 1);

            /* The string formed in subStr is checked to be any one of below */

            /* Check the string is a keyword */
            if (isValidKeyword(subStr) == e_success)
            {
                printf("'%s' : Keyword\n", subStr);
            }
            
            /* Check the string is an integer */
            else if (isValidInteger(subStr) == e_success)
            {
                printf("'%s' : Constant\n", subStr);
            }

            /* Check the string is a floating number */
            else if (isRealNumber(subStr) == e_success)
            {
                printf("'%s' : Floating number\n", subStr);
            }

            /* Check the string is an identifier */
            else if (isvalidIdentifier(subStr) == e_success && isValidDelimiter(str[right - 1]) == e_failure)
            {
                printf("'%s' : Identifier\n", subStr);
            }

            /* Check the string is non of the above */
            else if (isvalidIdentifier(subStr) == e_failure && isValidDelimiter(str[right - 1]) == e_failure)
            {
                printf("Invalid Identifier : '%s'\n", subStr);
            }
         
            left = right;
        }
    }
}