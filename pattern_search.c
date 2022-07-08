//The program is designed to search for the text in a template file.
//Information is written to the file.txt.
//The work with the signal handler is shown.Standard Ctrl-Z handling
//replaced with new function.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <setjmp.h>

int count = 0;
sigjmp_buf stack;

void func ()                                //interrupt handler function
{
    count++;
    printf ("Do you want to go out?\n\n");
    printf ("Count to ten : ");
    printf ("%d\n\n",count);
    if (count == 10)
	signal (SIGINT,0);
    siglongjmp (stack,1);

}
int main()
{   

    struct sigaction prer;
    prer.sa_handler = func;
    prer.sa_flags = 0;
    sigprocmask (0,0,&prer.sa_mask);
    sigaction (SIGINT,&prer,0);    

    // SC sigaction() allows the process to establish
    //your response to receive a signal


    int fd;
    char name[256];
    char sample[80];
    char buffer[1000];
    memset (name,0,256);
    memset (sample,0,80);
    memset (buffer,0,512);
    int p[2];
    creat("file.txt",0777);
   

    while (1)
    {

        sigsetjmp (stack,1);

	printf ("Enter file name : ");
	scanf ("%s",name);

        sigsetjmp (stack,1);

        printf ("Enter string-pattern : ");
        scanf ("%s",sample);
	if (!access(name,F_OK))
	printf("In file %s we are looking for lines \"%s\". \n",name,sample);

        pipe(p);

        if (fork()==0)
        {
	    close (p[0]);
	    close (1);
            dup2(p[1],1);
            execl ("/bin/grep","grep","--color",sample,name,NULL);
        }
        else
        { 
       
	    wait(0);
            close (p[1]);

            //open the file for writing and attendance read-write
            //pointer to the end of the file


            fd = open ("file.txt",O_WRONLY|O_APPEND);  

            //a handle is printed to check for the existence of the Process's
            //User Descriptor Table of Open Files 

            printf ("%d\n",fd);
            read (p[0],buffer,512);
            printf ("%s\n",buffer);
            write (fd,buffer,512);
            memset(buffer,0,512);
            
        }
        
    }

return 0;
}
