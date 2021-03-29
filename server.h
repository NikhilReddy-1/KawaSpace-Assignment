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


struct u_node{
    int sockfd;
    char username[30];
};
typedef struct u_node user_node;

int s_sock = 0;     //Server socket
int flag = 0;       //Termination flag
int sockfd1;
int user_count = 0; //Total num of current users

int sockarr[100];   //Array to store all sockFDs of users

pthread_t thread1;


//Error return function using perror
void error()
{
    fprintf(stderr,"\nERROR VAL:%d\n",errno);
    fprintf(stderr,"%s\n",strerror(errno));
    exit(1);
}

//Announcing to other users that a user has entered the chat
void UserJoin(int sock,char * username)
{
    char temp[30];
    
    strcpy(temp,"");
    strcpy(temp,username);
    strcat(temp,"has entered the chat");

    for(int i=0;i<user_count;i++){
        if(sockarr[i] != sock){
            write(sockarr[i],temp,MAX_MSG_LEN);
        }
    }
}

//Driver function for user handling
void * UserHandler(void * ptr)
{
    char Username[USERNAME_LEN] = {};

    //user_node * new_user = (user_node*)malloc(sizeof(user_node));

    int connfd = *((int*)ptr);        //Store sockFD in sturct


    int ret = read(connfd,Username,30);     //Receive username
    if(ret == -1){
        printf("%s",strerror(errno));
    }
    
    printf("%s is online\n",Username);













}