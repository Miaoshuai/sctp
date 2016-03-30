/*======================================================
    > File Name: server.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年03月30日 星期三 21时11分46秒
 =======================================================*/
#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#define SERVER_PORT 3333
#define BUFFER_SIZE 1024
#define LISTEN_QUEUE 100

class SctpServer
{
    public:
        SctpServer();
        void start(void);
    private:
        //开启监听socket
        void listenSocket(void);
        //循环处理请求
        void loop(void);

        int sockFd_;
        int messageFlags_;
        char readBuf_[BUFFER_SIZE];
        struct sockaddr_in clientAddr_;
        struct sockaddr_in serverAddr_;
        struct sctp_sndrcvinfo sri_;
        struct sctp_event_subscribe events_;
        int streamIncrement_;
        socklen_t len_;
        size_t readSize_;
};
