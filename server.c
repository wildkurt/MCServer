//
// Created by wende on 10/7/2022.
//
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//These are functions for the main menu
void startMCServer(struct Servers *servers){
    //This function will list the available servers
    //and allow user to select the server they wish
    //to start.
    FILE *running;
    int option = 0;
    char command[MAX_ARRAY_SIZE] = "screen -dmS ";
    // Need to check and see if a server is
    //running first.
    if(isAServerRunning()){
        return;
    }
    //See if the list of servers are empty
    if(servers[0].name == 0){
        addMCserver(servers);
    }
    //List the available servers
    //Get the selection from the user
    while(1){
        listServers(servers);
        printf("Please select the server to run.\n");
        scanf("%d",&option);

        if(notAValidSelection(servers,option)){
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
    system(command);
    fclose(running);
}
void stopMCServer(){
    FILE *running;
    char readBuffer[MAX_ARRAY_SIZE]={0};
    char command[MAX_ARRAY_SIZE]={0};
    char *prefix = "screen -S ";
    char *suffix = " -X stuff \"stop^M\"";
    //check if a server is running
    if(isAServerRunning()){
        running = fopen("running","r");
        fread(readBuffer,MAX_ARRAY_SIZE,MAX_ARRAY_SIZE, running);
        strcat(command, prefix);
        strcat(command, readBuffer);
        strcat(command, suffix);
        system(command);
    }
    else{
        fprintf(stderr,"No Server is running\n");
    }
}
void addMCserver(struct Servers *servers){
    char nameBuffer[MAX_ARRAY_SIZE]={0};
    char pathBuffer[MAX_ARRAY_SIZE]={0};
    int index = 0;
    printf("Provide a name and the file path to\n");
    printf("the starting script for the MC server\n");
    printf("Type \"exit\" when finished inputing servers.\n");
    while(1){
        printf("Enter a name for the server: ");
        fgets(nameBuffer, MAX_ARRAY_SIZE, stdin);
        if(strcmp("exit\n",nameBuffer)==0)
            break;
        nameBuffer[strlen(nameBuffer) - 1] = '\0';
        printf("You entered server name %s.\n", nameBuffer);
        printf("Enter the path to the start up script for the server.");
        fgets(pathBuffer, MAX_ARRAY_SIZE, stdin);
        pathBuffer[strlen(pathBuffer)-1] = '\0';
        printf("You entered %s as the path.\n", pathBuffer);
        struct Servers temp;
        temp.name = calloc(sizeof(char),1+strlen(nameBuffer)*sizeof(char));
        temp.filePath = calloc(sizeof(char),1+strlen(pathBuffer)*sizeof(char));
        strcat(temp.name, nameBuffer);
        strcat(temp.filePath, pathBuffer);
        index = findEmptySpot(servers);
        if(index > -1){
            servers[index] = temp;
        }
        zeroArray(nameBuffer);
        zeroArray(pathBuffer);
    }
    if(servers[0].name == 0){
        printf("No servers have been entered\n");
        exit(1);
    }
}
/** To remove a server:
 * Case 1) the server is at the front: Need to shuffle all the
 * servers to the left
 * Case 2) the server is at the end of the array: Just zero the element
 * Case 3) the server is in the middle of the array: shuffle everything
 * to the left*/
void removeMCServer(struct Servers *servers){
    char input = 0;
    while(1){
        printf("Please select the server you wish to remove\n");
        listServers(servers);
        input = getchar();
        if(notAValidSelection(servers,input - '0')){
            printf("%c is not a valid selection\n",input);
        }
        else{
            performRemovalAction(servers,input-'0'-1);
            break;
        }
    }
}
void whatServerIsRunning(){
    char *command = "screen -ls";
    system(command);
}
void enterMCServerScreen(){
    FILE *running;
    char readBuffer[MAX_ARRAY_SIZE]={0};
    char command[MAX_ARRAY_SIZE]={0};

    if(isAServerRunning()){
        running = fopen("running","r");
        fread(readBuffer,MAX_ARRAY_SIZE,MAX_ARRAY_SIZE, running);
        strcat(command, "screen -r ");
        strcat(command, readBuffer);
        system(command);
    }
    else{
        fprintf(stderr, "No screen to join\n");
    }
}
//Background functions
/**This function should only run if a serverfile exists
 * and if it is not empty.*/
int copyFromServersFile(struct Servers *servers){
    FILE *input;
    int size = 0, index = 0;
    char nameBuffer[MAX_ARRAY_SIZE] = {0};
    char pathBuffer[MAX_ARRAY_SIZE] = {0};
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
void writeToServersFile(struct Servers *servers){
    FILE *serversfile;
    char writeBuffer[MAX_ARRAY_SIZE] = {0};

    if(servers[0].name == 0)
        return;

    serversfile = fopen("serversfile","w");
    if(serversfile == NULL){
        fprintf(stderr, "Unable to open the serversfile for writting\n");
        exit(0);
    }
   for(int i = 0; servers[i].name != 0;i++){
       strcat(writeBuffer,servers[i].name);
       strcat(writeBuffer,",");
       strcat(writeBuffer,servers[i].filePath);
       fwrite(writeBuffer, MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, serversfile);
       zeroArray(writeBuffer);
   }
   fclose(serversfile);
}
/** When determining if a minecraft server is running, need to
 * check screen and also the running file to make sure they are
 * in the same state. If a server is running, then the name of
 * the server is in the running file and the name of the server
 * can be found in the screen list output file.
 * Case 1: running = none, screen no sockets: return false
 * Case 2: running = <name> screen has <name>: return true
 * Case 3: running = none, screen doesn't say no socket:
 * add server name to running file and return true
 * Case 4: running = <name>, screen says no socket:
 * set running file to "none" and return false*/

int isAServerRunning(){
    FILE *running;
    FILE *screenoutput;
    char *command = "screen -ls > screenoutput";
    char readBuffer[MAX_ARRAY_SIZE]={0};
    char readBuffer2[MAX_ARRAY_SIZE]={0};
    char *noSocket = "No Sockets found in";
    running = fopen("running","r+");

    if(running == NULL){
        fprintf(stderr,"Unable to open running file\n");
        exit(1);
    }
    system(command);
    screenoutput = fopen("screenoutput","r");
    if(screenoutput == NULL){
        fprintf(stderr,"Attempt to read screen failed\n");
        exit(1);
    }
    if(fread(readBuffer2, MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, screenoutput) == 0){
        fprintf(stderr, "Screen output file is empty\n");
    }
    //The screen outputs one line for no socket and three if there is one
    //Second line contains the name of the screen
    if(fread(readBuffer, MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, running)){
        if(strstr(readBuffer,"none")){
            if(strstr(readBuffer2, noSocket))
                return 0; //No socket running
            else{
                //there is a socket running, update the running file
                //Rewind file pointer
                rewind(running);
                //Zero readBuffer
                zeroArray(readBuffer);
                //Read next line of screenoutput file
                fread(readBuffer2, MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, screenoutput);
                //get the name of the running screen
                scanf(".%s",readBuffer);
                //Write the name to the running file
                fwrite(readBuffer, MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, running);
                fclose(running);
                fclose(screenoutput);
                return 1;
            }
        }
        else{
            //Need to see if there is a screen running as well
            if(strstr(readBuffer2, noSocket)){
                rewind(running);
                fwrite("none", MAX_ARRAY_SIZE, MAX_ARRAY_SIZE, running);
                fclose(running);
                fclose(screenoutput);
                return 0;
            }
            else{
                return 1;
            }
        }
    }
}
void listServers(struct Servers *servers){
    int index = 0;
    while(servers[index].name != 0){
        printf("%d) %s\n", index + 1, servers[index].name);
        index++;
    }
}
//Checks to see if the option is a valid server
int notAValidSelection(struct Servers *servers, int option){
    if(option < 0 || option > 200)
        return 1;
    else if(servers[option].name != 0){
        return 0;
    }
    else{
        return 1;
    }
}
//Finds the first empty spot in the servers array
int findEmptySpot(struct Servers *servers){
    int i = 0;
    for(;i < MAX_ARRAY_SIZE;i++){
        if(servers[i].name == 0)
            return i;
    }
    return -1;
}

void zeroArray(char *arr){
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        arr[i] = '\0';
}

void performRemovalAction(struct Servers *servers, int opt){
    int size = 0;
    while(servers[size].name != 0){
        size++;
    }
    if(opt == 0 && size == 1){
        servers[0].name = 0;
        servers[0].filePath = 0;
    }
    else{
        for(int i = opt; servers[i].name != 0; i++){
            servers[i] = servers[i+1];
        }
    }
}