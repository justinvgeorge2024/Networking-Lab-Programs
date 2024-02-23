// header file
#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) {
    // initialize variables
    int client_sock;
    struct sockaddr_in client_addr, server_addr;
    char client_msg[2000], server_msg[2000];

    // clean buffer that had been initialized
    memset(client_msg, '\0', sizeof(client_msg));
    memset(server_msg, '\0', sizeof(server_msg));

    // create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(client_sock < 0) {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // set port and IP
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(4040);

    // connect to server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
    {
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    // send message to server
    printf("Enter message: ");
    fgets(client_msg,2000,stdin);
    if(send(client_sock, client_msg, strlen(client_msg), 0)<0){
        printf("Unable to send the message\n");
        return -1;
    }
    printf("Message has been send.\n");
    
    printf("Waiting for message from server\n");
    // receive message from the server
    if (recv(client_sock, server_msg, sizeof(server_msg), 0) < 0)
    {
        printf("Couldn't receive\n");
        return -1;
    }
    printf("Message from server: %s\n", server_msg);

    // close the connection
    close(client_sock);
    return 0;
}
