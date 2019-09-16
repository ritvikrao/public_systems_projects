// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h>

// Create your node_t type here
typedef struct LinkedList{
	unsigned char wins;
	struct LinkedList* next;
}node_t;

// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

node_t* create_list(){
	FILE* f;
	f = fopen("./data.txt","r");
	if(NULL==f){
		fprintf(stderr, "Error opening file; program terminating");
		exit(1);
	}
	int buffer;
	//create first node outside of loop
	node_t* current;
	node_t* tail;
	current = malloc(sizeof(node_t));
	fscanf(f, "%d",&buffer);
	current->wins=buffer;
	current->next=NULL;
	node_t* head = current;
	while(fscanf(f, "%d", &buffer) != EOF){
		tail = malloc(sizeof(node_t));
		tail->wins=buffer;
		tail->next=NULL;
		current->next=tail;
		current=tail;
	}
	fclose(f);
	return head;
}

void print_list(node_t* node){
	while(node!=NULL){
		if(node->wins<22){
			printf("%d wins -- worse than the worst all time in the majors\n", node->wins);
		}
		else if(node->wins<46){
			printf("%d wins -- worse than the worst Sox season of all time\n", node->wins);
		}
		else if(node->wins<63){
			printf("%d wins -- among the worst in the league\n", node->wins);
		}
		else if(node->wins<82){
			printf("%d wins -- below .500 in 162-game season\n", node->wins);
		}
		else if(node->wins<90){
			printf("%d wins -- meh\n", node->wins);
		}
		else if(node->wins<95){
			printf("%d wins -- pretty good\n", node->wins);
		}
		else if(node->wins<108){
			printf("%d wins -- among the best\n", node->wins);
		}
		else{
			printf("%d wins -- the best of all time\n", node->wins);
		}
		node = node->next;
	}
}

void free_list(node_t* node){
	while(node!=NULL){
		node_t* previous = node;
		node = node->next;
		free(previous);
	}
}



int main(){  
	node_t* node = create_list();
	node_t* node2 = node;
	print_list(node);
	free_list(node2);
	return 0;
}
