#include <stdio.h> // Any other headers we need here
#include "malloc.h" // We bring in the old malloc function
		    // NOTE: You should remove malloc.h, and not include <stdlib.h> in your final implementation.
#include <string.h>
#include <unistd.h>

typedef struct block{
	size_t size;
	struct block* next;
	int free;
}block_t;

#define BLOCK_SIZE sizeof(block_t)

block_t* block_head = NULL; // global to define the linked list of blocks

block_t* findOptimalFreeBlock(size_t s){
	block_t* block_list = block_head;
	block_t* optimal_block = NULL;
	while(block_list!=NULL){
		if((block_list -> size >= s) && (block_list -> free == 1)){
			if(optimal_block == NULL){
				optimal_block = block_list;
			}
			else if(optimal_block -> size > block_list -> size){
				optimal_block = block_list;
			}
		}
	block_list = block_list -> next;
	}
	return optimal_block;
}

block_t* getLastBlock(){
	if(block_head==NULL){
		return NULL;
	}
	else{
		block_t* last_block = block_head;
		while(last_block -> next != NULL){
			last_block = last_block -> next;
		}
		return last_block;
	}
}

void* extendMemory(size_t s){
	//get to the last block
	block_t* last = getLastBlock();
	//extend the memory with sbrk
	block_t* newBlock; 
	newBlock = sbrk(s + BLOCK_SIZE);
	if ((void*) newBlock == (void*) -1){
		return NULL;
	}
	newBlock -> size = s;
	newBlock -> next = NULL;
	newBlock -> free = 0;
	if(last == NULL){
		block_head = newBlock;
	}
	else{
		last -> next = newBlock;
	}
	return (newBlock+1);
}

void* mymalloc(size_t s){

	//void* p = (void*)malloc(s); 	// In your solution no calls to malloc should be made!
					// Determine how you will request memory :)
	
	//iterate to find best block
	block_t* bestBlock = findOptimalFreeBlock(s);
	//if the size is found, allocate the memory and return the pointer
	if(bestBlock != NULL){
		bestBlock -> free = 0;
		printf("malloc %zu bytes\n",s);
		return(bestBlock+1);//+1 will get us to the actual memory
	}
	//TODO: if the size is not found, create new block and memory with sbrk
	void* p = extendMemory(s);
	if(p == NULL){
		return NULL;
	}
	printf("malloc %zu bytes\n",s);
	return p;
}

void* mycalloc(size_t nmemb, size_t s){

	//void* p = (void*)calloc(nmemb,s); 	// In your solution no calls to calloc should be made!
						// Determine how you will request memory :)

	//If either input is 0, return NULL
	if((nmemb==0) || (s==0)){
		return NULL;
	}
	//run malloc with input nmemb*s
	void* p = malloc(nmemb*s);
	memset(p, 0, nmemb*s);
	//return memory location
	printf("calloc %zu bytes\n",s);
	
	return p;
}
	
void myfree(void *ptr){
	//TODO: if input is NULL, return with no value
	if(!ptr){
		return;
	}
	//TODO: check that the pointer exists within the current memory
	block_t* ptrBlock = (block_t*)ptr - 1;
	//TODO: if the pointer is not found, return
	//TODO: check if the corresponding block is free or not
	//TODO: if already free, return
	if(ptrBlock -> free == 1) return;
	//TODO: if not already free, mark as free and return
	else{
		ptrBlock -> free = 1;
	}
	printf("Freed some memory\n");
	free(ptr);
}
	
