#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10  // Taille du tableau
#define NUM_THREADS 4  // Nombre de thread


int totalSum = 0;  // Variable globale pour stocker la somme totale

// Structure pour stocker les arguments d'une section de tableau 

typedef struct {
    int *start; 		// Pointeur vers le début de la section
    int *end;			// Pointeur vers la fin de la section
    pthread_mutex_t *lock;		// Pointeur vers le verrou mutex
} PartialSumArgs;

//--Fonction pour calculer la somme partielle d'une section du tableau--//

void *sum_partial(void *args) {
    PartialSumArgs *partialArgs = (PartialSumArgs *)args;

    int partialSum = 0;
    
	//parcours de la section et calcul de la somme partielle
    int *p;
    for (p = partialArgs->start; p < partialArgs->end; p++) {
        partialSum += *p;
    }
	
	// Verrouillage du mutex
    pthread_mutex_lock(partialArgs->lock);
    
    totalSum += partialSum;
    
    // Déverrouillage du mutex
    pthread_mutex_unlock(partialArgs->lock); 
    
    pthread_exit(NULL);
}

//---------------------------------------------//

int main() {
    int array[ARRAY_SIZE];
    int i;
    
	//remplissage du tableau
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

	//initialisation d'un mutex
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL); 

	//declaration des threads
    pthread_t threads[NUM_THREADS];  

	//tableau de structures pour stocker les arguments des threads.
    PartialSumArgs threadArgs[NUM_THREADS];
    
	//taille de chaque section
    int sectionSize = ARRAY_SIZE / NUM_THREADS;
    
    //correspondance thread__section
    for (i = 0; i < NUM_THREADS; i++) {
        threadArgs[i].start = (array+i * sectionSize);  // Début de la section
        threadArgs[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * sectionSize)); // Fin de la section
        threadArgs[i].lock = &lock; // Pointeur vers le mutex
		
		// Création du thread avec la fonction sum_partial et les arguments correspondants

        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Erreur lors de la creation du thread %d\n", i);
            return 1;
        }
    }
	
	//organisation des threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Somme totale : %d\n", totalSum);
	
	//Le mutex est détruit pour libérer les ressources utilisées par celui-ci.
    pthread_mutex_destroy(&lock);

    return 0;
}
