#include <stdio.h>      
#include <pthread.h>    
#include <stdlib.h>     
#include <unistd.h>     

// Premi�re fonction ex�cut�e par un thread
void *thread_func1(void *arg) {
    sleep(1);   // Attendre une seconde
    printf("Thread 1: bonjour! \n");  
    return NULL;    //Terminer la fonction et retourner NULL
}

// Deuxi�me fonction ex�cut�e par un thread
void *thread_func2(void *arg) {
    printf("Thread 2: Salut! \n");   
    sleep(2);   // Attendre deux secondes
    return NULL;    //Terminer la fonction et retourner NULL
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;   //stockage les identifiants des threads

    // Cr�er le premier thread qui ex�cute la fonction thread_func1
    pthread_create(&thread1, NULL, thread_func1, NULL);

    // Attendre que le premier thread se termine
    pthread_join(thread1, NULL);

    // Cr�er le deuxi�me thread qui ex�cute la fonction thread_func2
    pthread_create(&thread2, NULL, thread_func2, NULL);

    // Attendre que le deuxi�me thread se termine
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;   //Terminer le programme avec un code de sortie de succ�s
}

