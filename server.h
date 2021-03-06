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

char message[MAX_MSG_LEN];      //Message to be sent
char username[USERNAME_LEN];    //Username of the client

//User node to store info about the client
struct u_node{
    int sockfd;
    char username[30];
};
typedef struct u_node user_node;



int s_sock = 0;     //Server socket
int flag = 0;       //Termination flag
int sockfd1;        //Socket for accepting the client
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
//Send message to all users except self
void SendMessage(int sock,char * buff,char * uname)
{
    char temp[USERNAME_LEN];

    strcpy(temp,"");        //Building the message string
    strcpy(temp,uname);
    strcat(temp,"> ");
    strcat(temp,buff);

    for(int i=0;i<user_count;i++){
        if(sockarr[i] != sock){
            write(sockarr[i],temp,strlen(temp));
        }
    }
}


//Announcing to other users that a user has entered the chat
void UserJoin(int sock,char * username)
{
    char temp[30];
    
    strcpy(temp,"");
    strcpy(temp,username);
    strcat(temp," has entered the chat");

    for(int i=0;i<user_count;i++){
        if(sockarr[i] != sock){
            write(sockarr[i],temp,MAX_MSG_LEN);
        }
    }
}
//Announcing exit of the user to all other users
void UserExit(int sock,char * username)
{
    char temp[30];
    
    strcpy(temp,"");
    strcpy(temp,username);
    strcat(temp," has left the chat");

    for(int i=0;i<user_count;i++){
        if(sockarr[i] != sock){
            write(sockarr[i],temp,MAX_MSG_LEN);
        }
    }
}

//Driver function for user handling
void * UserHandler(void * ptr)
{

    user_node * new_user = (user_node*)malloc(sizeof(user_node));   //To store sockFD and Username
    int connfd = *(int*)ptr;        //Store sockFD in sturct


    int ret = read(connfd,new_user->username,31);     //Receive username
    if(ret == -1){
        printf("%s",strerror(errno));
    }    
    printf("%s is online\n",new_user->username);


    UserJoin(connfd,new_user->username);            //User join announcement


    while(strncmp(message,"/q",2) != 0){
        ret = read(connfd,message,1024);
        if(ret == -1){
            error();
        }
        if(strncmp(message,"/q",2) != 0){
            printf("%s> %s\n",new_user->username,message);
            SendMessage(connfd,message,new_user->username);
        }else{                                                                  //Exit Case for the chat
            printf("%s has left the chat\n",new_user->username);
            UserExit(connfd,new_user->username);                //Exit announcement
            user_count--;                                       //Decrease user count
        }
    }


}