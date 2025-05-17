//Program 7.2:
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // system
int main() {
	//uncomment each of these lines one by one - only one of the 5
	execl("/bin/ls", "/bin/ls", "-l", NULL);
	//execlp("ls", "ls", "-l", NULL);
	//execl("/bin/ls","/bin/ls","-l","p1.c","execl.c", "fork1.c", "xx", NULL);
	//execl("/bin/ls","/bin/ls","-l","*.c", NULL); //will not be interpreted as expected
	//system("ls -l *.c");
}
