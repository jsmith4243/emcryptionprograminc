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

    char buffer[100000];
    if (argc < 4) {

       fprintf(stderr,"usage %s plaintext key port\n", argv[0]);
       exit(0);
    }
    
    FILE *plaintextFile;
    FILE *keyFile;
    plaintextFile = fopen(argv[1], "r");
    keyFile = fopen(argv[2], "r");
    long plaintextFileLength;
    long keyFileLength;
    
    char *plaintext = 0;
    char *key = 0;
    
    if (plaintextFile)
    {
    
    	fseek(plaintextFile, 0, SEEK_END);
    	
    	plaintextFileLength = ftell(plaintextFile);
    	
    	fseek(plaintextFile, 0, SEEK_SET);
    	

    	plaintext = malloc(plaintextFileLength);
    	
    	

    	if (plaintext)
    	{
    		fread(plaintext, 1, plaintextFileLength, plaintextFile);
    	}
    	
    	fclose(plaintextFile);
    }
    
    
    if (keyFile)
    {
    
    
    
    	fseek(keyFile, 0, SEEK_END);
    	
    	keyFileLength = ftell(keyFile);
    	
    	

    	fseek(keyFile, 0, SEEK_SET);
    	
  
    	key = malloc(keyFileLength);
    	
    	
    	
    	
    	
    	if (key)
    	{
    		fread(key, 1, keyFileLength, keyFile);
    	}
    	
    	fclose(keyFile);
    }
    
    plaintext[(strlen(plaintext)-2)] = '\0';
    key[(strlen(key)-1)] = '\0';
    
    
    
    if (strlen(key) < strlen(plaintext))
    {
    
    	printf("ERROR: the key is smaller than the plaintext. Exiting with error.\n");
    	return 1;
    	
    
    }
    

    	

    
    portno = atoi(argv[3]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
        
           		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
   			error("setsockopt(SO_REUSEADDR) failed");
        
   

    server = gethostbyname("localhost");
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
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
   
    bzero(buffer,100000);

    
     n = read(sockfd,buffer,100000);
	 if (n < 0) 
     error("ERROR reading from socket");
     

     
     char newPort[8];
     int newPortInt;
     
     strcpy(newPort, buffer);
     
  
     newPortInt = atoi(newPort);
     
  
     
      
     
     close(sockfd);
     
     
     

     
    
     
    portno = newPortInt;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
        
        
           		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
   			error("setsockopt(SO_REUSEADDR) failed");
        

   
    server = gethostbyname("localhost");
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
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    bzero(buffer,100000);
    
     
     
    
    char space[2] = " ";
    char keyTag[5] = "KEY:";
    char plainTextTag[11] = "PLAINTEXT:";
    char transmissionTag[14] = "TRANSMISSION:";
    
    strcat(buffer, &transmissionTag);
    strcat(buffer, &space);
    strcat(buffer, &keyTag);
    strcat(buffer, &space);
    strcat(buffer, key);
    strcat(buffer, &space);
    strcat(buffer, &plainTextTag);
    strcat(buffer, &space);
    strcat(buffer, plaintext);
    
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,100000);
    n = read(sockfd,buffer,100000);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    
  
    
    return 0;
}