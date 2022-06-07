# xv6-bosted-lottery-scheduling
In this project, I modify xv6 to schedule processes using lottery scheduling. Further, the scheduler will boost the priority of sleeping processes so they get their fair share of CPU time.


## Basic Lottery Scheduler
Lottery SchedulingLinks to an external site. is a proportional share policy which fixes this by asking users to grant tickets to processes. The scheduler holds a lottery every tick to determine the next process. Since important processes are given more tickets, they end up running more often on the CPU over a period of time.

In scheduler, each process runs for an entire tick until interrupted by the xv6 timer. At each tick, the scheduler holds a lottery between RUNNABLE processes and schedules the winner. When a new process arives, it should have the same number of tickets as its parent. The first process of xv6 should start with 1 ticket. You will also create a system call settickets(int pid, int tickets), to change the number of tickets held by the specified process.

As an example, if there is a process A with 1 ticket and process B with 4 tickets, this is what the timeline might look like:

timer tick	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20
scheduled	  B	B	A	B	B	B	B	B	B	A	  A	  B	  B	  B	  A	  B	  B	  B	  B	  B

## Compensating processes for blocking
Many schedulers contain some type of incentive for processes with no useful work to sleep (or block) and voluntarily relinquish the CPU so another process can run; this improves overall system throughput since the process isn't wastefully holding on to the CPU doing nothing.  To provide this incentive, your scheduler will track the number of ticks a process was sleeping. Once it's runnable, it will boost (double) the number of tickets for the same number of ticks. For instance, if a process slept for 5 ticks, its tickets would be artificially doubled for the next 5 lotteries it participates in.

Example 1: a process A has 1 ticket and B has 4 tickets. Process A sleeps for 2 ticks, and is therefore given double tickets for the next 2 lotteries after it wakes. This allows the scheduler to keep the CPU usage ratio equal to the ratio of tickets, even when process A is blocked. The timeline could look like the following in this case (description below the timeline):

imer tick	        1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20
scheduled	        B	A	B	B	B	A	A	B	B	B	  B	  B	  B	  A	  B	  B	  B	  B	  B	  B
sleeping/blocked			        A	A											  A	  A				
A lottery tickets	1	1	-	-	2	2	1	1	1	1	  1	  1	  1	  1	  -	  -	  2	  2	  1	  1
B lottery tickets	4	4	4	4	4	4	4	4	4	4	  4	  4	  4	  4	  4	  4	  4	  4	  4	  4
