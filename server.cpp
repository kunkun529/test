#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    char ip[] = "0.0.0.0";//
    int port = 1234;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(sock, 20);

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_addr_size);

    char buffer[200], msg[200];
    while(strcmp(buffer, "q") != 0 ){
        int ret = 0;
        cout << ">>> ";
        cin >> msg;
        write(client_sock, msg, sizeof(msg));
        if(strcmp(msg, "q") == 0){
            break;
        }
        while(ret != 199){
            ret = read(client_sock, buffer, sizeof(buffer)-1);
            sleep(0.2);
        }
        cout << "client: " << buffer << endl;
    }
   
    close(client_sock);
    close(sock);

    return 0;
}

