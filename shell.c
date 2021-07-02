/*
CO327 Operating Systems
Lab01 - shell
E16049
*/
/*
README
    this is a simple shell application.
    to exit , user shoud enter q.
    sudo is not included.
    commands like ls -all can be processed and executed.
    first the program checks the existance of the command.
    then checks the execute permissions of the command
    if everything is ok, then the command is executed by a child process.
*/
#include <stdio.h>
//#include <sys/syscall.h>    
#include <unistd.h>         
#include <stdlib.h>
#include <string.h>
// #include <sys/stat.h>
// #include <ctype.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

    char usrCMD[100];                       //for taking input 
    char cpyCMD[100];                       //copy the input
    const char*binpath = "/bin/";           //to chek the command exists
    char path[100];                         //path
    int length=0;
    int wstatus=0;//for wait status

    while (1)
    {

        printf("Enter a command to execute (q to exit): ");
        fgets(usrCMD,100,stdin);            //get input
        if(strcmp(usrCMD,"q\n")==0)
            return 0;
        usrCMD[strcspn(usrCMD,"\n")] = 0;   //remove newline character
        strcpy(cpyCMD,usrCMD);
        /* set the first space to 0, to remove arguments.*/
        cpyCMD[strcspn(usrCMD," ")] = 0;
        strcpy(path,binpath);               //copy binpath to path
        strcat(path,cpyCMD);                //path = path+command

        if (access(path,F_OK)==0) //then the command exists!
        {
            if( access(path,X_OK) == 0){       //to check the given command is exists and 
                pid_t pid = fork(); //create child process
                if(pid>0)           //if this is the parent process, wait till child to finish
                    waitpid(pid,&wstatus,0);
                else if(pid == 0)   //if this is child process, break the loop to execute command
                    break;
                else 
                    printf("Execution Failed\n");
            }else 
            printf("User does not have the permission to execute the command\n");
        }else   
            printf("Command not found\n");
    }
    system(usrCMD);

    return 0;
}

