#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    const char * ip = "127.0.0.1";
    int port = 1234;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        cout << "connect socket error." << endl;
        return -1;
    }
   
    char buffer[200], msg[200];
    while(strcmp(msg, "q") != 0){
        int ret = 0;
        while(ret != 199){
            ret = read(sock, buffer, sizeof(buffer)-1);
            sleep(0.2);
        }
        cout << "server: " << buffer << endl;
        if(strcmp(buffer, "q") == 0){
            break;
        }
        cout << ">>> ";
        memset(&buffer, 0, sizeof(buffer)); 
        cin >> msg;
        write(sock, msg, sizeof(msg));
    }
      
    close(sock);

    return 0;
}