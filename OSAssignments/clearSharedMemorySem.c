//
//  clearSharedMemorySem.c
//  OSAssignments
//
//  Created by Arnab Sen on 01/04/18.
//  Copyright © 2018 Arnab Sen. All rights reserved.
//

#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
int main(){
    
    
    printf("Deleting semaphores and shared memory\n");
    
    
    //Fetching semaphore
    semget((key_t)1234432, 1, IPC_RMID); //For mutex
    semget((key_t)123455, 1, IPC_RMID); //For full
    semget((key_t)123495, 1,  IPC_RMID); //For empty
    shmget((key_t)1223, sizeof(int), IPC_RMID); //Shared variable bufffer
    
}
