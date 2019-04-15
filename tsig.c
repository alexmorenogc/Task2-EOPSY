#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM_CHILD 3

// declaration
void sighup();
void sigint();
void sigquit();

void main()
{
	int pid_p = getpid();
	int pid;
	int childs[NUM_CHILD];

	printf("Parent pid: %d\n", pid);
	for (int i = 0; i < NUM_CHILD; i++){
		if (getpid() == pid_p){
			pid = fork();
			childs[i] = pid;
			sleep(1);
		}

		if (pid == 0) { //child
			signal(SIGHUP, sighup);
			signal(SIGINT, sigint);
			signal(SIGQUIT, sigquit);
			printf("Child process %d\n", getpid());
			while(1);
		} else if (pid < 0) {
			printf("Something is wrong\n");
			for (int j = 0; j < i; j++){
				printf("Parent: killing %d\n", childs[i]);
				kill(childs[i], SIGQUIT);
				sleep(1);
			}
		} else {

			sleep(1);
			printf("Parent sending kills\n\n");
			for (int i = 0; i < NUM_CHILD; i++){
				printf("Parent: killing %d\n", childs[i]);
				kill(childs[i], SIGQUIT);
				sleep(1);
			}
		}
	}
}

// sighup() function definition
void sighup()

{
	signal(SIGHUP, sighup); /* reset signal */
	printf("CHILD: I have received a SIGHUP pid: %d\n", getpid());
}

// sigint() function definition
void sigint()

{
	signal(SIGINT, sigint); /* reset signal */
	printf("CHILD: I have received a SIGINT pid: %d\n", getpid());
}

// sigquit() function definition
void sigquit()
{
	printf("My DADDY has Killed me!!! pid: %d\n", getpid());
	exit(0);
}
