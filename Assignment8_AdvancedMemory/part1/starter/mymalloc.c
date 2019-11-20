// You should start with your previous assignment's mymalloc.c :)
//
//
#define _GNU_SOURCE
#define cpus get_nprocs()
#include <stdio.h> // Any other headers we need here
#include "malloc.h" 
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <sched.h>
#include <pthread.h>

typedef struct block{
	size_t size;
	struct block* next;
	int free;
}block_t;

#define BLOCK_SIZE sizeof(block_t)

block_t** block_head = NULL; // global to define the linked lists of blocks
pthread_mutex_t locks[128];

block_t* findOptimalFreeBlock(size_t s){
  int cpu = sched_getcpu();
  pthread_mutex_lock(&locks[cpu]);
	block_t* block_list = block_head[cpu];
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
  pthread_mutex_unlock(&locks[cpu]);
	return optimal_block;
}

block_t* getLastBlock(){
  int cpu = sched_getcpu();
	if(block_head[cpu]==NULL){
		return NULL;
	}
	else{
		block_t* last_block = block_head[cpu];
		while(last_block -> next != NULL){
			last_block = last_block -> next;
		}
		return last_block;
	}
}

void splitBlock(block_t* block, size_t s){
  int cpu = sched_getcpu();
  pthread_mutex_lock(&locks[cpu]);
	int spaceLeft = (block -> size) - s;
   void* tempBlock = (void*) block;
   tempBlock += s + sizeof(block_t);
   block_t* additionalBlock = (block_t*) tempBlock;
   additionalBlock -> size = block -> size - s - sizeof(block_t);
   additionalBlock -> next = block -> next;
   additionalBlock -> free = 1;
   block -> size = s;
   block -> next = additionalBlock;
   pthread_mutex_unlock(&locks[cpu]);
   return;
}

void* extendMemory(size_t s){
  int cpu = sched_getcpu();
  pthread_mutex_lock(&locks[cpu]);
	//get to the last block
	block_t* last = getLastBlock();
	//extend the memory
	block_t* newBlock; 
  	if(s>4095){
		newBlock = (block_t*) mmap(0, s, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
     if ((void*) newBlock == (void*) -1){
     pthread_mutex_unlock(&locks[cpu]);
		  return NULL;
	  }
		newBlock -> size = (((s-1)/4096)+1)*4096; 
	}
	else{
		newBlock = sbrk(s + BLOCK_SIZE);
   if ((void*) newBlock == (void*) -1){
    pthread_mutex_unlock(&locks[cpu]);
		return NULL;
	  }
     newBlock -> size = s;
	}
	newBlock -> next = NULL;
	newBlock -> free = 0;
	if(last == NULL){
		block_head[cpu] = newBlock;
	}
	else{
		last -> next = newBlock;
	}
 if(newBlock -> size >= s + sizeof(block_t) + 4){
     pthread_mutex_unlock(&locks[cpu]);
     splitBlock(newBlock, s);
     pthread_mutex_lock(&locks[cpu]);
   }
   pthread_mutex_unlock(&locks[cpu]);
	return (newBlock+1);
}

void* mymalloc(size_t s){
	//if this is the first malloc call, initialize the global heap
   if(block_head==NULL){
     block_head = sbrk(sizeof(block_t*)*cpus);
     int x;
     for(x=0; x<cpus; x++){
       pthread_mutex_init(&locks[x], 0);
     }
   }
	//iterate to find best block
	block_t* bestBlock = findOptimalFreeBlock(s);
	//if the size is found, allocate the memory and return the pointer
	if(bestBlock != NULL){
		bestBlock -> free = 0;
		printf("malloc %zu bytes\n",s);
   if(bestBlock -> size >= s + sizeof(block_t) + 4){
     splitBlock(bestBlock, s);
   }
		return(bestBlock+1);//+1 will get us to the actual memory
	}
	//if the size is not found, create new block and memory
	void* p = extendMemory(s);
	if(p == NULL){
		return NULL;
	}
 //TODO: add splitting logic
	printf("malloc %zu bytes\n",s);
	return p;
}

void* mycalloc(size_t nmemb, size_t s){
  if(block_head==NULL){
     //int cpus = get_nprocs();
     block_head = sbrk(sizeof(block_t*)*cpus);
     int x;
     for(x=0; x<cpus; ++x){
       pthread_mutex_init(&locks[x], 0);
     }
   }
  int cpu = sched_getcpu();
	//If either input is 0, return NULL
	if((nmemb==0) || (s==0)){
		return NULL;
	}
	//run malloc with input nmemb*s
	void* p = malloc(nmemb*s);
 pthread_mutex_lock(&locks[cpu]);
	memset(p, 0, nmemb*s);
 pthread_mutex_unlock(&locks[cpu]);
	//return memory location
	printf("calloc %zu bytes\n",s);
	
	return p;
}
	
void myfree(void *ptr){
	//if input is NULL, return with no value
	if(!ptr){
		return;
	}
 int cpu = sched_getcpu();
 pthread_mutex_lock(&locks[cpu]);
	//get pointer to block
	block_t* ptrBlock = (block_t*)ptr - 1;
	//if already free, return
	if(ptrBlock -> free == 1) return;
	//if not already free, mark as free and return
	else{
		ptrBlock -> free = 1;
	}
 pthread_mutex_unlock(&locks[cpu]);
	printf("Freed some memory\n");
}
	
