/*
 -------------------------------------
 File:    201490550_a04.c
 Project: CP386 Assigment 4
 CP386 Assignment 4: Deadlock Avoidance - Banker's Algorithm
 -------------------------------------
 Author:  Roy Ceyleon
 ID:      201490550
 Github:  xeyleon
 Email:   ceyl0550@mylaurier.ca
 Version  2021-06-19
 -------------------------------------
 Comments:
 
 */
 
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <semaphore.h>

#define INPUT_FILE "sample4_in.txt"  //Input filename
#define MAX_CLIENTS 5           //The number of clients supported
#define RES_TYPE_COUNT 4        //The number of different resources available

///Macro Definiitons
#define MAX_BUFFER 100
#define REQUEST_CMD "RQ"
#define RELEASE_CMD "RL"
#define STATUS_CMD "*"
#define RUN_CMD "RUN"
#define QUIT_CMD "QUIT"
#define MIN(a,b) ((a) < (b) ? a : b)
enum COMMANDS {RQ = 1, RL = 2, STATUS = 3, RUN = 4, QUIT = 5};

//Function Declarations
void initMax();
void printMax();
void printNeed();
void printAllocation();
void printAvailable();
bool getCommand();
bool validateCommand(char *command);
int identifyCommand();
void request(char *cmd[]);
void release(char *cmd[]);
void displayData();
void run();
void processCommand(char *command);
void updateNeed();

//Banker's Algorithm Data Structures
int maximum[MAX_CLIENTS][RES_TYPE_COUNT];
int available[RES_TYPE_COUNT];
int allocation[MAX_CLIENTS][RES_TYPE_COUNT];
int need[MAX_CLIENTS][RES_TYPE_COUNT];

int main(int argc, char *argv[]){
    printf("Number of Customers: %d\n", MAX_CLIENTS);

    printf("Currently Available resources: ");
    for (int i = 1; i < argc; i++)
    {
        available[i - 1] = atoi(argv[i]);
        printf("%d ", available[i - 1]);
        if (i == argc-1)
            printf("\n");
    }

    initMax();
    updateNeed();
    printf("Maximum resources from file:\n");
    printMax();

    while (getCommand());

    return 0;
}

void initMax() {
    FILE *fp = fopen(INPUT_FILE, "r");
    for (int i = 0; i < MAX_CLIENTS; i++)
        for (int j = 0; j < RES_TYPE_COUNT; j++)
            fscanf(fp, "%d,", &maximum[i][j]);
    fclose(fp);
}

void updateNeed() {
    for (int i = 0; i < MAX_CLIENTS; i++)
        for (int j = 0; j < RES_TYPE_COUNT; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

void printMax(){
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        for (int j = 0; j < RES_TYPE_COUNT; j++)
            printf("%d ", maximum[i][j]);
        printf("\n");
    }
}

void printNeed(){
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        for (int j = 0; j < RES_TYPE_COUNT; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

void printAllocation(){
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        for (int j = 0; j < RES_TYPE_COUNT; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }
}

void printAvailable(){
    for (int i = 0; i < RES_TYPE_COUNT; i++)
        printf("%d ", available[i]);
    printf("\n");
}

bool getCommand(){
    char* input = calloc(MAX_BUFFER, sizeof(char));

    printf("Enter Command: ");
    while (fgets(input, MAX_BUFFER, stdin) != NULL){
        if (input[0] == '\n')
            continue;
        else
            break;
    }

    input[strcspn(input,"\n")] = 0;
    if (validateCommand(input)){
        switch(identifyCommand(input)){
            case RQ:
            case RL:
                processCommand(input);
                break;
            case STATUS:
                displayData();
                break;
            case RUN:
                run();
                break;
            case QUIT:
                printf("Program aborted.\n");
                exit(0);
                break;
            default:
                printf("Unknown error\n");
                break;
        }
    }

    free(input);
    return true;
}

void displayCommands(){
    printf("Please refer to program documentation for proper command entry.\n");
}

bool validateCommand(char *command){
    
    char temp[strlen(command)];
    strcpy(temp, command);
    char *token = strtok(temp, " ");

    if ( !(strcmp(token,REQUEST_CMD)) || (!(strcmp(token,RELEASE_CMD))) ){
        char cmd[3];
        strcpy(cmd, token);
        int arg_count = 0;
        while(token != NULL){
            if (isdigit(*token) > 0)
                arg_count++;
            token = strtok(NULL, " ");
        }
        if (arg_count != 5){
            printf("%s: Invalid Usage\n", cmd);
            printf("Example Usage: %s 4 1 2 3 3\n", cmd);
            return false;
        }
        else
            return true;
    }
    else if ( !(strcmp(token,RUN_CMD)) || !(strcmp(token,STATUS_CMD)) || !(strcmp(token,QUIT_CMD)) )
        return true;

    printf("Invalid Command\n");
    return false;
}

int identifyCommand(char *command){
    char temp[strlen(command)];
    strcpy(temp, command);
    char *token = strtok(temp, " ");
    if (!(strcmp(token,REQUEST_CMD)))
        return RQ;
    if (!(strcmp(token,RELEASE_CMD)))
        return RL;
    if (!(strcmp(token,RUN_CMD)))
        return RUN;
    if (!(strcmp(token,STATUS_CMD)))
        return STATUS;
    if (!(strcmp(token,QUIT_CMD)))
        return QUIT;

    return 0;
}

void processCommand(char *command){
    char *cmd[20];
    char temp[strlen(command)];
    strcpy(temp, command);
    char *token = strtok(temp, " ");
    int i = 0;
    while (token != NULL) {
        cmd[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    if (atoi(cmd[1]) >= MAX_CLIENTS){
        printf("%s: Invalid client number\n", cmd[0]);
        return;
    }

    if (!(strcmp(cmd[0],REQUEST_CMD)))
        request(cmd);
    if (!(strcmp(cmd[0],RELEASE_CMD)))
        release(cmd);
}

void request(char *cmd[]){

    int client_id = atoi(cmd[1]);
    int res_request = 0;
    for (int i = 0; i < RES_TYPE_COUNT; i++){
        res_request = MIN(atoi((cmd[2+i])),maximum[client_id][i]);
        if (res_request > available[i]){
            printf("Resource request cannot be satisfied\n");
            return;
        }

        if (res_request+allocation[client_id][i] > need[client_id][i]){
            printf("A client cannot request more resources than the maximum declared\n");
            return;
        }
    }
    for (int i = 0; i < RES_TYPE_COUNT; i++){
        res_request = MIN(atoi((cmd[2+i])),maximum[client_id][i]);
        available[i] -= res_request;
        need[client_id][i] -= res_request;
        allocation[client_id][i] += res_request;
    }

    printf("Resource request is satisfied\n");
}

void release(char *cmd[]){
    int client_id = atoi(cmd[1]);
    int res_release = 0;

    for (int i = 0; i < RES_TYPE_COUNT; i++){
        res_release = MIN(atoi((cmd[2+i])),allocation[client_id][i]);
        available[i] += res_release;
        need[client_id][i] += res_release;
        allocation[client_id][i] -= res_release;
    }

    printf("Resources released\n");
}

void displayData(){
    printf("Maximum:\n");
    printMax();
    printf("Current Need:\n");
    printNeed();
    printf("Current Allocation:\n");
    printAllocation();
    printf("Currently Available resources: ");
    printAvailable();
}

void run(){

}