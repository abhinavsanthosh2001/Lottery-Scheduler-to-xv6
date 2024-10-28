#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"
#include "spinlock.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/* The following code is added/modified by your Kamal and kxv230005
** System call to set the number of tickets for a process.
*/

int
sys_settickets(void)
{
  int n;
  // Get the number of tickets from the user
  if(argint(0, &n) < 0)
    return -1;

  // Check if the number of tickets is valid
  if(n < 1)
    return -1;

  // Set the number of tickets for the process
  proc->tickets = n;
  return 0;
}

/* End of code added/modified */

/* The following code is added/modified by your Abhinav and axs230311
** System call to get the process statistics.
*/

int
sys_getpinfo(void)
{
  struct pstat *ps;

  // Get the pstat structure from the user
  if(argptr(0, (void*)&ps, sizeof(*ps)) < 0 || ps == NULL)
    return -1;
  
  // Get the process statistics
  acquire(&ptable.lock);
  int i;
  for(i = 0; i < NPROC; i++) {
    ps->inuse[i] = (ptable.proc[i].state != UNUSED);
    ps->tickets[i] = ptable.proc[i].tickets;
    ps->pid[i] = ptable.proc[i].pid;
    ps->ticks[i] = ptable.proc[i].ticks;
  }
  release(&ptable.lock);

  return 0;
}

/* End of code added/modified */


