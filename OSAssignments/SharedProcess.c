//
//  SharedProcess.c
//  OSAssignments
//
//  Created by Arnab Sen on 23/03/18.
//  Copyright © 2018 Arnab Sen. All rights reserved.
//

#include <stdio.h>
#include <sys/shm.h>
int main(){
    int key = 9;
    int sm = shmget((key_t)345, sizeof(int), IPC_CREAT);
    
    
    int *sh = (int *)shmat(sm, NULL, 0);
    printf("%d\n",*sh);
    *sh=1;
    while(*sh!=0);
    printf("Other proces: %d\n", *sh);
}
