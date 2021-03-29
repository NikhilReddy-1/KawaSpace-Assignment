#include "client.h"


int main()
{
    int ret;
    int r_flag = 0;

    char message[MAX_MSG_LEN];
    char username[USERNAME_LEN];
    char choice[2] = {};


    struct sockaddr_in c_info;              //Socket info initialize

    c_info.sin_addr.s_addr = INADDR_ANY;    //Local interface IP
    c_info.sin_family = AF_INET;            //IPv4 protocol
    c_info.sin_port = htons(PORT);          //Host to network short the port



    while(r_flag == 0){
        flag = 0;
        system("clear");
        printf("Enter your choice\n\n\t/c for chat\n\t/x to exit");
        scanf("%s",choice);
        printf("Choice is %s\n",choice);
        while((getchar()) != '\n');

        if(strcmp(choice,"/c") == 0){                   //"/c" condition
            system("clear");
            c_sock = socket(AF_INET,SOCK_STREAM,0);
            if(c_sock == -1){
                error();
            }
            //Connect to the srever
            int connfd = connect(c_sock,(struct sockaddr*)&c_info,sizeof(c_info));
            if(connfd == -1){
                error();
            }
            
            strcpy(username,"");
            system("clear");                        //Clear screen

            printf("\n\t\tEnter your Username\n\n");
            fgets(username,strlen(username),stdin);
            //scanf("%s",username);
            printf("\n\n");
            username[strlen(username)-1] = '\0';    //Removing '\n' from the end of the string


            int snn = write(connfd,username,strlen(username)+1);    //Sending username
            if(snn == -1){
                printf("Send error\n");
                exit(0);
            }

            pthread_t SendHandle;
            if(pthread_create(&SendHandle,NULL,SendMessage,(void*)&connfd) != 0){
                error();
            }

            pthread_t RecvHandle;
            if(pthread_create(&RecvHandle,NULL,RecvMessage,(void*)&connfd) != 0){
                error();
            }

            while(1){
                if(flag == 1){
                    close(c_sock);
                    break;
                }
            }
        }
        else if(strcmp(choice,"/x") == 0){      //"/x" Condition
            flag = 1;
            close(c_sock);
            r_flag = 1;
        }
    }


    return 0;
}