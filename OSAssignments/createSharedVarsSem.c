//
//  createSharedVarsSem.c
//  OSAssignments
//  Bounded Buffer problem with semaphores
//  Created by Arnab Sen on 25/03/18.
//  Copyright © 2018 Arnab Sen. All rights reserved.
//  Unix System V supported semaphores. Use ipcs and ipcrm before running programs otherwise allocation can be a failure.
//  DO NOT forget to remove Sempahores. They persist in the system even program ends.
//  Use ipcrm -s <sem_id> or use semctl(sem_id, semnum , IPC_RMID) ALWAYS (for semaphores).
//  Use ipcrm -m <shm_id> or use semctl(sem_id, semnum , IPC_RMID) ALWAYS (for shared memory).



#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>


/* <-- Required  for Linux systems like Fedora. Please un-comment if using Linux. Because no definition is present -->
union semun {
    int     val;            // value for SETVAL
    struct  semid_ds *buf;  // buffer for IPC_STAT & IPC_SET
    u_short *array;         // array for GETALL & SETALL
};
*/



int main(){
    
    printf("Initilaiser Program\n");
    union semun arg_mutex, arg_full, arg_empty;
    
    //Getting Semaphore ID
    int mutex_id = semget((key_t)1234432, 1, IPC_CREAT|0666); //For mutex
    int full_id = semget((key_t)123455, 1, IPC_CREAT|0666); //For full
    int empty_id = semget((key_t)123495, 1, IPC_CREAT|0666); //For empty
    int buffer_id = shmget((key_t)1223, sizeof(int), IPC_CREAT|0666); //Shared variable bufffer
   
    
    
    //Attaching Shared variable to the system
    int *buffer = (int *)shmat(buffer_id, 0, IPC_R|IPC_W);
    
    //Setting values to mutex, full, empty & initialising buffer.
    arg_mutex.val = 1;
    arg_full.val = 0;
    arg_empty.val = 2;
    *buffer = 0;
    
    //Initialing mutex, full, empty
    semctl(mutex_id, 0, SETVAL, arg_mutex);
    semctl(full_id, 0, SETVAL, arg_full);
    semctl(empty_id, 0, SETVAL, arg_empty);
    
    //Detaching buffer
    shmdt(buffer);
    int temp = semctl(mutex_id, 0, GETVAL);
    temp = semctl(full_id, 0, GETVAL);
    temp = semctl(empty_id, 0, GETVAL);
    
    while(1);
    
}
