/*======================================================
    > File Name: main.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年03月30日 星期三 23时35分26秒
 =======================================================*/
#include "server.h"

int main(int argc,char **argv)
{
  SctpServer server;
  server.start();
  return 0;
}
