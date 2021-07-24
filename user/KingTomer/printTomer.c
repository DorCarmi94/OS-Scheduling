#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"

int main(int argc, char** argv)
{
    trace(1<<SYS_fork,getpid());
    int newPid= fork();
    if(newPid!=0)
    {
        int status;
        wait(&status);
        fprintf(2,"Child %d finished\n",newPid);
    }
    else
    {
        fprintf(2,"Child running\n");
    }
    
    fprintf(2,"Hello tomer\n");
    exit(0);
}