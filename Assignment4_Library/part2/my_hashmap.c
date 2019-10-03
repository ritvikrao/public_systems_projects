// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf  output. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// - You may add any helper functions that you think you need (if any, or otherwise for debugging)
// ==================================================
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "containers.h"
#include "my_hashmap.h"


// Simple hash function that will put a key into a bucket
// The module operator will make sure we do not go out of bounds.
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
hashmap_t* hashmap_create(unsigned int _buckets){
    // Allocate memory for our hashmap
	hashmap_t* newHash = (hashmap_t*) malloc(sizeof(hashmap_t));
    // Set the number of buckets
	newHash -> buckets = _buckets;
    // Initialize our array of lists for each bucket
	newHash -> arrayOfLists = (node_t**) malloc(sizeof(node_t*)*_buckets);
    // Setup our hash function to point to our
    // stringHash function.
	newHash -> hashFunction = stringHash;
    // Return the new map that we have created
    return newHash;
}


// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// Attempting to delete a NULL hashmap should exit(1)
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap){
    if(_hashmap != NULL){
	int i;
	for(i=0; i<_hashmap->buckets; i++){
		node_t* node = _hashmap -> arrayOfLists[i];
		while(node!=NULL){
                	node_t* previous = node;
                	node = node->next;
			free(previous -> kv -> key);
			free(previous -> kv -> value);
			free(previous -> kv);
                	free(previous);
        	}
	}
	free(_hashmap->arrayOfLists);
	free(_hashmap);
    }
    else{
	exit(1);
    }
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Attempting hashmap_hasKey on a NULL hashmap should exit(1)
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search (i.e. iterate through) that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key){
	if(_hashmap == NULL){
		exit(1);
	}
	int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);
	node_t* list = _hashmap -> arrayOfLists[bucket];
	while(list!=NULL){
		if(strcmp(list -> kv -> key,key) == 0) return 1;
		list = list -> next;
	}
	return 0;
}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
//  - Attempting hashmap_insert on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value){
    	if(_hashmap == NULL){
                exit(1);
        }
	if(hashmap_hasKey(_hashmap, key)==1) return;
	int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);
	node_t* list = _hashmap -> arrayOfLists[bucket];
	//make the node
	pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
        newpair -> key = (char*) malloc(strlen(key) * sizeof(char));
        newpair -> value = (char*) malloc(strlen(value) * sizeof(char));
	strcpy(newpair -> key, key);
	strcpy(newpair -> value, value);
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
        newnode -> next = NULL;
        newnode -> kv = newpair;
	//if there is no node
	if(list==NULL){
		_hashmap -> arrayOfLists[bucket] = newnode;
		return;
	}
	// if there is already a node
	while(list -> next!=NULL) list = list -> next;
	list -> next = newnode;
	return;
}

// Return a value from a key 
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
//  - Attempting hashmap_getValue on a NULL hashmap should exit(1)
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key){
	if(_hashmap == NULL){
                exit(1);
        }
	if(hashmap_hasKey(_hashmap, key)==0) return NULL;
	int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);
	node_t* list = _hashmap -> arrayOfLists[bucket];
	while(strcmp(list -> kv -> key, key) != 0) list = list -> next;
	return list -> kv -> value;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
//  - Attempting hashmap_removeKey on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key){
	if(_hashmap == NULL){
                exit(1);
        }
	if(hashmap_hasKey(_hashmap, key)==0) return;
	int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);
        node_t* list = _hashmap -> arrayOfLists[bucket];
	//if the first node has the key
	if(strcmp(list -> kv -> key, key) == 0){
		_hashmap -> arrayOfLists[bucket] = _hashmap -> arrayOfLists[bucket] -> next;
		free(list -> kv -> key);
		free(list -> kv -> value);
		free(list -> kv);
		free(list);
		return;
	}
	node_t* remove = list -> next;
	node_t* prev = list;
	while(strcmp(remove -> kv -> key, key) != 0){
		remove = remove -> next;
		prev = prev -> next;
	}
	prev -> next = remove -> next;
	free(remove -> kv -> key);
        free(remove -> kv -> value);
        free(remove -> kv);
	free(remove);
	return;
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
//  - Attempting hashmap_update on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue){
	if(_hashmap == NULL){
                exit(1);
        }
	if(hashmap_hasKey(_hashmap, key)==0) return;
        int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);
        node_t* list = _hashmap -> arrayOfLists[bucket];
        while(strcmp(list -> kv -> key, key) != 0) list = list -> next;
	list -> kv -> value = (char*) realloc(list -> kv -> value, sizeof(char) * strlen(newValue));
	strcpy(list -> kv -> value, newValue);
	return;
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
//  - Attempting hashmap_printKeys on a NULL hashmap should exit(1)
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	if(_hashmap == NULL){
                exit(1);
        }
	//TODO
	int i;
	int j = (int) _hashmap -> buckets;
	for(i=0; i<j; i++){
		printf("Bucket %d:\n", i);
		node_t* list = _hashmap -> arrayOfLists[i];
		while(list!=NULL){
			printf("\n");
			printf("Key: %s\n", list -> kv -> key);
			printf("Value: %s\n", list -> kv -> value);
			list = list -> next;
		}
		printf("\n");
	}
	return;
}

