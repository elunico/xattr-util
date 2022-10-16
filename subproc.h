//
// Created by Thomas Povinelli on 10/16/22.
//

#ifndef XATTR_UTIL_SUBPROC_H
#define XATTR_UTIL_SUBPROC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define NEEDS_FREE

struct proc_result
{
    char* output;
    int retval;
};

void child_handler (int sig);

struct proc_result* NEEDS_FREE get_proc_result (char* output, char* args[], int argc);

void free_proc_result (struct proc_result* result);

#endif //XATTR_UTIL_SUBPROC_H
