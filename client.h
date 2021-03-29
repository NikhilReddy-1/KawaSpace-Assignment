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


void * SendMessage(void * ptr){
    char message[1024];
    
    while(1){
        fgets(message,1024,stdin);
        message[strlen(message)-1] = '\0';

        //printf("TEST:%s\n",message);

        int ret = write(c_sock,message,strlen(message)+1);
        if(ret == -1){
            error();
        }


        if(strcmp(message,"/q") == 0){
            printf("Client logged out\n");
            write(c_sock,message,strlen(message)+1);
            flag = 1;
            break;
        }
    }
}


void * RecvMessage(){
    char buff[1024];
    while (1) {
        bzero(&buff,sizeof(buff));
        int receive = read(c_sock, buff, 1024);	//dexetai to mhnyma, to kanoyme etsi gt otan h metavlith pairnei thn timh 1 
	if (receive > 0) {			//tote doulevei swsta alliws an einai 0 tote apetyxe
            printf("%s\n", buff);
        }
		else{
			printf("error in recvHandler....\n");
            break;
        }
		
    }
}