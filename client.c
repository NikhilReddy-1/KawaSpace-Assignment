#include "client.h"


int main()
{
    int ret;

    char message[MAX_MSG_LEN];
    char username[USERNAME_LEN];


    struct sockaddr_in c_info;              //Socket info initialize

    c_info.sin_addr.s_addr = INADDR_ANY;    //Local interface IP
    c_info.sin_family = AF_INET;            //IPv4 protocol
    c_info.sin_port = htons(PORT);          //Host to network short the port

    //Initialize socket
    c_sock = socket(AF_INET,SOCK_STREAM,0);
    if(c_sock == -1){
        error();
    }
    //Connect to the srever
    int connfd = connect(c_sock,(struct sockaddr*)&c_info,sizeof(c_info));
    if(connfd == -1){
        error();
    }


    system("clear");                        //Clear screen
    printf("\t\tEnter your Username\n\n");
    fgets(username,USERNAME_LEN,stdin);
    //RemoveNewLine(username);                //Remove the '\n' character from end
    username[strlen(username)-1] = '\0';


    int snn = write(connfd,username,strlen(username)+1);    //Sending username
    if(snn == -1){
        printf("Send error\n");
        exit(0);
    }

    pthread_t 

}