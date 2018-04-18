#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
struct Node{
	int pid;
	int s_add;
	int size;
	struct Node *next;
};
//Indicating the head node as pid=0
//Indicating the hole as pid=-1

int next_start_add=0;

struct Node *head;
struct Node* new(int pid, int size){
	struct Node* node=(struct Node*)malloc(sizeof(struct Node));
	node->pid=pid;
	node->s_add = next_start_add;
	next_start_add = next_start_add + size;
	node->size=size;
	node->next=NULL;
	return node;
	
}
struct Node* addNode(int pid, int size){
	struct Node* node = head;
	while(node->next!=NULL){
		node=node->next;
	}
	node->next = new(pid,size);
	return head;
}
int main()
{
	struct Node* node;
	int pid, add, sz,h=1;
	head = new(0,0);
	while(h){
		printf("1. Process\n2. Hole\n3. Display\n0. Exit\n");
		
		scanf("%d",&h);

			if(h==1){
				printf("Enter process ID:  ");
				scanf("%d",&pid);
				printf("Enter size:  ");
				scanf("%d",&sz);
				head = addNode(pid,sz);
			}
			if(h==2) {
				printf("Enter size:  ");
				scanf("%d",&sz);
				head = addNode(-1,sz);
			}
			if(h==3){
				node = head;
				while(node!=NULL){
					if(node->pid==0){
						printf("|head|\n");
					}else if(node->pid==-1){
						printf("|HOLE|ADD: %d|SIZE: %d|\n",node->s_add, node->size);
					}else{
						printf("|PID: %d|ADD: %d|SIZE: %d|\n",node->pid,node->s_add, node->size);
					}
					node= node->next;
				}
			printf("\n");
			}
			if(h==0){
				break;
			}

	}
	
	
}
