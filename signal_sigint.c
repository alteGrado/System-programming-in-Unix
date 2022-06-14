#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int n = 0;
void func( )
{
    n = n + 1;
    printf ("Received signal Ctrl-C  number : %d\n",n);
}
int main()
{   
    int k;
    struct sigaction m,o;
    sigemptyset(&m.sa_mask);
    sigprocmask(0,0,&m.sa_mask);
    m.sa_handler = func;
    m.sa_flags = 0;

    if (sigaction (SIGINT,&m,&o)==-1)
	printf("Error in sigaction\n");

    for (k = 0; k < 100 ; k++)
        { 
            printf("%d Click Ctrl-C\n",k);
	    sleep(2);
        }
return 0;
}
