/*======================================================
    > File Name: server.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年03月30日 星期三 21时22分28秒
 =======================================================*/
#include "server.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

SctpServer::SctpServer()
    :streamIncrement_(1)
{

}

void SctpServer::listenSocket(void)
{
    //创建SCTP套接字
    sockFd_ = socket(AF_INET,SOCK_SEQPACKET,IPPPOTO_SCTP);
    bzero(&serverAddr_,sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr_.sin_port = htons(SERVER_PORT);
    
    //地址绑定
    bind(sockFd_,(SA *)&serverAddr_,sizeof(serverAddr_));

    //设置SCTP通知事件(此处只设置了I/O通知事件)
    bzero(&events_,sizeof(events_));
    events_.sctp_data_io_event = 1;
    setsockopt(sockFd_,IPPROTO_SCTP,SCTP_EVENTS,&events_,sizeof(events_));
    
    //开始监听
    listen(sockFd_,LISTEN_QUEUE);
}

void SctpServer::loop(void)
{
    while(true)
    {
        len_ = sizeof(struct sockaddr_in);
        //从socket读取内容
        readSize_ = sctp_recvmsg(sockFd_,readBuf_,BUFFER_SIZE,
                                 (SA *)&clientAddr_,&len_,&sri_,&msgFlags_);
        //增长消息流号
        if(streamIncrement_)
        {
            sri_.sinfo_stream++;
            if(sri_.sinfo_stream >= sctp_get_no_strms(sockFd_,(SA *)&clientAddr_,len_))
            {
                sri_.sinfo_stream = 0;
            }
        }
        sctp_sendmsg(sockFd_,readBuf_,readSize_,
                     (SA *)&clientAddr_,len_,
                      sri_.sinfo_ppid,sri_.sinfo_flags,sri_.sinfo_stream,0,0);
    }
}

void SctpServer::start(void)
{
    listenSocket();
    loop();
}
