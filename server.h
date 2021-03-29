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


#define MAX_MSG_LEN 1024
#define USERNAME_LEN 30


int s_sock = 0;     //Server socket
int flag = 0;       //Termination flag


