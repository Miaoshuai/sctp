/*======================================================
    > File Name: client.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年03月30日 星期三 21时55分04秒
 =======================================================*/
#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SERVER_PORT 3333

class SctpClient
{
    public:
        SctpClient():echoToAll_(0)
        {
    
        }

        void start(void)
        {
            makeSocket();
        }
    private:
        void makeSocket(void)
        {
            sockFd_ = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP);
            bzero(&serverAddr_,sizeof(serverAddr_));
            serverAddr_.sin_family = AF_INET;
            serverAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
            serverAddr_.sin_port = htons(SERVER_PORT);

            bzero(&events_,sizeof(events_));
            events_.sctp_data_io_event = 1;
            setsockopt(sockFd_,IPPROTO_SCTP,SCTP_EVENTS,&events_,sizeof(events_));
            if(echoToAll_ == 0)
            {
                sctpstr_cli(stdin,sockFd_,(SA *)&serverAddr_,sizeof(serverAddr_));
            }
            else
            {
                sctpstr_cli_echoall(stdin,sockFd_,(SA *)&serverAddr_,sizeof(serverAddr_));
            }
            close(sockFd_);
        }

        int sockFd_;
        struct sockaddr_in serverAddr_;
        struct sctp_event_subscribe events_;
        int echoToAll_;
};
