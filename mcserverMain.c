//
// Created by minecraft on 11/29/22.
//
#include <stdio.h>
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
int main(int argc, char *argv[]){
    char input;
    struct Node *head=0;

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
            case '6' : printf("Not implemented yet\n");break;
            case '7' : printf("Not implemented yet\n");break;
            case 'x' : break;
            default: printf("Invalid option\n"); break;
        }
    }
    printf("Goodbye\n");
    return 0;
}
