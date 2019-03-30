/*
* 根据所学的前三小节的知识写一个Demo
*/
#include <sys/socket.h>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cassert>
#include <libgen.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>

using namespace std;

//停止的信号
static bool stop = false;
static void handle_term(int sig){
    stop = true;
}


int main(int argc, char ** argv){
    //信号 回调 SIGTERM指定监听发送给本程序的终止请求信号
    signal(SIGTERM, handle_term);

    if (argc < 3){
        cout << "usage:" << basename(argv[0]) <<
            "ip_address port_number backlog" << endl;
        return 1;
    }
    const char * ip = argv[1];
    //将字符串转换为整形数
    int port = atoi(argv[2]);
    //指定最大连接数
    int backlog = atoi(argv[3]);

    //创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //创建失败则断言
    assert(sockfd >= 0);

    //创建IPV4 socket地址
    struct sockaddr_in address;
    //将address的内存初始化
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    //将字符串IP地址转换后存储到address里
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, backlog);
    assert(ret != -1);

    //创建连接套接字
    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);

    //等待连接
    while (!stop){
        sleep(1);
        //接收连接
        int connfd = accept(sockfd, (struct sockaddr *)&client, &client_addrlength);
        if (connfd < 0){
            //连接失败
            cout << "[-]Error code is: " << errno << endl;
            exit(errno);
        }
        else{
            //打印连接后的客户端信息 创建一个ipv4信息大小的数组
            char remote[INET_ADDRSTRLEN];
            cout << "[+]Connected with ip: "
                //将client的sin_addr转换成字符串存储到remote数组中
                << inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN)
                << "\tport:"
                //将端口信息转换成数字类型
                << ntohs(client.sin_port)
                << endl;
            //connfd保存的是这次连接的信息 而client保存的则是客户端的信息
            close(connfd);
        }
    }

    //程序结束关掉socket
    close(sockfd);

    return 0;
}
