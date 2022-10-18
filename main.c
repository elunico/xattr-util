//
// Created by Thomas Povinelli on 10/15/22.
//
#include <signal.h>
#include <stdio.h>
#include "subproc.h"
#include "split.h"

int main (int argc, char const* argv[])
{
    signal (SIGCHLD, child_handler);

    char* args[] = { "giant-file.txt" };
    struct proc_result* attrs = get_proc_result ("cat", args, 1);
    puts (attrs->output); // ("%s\n", attrs->output);

//    struct split_result* result = split (attrs->output, '\n', -1);

//    struct split_result_element* tok = result->head;
//    while (tok != NULL)
//    {
//        printf ("%s, ", tok->string);
//        tok = tok->next;
//    }

    free_proc_result (attrs);
//    free_split_result (result);

}
