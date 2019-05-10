#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define NUM_CHILD 5

int main()
{
	int pid_p = getpid();
	pid_t pid;
	int childs[NUM_CHILD], time, exit_codes[NUM_CHILD];

	printf("Parent pid: %d\n", pid_p);
	for (int i = 0; i < NUM_CHILD; i++){
		if (getpid() == pid_p){
			pid = fork();
			childs[i] = pid;
		}

		if (pid < 0) { // Error
			printf("Something is wrong\n");
			/* 2.2 send to all already created child processes SIGTERM signal */

			/* 2.2 finish with the exit code 1 */
			exit(1);
		} else if (pid > 0) { // Parent
			/* 2.1  Insert one second delays between consecutive fork() calls. */
			sleep(1);
		} else if (pid == 0) { // Child
			/* 4.1  Print process identifier of the parent process */
			printf("Child process %d with Parent %d\n", getpid(), pid_p);
			/* 4.2 Sleep for 10 seconds */
			sleep(10); // TODO: change to 10s
			/* 4.3 Print a message about execution completion */
			printf("Execution completed pid %d\n", getpid());
			exit(100 + i);
		}
	}
	/* 2.3 Print a message about creation of all child processes. */
	printf("All the Childs created.\n");

	int i = 0;
	/* 2.4 Call in a loop the wait() function, until receiving from the system
  information that there are no more processes to be synchronized with the
  parent one */
	while(wait(&time) > 0) {
			 if(WIFEXITED(time)) {
						exit_codes[i++] =  WEXITSTATUS(time);
			 }
	}
	/* Print a message that there are no more child processes. In this
  loop do count child processes terminations and, at the very end of the
  parent process, print a message with the number of just received child
  processes exit codes. */
	printf("Exit codes recived: %d\n", i);

	printf("Execution completed\n");
	return 0;
}
