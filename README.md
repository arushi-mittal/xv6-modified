## OSN Assignment 5: CPU Scheduling Algorithms

### Description:

Add the `waitx` system call to update the creation time, end time and total run time of a process.

Add the `ps` user command, which, given a process ID, shows information about it such as PID, priority, state, runtime, wait time, times run, current queue, etc.

Add schedulers which can be set using the `SCHEDULER` flag. 

Add `RR` (default), `FCFS`, `PBS` with functions to change the priority of a process, and `MLFQ` with the ability to change priority and promote or demote a process to 5 different queues accordingly.   

### waitx:

The `waitx` system call modifies `defs.h`, `syscall.c`, `syscall.h`, `sysproc.c`, 
`user.h` and `usys.S` to add the system call.

The `waitx` function is added in `proc.c` to execute the waitx system call
using the `time.c` file. This file sends 2 pointers to the waitx call to 
store wait time and run time and displays.

In `proc.h` we added `ctime`, `etime`, `iotime` and `rtime` to store start time, 
end time, I/O time and run time of the file. In `allocproc` function in
`proc.c` we set the initial values of these fields. In `proc.c` these 
values are updated and used to calculate the wait and run time.

### ps:

The `ps` system call was added similarly to `waitx`. It is a void function 
taking no values but for MLFQ it displays additional fields. It simply
accesses the fields of all the processes and displays them by looping
over the process table. It is implemented in `ps.c`.

### set_priority:

It is implemented like `waitx` and `ps` to create a system call from the 
`set_priority.c` file. It searches for the process whose pid matches
the one entered and makes the needed changes. In `allocproc()` the 
default priority for all processes is set to `60`.

### Schedulers:

The schedulers are implemented in `proc.c` and `trap.c` mainly.

#### RR:
This is the default policy used, no changes made here.

#### FCFS:
The start time of each process is checked and once the process with 
lowest time is found it is executed. It does not yield in the `trap.c`
file to ensure FCFS is followed.

#### PBS:

A new field priority is added in `proc` struct. The process with the 
highest priority is found after looping through the ptable and is 
executed. If it is not the only one, it yields and another process 
with equal or higher priority takes its place because of the yield
function and round robin scheduler.

#### MLFQ:

We create an array of queues where all processes are stored. We add
the fields queue, ticks, enter, change to implement MLFQ.

Whenever a process exceeds the time in `qticks`, it is removed from the
present queue and sent to a lower queue, unless it is the lowest queue. 
However, if it has been there for more than `30` ticks, it is removed and 
sent to a higher queue. `Addq` and `remq` add and remove a process from the 
queue specified. Incr increases the clock ticks and changeq reassigns the 

The `userinit`, `fork`, `kill`, `wakeup1`, `yield`, `wait`, `waitx` functions are changed
as well to ensure MLFQ executes correctly. In `trap.c` we check if a process
exceeds its time slice to cause it to yield.'

### Report

Analyze the difference between the different schedulers and use a benchmark function to determine which one is fastest.


## **Original README**




NOTE: we have stopped maintaining the x86 version of xv6, and switched
our efforts to the RISC-V version
(https://github.com/mit-pdos/xv6-riscv.git)

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern x86-based multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)). See also https://pdos.csail.mit.edu/6.828/, which
provides pointers to on-line resources for v6.

xv6 borrows code from the following sources:
    JOS (asm.h, elf.h, mmu.h, bootasm.S, ide.c, console.c, and others)
    Plan 9 (entryother.S, mp.h, mp.c, lapic.c)
    FreeBSD (ioapic.c)
    NetBSD (console.c)

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by Silas
Boyd-Wickizer, Anton Burtsev, Cody Cutler, Mike CAT, Tej Chajed, eyalz800,
Nelson Elhage, Saar Ettinger, Alice Ferrazzi, Nathaniel Filardo, Peter
Froehlich, Yakir Goaron,Shivam Handa, Bryan Henry, Jim Huang, Alexander
Kapshuk, Anders Kaseorg, kehao95, Wolfgang Keller, Eddie Kohler, Austin
Liew, Imbar Marinescu, Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi
Merimovich, Mark Morrissey, mtasm, Joel Nider, Greg Price, Ayan Shafqat,
Eldar Sehayek, Yongming Shen, Cam Tenny, tyfkda, Rafael Ubal, Warren
Toomey, Stephen Tu, Pablo Ventura, Xi Wang, Keiichi Watanabe, Nicolas
Wolovick, wxdao, Grant Wu, Jindong Zhang, Icenowy Zheng, and Zou Chang Wei.

The code in the files that constitute xv6 is
Copyright 2006-2018 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

We don't process error reports (see note on top of this file).

BUILDING AND RUNNING XV6

To build xv6 on an x86 ELF machine (like Linux or FreeBSD), run
"make". On non-x86 or non-ELF machines (like OS X, even on x86), you
will need to install a cross-compiler gcc suite capable of producing
x86 ELF binaries (see https://pdos.csail.mit.edu/6.828/).
Then run "make TOOLPREFIX=i386-jos-elf-". Now install the QEMU PC
simulator and run "make qemu".
