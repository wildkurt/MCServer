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
void removeNode(struct Node *node){
    (node->prev)->next = node->next;
    if(node->next != 0)
        (node->next)->prev = node->prev;
    free(node->name);
    free(node->directory);
    free(node);
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
    struct Node *temp=0;

    listServers((*head));

    if((*head) == 0)
        return;
    temp = (*head);
    printf("Select the server you wish to remove: ");
    input = (int) getchar() - '0';
    getchar();
    //Case 1: only one server
    //Case 2: More than one
    //Case 2a: Node at front
    //Case 2b: Node in the middle
    //Case 2c: Node at the end
    if(input == 1 && temp->next == 0){
        //free the node and set head to 0
        free((*head)->name);
        free((*head)->directory);
        free((*head));
        (*head) = 0;
    }
    else{
        for(int i = 1; i < input; i++){
            temp=temp->next;
        }
        removeNode(temp);
    }
}