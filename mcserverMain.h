//
// Created by minecraft on 11/29/22.
//

#ifndef MCSERVER_MCSERVERMAIN_H
#define MCSERVER_MCSERVERMAIN_H

#define MAX_ARRAY_SIZE 200

struct Node{
    char *directory;
    char *name;
    struct Node *next;
    struct Node *prev;
};

void push(struct Node**, char*, char*);
void pop(struct Node**);
void listServers(struct Node *);
void addServer(struct Node**);
void removeServer(struct Node**);
void startServer(struct Node*);
void runningServer();
void stopRunningServer(struct Node*);
void joinServerInstance(struct Node*);
void openServerList(struct Node **);
void closeServerList(struct Node **);
#endif //MCSERVER_MCSERVERMAIN_H
