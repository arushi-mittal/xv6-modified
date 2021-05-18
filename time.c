#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main (int argc,char *argv[])
{   
    int i;
    for (i = 0; i < argc - 1; i++) {
        argv[i] = argv[i + 1];
    }
    argv[i] = '\0';
	int pid;
	int a = 0, b = 0;	
	pid = fork();
	if (pid == 0)
  	{	
  		exec(argv[0], argv);
    	printf(1, "exec %s failed\n", argv[1]);
    }
  	else
 	{
    	waitx(&a, &b);
 	}  
 	printf(1, "Wait Time: %d\nRun Time: %d\n", a, b); 
 	exit();
}