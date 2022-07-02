/*Program to display all files in a given directory written in C/C++*/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main ()
{
    int p[2],p1[2];
    pipe (p);          //creating an interprocessor channel
    if (fork()==0)     //creating a child process
    {
	close (p[0]);  //the side of the channel is closed for reading
	dup2(p[1],1);        //duplicate the pipe descriptor to write to the 
                             //standard output descriptor
        system("file *.*");  // running the "file *.*" utility within a process
        _exit(0);            //close all files open in this process,I/O buffer
                             //is not pushed
    }
    else
    {
	wait(0);
	pipe(p1);
        close (p[1]);
        if (fork()==0)       //creating a second child process
	    {
		close (p1[0]);
		dup2(p1[1],1);
		dup2(p[0],0);
		system("grep \"C source\"");
		_exit(1);
	    }
	else
	    {
		wait(0);
		close(p1[1]);
		dup2(p1[0],0);            //take information from the second child
		system ("cut -d: -f 1");  //cuts the first field before the colon 
                                          //separator
                _exit(0);
            }
      }
return 0;
}

	    


