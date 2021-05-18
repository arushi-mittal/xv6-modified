
The benchmark.c file is used to create processes.
The time command gives the time used by each 
scheduler (wait time + run time = total time) 
shown below.


RR Run Time = 2000 + 7 = 2007

PBS Time = 2002 + 5 = 2007

FCFS Time = 2873

MLFQ Time = 2015

FCFS was the worst performing scheduler. PBS and RR had 
identical performance but RR had lesser wait time. MLFQ was
comparable to RR and PBS but slightly worse.
