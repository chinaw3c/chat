/*
 * 根据所学的前三小节的知识写一个Demo
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>
#include <libgen.h>
#include <iostream>
#include <signal.h>

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
    //清空address的内存
    memset(&address, 0, sizeof(address));


}
