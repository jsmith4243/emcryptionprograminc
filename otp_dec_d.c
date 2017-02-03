/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
   
//v2 - use other port
//v3 - fork
//v4 - infinite loop
//v5 - refined enc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int firstRun = 1;

int main(int argc, char *argv[])
{

	
	pid_t childPID;
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[100000];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
    
    	fprintf(stderr,"ERROR, no port provided\n");
    	exit(1);
    	
     }
     
    
     
     while (1)
     {
     
     	
     
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
			error("ERROR opening socket");
			
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
   		error("setsockopt(SO_REUSEADDR) failed");
			

   			
		bzero((char *) &serv_addr, sizeof(serv_addr));
		if (firstRun)
		{
		portno = atoi(argv[1]);
		}
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
			error("ERROR on binding");
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     	if (newsockfd < 0) 
          error("ERROR on accept");
          
        
        
     	bzero(buffer,100000);

		int randomSocket;
		randomSocket = rand () % 10000 + 50000;
		char randomSocketStr[6];
		sprintf(randomSocketStr, "%d", randomSocket);
     

		n = write(newsockfd,randomSocketStr,100000);
		if (n < 0) error("ERROR writing to socket");
     
     	close(newsockfd);
     	close(sockfd);
     
     	childPID = fork();
     	
     	

     	if(childPID == 0) 
     	{
     	
     
     
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
     		if (sockfd < 0) 
       			error("ERROR opening socket");
       			
       		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
   			error("setsockopt(SO_REUSEADDR) failed");
   			
			bzero((char *) &serv_addr, sizeof(serv_addr));
			portno = randomSocket;
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = INADDR_ANY;
			serv_addr.sin_port = htons(portno);
			if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
            	error("ERROR on binding");
     		listen(sockfd,5);
			clilen = sizeof(cli_addr);
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     		if (newsockfd < 0) 
          		error("ERROR on accept");
     		bzero(buffer,100000);

			n = read(newsockfd,buffer,100000);
     		if (n < 0) error("ERROR reading from socket");
	
			int size = 0;
			size = sizeof(buffer);

    

    		char space[2] = " ";
    
    		char key[100000];
    		key[0] = '\0';
    		char plaintext[100000];
    		plaintext[0] = '\0';
     
    		char *token;
        
    		token = strtok(buffer, " ");
       
 
		
    		while (token != NULL)
    		{

    			token = strtok(NULL, " ");
    	

       			if (strcmp(token, "KEY:" ) == 0) 
        		{     
        
        	
        			while (strcmp(token, "PLAINTEXT:") != 0)
        			{
        	
        		
        	
        				token = strtok(NULL, " ");
        	
        				if(strcmp(token, "PLAINTEXT:") != 0)
        				{
        	
        					strcat(key, token);
        				}
        	
        			}
        		}
        
        	
        
       			if (strcmp(token, "PLAINTEXT:" ) == 0)
        		{
        	
        	
        			while(token = strtok(NULL, " " ))
        			{
        	
        				strcat(plaintext, token);
        		
        				strcat(plaintext, space);
        			}
        		}
    		}
    
    
 
    
    		char encryptedPlaintext[100000];
    
    		char currentChar;
    
    		strcpy(encryptedPlaintext, plaintext);
    

    
    
    		for (int i = 0; i < strlen(encryptedPlaintext)-1; i++)
    		{
    
    			if (encryptedPlaintext[i] == 32) /*is space*/
    			{
    				continue;
    			}
    			else
    			{
    	

    			
    				/*encryptedPlaintext[i] = ( mod( (encryptedPlaintext[i]-65) + (key[i] - 65) ,26) )+65;*/
    				

					encryptedPlaintext[i] = ( mod( (encryptedPlaintext[i]-65) - (key[i] - 65)  ,26) ) +65;
					
					
    			}
   			}
    

    

     

    		n = write(newsockfd,encryptedPlaintext,100000);
			if (n < 0)
				error("ERROR writing to socket");
    		close(newsockfd);
     		close(sockfd);





     		return 0;
    
     	}
    
	 	else 
	 	{
	 		

	 		
	 		firstRun = 0;
	 		
	 		close(newsockfd);
     		close(sockfd);
	 
	 		
	
	 	}
 
	} 
     

	return 0; 
	
}