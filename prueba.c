#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILD 5 /*Number of child processes*/


int main()
{
    pid_t  pid,wpid;
    int id,i,killcode,status;
    int childs[NUM_CHILD], childs_ecodes[NUM_CHILD];

    pid = getpid(); /*Get parent ID*/

    for( i = 0; i < NUM_CHILD; i++ )
    {

          id = fork();  /* Storing all the created childs */
          childs[i] = id;

          if( id > 0 )  /* Parent Process */ {
               sleep(1); /*1 Second delays between fork calls*/
          } else if( id==0 ) /* Child Process */ {
               pid = getpid();

               /*Here the child sleeps for 10 secods*/
               printf("Parent[%d], created Child [%d].\n", getppid(), pid);
               sleep(10);
               exit(100 + i); /*Exit codes 100,...,10n  where n = NUM_CHILD*/
          } else /* Fork creation error */ {
               fprintf( stderr, "[%d] error: fork() failed.\n", pid );

               for ( int j = 0; j <= i; j++ )  /*Killing all the created child processes*/
               {
                    printf("Parent[%d]: sending SIGTERM signal.\n",getppid() );
                    killcode = kill(childs[j],SIGTERM);
                    printf("Child[%d]: recived SIGTERM signal, terminating.\n",childs[j] );

                    if ( killcode == 0 ) {
                         printf("Child[%d] terminated successfully. \n",childs[j]);
                    } else {
                         printf("ERROR while killing Child[%d]",childs[j]);
                    }
               }
               exit(1);
          }
     }

     printf("\n");
     printf("Parent[%d]: All Child Processes have been created.\n", pid);
     printf("Parent[%d]: There are no more Child Processes.\n", pid);


     /* Wait for children to exit */
     int k = 0;
     printf("puto status ahora: %d\n", status);
     while( wait(&status) > 0 )
     {
          if( WIFEXITED(status) )
          {
               childs_ecodes[k] =  WEXITSTATUS(status);
               printf("status= %d k= %d childs_ecodes[k]=%d\n", status,k,childs_ecodes[k] );
               /* Not needed but I check if I get the correct exit codes for each child */
               //printf("Child[%d]: terminated with status: %d\n", childs[k],  childs_ecodes[k]);
               k++; //Counting the exit codes
          }


     }

     printf("\n");
     printf("Parent[%d]: [%d] Child Processes exit codes. \n\n", pid,k);
     printf("\n\n");
     printf("Parent[%d]: Execution completed!.\n", pid);

     return 0;
}
