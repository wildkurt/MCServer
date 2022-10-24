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

struct Servers servers[MAX_ARRAY_SIZE];

void startMCServer();
void stopMCServer();
void addMCserver();
void removeMCServer();
void whatServerIsRunning();
void enterMCServerScreen();
int copyFromServersFile();
void writeToServersFile();
int isAServerRunning();
void listServers();
int notAValidSelection(int option);
int findEmptySpot();
void zeroArray(char *arr);
void performRemovalAction(int opt);

#endif //MCSERVER_SERVER_H
