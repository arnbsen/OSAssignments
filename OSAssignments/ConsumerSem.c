//
//  ConsumerSem.c
//  OSAssignments
//
//  Created by Arnab Sen on 25/03/18.
//  Copyright © 2018 Arnab Sen. All rights reserved.
//
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
//Atomic operations on Semaphores
void Wait(int mtx_id, int n){
    struct sembuf buf;
    buf.sem_flg = SEM_UNDO;
    buf.sem_num = 0;
    buf.sem_op = -1;
     printf("%d",semop(mtx_id, &buf, 1));
}
void Signal(int mtx_id){
    struct sembuf buf;
    buf.sem_flg = SEM_UNDO;
    buf.sem_num = 0;
    buf.sem_op = 1;
    printf("%d",semop(mtx_id, &buf, 1));
    
}
int main(int argc, const char * argv[]){
    
    
        time_t t1 = time(NULL);
        int n = 1;
        //Fetching semaphore
        int mutex_id = semget((key_t)1234432, 1, IPC_R|IPC_W|IPC_M); //For mutex
        int full_id = semget((key_t)123455, 1, IPC_R|IPC_W|IPC_M); //For full
        int empty_id = semget((key_t)123495, 1, IPC_R|IPC_W|IPC_M); //For empty
        int buffer_id = shmget((key_t)1223, sizeof(int), IPC_R|IPC_W|IPC_M); //Shared variable bufffer
        
        //Attaching Shared variable to the system
        int *buffer = (int *)shmat(buffer_id, 0, IPC_R|IPC_W);
    
        //sscanf(argv[1], "%d", &n);
        printf("Consumer %d is starting\n",n);
        
        while(1){
           
            Wait(full_id,n);
            Wait(mutex_id, n);
            
            
            printf("Consumer %d is in critical section at time [%s]\n",n, ctime(&t1));
            
            printf("Value of buffer before critical section: %d\n", *buffer);
            *buffer = *buffer - 1;
            printf("Value of buffer after critical section: %d\n", *buffer);
            
            
            Signal(mutex_id);
            
            Signal(empty_id);
            
            
        }
        
    
}

