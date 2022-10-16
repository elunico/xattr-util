//
// Created by Thomas Povinelli on 10/16/22.
//

#ifndef XATTR_UTIL_TRIM_H
#define XATTR_UTIL_TRIM_H

struct split_result_element
{
    char *string;
    int index;
    struct split_result_element* next;
};

struct split_result
{
    int total;
    int current;
    struct split_result_element* head;
    struct split_result_element* tail;
};

struct split_result* /* NEEDS FREE */ split (char* string, char delim, int limit);

#endif //XATTR_UTIL_TRIM_H
