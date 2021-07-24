#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"


void someCode()
{
int i=0;
   int count=0;
   int newPid=fork();
   if(newPid==0)
   {
       //Child
       //sleep(5);
       sleep(5);
       for(i=0;i<__INT32_MAX__;i++)
       {
           count++;
       }
       sleep(1);
       fprintf(2,"I am the child\n");
       exit(0);
   }
   else
   {
        //Father
        //int waitAns=wait(&newPid);
        //fprintf(2,"Wait ans is: %d\n",waitAns);
        
        struct perf myperf;
        //struct perf* myPerfPtr=&myperf;
        struct perf* myperptr=&myperf;
        myperptr->ctime=333;
        fprintf(2,"User pref address: %d\n",&myperf);
        int ans=wait_stat(&newPid,&myperf);
        
        
        fprintf(2,"Ctime:%d\n",myperptr->ctime);
        fprintf(2,"Ttime:%d\n",myperptr->ttime);
        fprintf(2,"Stime:%d\n",myperptr->stime);
        fprintf(2,"Retime:%d\n",myperptr->retime);
        fprintf(2,"Rutime:%d\n",myperptr->rutime);
        fprintf(2,"Ans:%d\n",ans);
        exit(0);
   }
   

    fprintf(2,"Hello tomer\n");

    int status=5;
    int waitAns=wait(&status);
    fprintf(2,"Wait ans: %d",waitAns);

    struct perf myperf;
    struct perf* myPerfPtr=&myperf;
    
    int ans=wait_stat(&status,&myperf);
    fprintf(2,"Ctime:%d\n",myPerfPtr->ctime);
    fprintf(2,"Ttime:%d\n",myPerfPtr->ttime);
    fprintf(2,"Stime:%d\n",myPerfPtr->stime);
    fprintf(2,"Retime:%d\n",myPerfPtr->retime);
    fprintf(2,"Rutime:%d\n",myPerfPtr->rutime);
    fprintf(2,"Bursttime:%d\n",myPerfPtr->average_bursttime);
    fprintf(2,"Ans:%d\n",ans);
    wait(&status);
    ans=wait_stat(&status,&myperf);
    fprintf(2,"Ctime:%d\n",myPerfPtr->ctime);
    fprintf(2,"Ttime:%d\n",myPerfPtr->ttime);
    fprintf(2,"Stime:%d\n",myPerfPtr->stime);
    fprintf(2,"Retime:%d\n",myPerfPtr->retime);
    fprintf(2,"Rutime:%d\n",myPerfPtr->rutime);
    fprintf(2,"Bursttime:%d\n",myPerfPtr->average_bursttime);
    fprintf(2,"Ans:%d\n",ans);
    
    exit(0);
}


void testForFCFS()
{
    fprintf(2,"Welcome to tomer's show\n");
    int i=0;
    int kidA=fork();
    int kidB;
    if(kidA==0)
    {
        for (i = 0; i < __INT16_MAX__; i++)
        {
            fprintf(2,"A");
        }
        
    }
    else
    {
        //Father
        sleep(1);
        kidB=fork();
        if(kidB==0)
        {
            //kidB
            for (i = 0; i < __INT16_MAX__; i++)
            {
                fprintf(2,"B");
            }
        }
        else
        {
            wait(&kidB);
        }
        wait(&kidA);
        fprintf(2,"\nFather finished\n");
        

    }
}

void test3()
{
    struct perf perfF;
    struct perf perfS;
    int slowChild;
    int fastChild;
    slowChild=fork();
    if(slowChild==0)
    {
        //In the slow child
        for (int i = 0; i < __INT32_MAX__; i++)
            {
                fprintf(2,"S");
            }
    }
    else
    {
        //Father
        fastChild=fork();
        if(fastChild==0)
        {
            //In fast child
            for (int i = 0; i < __INT16_MAX__; i++)
            {
                fprintf(2,"F");
            }
        }
        else
        {
            //Father
            wait_stat(&fastChild, &perfF);
        }
        wait_stat(&slowChild, &perfS);
    }

    fprintf(2,"Hello tomer!");
    exit(0);
}

void generalSchedCheck()
{
     struct perf perfMeyuhas;
    struct perf perfBur;
    int BurVeAmHaaretz;
    int Meyuhas;
    Meyuhas=fork();
    if(Meyuhas==0)
    {
        sleep(1);
        //In the slow child
        //set_priority(2);
        for (int i = 0; i < __INT16_MAX__; i++)
        {
            fprintf(2,"$");
        }
        exit(0);
    }
    else
    {
        //Father
        BurVeAmHaaretz=fork();
        if(BurVeAmHaaretz==0)
        {
            //In bur child
            //set_priority(2);
            for (int i = 0; i < __INT16_MAX__; i++)
            {
                fprintf(2,"!");
                
            }
            exit(0);
        }
        else
        {
            //Father
            wait_stat(&BurVeAmHaaretz, &perfBur);
        }
        wait_stat(&Meyuhas, &perfMeyuhas);
    }

    fprintf(2,"Hello tomer!");
    exit(0);
}


void testTrace()
{
    //
    int mask=  (1<<SYS_fork) | (1<<SYS_kill) | (1<<SYS_sbrk) |(1<<SYS_exit)|(1<<SYS_wait) |(1<<SYS_getpid);
    trace(mask,getpid());
    int pr=fork();
    if(pr==0)
    {
        trace(mask,getpid());
        fprintf(2,"I am the child\n");
        sbrk(4096);
        kill(getpid());
        exit(0);
    }
    else
    {
        wait(&pr);
    }
    sleep(1);
    exit(0);
}

int main(int argc, char** argv)
{
    someCode();
    //testTrace();
   //generalSchedCheck();
   exit(0);
}