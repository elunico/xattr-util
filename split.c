//
// Created by Thomas Povinelli on 10/16/22.
//

#include "split.h"
#include <string.h>
#include <stdlib.h>

struct split_result* /* NEEDS FREE */ split (char* string, char delim, int limit)
{
    int count = 0;

    struct split_result* result = calloc (sizeof (*result), 1);


    char* start = string;
    while (*string)
    {
        if (count == limit)
            break;
        
        if (*string == delim)
        {
            char old = *string;
            *string = '\0';
            char* token = strdup (start);
            *string = old;
            start = string + 1;

            struct split_result_element* elm = malloc (sizeof (*elm));
            elm->string = token;
            elm->index = count;
            elm->next = NULL;

            if (result->head == NULL)
            {
                result->head = elm;
                result->tail = elm;
            } else
            {
                result->tail->next = elm;
                result->tail = result->tail->next;
            }
            count++;
        }
        string++;
    }
    result->current = 0;
    result->total = count;
    return result;
}

void free_split_result (struct split_result* result)
{
    struct split_result_element* start = result->head;
    while (start!= NULL) {
        if (start->string != NULL) {
            free(start->string);
        }
        struct split_result_element* next = start->next;
        free(start);
        start = next;
    }
    free(result);
}