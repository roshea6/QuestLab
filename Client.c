#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];   //Buffer for message to be stored in
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]); //Get the port number from the passed in arguements
    sockfd = socket(AF_INET, SOCK_STREAM, 0);   //Create the socket and assign it to sockfd var
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);    //Obtain the name of the host server that you'll communicate with from passed in args
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //Establish connection to the host. Will continuously run until succesful connection or error (i.e connection specified server doesn't exist)
        error("ERROR connecting");

    printf("Send 'quit' to exit \n");

    while(1)
    {
        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);    //Get user message and put it in the buffer

        if(strncmp(buffer, "quit\n", sizeof("quit\n")) == 0)
        {
            char buffer2[] = "Client has disconnected";
            n = write(sockfd,buffer2,strlen(buffer2));   //Inform the server that you have disconnected
            break;
        }

        else
        {
            n = write(sockfd,buffer,strlen(buffer));    //Write the buffer to the socket
            if (n < 0) 
                error("ERROR writing to socket");
            bzero(buffer,256);  //Clear buffer
            n = read(sockfd,buffer,255);    //Read response from server from the buffer
            if (n < 0) 
                error("ERROR reading from socket");
            printf("%s\n",buffer);  //Display response
        }
        
        
    }
    
    close(sockfd);  //Close the socket 
    return 0;
}