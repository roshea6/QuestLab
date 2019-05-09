/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256]; //Server will read data from socket into this buffer
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);  //socket() creates a new socket and assigns it to sockfd var
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);    //Get port number that socket will bind to later 
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //Binds socket to the assigned port number
        error("ERROR on binding");

        
    listen(sockfd,5); //Tell socket to listen for incoming connections
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //Accept new incoming socket connection from the client. Continuously runs until connection happens
    if (newsockfd < 0) 
        error("ERROR on accept");

    printf("Client connected \n");
 

     while(1)
     {
        bzero(buffer, 256); //Clear buffer in between new messages
        n = read(newsockfd,buffer,255);    //Read data from socket into the buffer
        if (n < 0) error("ERROR reading from socket");

        else if(strncmp(buffer, "Client has disconnected", sizeof("Client has disconnected")) == 0) //If client sends disconnected message then break out of loop
        {
            printf("%s\n", buffer);
            break;
        }

        printf("Message received from client: %s\n",buffer);    //Display message from client
        // n = write(newsockfd,"I got your message",18);  //Send confirmation message back to client
        // if (n < 0) 
        // {
        //     error("ERROR writing to socket");
        // }
        

     }

     close(newsockfd);  //Close the sockets
     close(sockfd);
     return 0; 
}