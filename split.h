//
// Created by Thomas Povinelli on 10/16/22.
//

#ifndef XATTR_UTIL_TRIM_H
#define XATTR_UTIL_TRIM_H

struct split_result_element
{
    char* string;
    int index;
    struct split_result_element* next;
};

struct split_result
{
    int total;
    struct split_result_element* current;
    struct split_result_element* head;
    struct split_result_element* tail;
};

struct split_result* /* NEEDS FREE */ split (char* string, char delim, int limit);

struct split_result_element* split_result_next(struct split_result* result);

void free_split_result (struct split_result* result);

#endif //XATTR_UTIL_TRIM_H
