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
void startMCServer(struct Servers *servers);
void stopMCServer();
void addMCserver(struct Servers *servers);
void removeMCServer(struct Servers *servers);
void whatServerIsRunning();
void enterMCServerScreen();
int copyFromServersFile(struct Servers *servers);
void writeToServersFile(struct Servers *servers);
int isAServerRunning();
void listServers(struct Servers *servers);
int notAValidSelection(struct Servers *servers, int option);
int findEmptySpot(struct Servers *servers);
void zeroArray(char *arr);
void performRemovalAction(struct Servers *servers, int opt);

#endif //MCSERVER_SERVER_H
