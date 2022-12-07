//
// Created by minecraft on 11/29/22.
//
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mcserverMain.h"

void push(struct Node** head, char* directory, char* name){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->directory = calloc(sizeof(char),1+strlen(directory)*sizeof(char));
    newNode->name = calloc(sizeof(char),1+strlen(name)*sizeof(char));
    strcat(newNode->directory, directory);
    strcat(newNode->name, name);
    newNode->next = (*head);
    newNode->prev = 0;
    if((*head) != 0)
        (*head)->prev = newNode;
    (*head)=newNode;
}

void pop(struct Node **head){
    struct Node *temp;
    //char *path = strdup((*head)->directory);
    //char *name = strdup((*head)->name);
    //printf("Removed %s and %s\n", path, name);
    temp = (*head);
    (*head) = (*head)->next;
    free(temp->directory);
    free(temp->name);
    free(temp);
}

void listServers(struct Node *head){
    int counter = 1;
    if(head == 0){
        printf("The server list is empty\n");
        return;
    }
    printf("The list of servers is: \n");
    while(head != 0){
        printf("%d. %s\n", counter, head->name);
        head = head->next;
        counter++;
    }
    printf("End of list\n\n");
    sleep(3);
}

void addServer(struct Node ** head){
    char directoryPath[MAX_ARRAY_SIZE]={0};
    char serverName[MAX_ARRAY_SIZE] = {0};

    printf("Input the name of the server: ");
    fgets(serverName, MAX_ARRAY_SIZE, stdin);
    printf("Enter the path to the start up script: ");
    fgets(directoryPath, MAX_ARRAY_SIZE, stdin);
    serverName[strlen(serverName) - 1] = '\0';
    directoryPath[strlen(directoryPath)-1] = '\0';
    push(head, directoryPath,serverName);
}
/**1. List the nodes available to remove
 * 2. Get input for the desired node to remove
 * 3. Find the node
 * 4. Remove it*/
void removeServer(struct Node **head){
    int input = 0;
    struct Node *temp = 0;
    if((*head) == 0)
        return;
    temp = (*head);
    listServers(*head);

    printf("Select the server you wish to remove: ");
    input = getchar() - '0';
    getchar();

    for(int i = 1; i < input; i++){
        temp = temp->next;
    }
    //case 1: node at front
    if(temp->prev == 0){
        if(temp->next == 0){
            (*head) = 0;
        }
        else{
            (*head) = temp->next;
            free(temp->name);
            free(temp->directory);
            free(temp);
        }
    }
    //case 2: node in middle
    else if(temp->prev != 0 && temp->next != 0){
        (temp->prev)->next = temp->next;
        (temp->next)->prev = temp->prev;
        free(temp->name);
        free(temp->directory);
        free(temp);
    }
    //case 3: node at end
    else if(temp->prev != 0 && temp->next == 0){
        (temp->prev)->next = 0;
        free(temp->name);
        free(temp->directory);
        free(temp);
    }
}

void startServer(struct Node *head){
    int input = 0;
    char command[MAX_ARRAY_SIZE] = {0};
    char *commandA = "screen -dmS ";
    FILE *output;
    extern char runningpath[];

    listServers(head);
    printf("Which server do you wish to start?: \n");
    input = getchar() - '0';
    getchar();

    for(int i = 1; i < input; i++){
        head = head->next;
    }

    strcat(command, commandA);
    strcat(command, head->name);
    strcat(command, " ");
    strcat(command, head->directory);
    system(command);

    output =  fopen(runningpath, "w");
    fputs(head->name,output);
    fclose(output);
}

void runningServer(){
    char *command = "screen -ls";
    system(command);
}

void stopRunningServer(struct Node*){
    FILE *input, *output;
    char serverName[MAX_ARRAY_SIZE] = {0};
    char command[MAX_ARRAY_SIZE] = {0};
    char *commandA = "screen -S ";
    char *commandB = " -X stuff \"stop^M\"";
    extern char runningpath[];

    input = fopen(runningpath,"r");
    fgets(serverName,MAX_ARRAY_SIZE,input);
    fclose(input);
    output = fopen(runningpath,"w");
    fputs("none",output);
    fclose(output);

    strcat(command, commandA);
    strcat(command, serverName);
    strcat(command, commandB);
    system(command);
}

void joinServerInstance(struct Node*){
    FILE *running;
    char buffer[MAX_ARRAY_SIZE] = {0};
    char *commandA = "screen -r ";
    char command[MAX_ARRAY_SIZE] = {0};
    extern char runningpath[];

    running = fopen(runningpath,"r");
    fgets(buffer,MAX_ARRAY_SIZE,running);

    strcat(command, commandA);
    strcat(command, buffer);
    system(command);
}

void openServerList(struct Node **head){
    FILE *savedFile;
    char name[MAX_ARRAY_SIZE] = {0};
    char path[MAX_ARRAY_SIZE] = {0};
    char buffer[MAX_ARRAY_SIZE] = {0};
    extern char savepath[];

    savedFile = fopen(savepath, "r");
    if(savedFile == 0)
        return;
    while(fgets(buffer, MAX_ARRAY_SIZE, savedFile)){
        sscanf(buffer,"%s""%s", name, path);
        push(head,path,name);
    }
    fclose(savedFile);
}

void closeServerList(struct Node **head){
    FILE *savedFile;
    extern char savepath[];

    savedFile = fopen(savepath,"w");

    if(savedFile == 0){
        fprintf(stderr,"Save Failed");
        return;
    }
    while((*head)!=0){
        fputs((*head)->name, savedFile);
        fputs(" ",savedFile);
        fputs((*head)->directory, savedFile);
        fputs("\n",savedFile);
        pop(head);
    }
    fclose(savedFile);
}