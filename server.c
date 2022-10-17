//
// Created by wende on 10/7/2022.
//
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//These are functions for the main menu
void startMCServer(){
    //TODO
    //This function will list the available servers
    //and allow user to select the server they wish
    //to start.
    FILE *running;
    int option = 0;
    char command[MAX_ARRAY_SIZE] = "screen -dmS ";
    extern struct Servers servers[];
    // Need to check and see if a server is
    //running first.
    if(isAServerRunning()){
        return;
    }
    //See if the list of servers are empty
    if(servers[0].name == 0){
        addMCserver();
    }
    //List the available servers
    //Get the selection from the user
    while(1){
        listServers();
        printf("Please select the server to run.\n");
        scanf("%d",&option);
        if(option < 0 || option > 200){
            printf("%d is a invalid selection\n", option);
            continue;
        }
        else if(notAValidSelection(option)){
            printf("%d is a invalid selection\n", option);
            continue;
        }
        else
            break;
    }
    //update the running file
    running = fopen("running","w");
    fputs(servers[option].name, running);
    //build the command string for system
    strcat(command,servers[option].name);
    strcat(command," ");
    strcat(command,servers[option].filePath);
    //For testing purposes, this will just print
    printf("System command is: %s\n", command);
    //This will execute the creation of a screen and start the MC server
    //system(command);
    fclose(running);
}
void stopMCServer(){
    //TODO
    printf("Stopping Server not yet implemented\n");
}
void addMCserver(){
    char nameBuffer[MAX_ARRAY_SIZE]={0};
    char pathBuffer[MAX_ARRAY_SIZE]={0};
    int index = 0;
    printf("Provide a name and the file path to\n");
    printf("the starting script for the MC server\n");
    printf("Type \"exit\" when finished inputing servers.\n");
    while(1){
        printf("Enter a name for the server: ");
        fgets(nameBuffer, MAX_ARRAY_SIZE, stdin);
        if(strcmp("exit",nameBuffer)!=0)
            break;
        printf("You entered server name %s.\n", nameBuffer);
        printf("Enter the path to the start up script for the server.");
        if(strcmp("exit",pathBuffer)!=0)
            break;
        fgets(pathBuffer, MAX_ARRAY_SIZE, stdin);
        printf("You entered %s as the path.\n", pathBuffer);
        struct Servers temp;
        temp.name = malloc(1+strlen(nameBuffer)*sizeof(char));
        temp.filePath = malloc(1+strlen(pathBuffer)*sizeof(char));
        index = findEmptySpot();
        if(index > -1){
            servers[index] = temp;
        }
    }
}
void removeMCServer(){
    //TODO
    printf("Removing Server not yet implemented\n");
}
void whatServerIsRunning(){
    //TODO
    printf("Running Server not yet implemented\n");
}
void enterMCServerScreen(){
    //TODO
    printf("Enter screen not yet implemented\n");
}
//Background functions
/**This function should only run if a serverfile exists
 * and if it is not empty.*/
int copyFromServersFile(){
    FILE *input;
    int size = 0, index = 0;
    char nameBuffer[MAX_ARRAY_SIZE] = {0};
    char pathBuffer[MAX_ARRAY_SIZE] = {0};
    extern struct Servers servers[];
    //open the file
    input = fopen("serversfile","r");
    //See if the file exists
    if(input == NULL)
        return 0;
    //See if the file is empty
    else{
        fseek(input, 0, SEEK_END);
        size = ftell(input);
        if(size == 0)
            return 0;
    }
    while(feof(input)==0){
        if(fscanf(input,"%s, %s",nameBuffer,pathBuffer)){
            struct Servers temp;
            temp.name = malloc(1 + strlen(nameBuffer)* sizeof(char));
            temp.filePath = malloc(1 + strlen(pathBuffer)* sizeof(char));
            servers[index++] = temp;
        }
    }
    fclose(input);
    return 1;
}
/**This should only run if there are servers in the servers
 * array when the program exits.*/
void writeToServersFile(){
    //TODO
}

int isAServerRunning(){
    FILE *running;
    FILE *screenoutput;
    char *command = "screen -ls > screenoutput";
    char readBuffer[MAX_ARRAY_SIZE];

    running = fopen("running","r");

    if(running == NULL){
        printf("The running file can not be found or opened\n");
        return 0;
    }
    if(fread(readBuffer, MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, running) == 0)
        return 0;
    else if(strcmp("none", readBuffer) == 0)
        return 0;
    else{
        system(command);
        screenoutput = fopen("screenouput","r");
        if(screenoutput != NULL){

        }
    }
}
void listServers(){
    //TODO
}
//Checks to see if the option is a valid server
int notAValidSelection(int option){
    extern struct Servers servers[];
    if(servers[option].name == 0){
        return 1;
    }
    else{
        return 0;
    }
}
//Finds the first empty spot in the servers array
int findEmptySpot(){
    extern struct Servers servers[];
    int i = 0;
    for(;i < MAX_ARRAY_SIZE;i++){
        if(servers[i].name == 0)
            return i;
    }
    return -1;
}