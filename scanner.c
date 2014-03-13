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
static void skip_comment(char* line);
static void skip_blanks(char* line);
static ??? get_word(???); //still need to work this out
static double get_number(char* currLine);
static char* get_string(char* currLine);
static ??? get_special(???);
static void downshift_word(char* lower);
static BOOLEAN is_reserved_word(char* sentWord);

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
    char *token_ptr = &token_string; //write some code to point this to the beginning of token_string
    //I am missing the most important variable in the function, what is it?  Hint: what should I return?
    Token tk;
    //1.  Skip past all of the blanks
    token_ptr=skip_blanks(token_ptr);
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
    ch=getchar();
    //3.  Call the appropriate function to deal with the cases in 2.

    return tk; //What should be returned here?
}

//I need to figure out what is being passsed to this
static char get_char(char *currLine)
{
    /*
     If at the end of the current line (how do you check for that?),
     we should call get source line.  If at the EOF (end of file) we should
     set the character ch to EOF and leave the function.
     */
     if(currLine[0]=='\0'){
        if(get_source_line(currLine)==FALSE){
            return EOF;
        }
     }

    /*
     Write some code to set the character ch to the next character in the buffer
     */

     ++currLine;

     return currLine[0];
}

//done
static void skip_blanks(char* line)
{
    /*
     Write some code to skip past the blanks in the program and return a pointer
     to the first non blank character
    */
    while(line[0]==' '){
        ++line;
    }

}

//done
static void skip_comment(char* line)
{
    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
    */
    while(line[i]!='}'){
        ++line;
    }
}

//needs a return. What is it?
static ??? get_word(char *currLine)
{
    /*
     Write some code to Extract the word
    */
    char *en=strchr(currLine, ' ');
    int index=(int)(en-currLine);
    char *foundWord;    //foundWord is the extracted word
    foundWord=(char*)malloc(index+1);
    memcpy(foundWord, currLine, index);    //makes a substring from 0 to the index of the space
    foundWord[index]='\0';

    //Downshift the word, to make it lower case

    char *e=strchr(foundWord, '\0');
    int length=(int)(e-foundWord);
    char* lower;
    lower=(char*)malloc(length+1);
    memcpy(lower, foundWord, length);    //makes a substring from 0 to the index of the space
    lower[length]='\0';

    downshift_word(lower); //send foundWord to downshift_word and overwrite foundWord to the lowercase

    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
    */
    if(is_reserved_word(lower)==FALSE){
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
    char *en=strchr(currLine, ' ');
    int index=(int)(en-currLine);
    char *foundNum=0;    //foundWord is the extracted word
    foundNum=(char*)malloc(index+1);
    memcpy(foundNum, currLine, index);    //makes a substring from 0 to the index of the space
    foundNum[index]='\0';

    double d;       //set up the double variable
    char *Ptr;      //declare the Pointer where d is saved to

    d=strtod(foundNum, &Ptr);       //put the value at Ptr to the variable d

    return d;       //return the double

}

//I think this is done
static char* get_string(char *currLine)
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

    char *theString=0;
    theString=(char*)malloc(index2-index);
    memcpy(theString, currLine+index+1, index2-index-1);
    theString[index2-index]='\0';

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
static void downshift_word(char *sentWordPtr)
{
    /*
     Make all of the characters in the incoming word lower case.
    */
    char *en=strchr(sentWordPtr, '\0');
    int length=(int)(en-sentWordPtr);
    char cr[length+1];    //make an array
    int i=0;
    while(*sentWordPtr!='\0'){          //while the character in the string is not \0
        cr[i]=tolower(*sentWordPtr);    //build the array of lowercase characters
        ++i;
        ++sentWordPtr;
    }
    cr[length]='\0';                         //null character to the end of the array
    //puts(cr);                  //IDK why, but it is here
    sentWordPtr=sentWordPtr-52;
    memcpy(sentWordPtr, cr, length);
}
static BOOLEAN is_reserved_word(char* sentWord)
{
    /*
     Examine the reserved word table and determine if the function input is a reserved word.
    */
    return FALSE;
}

