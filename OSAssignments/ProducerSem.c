//
//  ProducerSem.c
//  OSAssignments
//
//  Created by Arnab Sen on 25/03/18.
//  Copyright © 2018 Arnab Sen. All rights reserved.
//

#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>


/* <-- Required for some Linux systems. Please un-comment if no definition is present -->
 struct sembuf {
    u_short sem_num;        // semaphore Number
    short   sem_op;         // semaphore operation
    short   sem_flg;        // operation flags
};
*/


//Atomic operations on Semaphores
void Wait(int mtx_id, int n){
    struct sembuf buf;
    buf.sem_flg = SEM_UNDO;
    buf.sem_num = 0;
    buf.sem_op = -1; //Negative number causes the semaphore value to decrement by absolute value of the number
    printf("%d",semop(mtx_id, &buf, 1)); //If semaphore value is <= 0. The process SLEEPS.
}
void Signal(int mtx_id){
    struct sembuf buf;
    buf.sem_flg = SEM_UNDO;
    buf.sem_num = 0;
    buf.sem_op = 1; //Positive number causes the semaphore value to increment by absolute value of the number
    printf("%d",semop(mtx_id, &buf, 1)); //If semaphore value is > 0. The process RUNS.
    
}
int main(int argc, const char * argv[]){
    
    //Fetching semaphore
    //For BSD based systems IPC_R = SHM_R, IPC_W = SHM_W. We can use IPC_<permission> in place of SHM_<permission>
    int mutex_id = semget((key_t)1234432, 1, SHM_R | SHM_W); //For mutex
    int full_id = semget((key_t)123455, 1, SHM_R | SHM_W); //For full
    int empty_id = semget((key_t)123495, 1, SHM_R | SHM_W); //For empty
    int buffer_id = shmget((key_t)1223, sizeof(int), SHM_R | SHM_W); //Shared variable bufffer
    
    //Attaching Shared variable to the system
    int *buffer = (int *)shmat(buffer_id, 0, SHM_R | SHM_W);
    
    
    int n=1;

    //sscanf(argv[1], "%d", &n); //If you want to use command line to provide Consumer Number. Un-comment this line
    printf("Producer %d is starting\n",n);
    
    while(1){
        
        Wait(empty_id,n);
        
        Wait(mutex_id,n);
       
        
        printf("Producer %d is in critical section\n",n);
        
        printf("Value of buffer before critical section: %d\n", *buffer);
        *buffer = *buffer + 1;
        printf("Value of buffer after critical section: %d\n", *buffer);
        
        
       
        Signal(mutex_id);
        
        Signal(full_id);
       
        
        
    }
    
}
