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
	unsigned char buffer;
	//create first node outside of loop
	node_t* current;
	node_t* tail;
	current = malloc(sizeof(node_t));
	fscanf(f, "%c", buffer);
	current->wins=buffer;
	current->next=NULL;
	node_t* head = current;
	while(fscanf(f, "%c", buffer) != EOF){
		tail = malloc(sizeof(node_t));
		tail->wins=buffer;
		tail->next=NULL;
		current->next=tail;
		current=tail;
	}
	return head;
}

void print_list(node_t* node){
	while(node!=NULL){
		printf("%c wins\n", node->wins);
		node = node->next;
	}
}

void free_list(node_t* node){
	node_t* previous = node;
	while(node!=NULL){
		node = node->next;
		free(previous);
		node_t* previous = node;
	}
}



int main(){  
	node_t* node = create_list();
	node_t* node2 = node;
	//print_list(node);
	//free_list(node2);
	return 0;
}
