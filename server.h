//
// Created by wende on 10/7/2022.
//

#ifndef MCSERVER_SERVER_H
#define MCSERVER_SERVER_H


#define MAX_ARRAY_SIZE 200

struct Servers{
    char *name;
    char *filePath;
};
void startMCServer();
void stopMCServer();
void addMCserver();
void removeMCServer();
void whatServerIsRunning();
void enterMCServerScreen();
void copyFromServersFile();
void writeToServersFile();
void checkIfServerFileIsEmpty();
int isAServerRunning();
void listServers();

#endif //MCSERVER_SERVER_H
