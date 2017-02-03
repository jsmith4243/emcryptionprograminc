/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: user2
 *
 * Created on February 27, 2016, 1:25 AM
 */




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


#include <fcntl.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    pid_t childPID;
    

    
    while(1)
    {
        
        childPID = fork();
        if(childPID == 0) // child process
        {
            
            while(1)
            {
            
            sleep(1);
            printf("child\n");
            return 0;
            }
            
            
            
            
            
            
        }
        else //parent
        {
            
            while(1)
            {
            
            sleep(1);
            printf("parent\n");
            }
            
            
            
        }
    }
    
    
    return (EXIT_SUCCESS);
}

