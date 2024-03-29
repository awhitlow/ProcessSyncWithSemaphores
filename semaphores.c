/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define  CHILD		0       /* Return value of child proc from fork call */

int main()
{
    sem_t * mutex[5];          /* my semaphores */
    
    int pid;		/* Process id after fork call */
    int i;		/* Loop index. */
    int N;		/* Number of requests to process */
    int status;  	/* Exit status of child process. */
    int type;           /* Type of animal */

    /*   Initialization of the semaphores   */
    if ((mutex[0] = sem_open("elephant", O_CREAT, 0644, 1)) == SEM_FAILED ||
        (mutex[1] = sem_open("dog", O_CREAT, 0644, 1)) == SEM_FAILED ||
        (mutex[2] = sem_open("cat", O_CREAT, 0644, 1)) == SEM_FAILED ||
        (mutex[3] = sem_open("mouse", O_CREAT, 0644, 1)) == SEM_FAILED ||
        (mutex[4] = sem_open("parrot", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror("semaphore initilization");
        exit(1);
    }
     
    printf("How many requests to be processed: ");
    scanf("%d",&N);

    for (i=1; i<=N; i++) {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) {
   	        /* Fork failed! */
	        perror("fork");
	        exit(1);
        }
        
        
        if (pid == CHILD) {
	        pid = getpid();
            switch (type) {

		    case 1: /* Elephant code*/
                    printf("     Elephant process with pid %d wants in.\n",pid);
                    sem_wait(mutex[3]);
                    fflush(stdout);
                    printf("     Elephant process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Elephant process with pid %d is out.\n",pid);
                    sem_post(mutex[0]);
                    fflush(stdout); 
                    break;

		    case 2:  /*Dog code*/
                    printf("     Dog process with pid %d wants in.\n",pid);
                    sem_wait(mutex[2]);
                    fflush(stdout);
                    printf("     Dog process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Dog process with pid %d is out.\n",pid);
                    sem_post(mutex[2]);
                    fflush(stdout);
		            break;

		    case 3: /*Cat Code*/
                    printf("     Cat process with pid %d wants in.\n",pid);
                    sem_wait(mutex[1]); 
                    sem_wait(mutex[4]);
                    fflush(stdout);
                    printf("     Cat process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Cat process with pid %d is out.\n",pid);
                    sem_post(mutex[2]); 
                    sem_post(mutex[4]);
                    fflush(stdout);
		            break;

		    case 4: /*Mouse code*/
                    printf("     Mouse process with pid %d wants in.\n",pid);
                    sem_wait(mutex[0]); 
                    sem_wait(mutex[4]);
                    fflush(stdout);
                    printf("     Mouse process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Mouse process with pid %d is out.\n",pid);
                    sem_post(mutex[2]); sem_post(mutex[4]);
                    fflush(stdout); 
		            break;
		
		    case 5: /*Parrot  Code*/
                    printf("     Parrot process with pid %d wants in.\n",pid);
                    sem_post(mutex[2]); 
                    sem_post(mutex[3]);
                    fflush(stdout);
                    printf("     Parrot process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Parrot process with pid %d is out.\n",pid);
                    sem_post(mutex[2]); 
                    sem_post(mutex[3]);
                    fflush(stdout);
		            break;
            }
            exit(0);
        }
    }
    
    /* Now wait for the child processes to finish */
    for (i=1; i<=N; i++) {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}











