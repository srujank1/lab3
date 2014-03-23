//
//  scanner.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include <ctype.h>

/*******************
Static functions needed for the scanner
You need to design the proper parameter list and
return types for functions with ???.
******************/

//need to dertermine returns
static char get_char();
static void skip_comment();
static void skip_blanks();
static char* get_word(); //still need to work this out
static char* get_number();
static char* get_string();
static char* get_special();
static void downshift_word(char* lower);
static BOOLEAN is_reserved_word(char* sentWord);
static void initSourceLine();

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

static char *theSourceLine="";
static char theSourceLineArray[MAX_SOURCE_LINE_LENGTH];


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

static void initSourceLine(){
theSourceLineArray[MAX_SOURCE_LINE_LENGTH];
theSourceLine=theSourceLineArray;

}

BOOLEAN get_source_line()
{

   char print_buffer[MAX_SOURCE_LINE_LENGTH + 9];
   //char source_buffer[MAX_SOURCE_LINE_LENGTH];
   static int line_number = 0;

   if (fgets(theSourceLineArray, MAX_SOURCE_LINE_LENGTH, src_file) != NULL)
   {
       initSourceLine();
       ++line_number;
       sprintf(print_buffer, "%4d: %s", line_number, theSourceLine);
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
   Token* tk=(Token*)malloc(sizeof(Token));
   RwStruct w;
   //where to store the taken line


   skip_blanks(theSourceLine);
   //1.  Skip past all of the blanks
   if(strlen(theSourceLine)<=1){
       if(!get_source_line()){
           ch=EOF;

       }
   }
   else
   {
      skip_blanks(theSourceLine);
       ch=get_char(theSourceLine);
   }


   //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
   //3.  Call the appropriate function to deal with the cases in 2.

   if(ch=='{'){
       skip_comment(theSourceLine);
       skip_blanks(theSourceLine);
       ch=get_char(theSourceLine);
   }

   if (isalpha(ch)!=0) {

       token_ptr=get_word(theSourceLine);
       tk->literal_value=token_ptr;
       tk->literal_type=REAL_LIT;
       if(strcmp(token_ptr, "program")==0){
           tk->token_code=PROGRAM;
       }
       else if(strcmp(token_ptr, "const" )==0){
           tk->token_code=CONST;
       }
       else if(strcmp(token_ptr, "var" )==0){
           tk->token_code=VAR;
       }
       else if(strcmp(token_ptr, "begin" )==0){
           tk->token_code=BEGIN;
        }
       else if(strcmp(token_ptr, "repeat" )==0){
           tk->token_code=REPEAT;
        }
        else if(strcmp(token_ptr, "if" )==0){
           tk->token_code=IF;
        }
        else if(strcmp(token_ptr, "then" )==0){
           tk->token_code=THEN;
        }
        else if(strcmp(token_ptr, "end" )==0){
           tk->token_code=END;
        }
        else if(strcmp(token_ptr, "else" )==0){
           tk->token_code=ELSE;
        }
        else if(strcmp(token_ptr, "until" )==0){
           tk->token_code=UNTIL;
        }
        else if(strcmp(token_ptr, "error" )==0){
           tk->token_code=ERROR;
        }
        else if(strcmp(token_ptr, "do" )==0){
           tk->token_code=DO;
        }
        else if(strcmp(token_ptr, "while" )==0){
           tk->token_code=WHILE;
        }
        else if(strcmp(token_ptr, "with" )==0){
           tk->token_code=WITH;
        }
        else if(strcmp(token_ptr, "not" )==0){
           tk->token_code=NOT;
        }
       else if(strcmp(token_ptr, "to" )==0){
           tk->token_code=TO;
        }
        else if(strcmp(token_ptr, "set" )==0){
           tk->token_code=SET;
        }
        else if(strcmp(token_ptr, "record" )==0){
           tk->token_code=RECORD;
        }
        else if(strcmp(token_ptr, "for" )==0){
           tk->token_code=FOR;
        }
        else if(strcmp(token_ptr, "in" )==0){
           tk->token_code=IN;
        }
        else if(strcmp(token_ptr, "goto" )==0){
           tk->token_code=GOTO;
        }
        else if(strcmp(token_ptr, "div" )==0){
           tk->token_code=DIV;
        }
        else if(strcmp(token_ptr, "ffile" )==0){
           tk->token_code=FFILE;
        }
        else if(strcmp(token_ptr, "function" )==0){
           tk->token_code=FUNCTION;
        }
        else if(strcmp(token_ptr, "and" )==0){
           tk->token_code=AND;
        }
        else if(strcmp(token_ptr, "array" )==0){
           tk->token_code=ARRAY;
        }
        else if(strcmp(token_ptr, "procedure" )==0){
           tk->token_code=PROCEDURE;
        }
        else if(strcmp(token_ptr, "type" )==0){
           tk->token_code=TYPE;
        }
        else if(strcmp(token_ptr, "packed" )==0){
           tk->token_code=PACKED;
        }
        else if(strcmp(token_ptr, "or" )==0){
           tk->token_code=OR;
        }
        else if(strcmp(token_ptr, "downto" )==0){
           tk->token_code=DOWNTO;
        }
        else if(strcmp(token_ptr, "case" )==0){
           tk->token_code=CASE;
        }
        else if(strcmp(token_ptr, "of" )==0){
           tk->token_code=OF;
        }

       else{
           tk->literal_type=REAL_LIT;
           tk->token_code=IDENTIFIER;
       }


   }else if (isdigit(ch)) {
       token_ptr=get_number(theSourceLine);
       tk->literal_value=token_ptr;
       tk->literal_type=INTEGER_LIT;
       tk->token_code=NUMBER;
   }else if(ch=='"'){
       token_ptr=get_string(theSourceLine);
       tk->literal_value=token_ptr;
       tk->literal_type=STRING_LIT;
       tk->token_code=STRING;
   }else if(ch==EOF){
       tk->token_code=END_OF_FILE;
   }else{
       token_ptr=get_special(theSourceLine);
       tk->literal_value=token_ptr;
       tk->literal_type=REAL_LIT;
       if(strcmp(token_ptr, "^")==0){
           tk->token_code=UPARROW;
       }else if(strcmp(token_ptr, "*")==0){
           tk->token_code=STAR;
       }else if(strcmp(token_ptr, "(")==0){
           tk->token_code=LPAREN;
       }else if(strcmp(token_ptr, ")")==0){
           tk->token_code=RPAREN;
       }else if(strcmp(token_ptr, "-")==0){
           tk->token_code=MINUS;
       }else if(strcmp(token_ptr, "+")==0){
           tk->token_code=PLUS;
       }else if(strcmp(token_ptr, "=")==0){
           tk->token_code=EQUAL;
       }else if(strcmp(token_ptr, "[")==0){
           tk->token_code=LBRACKET;
       }else if(strcmp(token_ptr, "]")==0){
           tk->token_code=RBRACKET;
       }else if(strcmp(token_ptr, ":")==0){
           tk->token_code=COLON;
       }else if(strcmp(token_ptr, ";")==0){
           tk->token_code=SEMICOLON;
       }else if(strcmp(token_ptr, "<")==0){
           tk->token_code=LT;
       }else if(strcmp(token_ptr, ">")==0){
           tk->token_code=GT;
       }else if(strcmp(token_ptr, ",")==0){
           tk->token_code=COMMA;
       }else if(strcmp(token_ptr, ".")==0){
           tk->token_code=PERIOD;
       }else if(strcmp(token_ptr, "/")==0){
           tk->token_code=SLASH;
       }else if(strcmp(token_ptr, ":=")==0){
           tk->token_code=COLONEQUAL;
       }else if(strcmp(token_ptr, "<=")==0){
           tk->token_code=LE;
       }else if(strcmp(token_ptr, ">=")==0){
           tk->token_code=GE;
       }else if(strcmp(token_ptr, "!=")==0){
           tk->token_code=NE;
       }else if(strcmp(token_ptr, "..")==0){
           tk->token_code=DOTDOT;
       }
       else
       {
           tk->token_code=NO_TOKEN;
       }

   }

   tk->next=NULL;


   return tk; //What should be returned here?
}

//I need to figure out what is being passsed to this
static char get_char()
{
   /*
    If at the end of the current line (how do you check for that?),
    we should call get source line.  If at the EOF (end of file) we should
    set the character ch to EOF and leave the function.
    */
    char c;
    if(theSourceLine[0]=='\0'){
       if(get_source_line(theSourceLine)==FALSE){
           return EOF;
       }
    }
    else
    {
        c=theSourceLine[0];
        return c;
    }
   // c=theSourceLine[0];

   /*
    Write some code to set the character ch to the next character in the buffer
    */


   // return c;
}

//done
static void skip_blanks()
{
   /*
    Write some code to skip past the blanks in the program and return a pointer
    to the first non blank character
   */
   while(theSourceLine[0]==' ' || theSourceLine[0]=='\t'){
       ++theSourceLine;
   }

}

//done
static void skip_comment()
{
   /*
    Write some code to skip past the comments in the program and return a pointer
    to the first non blank character.  Watch out for the EOF character.
   */
   do{
       ++theSourceLine;
   }while(theSourceLine[0]!='}');
   ++theSourceLine;
}

//needs a return. What is it?
static char* get_word()
{
   /*
    Write some code to Extract the word
   */
   char *en=strchrnul(theSourceLine, ' ');
   int index=(int)(en-theSourceLine);
   char *foundWord;    //foundWord is the extracted word
   foundWord=(char*)malloc(index+1);
   memcpy(foundWord, theSourceLine, index);    //makes a substring from 0 to the index of the space
   foundWord[index]='\0';

   int i=0;
   while(i<index){
       if(!isdigit(foundWord[i]) && !isalpha(foundWord[i])){
          foundWord[i]='\0';
          i=i+index;
       }
       ++i;
   }


   //Downshift the word, to make it lower case

   char *e=strchr(foundWord, '\0');
   int length=(int)(e-foundWord);
   char* lower;
   lower=(char*)malloc(length+1);
   memcpy(lower, foundWord, length);    //makes a substring from 0 to the index of the space
   /*if(isalpha(lower[length-1]) || isdigit(lower[length-1])){
       lower[length]='\0';
       theSourceLine=theSourceLine+length;
       downshift_word(lower); //send foundWord to downshift_word and overwrite foundWord to the lowercase


       //Write some code to Check if the word is a reserved word.
       //if it is not a reserved word its an identifier.

       free(foundWord);
       return lower;
   }
   int i=1;
   while(!isalpha(lower[length-i]) && !isdigit(lower[length-i])){
       ++i;
   }
   lower[length-i+1]='\0';
   */






   downshift_word(lower); //send foundWord to downshift_word and overwrite foundWord to the lowercase
   theSourceLine=theSourceLine+length;
   /*
    Write some code to Check if the word is a reserved word.
    if it is not a reserved word its an identifier.
   */
   free(foundWord);
   return lower;
}

//I think this is done?
static char* get_number()
{
   /*
    Write some code to Extract the number and convert it to a literal number.
   */
   char *en=strchrnul(theSourceLine, ' ');
   int index=(int)(en-theSourceLine);
   char *foundNum=0;    //foundWord is the extracted word
   foundNum=(char*)malloc(index+1);
   memcpy(foundNum, theSourceLine, index);    //makes a substring from 0 to the index of the space

   if(isalpha(foundNum[index-1]) || isdigit(foundNum[index-1])){
       foundNum[index]='\0';
       theSourceLine=theSourceLine+index;
       downshift_word(foundNum); //send foundWord to downshift_word and overwrite foundWord to the lowercase

       /*
       Write some code to Check if the word is a reserved word.
       if it is not a reserved word its an identifier.
       */
       return foundNum;
   }
   int i=1;
   while(!isalpha(foundNum[index-i]) && !isdigit(foundNum[index-i])){
       ++i;
   }
   foundNum[index-i+1]='\0';
   theSourceLine=theSourceLine+i+1;

   return foundNum;       //return the string actually It could return d, I'm not sure

}

//I think this is done
static char* get_string()
{
   /*
    Write some code to Extract the string
   */
   char *first=strchrnul(theSourceLine, '\"');
   int index=(int)(first-theSourceLine);
   char *second=strchrnul(theSourceLine+index+1, '\"');
   int index2=(int)(second-theSourceLine);

   char *theString=0;
   theString=(char*)malloc(index2-index);
   memcpy(theString, theSourceLine+index+1, index2-index-1);
   theString[index2-index]='\0';
   theSourceLine=theSourceLine+index2-index+1;


   return theString;

}

static char* get_special()
{
  /*
   Write some code to Extract the special token.  Most are single-character
   some are double-character.  Set the token appropriately.

  char temp[MAX_TOKEN_STRING_LENGTH];
  char chr=get_char();
  while(chr=='\n' || chr=='\r'){
      ++theSourceLine;
      chr=get_char();
  }

  temp[0]=chr;
  ++theSourceLine;
  int i=1;
  if(chr==':' || chr=='<' || chr=='>' || chr=='!' || chr=='.'){
      chr=theSourceLine[0];
      if(chr=='=' || chr=='.'){
          ++theSourceLine;
          ++i;
          temp[1]=chr;
          temp[2]='\0';
      }else{
          temp[1]='\0';
      }
  }

  char *foundWord;    //foundWord is the extracted word
  foundWord=(char*)malloc(i+1);
  memcpy(foundWord, temp, i);    //makes a substring from 0 to the index of the space
  foundWord[i]='\0';

  return foundWord;*/
    char temp[MAX_TOKEN_STRING_LENGTH];
    char chr=get_char();
    while(chr=='\n' || chr=='\r'){
        ++theSourceLine;
        chr=get_char();
    }
    int i=0;
    while(!isdigit(chr) && !isalpha(chr) && chr!=' ' && chr !='\n' && chr!='\r' && chr!='\0'){

        temp[i]=chr;

        ++i;
        ++theSourceLine;

        chr=get_char();
    }



    char *foundWord; //foundWord is the extracted word
    foundWord=(char*)malloc(i+1);
    memcpy(foundWord, temp, i); //makes a substring from 0 to the index of the space
    foundWord[i]='\0';

    return foundWord;
}





//done
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
   sentWordPtr=sentWordPtr-i;
   memcpy(sentWordPtr, cr, length);
}

static BOOLEAN is_reserved_word(char* sentWord)
{
   /*
    Examine the reserved word table and determine if the function input is a reserved word.
   */
   RwStruct w;
   int i=0;
   if(strlen(sentWord)<=7){
   w=rw_table[strlen(sentWord)-2][0];

       while(w.string!=NULL){
           if(strcmp(w.string, sentWord)==0){
               return TRUE;
           }

           ++i;
           w=rw_table[strlen(sentWord)-2][i];
       }

   }

   return FALSE;
}

