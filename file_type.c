#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{   int c;
    int duct[2];
    char name[256],buf[80];
    memset(name,0,256);
    memset(buf,0,80);
    while (1)
    {
	printf("Enter the name: ");
	scanf("%s",name);
	if(!access (name,F_OK))
	    break;
    }
    printf ("%s :",name);
    pipe(duct);       //creating an interprocessor channal
    if (fork()==0)
    {
    /*child process*/
    close (duct[0]);
    close (1);
    dup (duct[1]);    //instead of output to the monitor,a channel
                      //appears

    execl ("/bin/ls","ls","-la","-d",name,NULL);
    }  
    else
    {
    /*parent process*/
    wait(0);
    close(duct[1]);
    c = read (duct[0],buf,80);
    printf ("The read function returns %d successfully read bytes.\n",c);
    while(1)
    {
	if (c != 0)
	    {
		if (buf[0] == '-') printf ("file-normal\n");
	        if (buf[0] == 'd') printf ("directory\n");
		if (buf[0] == 'p') printf ("file-channel\n");
		if (buf[0] == 'c') printf ("file specialized byte-oriented\n");
		if (buf[0] == 'b') printf ("file specialized block-oriented\n");
		if (buf[0] == 's') printf ("nest file\n");
		if (buf[0] == 'l') printf ("file-symbolic link\n");
                memset(buf,0,80);
            }
        else break;
    exit(0);
    }
    }
return 0;
}

