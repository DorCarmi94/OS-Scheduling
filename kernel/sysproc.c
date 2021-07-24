#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"




void printTrace(int shiftNum, char* sysName, int retVal)
{
  int pmask;
  int checkTrace;
  
  struct proc *p = myproc();

  pmask=p->print_mask;
  checkTrace=1;
  checkTrace=checkTrace<<shiftNum;
  checkTrace=checkTrace&pmask;
  
    if(p->print_mask!=0)
    {
      if(checkTrace)
      {
        printf("%d: syscall %s -> %d\n",p->pid,sysName,retVal);
      }
    }
}


uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
  {
    return -1;
  }
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  int ans=myproc()->pid;
  return ans;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
  {
    return -1;
  }
  int ans=wait(p);
  return ans;
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  struct proc *p;
  int pmask;

  p = myproc();
  pmask=p->print_mask;

  if(argint(0, &n) < 0){
    if(pmask!=0)
    {
      if((1 << SYS_sbrk) & pmask)
      {
        printf("%d: syscall sbrk %d -> %d\n",p->pid, n, -1);
      }
    }
    return -1;
  }
  addr = myproc()->sz;
  if(growproc(n) < 0){
    if(pmask!=0)
    {
      if((1 << SYS_sbrk) & pmask)
      {
        printf("%d: syscall sbrk %d -> %d\n",p->pid, n, -1);
      }
    }
    return -1;
  }

  if(pmask!=0)
  {
    if((1 << SYS_sbrk) & pmask)
    {
      printf("%d: syscall sbrk %d -> %d\n",p->pid, n, addr);
    }
  }
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
  {
    return -1;
  }
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_trace(void)
{
  int mask;
  int pid;
  if(argint(0, &mask) < 0){
    return -1;
  }
  if(argint(1,&pid)<0)
  {
    return -1;
  }
  int ans = trace(mask,pid);
  return ans;
}

uint64
sys_set_priority(void)
{
  int priority;

  if(argint(0, &priority) < 0)
    return -1;
  return set_priority(priority);
}

uint64
sys_wait_stat(void)
{
  uint64 p;
  uint64 performance;
  
  if(argaddr(0, &p) < 0)
  {
    return -1;
  }
  if(argaddr(1, &performance) < 0)
  {
    return -1;
  }

  int ans=wait_stat((uint64)p,(struct perf*)&performance);
  return ans;
}