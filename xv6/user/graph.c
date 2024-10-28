/* The following code is added/modified by your Kamal and kxv230005
** Code for testing number of ticks for different processes with 3:2:1 tickets.
** We use the results obtained by this to plot out graph.
*/

#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

#define NEWPROC 3
#define TICKETS_A 30
#define TICKETS_B 20
#define TICKETS_C 10

// function for spin
void spin() {
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < 50; ++i){
		for(j = 0; j < 1000000; ++j){
			k = j % 10;
			k = k + 1;
		}
	}
}

int main(int argc, char *argv[]) {
   struct pstat st;
   int pid[NPROC];
   int tickets[NEWPROC] = {TICKETS_A, TICKETS_B, TICKETS_C};
   int i;

   printf(1,"Starting processes...\n");
   for (i = 0; i < NEWPROC; i++) {
        pid[i] = fork();
        if (pid[i] == 0) {
            settickets(tickets[i]);
            spin();
            exit();
        }
   }

   // Let the processes run for a while
   sleep(500);

   if (getpinfo(&st) != 0) {
        printf(1,"Error getting process info\n");
        exit();
   }

   printf(1, "\n**** PInfo ****\n");
   for(i = 0; i < NPROC; i++) {
      if (st.inuse[i]) {
         printf(1,"pid: %d tickets: %d ticks: %d\n", st.pid[i], st.tickets[i], st.ticks[i]);
      }
   }
   
   for (i = 0; i < NEWPROC; i++) {
        kill(pid[i]);
   }

   while (wait() > 0);

   printf(1,"Processes terminated.\n");
   exit();
}

/* End of code added/modified */