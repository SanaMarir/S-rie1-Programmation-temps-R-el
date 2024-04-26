#include <stdio.h>    
#include <pthread.h>    
#include <stdlib.h>     

// Fonction exécutée par le thread pour afficher un message
void *print_message(void *arg) {
    char *msg = (char*) arg;   // le passage d'argument
    printf("message = %s\n", msg); // Afficher le message
    return NULL;    // Retourner NULL car la fonction est de type void *
}

int main(int argc, char *argv[]) {
    pthread_t t;   // Déclarer une variable pour stocker l'identifiant du thread

    char *msg = "bonjour tout le monde";   // Déclare une chaîne de caractères à passer au thread

    // Crée un nouveau thread qui exécute la fonction print_message 
    if(pthread_create(&t, NULL, print_message, msg) != 0) {
    	// En cas d'erreur lors de la création du thread, afficher un message d'erreur
        perror("thread error");   
        return EXIT_FAILURE;      // Terminer le programme avec un code de sortie d'échec
    }

    // Attend que le thread 't' se termine
    pthread_join(t, NULL);

    return EXIT_SUCCESS;   // Termine le programme avec un code de sortie de succès
}

