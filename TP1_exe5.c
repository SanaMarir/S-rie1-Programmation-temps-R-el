#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TASKS 3

// Structure pour stocker les informations d'une tâche périodique
typedef struct {
    int id;		//identifiant
    int period;  // en secondes
} PeriodicTask;

// Fonction exécutée par chaque thread pour une tâche périodique
void *taskFunction(void *arg) {
    PeriodicTask *task = (PeriodicTask *)arg;	 // le passage d'argument
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL); //initialiser le comportement d'annulation du thread

    while (1) {
        sleep(task->period); //attendre une periode
        printf("Task %d executed.\n", task->id); 
        pthread_testcancel();  // Test d'annulation du thread
    }

    return NULL;
}

int main() {
    int TASK_PERIODS[]={1, 2, 3};	//periode de chaque tache
    pthread_t threads[NUM_TASKS];	//tableau de threads
    PeriodicTask tasks[NUM_TASKS];	//tableau de taches per
    int i;

	// Création des threads pour chaque tâche périodique
    for (i = 0; i < NUM_TASKS; i++) {
        tasks[i].id = i + 1;				//attribuer l'identifiant
        tasks[i].period = TASK_PERIODS[i];	//""  la periode
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]);	//cration du thread
    }

    sleep(8);			//attente
    
    // Annulation de chaque thread et attente de leur terminaison
    for (i = 0; i < NUM_TASKS; i++) {
        pthread_cancel(threads[i]);		//annulation
        pthread_join(threads[i], NULL);
    }
    return 0;
}
