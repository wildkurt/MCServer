//
// Created by wende on 10/7/2022.
//
#include "server.h"
//These are functions for the main menu
void startMCServer(){
    //This function will list the available servers
    //and allow user to select the server they wish
    //to start. Need to check and see if a server is
    //running first.
    if(isAServerRunning()){}
    else{
        listServers();
    }
}
void stopMCServer(){}
void addMCserver(){}
void removeMCServer(){}
void whatServerIsRunning(){}
void enterMCServerScreen(){}
//Background functions
void copyFromServersFile(){}
void writeToServersFile(){}
void checkIfServerFileIsEmpty(){}
int isAServerRunning(){}
void listServers(){}