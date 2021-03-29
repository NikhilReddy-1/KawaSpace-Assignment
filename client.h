#include <stdio.h>      //Std I/O
#include <stdlib.h>     //For Malloc() and Free()
#include <string.h>     //For string operatoins strcat()
#include <signal.h>     //For exit signals
#include <unistd.h>     //POSIX API
#include <sys/types.h>  //OS Types
#include <sys/socket.h> //Sockets Library
#include <netinet/in.h> //Inet Protocols
#include <arpa/inet.h>  //Internet Operations
#include <pthread.h>    //Multithreading Library
#include <errno.h>       //Error handling


#define MAX_MSG_LEN 1024
#define USERNAME_LEN 30
#define PORT 8080


int c_sock = 0;     //Server socket
int flag = 0;       //Termination flag


//Error return function using perror
void error()
{
    fprintf(stderr,"\nERROR VAL:%d\n",errno);
    fprintf(stderr,"%s\n",strerror(errno));
    exit(1);
}

void RemoveNewLine(char * username)
{
    username[strlen(username) - 1] = '\0';
}


void * SendMessage(){
    char message[MAX_MSG_LEN];

    while(1){
        fgets(message,MAX_MSG_LEN,stdin);
        message[strlen(message)-1] = '\0';

        write(c_sock,message,strlen(message)+1);

        if(strcmp(message,"/q") == 0){
            printf("Client logged out\n");
            write(c_sock,message,strlen(message)+1);
            flag = 1;
            break;
        }
    }
}


void * RecvMessage(){
    char message[MAX_MSG_LEN];

    while(1){
        int ret = read(c_sock,message,MAX_MSG_LEN);

        if(ret > 0){
            printf("%s\n",message);
        }       
        else{
        printf("Error in recvHandler");
        }
        break;
    }
}