#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char ** argv){
    //创建一个字符串ipv4地址
    in_addr a;
    a.s_addr = inet_addr("1.1.1.1");
    in_addr b;
    b.s_addr = inet_addr("2.2.2.2");

    char *ipv41 = inet_ntoa(a);
    char *ipv42 = inet_ntoa(b);


    cout << "address 1> " << ipv41 << endl;
    cout << "address 2> " << ipv42 << endl;


    return 0;
}
