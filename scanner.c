//
//  scanner.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include <stdio.h>
#include "scanner.h"

/*******************
 Static functions needed for the scanner
 You need to design the proper parameter list and
 return types for functions with ???.
 ******************/

//need to dertermine returns
static char get_char();
static ??? skip_comment(???);
static ??? skip_blanks(???);
static ??? get_word(???);
static ??? get_number(???);
static ??? get_string(???);
static ??? get_special(???);
static ??? downshift_word(???);
static BOOLEAN is_reserved_word(???);

typedef enum
{
    LETTER, DIGIT, QUOTE, SPECIAL, EOF_CODE,
}
CharCode;

/*********************
 Static Variables for Scanner
 Must be initialized in the init_scanner function.
 *********************/
static FILE *src_file;
static char src_name[MAX_FILE_NAME_LENGTH];
static char todays_date[DATE_STRING_LENGTH];
static CharCode char_table[256];  // The character table

typedef struct
{
    char *string;
    TokenCode token_code;
}
RwStruct;

const RwStruct rw_table[9][10] = {
    {{"do",DO},{"if",IF},{"in",IN},{"of",OF},{"or",OR},{"to",TO},{NULL,0}}, //Reserved words of size 2
    {{"and",AND},{"div",DIV},{"end",END},{"for",FOR},{"mod",MOD},{"nil",NIL},{"not",NOT},{"set",SET},{"var",VAR},{NULL,0}}, //Reserved words of size 3
    {{"case",CASE},{"else",ELSE},{"file",FFILE},{"goto",GOTO},{"then",THEN},{"type",TYPE},{"with",WITH},{NULL,0}}, //Reserved words of size 4
    {{"array",ARRAY},{"begin",BEGIN},{"const",CONST},{"label",LABEL},{"until",UNTIL},{"while",WHILE},{NULL,0}},  //Reserved words of size 5
    {{"downto",DOWNTO}, {"packed",PACKED},{"record",RECORD}, {"repeat",REPEAT},{NULL,0}},  // Reserved words of size 6
    {{"program", PROGRAM},{NULL,0}}, // Reserved words of size 7
    {{"function", FUNCTION},{NULL,0}}, // Reserved words of size 8
    {{"procedure", PROCEDURE},{NULL,0}}  // Reserved words of size 9
};

void init_scanner(FILE *source_file, char source_name[], char date[])
{
    src_file = source_file;
    strcpy(src_name, source_name);
    strcpy(todays_date, date);

    /*******************
     initialize character table, this table is useful for identifying what type of character
     we are looking at by setting our array up to be a copy the ascii table.  Since C thinks of
     a char as like an int you can use ch in get_token as an index into the table.
     *******************/

}
BOOLEAN get_source_line(char source_buffer[])
{

    char print_buffer[MAX_SOURCE_LINE_LENGTH + 9];
    char source_buffer[MAX_SOURCE_LINE_LENGTH];  //I've moved this to a function parameter.  Why did I do that?
    static int line_number = 0;

    if (fgets(source_buffer, MAX_SOURCE_LINE_LENGTH, src_file) != NULL)
    {
        ++line_number;
        sprintf(print_buffer, "%4d: %s", line_number, source_buffer);
        print_line(print_buffer, src_name, todays_date);
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }

}

Token* get_token()
{

    char ch; //This can be the current character you are examining during scanning.
    char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    char *token_ptr = ???; //write some code to point this to the beginning of token_string
    ???;  //I am missing the most important variable in the function, what is it?  Hint: what should I return?

    //1.  Skip past all of the blanks
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
    //3.  Call the appropriate function to deal with the cases in 2.

    return ???; //What should be returned here?
}


static char get_char(char *currLine)
{
    /*
     If at the end of the current line (how do you check for that?),
     we should call get source line.  If at the EOF (end of file) we should
     set the character ch to EOF and leave the function.
     */

    /*
     Write some code to set the character ch to the next character in the buffer
     */
}

static ??? skip_blanks(???)
{
    /*
     Write some code to skip past the blanks in the program and return a pointer
     to the first non blank character
    */


}

static ??? skip_comment(???)
{
    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
    */
}

//needs a return. What is it?
static ??? get_word(char *currLine)
{
    /*
     Write some code to Extract the word
    */

    //This first part might go into token, not sure
    char *en=strchr(currLine, ' ');
    int index=(int)(en-currLine);
    char *foundWord;    //foundWord is the extracted word
    strncpy(foundWord, currLine, index);    //makes a substring from 0 to the index of the space

    //Downshift the word, to make it lower case
    foundWord=downshift_word(foundWord); //send foundWord to downshift_word and overwrite foundWord to the lowercase

    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
    */
    if(is_reserved_word(foundWord)==FALSE){
        //needs body
        //it's an identifier
        //return something      PERHAPS pointer foundWord
    }else{
        //it's reserved
        //return something      PERHAPS pointer foundWord
    }
}

//I think this is done?
static double get_number(char *currLine)
{
    /*
     Write some code to Extract the number and convert it to a literal number.
    */

    //This first part might go into token, not sure
    char *en=strchr(currLine, ' ');
    int index=(int)(en-currLine);
    char *foundNum;    //foundWord is the extracted word
    strncpy(foundNum, currLine, index);    //makes a substring from 0 to the index of the space

    double d;       //set up the double variable
    char *Ptr;      //declare the Pointer where d is saved to

    d=strtod(foundNum, &Ptr);       //put the value at Ptr to the variable d

    return d;       //return the double

}

//I think this is done?
static char * get_string(char *currLine)
{
    /*
     Write some code to Extract the string
    */
    char *first=strchr(currLine, '\"');
    int index=(int)(first-currLine);
    printf("%d\n",index);
    char *second=strchr(currLine+index+1, '\"');
    int index2=(int)(second-currLine);
    printf("%d\n",index2);

    char *theString;
    strncpy(theString, currLine+index+1, index2-index);
    theString[index2-index-1]='\0';

    return theString;

}
static ??? get_special(???)
{
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
    */
}

//It's done. However, The puts needs to be there for some reason I dont understand
static char * downshift_word(char *sentWordPtr)
{
    /*
     Make all of the characters in the incoming word lower case.
    */
    char cr[MAX_SOURCE_LINE_LENGTH];    //make an array
    int i=0;
    while(*sentWordPtr!=NULL){          //while the character in the string is not \0
        cr[i]=tolower(*sentWordPtr);    //build the array of lowercase characters
        ++i;
        ++sentWordPtr;
    }
    cr[i]='\0';                         //null character to the end of the array
    sentWordPtr=cr;                     //sentWordPtr is set to the position of the new array
    puts(sentWordPtr);                  //IDK why, but it is here
    return sentWordPtr;                 //return the pointer
}
static BOOLEAN is_reserved_word(???)
{
    /*
     Examine the reserved word table and determine if the function input is a reserved word.
    */
    return FALSE;
}

