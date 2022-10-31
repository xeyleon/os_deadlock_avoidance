# Banker's Algorithm

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
3. Rename the file *makefile.gmk* to *makefile*.
    - ```mv makefile.gmk makefile```
4. Run the command ```make```.
5. The program is now ready to be invoked.
    - The program is invoked by passing the number of resources of each type via command line to intialize the available array by these values. For example, if there were four resource types, with ten instances of the first type, five of the second type, seven of the third type, and eight of the fourth type, you would invoke your program as follows:
	```./201490550_a04 10 5 7 8```
6. Once the program has been invoked, it awaits for user input commands.
    - Refer to the Features section for more details regarding commands.

***

## Features
The program allows the user to be the clients and interactively enter a request for resources, to release resources, or to output the values of the different data structures (available,maximum,allocation, and need) used with the Banker's Algorithm.

Clients are identified by their ID. The current implementation has a maximum of 5 clients, and their respective IDs range from 0-4.

**User Commands include:** *(All user commands are case-censitive.)*
+ ```RQ``` - Used to request more resources for a client. Clients cannot hold more resources than they have declared as their maximum. If a client request more than their maximum, the banker assumes the client is requesting their maximum.
    -  As an example of usage, if client 0 were to request the resources (3, 1, 2, 1), the following command would be entered: ```RQ 0 3 1 2 1```
    - Requests are approved, so long as sufficient resources are available to fulfill it. However, if the state resulting from the fulfillment of a request is unsafe, the banker will deny the request.
    - Absurd resource requests, such as ```RQ 1 100 100 100 100```, will be granted, so long as sufficient resources are available, as the banker will assume the client is requesting their maximum resource need. For instance, say client 1 has a need of 3 3 3 3 and the command ```RQ 1 100 100 100 100``` is executed. The banker will assume the client is requesting 3 3 3 3, and so long as resources are available and the state remains safe, accepts the request, and allocate 3 3 3 3 to client 1.
+ ```RL``` - Used to release resource form a client. The Banker ensures that clients cannot release more resources than they have been allocated. If a client commands to release more of a resource than they are currently allocated, the banker assumes the client desires to release the entirety of the respective resource that they are currently allocated. For instance, say client 1 current has 2 2 2 2 allocated and ```RL 1 100 100 100 100``` is executed. The banker will accept the command, but will only release 2 2 2 2 from client 1.
    + As an example of usage, if client 2 were to release the resources (3, 1, 2, 1), the following command would be entered: ```RL 2 3 1 2 1```
+ ```Status``` - Outputs the current state of the different data structures maintained by the banker.
+ ```Run``` - The banker determines the safe sequence and runs the sequence, while displaying details. If the state is unsafe, the banker will not proceed further.
+ ```Exit``` - Aborts the program.

*If an emergency stop is required you may use "CTRL+C" on your keyboard to abort the program.*

***

## Test Cases
### Program Execution
```bash
x@ubuntu:~/Desktop/assignment_4$ ./201490550_a04 10 10 10 10
Number of customers: 5
Currently available resources: 10 10 10 10 
Maximum resources from file:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Enter Command: 
```
### Status Command
```bash
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Available Resources:
10 10 10 10 
State: SAFE
Enter Command: 
```
### Resource Request Denial
```bash
Number of customers: 5
Currently available resources: 10 10 10 10 
Maximum resources from file:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Enter Command: RQ 0 3 3 3 3
Resource request has been satisfied.
Enter Command: RQ 4 2 2 2 2
Resource request has been satisfied.
Enter Command: RQ 3 1 1 1 1
Resource request has been satisfied.
Enter Command: RQ 1 1 1 1 1
Resource request has been satisfied.
Enter Command: RQ 3 1 1 1 1
Resource request has been denied due to safety concerns.
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
3 3 3 3 
1 1 1 1 
0 0 0 0 
1 1 1 1 
2 2 2 2 
Need Resources:
3 1 4 0 
3 1 2 1 
2 5 3 3 
5 2 2 1 
3 4 5 3 
Available Resources:
3 3 3 3 
State: SAFE
Enter Command: 
```

### Absurd Request
```bash
Enter Command: RQ 0 1000 1000 1000 1000
Resource request has been satisfied.
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
6 4 7 3 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
0 0 0 0 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Available Resources:
4 6 3 7 
State: SAFE
Enter Command: 
```
### Absurd Release
```bash
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Available Resources:
10 10 10 10 
State: SAFE
Enter Command: RQ 0 1000 1000 1000 1000
Resource request has been satisfied.
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
6 4 7 3 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
0 0 0 0 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Available Resources:
4 6 3 7 
State: SAFE
Enter Command: RL 0 10000 10000 1000 1000
Resources have been successfuly released.
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Available Resources:
10 10 10 10 
State: SAFE
Enter Command: 
```
### Execution of Program with Insufficient Resources
```bash
x@ubuntu:~/Desktop/assignment_4$ ./201490550_a04 1 1 1 1
Number of customers: 5
Currently available resources: 1 1 1 1 
Maximum resources from file:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
WARNING: The current state is unsafe.
Enter Command: RQ 0 1 1 1 1
Resource request has been denied due to safety concerns.
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Available Resources:
1 1 1 1 
State: UNSAFE
Enter Command: Run
Current state is unsafe. Unable to proceed.
Enter Command: 
```

***

## Use Examples
### Example 1
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
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 6 7 5 
Allocated Resources:
1 1 1 1 
0 0 0 0 
0 0 0 0 
1 2 3 1 
0 0 0 0 
Need Resources:
5 3 6 2 
4 2 3 2 
2 5 3 3 
5 1 0 1 
5 6 7 5 
Available Resources:
7 5 3 7 
State: SAFE
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

### Example 2
```bash
user@ubuntu:~/Desktop/assignment04$ ./201490550_a04 10 5 7 8
Number of customers: 5
Currently available resources: 10 5 7 8 
Maximum resources from file:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
Enter Command: RQ 0 1 0 0 1
Resource request has been satisfied.
Enter Command: RQ 1 1 1 1 1
Resource request has been satisfied.
Enter Command: RQ 2 2 2 2 2
Resource request has been satisfied.
Enter Command: RQ 3 1 1 1 1
Resource request has been satisfied.
Enter Command: RQ 4 1 0 0 0
Resource request has been satisfied.
Enter Command: Status
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
Allocated Resources:
1 0 0 1 
1 1 1 1 
2 2 2 2 
1 1 1 1 
1 0 0 0 
Need Resources:
5 4 7 2 
3 1 2 1 
0 3 1 1 
5 2 2 1 
4 5 7 5 
Available Resources:
4 1 3 3 
State: SAFE
Enter Command: Run
Safe Sequence is: < 1 3 2 4 0 >
Executing threads:
--> Client/Thread 1
	Allocated Resources: 1 1 1 1 
	Needed: 3 1 2 1 
	Available: 4 1 3 3 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 5 2 4 4 
--> Client/Thread 3
	Allocated Resources: 1 1 1 1 
	Needed: 5 2 2 1 
	Available: 5 2 4 4 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 6 3 5 5 
--> Client/Thread 2
	Allocated Resources: 2 2 2 2 
	Needed: 0 3 1 1 
	Available: 6 3 5 5 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 8 5 7 7 
--> Client/Thread 4
	Allocated Resources: 1 0 0 0 
	Needed: 4 5 7 5 
	Available: 8 5 7 7 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 9 5 7 7 
--> Client/Thread 0
	Allocated Resources: 1 0 0 1 
	Needed: 5 4 7 2 
	Available: 9 5 7 7 
	Thread has started.
	Thread has finished.
	Thread is releasing resources.
	New Available: 10 5 7 8 
Thread execution complete.
Enter Command: 
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
Roy Ceyleon's Contributions
```c
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
```

***

## About Developers
They love dogs.

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
