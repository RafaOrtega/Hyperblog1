/*Aprovechando el tema de hilos, elegí un programa basado en semaforos para resolver
problemas de sincronizacion
El código fue tomado de Programar en C: Semaforos POSIX. Youtube: WhileTrueThenDream
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define NR_LOOP 100000
static void * thread_1_function(void * arg);
static void * thread_2_function(void * arg);


static int counter = 0;

sem_t sem1;


int main(void){

    pthread_t thread_1, thread_2;

    sem_init(&sem1, 0, 1);
    pthread_create(&thread_1, NULL, * thread_1_function, NULL);
    pthread_create(&thread_2, NULL, * thread_2_function, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf(" Valor counter %d \n", counter);

    return 0;

}

static void * thread_1_function(void * arg){
    for (int i = 0; i < NR_LOOP; i++){
        sem_wait(&sem1);
        counter++;
        sem_post(&sem1);
    }
}

static void * thread_2_function(void * arg){
    for (int i = 0; i < NR_LOOP; i++){
        sem_wait(&sem1);
        counter--;
        sem_post(&sem1);
    }
}
