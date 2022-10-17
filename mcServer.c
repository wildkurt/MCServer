
#include <stdio.h>
#include "server.h"

/**This program is for starting and stopping Minecraft servers. Need
 * a menu with the options of:
 * 1. Start a server
 *      a. Opens another menu listing the servers
 * 2. stop a server
 *      a. Stops whatever server is running
 * 3. add a server
 *      a. adds the path and name of the server
 * 4. remove a server
 *      b. remove the path and name of a server
 * 5. See what server is running
 *      a. screen -ls
 * 6. Access the server command line
 *      a. screen -r <server>
 * 7. Exit the program*/

struct Servers serverList[MAX_ARRAY_SIZE];
int serverListSize = 0;

int main(int argc, char *argv[]){
    char input;
    //Explain what the program does
    printf("This program can start and stop Minecraft servers on this PC.\n");
    printf("New servers can be added and old ones removed.\n");
    printf("Determine what server is running, and access the server command line\n");
    //Menu for the 7 options
    while(1){
        printf("Please chose from the following options:\n");
        printf("1. Start a server\n");
        printf("2. Stop a server\n");
        printf("3. Add a server\n");
        printf("4. Remove a server\n");
        printf("5. What server is running?\n");
        printf("6. Enter server screen\n");
        printf("7. Exit program\n");

        input = getchar();
        getchar();

        switch (input) {
            case '1' : startMCServer();
            case '2' : stopMCServer();
            case '3' : addMCserver();
            case '4' : removeMCServer();
            case '5' : whatServerIsRunning();
            case '6' : enterMCServerScreen();
            case '7' : break;
        }
    }
    return 0;
}

