// Compile:     gcc -lpthread relay.c -o relay
// Run:         ./relay
//
// Fix the broken relay race
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h> // new library!

// TODO: Initialize any semaphores here
sem_t sem_global;
sem_t sem_global2;
sem_t sem_global3;


// A function to simulate a thread doing some work
// In our example, we simply sleep our thread.
void make_runner_run(){
    sleep(2);
}

// TODO: Modify Runner1 through Runner4
// so that Runner1 always executes first,
// then Runner2, then Runner3, then Runner4 last.
void *Runner1(void *vargp){
        printf("Usain Bolt has taken off!\n");
        make_runner_run();
	sem_post(&sem_global);
    return NULL;
}

void *Runner2(void *vargp){
	sem_wait(&sem_global);
        printf("Michael Johnson has taken off\n");
        make_runner_run();
	sem_post(&sem_global2);
        return NULL;
}

void *Runner3(void *vargp){
	sem_wait(&sem_global2);
        printf("Allyson Felix has taken off\n");
        make_runner_run();
	sem_post(&sem_global3);
        return NULL;
}

void *Runner4(void *vargp){
	sem_wait(&sem_global3);
        printf("Carmelita Jeter runs the anchor leg to the finish line!\n");
        make_runner_run();
        return NULL;
}

int main(){

    // Store our thread ids
        pthread_t tids[4];
        // Initialize semaphore(s)
        // TODO: Use sem_init for each of your semaphores
	sem_init(&sem_global, 0, 0);
	sem_init(&sem_global2, 0, 0);
	sem_init(&sem_global3, 0, 0);
        // Create our threads
        pthread_create(&tids[0],NULL,Runner1,NULL);
        pthread_create(&tids[1],NULL,Runner2,NULL);
        pthread_create(&tids[2],NULL,Runner3,NULL);
        pthread_create(&tids[3],NULL,Runner4,NULL);
        // Join threads
        pthread_join(tids[0],NULL);
        pthread_join(tids[1],NULL);
        pthread_join(tids[2],NULL);
        pthread_join(tids[3],NULL);
        // Destroy our semaphore
        // TODO: Use sem_destor(...) for each of your semaphores
	sem_destroy(&sem_global);
	sem_destroy(&sem_global2);
	sem_destroy(&sem_global3);
        return 0;
}
