#include "server.h"


int main()
{
    int ret;

    char message[MAX_MSG_LEN];
    char username[USERNAME_LEN];



    struct sockaddr_in s_info;              //Server Socket Info

    s_info.sin_family = AF_INET;            //IPv4 Protocol
    s_info.sin_port = htons(PORT);          //Host to Network short
    s_info.sin_addr.s_addr = INADDR_ANY;    //Local Interface IP


    //Initialize socket
    s_sock = socket(AF_INET,SOCK_STREAM,0); 
    if(s_sock == -1){
        error();
    }
    //Bind socket
    ret = bind(s_sock,(struct sockaddr*)&s_info,sizefo(s_info));
    if(ret == -1){
        error();
    }
    //Start listening for incoming connections
    ret = listen(s_sock,5);
    if(ret == -1){
        error();
    }

}