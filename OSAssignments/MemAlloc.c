#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
struct Node{
	int pid;
	int s_add;
	int size;
	struct Node *next;
};
//Indicating the head node as pid=0
//Indicating the hole as pid=-1
typedef struct Node Node;
int next_start_add=0;

Node *head;
Node* new(int pid, int size){
	Node* node=(struct Node*)malloc(sizeof(struct Node));
	node->pid=pid;
	node->s_add = next_start_add;
	next_start_add = next_start_add + size;
	node->size=size;
	node->next=NULL;
	return node;
	
}
Node* addNode(int pid, int size){
	Node* node = head;
	while(node->next!=NULL){
		node=node->next;
	}
	node->next = new(pid,size);
	return head;
}
int main(){
	Node* node,*temp;
	int pid, add, sz,h=1,ch=1;
	int min = INT_MAX;
	int max = INT_MIN;
	head = new(0,0);
	node = head;
	Node* headbkp = head;
	int hole_size = 100;
	//Initialing equal sized holes
	for(int i=0;i<=10;i++){
		node->next = new(-1, hole_size);
		hole_size = hole_size + 50;	
		node = node->next;
	}
	node=head;
	while(node!=NULL){
		printf("pid =%d start_add = %d size = %d\n",node->pid,node->s_add, node->size);
		node = node->next;
	}
	//---------The Algorithm starts here----------------//
	while(ch){
		printf("Enter your choice\n1. First Fit\n2. Worst Fit\n3. Best Fit\n4. Print\n");
		scanf("%d",&ch);
		if(ch==1){
				node = head->next;
				Node* node1 = head;
				printf("Enter the Process ID and size\n");
				scanf("%d%d",&pid,&sz);
				while(node!=NULL){
					if(node->pid==-1 && node->size>=sz){
						break;
					}
					node1 = node1->next;
					node=node->next;	
				}
				node1->next = new(pid, sz);
				node1=node1->next;
				node1->s_add = node->s_add;
				node1->next = node;
				node->size = node->size - sz;
				node->s_add = node1->s_add+sz;
				
				
		}else if(ch==2){ 
				node = head->next;
				Node* node1=head,*node2 = head;
				printf("Enter the Process ID and size\n");
				scanf("%d%d",&pid,&sz);
				
				while(node!=NULL){
				
					if(node->pid==-1 && node->size>sz && node->size > max){
						temp = node1;
						node2 = node;
						min = node->size - sz;
					
					}
					node1 = node1->next;
					node=node->next;
				}
				temp->next = new(pid, sz);
				temp = temp->next;
				temp->s_add = node2->s_add;
				temp->next = node2;
				node2->size = node2->size - sz;
				node2->s_add = temp->s_add+sz;
				
		}else if(ch==3){
				node = head->next;
				Node* node1=head,*node2 = head;
				printf("Enter the Process ID and size\n");
				scanf("%d%d",&pid,&sz);
				
				while(node!=NULL){
					if(node->pid==-1 && node->size>sz && (node->size - sz) < min){
						temp = node1;
						node2 = node;
						min = node->size - sz;
					
					}
					node1 = node1->next;
					node=node->next;
				}
				node2 = temp->next;
				temp->next = new(pid, sz);
				temp = temp->next;
				temp->s_add = node2->s_add;
				temp->next = node2;
				node2->size = node2->size - sz;
				node2->s_add = temp->s_add+sz;
				
				
						

		}else if(ch==4){
			node = head->next;
			while(node!=NULL){
			printf("pid =%d start_add = %d size = %d\n",node->pid,node->s_add, node->size);
			node = node->next;
			}
		}else{ 
			break;
		}

	}
}
