# CP386 Assignment 4: Banker's Algorithm

## Description
This program implements the Banker's Algorithm and simulates a banking machine, where the banker maintains track of the resources and clients (the user) can request for more or less resources from the banker. The banker onlys grant a request if it satisfies the safety algorithm. If a request does not leave the system in a safe state, the banker denies it.

***

## Motivation
To understand deadlock avoidance and practice the implementation of the Banker's Algorithm.
***

## Screenshots
![screenshot1](/img/screenshot01.png "Screenshot 1")
![screenshot2](/img/screenshot02.png "Screenshot 2")

***

## Installation
1. Download and unpack the repository into a directory of your choice.
2. Start up a terminal and enter the directory you have chosen.
3. Rename the file *makefile.mk* to *makefile*.
    - ```mv makefile.mk Makefile```
4. Run the command ```make```.
5. The program is now ready to be invoked.
    - The program is invoked by passing the number of resources of each type via command line to intialize the available array by these values. For example, if there were four resource types, with ten instances of the first type, five of the second type, seven of the third type, and eight of the fourth type, you would invoke your program as follows:
	```./assignment04.out 10 5 7 8```
6. Once the program has been invoked, it awaits for user input commands.
    - Refer to the Features section for more details regarding commands.

***

## Features
The program allows the user to be the clients and interactively enter a request for resources, to release resources, or to output the values of the different data structures (available,maximum,allocation, and need) used with the Banker's Algorithm.

Clients are identified by their ID. The current implementation has a maximum of 5 clients, and their respective IDs range from 0-4.

**User Commands include:** *(All user commands are case-censitive.)*
+ ```RQ``` - Used to request more resources for a client. Clients cannot hold more resources than they have declared as their maximum. If a client request more than their maximum, the banker assumes the client is request their maximum.
    -  As an example of usage, if client 0 were to request the resources (3, 1, 2, 1), the following command would be entered: ```RQ 0 3 1 2 1```
    - All requests are approved, so long as sufficient resources are available to fulfill. If the state resulting from the fulfillment of a request is unsafe, the banker will inform the user of this.
+ ```RL``` - Used to release resource form a client. Clients cannot release more resources than they have been allocated. If a client releases more than they hold, the banker assumes the client wishes to the the rest of the respective resource that they hold.
    + As an example of usage, if client 2 were to release the resources (3, 1, 2, 1), the following command would be entered: ```RL 2 3 1 2 1```
+ ```*``` - Outputs the current state of the different data structures.
+ ```RUN``` - The banker determines the safe sequence and runs the sequence, while displaying details. If a safe sequence cannot be determined, the banker will not proceed further.
+ ```QUIT``` - Aborts the program.

*If an emergency stop is required you may use "CTRL+C" on your keyboard to abort the program.*

***

## Tests
```bash
user@ubuntu:~/assignment_4$ ./201490550_a04 9 8 7 9
Number of customers: 5
Currently available resources: 9 8 7 9 
Maximum resources from file:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Enter Command: RQ 3 1 2 3 1
Resource request is satisfied.
Enter Command: RQ 0 1 1 1 1
Resource request is satisfied.
Enter Command: *
Maximum:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 

Current Need:
5 3 6 2 
4 2 3 2 
2 5 3 3 
5 1 0 1 
5 6 7 5 

Current Allocation:
1 1 1 1 
0 0 0 0 
0 0 0 0 
1 2 3 1 
0 0 0 0 

Currently Available Resources: 7 5 3 7 
Current State: SAFE
Enter Command: RUN
Safe Sequence is: < 1 2 3 0 4 >
Executing threads:
--> Client/Thread 1
	Allocated Resources: 0 0 0 0 
	Needed: 4 2 3 2 
	Available: 7 5 3 7 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 7 5 3 7 
--> Client/Thread 2
	Allocated Resources: 0 0 0 0 
	Needed: 2 5 3 3 
	Available: 7 5 3 7 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 7 5 3 7 
--> Client/Thread 3
	Allocated Resources: 1 2 3 1 
	Needed: 5 1 0 1 
	Available: 7 5 3 7 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 8 7 6 8 
--> Client/Thread 0
	Allocated Resources: 1 1 1 1 
	Needed: 5 3 6 2 
	Available: 8 7 6 8 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 9 8 7 9 
--> Client/Thread 4
	Allocated Resources: 0 0 0 0 
	Needed: 5 6 7 5 
	Available: 9 8 7 9 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 9 8 7 9 
Thread execution complete.
```

***

## Code Example
```c
//Function Declarations
void initMax();
void updateNeed();
void printMax();
void printNeed();
void printAllocation();
void printAvailable();
bool getCommand();
bool validateCommand(char *command);
int identifyCommand();
void processCommand(char *command);
void request(char *cmd[]);
void release(char *cmd[]);
void displayState();
void run();
bool getState();
void *threadRun(void *cid);

//Banker's Algorithm Data Structures
int maximum[MAX_CLIENTS][RES_TYPE_COUNT];
int available[RES_TYPE_COUNT];
int allocation[MAX_CLIENTS][RES_TYPE_COUNT];
int need[MAX_CLIENTS][RES_TYPE_COUNT];
int safe_sequence[MAX_CLIENTS] = {-1};
int state = SAFE;
```

***

## Authors
Roy Ceyleon

***

## Individual Contribution
...

***

## Credits
[Linux Manual](https://linux.die.net/man/)

[Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

***

## License
Copyright (c) 2021, Roy Ceyleon

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.