//
// Created by Thomas Povinelli on 10/15/22.
//
#include <signal.h>
#include <stdio.h>
#include "subproc.h"


int main (int argc, char const* argv[])
{
    signal (SIGCHLD, child_handler);

    char* args[] = { "main.py" };
    struct proc_result* attrs = get_proc_result ("xattr", args, 1);
    free_proc_result(attrs);

    printf ("%s\n", attrs->output);
}