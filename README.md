# Lottery Scheduler for xv6

## Overview
This project implements a Lottery Scheduler for the xv6 operating system. The scheduler is a probabilistic CPU scheduling algorithm where each process is assigned a certain number of tickets. A random lottery determines which process runs next, with the probability of selection based on the number of tickets a process holds. This project replaces the default Round Robin scheduler in xv6.

## Objectives
- Gain deeper understanding of the xv6 kernel.
- Implement a lottery scheduler by modifying the scheduler code in `proc.c`.
- Add system calls to set the number of tickets and retrieve process statistics.
- Generate a graph illustrating the proportional CPU allocation among processes.

## Features
1. **Lottery Scheduling**: Processes receive a portion of the CPU in proportion to the number of tickets assigned.
2. **Ticket Assignment System Call**: `int settickets(int num)` sets the number of tickets for the calling process.
3. **Process Statistics System Call**: `int getpinfo(struct pstat *p)` retrieves statistics on process execution.

## Testing
1. Multiple Test case files added to the users directory to test the lottery scheduler

## Graph Generation
1. Run the scheduler with three processes having tickets in a 3:2:1 ratio.
2. Record the results of time slices received by each process.
3. Plot a graph illustrating CPU allocation over time to verify the proportionality of the lottery scheduler.
