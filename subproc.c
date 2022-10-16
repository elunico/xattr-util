//
// Created by Thomas Povinelli on 10/16/22.
//

#include "subproc.h"
#include <signal.h>

#ifdef __APPLE__
typedef struct fd_set fd_set;
#endif

static int child_living = 0;

void child_handler(int sig)
{
    child_living = 0;
}

struct proc_result *get_proc_result(char *cmd, char *args[], int argc)
{
    int p[2] = {0, 0}, retval = -1;
    pid_t pid;
    int const BUF_SIZE = 65535;
    char *buf = calloc(sizeof(char), (BUF_SIZE + 1));

    int curSize = BUF_SIZE;
    char *complete_output = calloc(sizeof(char), curSize + 1);
    int curIndex = 0;

    pipe(p);
    child_living = 1;
    if ((pid = fork()) == 0)
    {
        // child

        char **arguments = calloc(sizeof(char *), argc + 2);

        arguments[0] = cmd;
        for (int i = 0; i < argc; i++)
            arguments[i + 1] = args[i];

        arguments[argc + 1] = NULL;

        close(STDOUT_FILENO);
        dup(p[1]);
        close(STDERR_FILENO);
        dup(p[1]);

        execvp(cmd, arguments);
    }
    else
    {
        fd_set desc = {0};
        FD_SET(p[0], &desc);

        struct timeval tmout = {0};
        tmout.tv_sec = 1;

        while (child_living && select(p[0] + 1, &desc, NULL, NULL, &tmout) > 0)
        {
            if (curIndex >= curSize)
            {
                char *newone = calloc(sizeof(char), curSize * 2);
                memcpy(newone, complete_output, curSize);
                free(complete_output);
                curSize *= 2;
                complete_output = newone;
            }
            if (FD_ISSET(p[0], &desc))
            {
                int count = read(p[0], buf, BUF_SIZE);
                memcpy(complete_output, buf, count);
                curIndex += count;
            }
        }

        waitpid(pid, &retval, WNOHANG);
    }
    struct proc_result *result = calloc(sizeof(struct proc_result), 1);
    result->output = complete_output;
    result->retval = retval;
    free(buf);
    return result;
}

void free_proc_result(struct proc_result *result)
{
    free(result->output);
    free(result);
}
