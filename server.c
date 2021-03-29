#include "server.h"


int main()
{
    int ret;        //Return value for various checks


    struct sockaddr_in s_info,c_info;              //Server Socket Info

    int c_len = sizeof(c_info);

    s_info.sin_family = AF_INET;            //IPv4 Protocol
    s_info.sin_port = htons(PORT);          //Host to Network short
    s_info.sin_addr.s_addr = INADDR_ANY;    //Local Interface IP


    //Initialize socket
    s_sock = socket(AF_INET,SOCK_STREAM,0); 
    if(s_sock == -1){
        error();
    }

    if(setsockopt(s_sock,SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int))<0){      //Use SO_REUSEADDR for repeated execution
        error();
    }

    //Bind socket
    ret = bind(s_sock,(struct sockaddr*)&s_info,sizeof(s_info));
    if(ret == -1){
        error();
    }
    //Start listening for incoming connections
    ret = listen(s_sock,5);
    if(ret == -1){
        error();
    }
    system("clear");        //Clear terminal screen
    printf("Listening for connection\n");

    while(1){
        sockfd1 = accept(s_sock,(struct sockaddr*)&c_info,(socklen_t*)&c_len);      //Accept Connection from client
        if(sockfd1 == -1){
            error();
        }
        strcpy(message,"");

        sockarr[user_count] = sockfd1;          //Add client's sockFD to array
        user_count++;

        ret = pthread_create(&thread1,NULL,UserHandler,(void*)&sockfd1);    //Create new thread for client
        if(ret == -1){
            error();
        }


    }
    //Exit cleanup
    close(s_sock);
    printf("Connection closed\n");
    pthread_join(thread1,NULL);
    close(sockfd1);

    return 0;


}