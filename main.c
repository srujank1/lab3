//
//  main.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include <stdio.h>
#include "common.h"
#include "print.h"
#include "scanner.h"

FILE *init_lister(const char *name, char source_file_name[], char dte[]);
void quit_scanner(FILE *src_file, Token *list);
void add_token_to_list(Token *list, Token *new_token);
static int c;


int main(int argc, const char * argv[])
{


    Token *token;
    Token *token_list; //This needs to be implemented as a linked list in scanner.h.
    char source_name[MAX_FILE_NAME_LENGTH];
    char date[DATE_STRING_LENGTH];
    FILE *source_file = init_lister(argv[1], "NEWTON.PAS", date);
    init_scanner(source_file, source_name, date);

   do
    {
        c++;
        token = get_token();
        add_token_to_list(token_list, token);
        print_token(token);
    }
    while (token != NULL);//What is the sentinal value that ends this loop?

    quit_scanner(source_file, token_list);
    return 0;
}


void add_token_to_list(Token *list, Token *new_token)
{
    // Add new_token to the list knowing that list is a linked list.

    if(list == NULL)
    {

        list= new_token;
        list->next=NULL;
    }
    else
    {
        NEXT = list;
        for( i= 1; i < c ; i++)
        {
            PREV =NEXT;
            NEXT=NEXT->next;
        }

        PREV->next = new_token;

        //new_token->next = list;
        //list = new_token;
    }


}


void quit_scanner(FILE *src_file, Token *list)
{
    Token *NEXT;

    while (list != NULL)
    {
            NEXT = list;
            list = list->next;
            free(NEXT);
    }

    fclose(src_file);
}


FILE *init_lister(const char *name, char source_file_name[], char dte[])
{
    time_t timer;
    FILE *file;

    //strcpy(source_file_name, name);
    file = fopen(source_file_name, "r");
    time(&timer);
    strcpy(dte, asctime(localtime(&timer)));
    return file;
}

