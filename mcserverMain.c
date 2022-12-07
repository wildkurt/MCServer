//
// Created by minecraft on 11/29/22.
//
#include <stdio.h>
#include <string.h>
#include "mcserverMain.h"
/**1. Need to provide a menu
 * 2. Option to add minecraft servers
 * 3. Option to remove minecraft servers
 * 4. Option to start minecraft servers
 * 5. Option to stop minecraft server
 * 6. Option to see what server is running
 * 7. Option to join minecraft server
 * 8. Option to quit program
 * 9. Option to list servers*/

char runningpath[MAX_ARRAY_SIZE];
char savepath[MAX_ARRAY_SIZE];

int main(int argc, char *argv[]){
    char input;
    struct Node *head=0;
    if(argc < 3){
        fprintf(stderr, "must provide paths to running.txt and servers.txt");
    }
    else{
        strcat(runningpath, argv[1]);
        strcat(savepath, argv[2]);
    }
    openServerList(&head);

    printf("Hello, this program will help manage multiple installations of Minecraft servers\n");
    while(input != 'x'){
        printf("1. List available servers\n");
        printf("2. Add a server\n");
        printf("3. Remove a server\n");
        printf("4. Start a server\n");
        printf("5. Currently running server\n");
        printf("6. Stop currently running server\n");
        printf("7. Join server instance\n");
        printf("Input an option from above, x to exit\n");
        input = getchar();
        getchar();
        printf("You selected %c\n",input);
        switch(input){
            case '1' : listServers(head); break;
            case '2' : addServer(&head); break;
            case '3' : removeServer(&head);break;
            case '4' : startServer(head); break;
            case '5' : runningServer();break;
            case '6' : stopRunningServer(head);break;
            case '7' : joinServerInstance(head);break;
            case 'x' : break;
            default: printf("Invalid option\n"); break;
        }
    }
    closeServerList(&head);
    printf("Goodbye\n");
    return 0;
}
