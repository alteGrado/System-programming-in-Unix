#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

sigjmp_buf depot;

int main()
{
    struct sigaction adaptation;
    void han();
    adaptation.sa_handler = han;
    sigprocmask(0,0,&adaptation.sa_mask);
    adaptation.sa_flags = 0;
    sigaction(SIGINT,&adaptation,0);      //new signal processing method
    
    int cout=0;
    char buf [90];
    memset (buf,'X',90);
    printf("Try pressing Ctrl-C.\n");
    while (cout < 90)  
    {
         printf ("%cx",buf[cout]);
         fflush(stdout);
         sleep(1);
         sigsetjmp(depot,1);
         cout++;
    }
    printf("\n");

return 0;
}

void han()
{
    system ("date");
    siglongjmp(depot,1);
}
