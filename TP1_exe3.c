#include <stdio.h>      
#include <pthread.h>   
#include <stdlib.h>    
#include <unistd.h>     

// Première tâche exécutée par un thread
void *tache1(void *arg) {
    int i = 0; 
    while(i < 5) {
        printf("tache1 a ete executee\n");  
        sleep(1);   // Attend une seconde
        i++;    // Incrémenter le compteur
    }
    return NULL;    // Terminer la fonction et retourner NULL
}

// Deuxième tâche exécutée par un thread
void *tache2(void *arg) {
    int j = 0;
    while(j < 3) {
        printf("exec tache2 a ete executee\n");   
        sleep(2);   // Attend deux secondes
        j++;    // Incrémenter le compteur
    }
    return NULL;    // Terminer la fonction et retourner NULL
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;   //  stockage les identifiants des threads

    // Crée le premier thread qui exécute la fonction tache1
    pthread_create(&thread1, NULL, tache1, NULL);

    // Attend que le premier thread se termine
    pthread_join(thread1, NULL);

    // Crée le deuxième thread qui exécute la fonction tache2
    pthread_create(&thread2, NULL, tache2, NULL);

    // Attend que le deuxième thread se termine
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;   // Terminer le programme avec un code de sortie de succès
}

