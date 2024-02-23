//Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
# define PORT 8080
#define MAXLINE 1024
// Driver code
int main () {
int sockfd;
char buffer [MAXLINE];
char msg[30];

struct sockaddr_in servaddr, cliaddr;
//Creating socket file descriptor
if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0){
perror ("socket creation failed" );
exit (EXIT_FAILURE);
}
printf("socket successfully created\n");
memset (&servaddr, 0, sizeof(servaddr) );
memset (&cliaddr, 0, sizeof(cliaddr) );
// Filling server information
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
// Bind the socket with the server address
if (bind (sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
{perror( "bind failed\n") ;
exit (EXIT_FAILURE);
}
printf("Bind successful\n");
int len, n;
n = sizeof(cliaddr); //len is value/result

printf("waiting to recieve message from client\n");

n = recvfrom(sockfd, (char *) buffer, MAXLINE, MSG_WAITALL,(struct sockaddr *) &cliaddr, &len) ;

buffer[n] = '\0';
printf("Client message: %s", buffer);

printf("Type message to be sent to client:");
fgets(msg,30,stdin);

sendto (sockfd, (const char *)msg, strlen (msg) , MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len) ;
printf ("Message sent.\n");
return 0;
}
