#include "server.h"


int main()
{
    int ret;

    char message[MAX_MSG_LEN];
    char username[USERNAME_LEN];



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

    printf("Listening for connection\n");

    while(1){
        sockfd1 = accept(s_sock,(struct sockaddr*)&c_info,(socklen_t*)&c_len);
        if(sockfd1 == -1){
            error();
        }
        strcpy(message,"");

        sockarr[user_count] = sockfd1;
        user_count++;

        ret = pthread_create(&thread1,NULL,UserHandler,(void*)&sockfd1);
        if(ret == -1){
            error();
        }


    }
    close(s_sock);
    printf("Connection closed\n");
    pthread_join(thread1,NULL);
    close(sockfd1);

    return 0;


}