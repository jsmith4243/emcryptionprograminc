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

int main(int argc, char *argv[])
{



	int keyLength;
	
	keyLength = atoi(argv[1]);

	char keyString[100000];
	

	char randomChar[2];
	
	int i = 0;
	for(i; i < keyLength; i++)
	{
	
		randomChar[0] = rand () % 25 + 65;
		
		//printf("randomChar is: %d\n", randomChar);
	
		strcat(&keyString, &randomChar);
	
	}
	
	printf("%s\n", keyString);

	return 0;

}