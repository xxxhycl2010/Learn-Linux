// A simple program that test exec functions ,include execl,execlp,execle,execv,execvp,execve
// 2015-12-14 20:01:48

#include <stdio.h>
#include <unistd.h>

int main()
{
   //execl("/bin/ls","ls","-al","/etc/passwd",(char*)0);   

   // execlp("/bin/ls","ls","-al","/etc/passwd",(char*)0);

    /*
    char *argv[] = {"ls","-al","/etc/passwd",(char*)0};
    char *envp[]={"PATH=/bin",0};
    execve("/bin/ls",argv,envp);
    */

//    char *argv[] = {"ls","-al","/etc/passwd",0};
//    execvp("/bin/ls",argv);
//
    system("ls -al /etc/passwd /etc/shadow");
}
