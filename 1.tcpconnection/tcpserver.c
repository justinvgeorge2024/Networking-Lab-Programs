#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
	int socket_desc, client_sock,client_size;
	struct sockaddr_in server_addr, client_addr;
	char server_message[2000], client_message[2000];

	memset(client_message, '\0', sizeof(client_message));
	memset(server_message, '\0', sizeof(server_message));

	// create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc < 0){
	printf("Socket creation failed\n");
	return -1;
	}
	printf("Socket created successfully!\n");

	// set port and ip
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4040);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// bind to set port and ip
	if(bind(socket_desc,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
	printf("Couldn't bind the port\n");
	return -1;
	}
	printf("Done with binding\n");
	if (listen(socket_desc, 1) < 0){
	printf("Error while listening!");
	return -1;
	}
	printf("Listening for connections.....\n");

	// accept an incoming connection
	client_size = sizeof(client_addr);
	client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);
	if (client_sock < 0)
	{
	printf("Can't accept");
	return -1;
	}
	else {
	printf("Connected IP: %s, Port: %d\n",
	inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));

	}

	// receive and send message (client <-> server)
	if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
	{
	printf("Couldn't receive\n");
	return -1;
	}
	printf("Message from client: %s", client_message);
	
        printf("Enter message: ");
	fgets(server_message,2000,stdin);
	if(send(client_sock, server_message, strlen(server_message), 0)<0) {
	printf("Can't send");
	return -1;
	}
	printf("Message has been sent to the client\n");
	// close the socket
	close(client_sock);
	close(socket_desc);
	return 0;
}
