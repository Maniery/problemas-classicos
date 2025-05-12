#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

// Vetor de semáforos (um para cada garfo)
sem_t *garfos;

// Número de filósofos
int N_FILOS;

// Protótipos
void *filosofo(void *);
int gera_rand(int);

int main(int argc, char **argv)
{
    pthread_t *tids;
    long i;

    if (argc != 2)
    {
        printf("Usage: %s num_filosofos\n", argv[0]);
        return 0;
    }

    srand(time(NULL));

    N_FILOS = atoi(argv[1]);

    // Aloca os semáforos dos garfos
    garfos = malloc(N_FILOS * sizeof(sem_t));
    for (i = 0; i < N_FILOS; i++)
        sem_init(&garfos[i], 0, 1);  // cada garfo está livre inicialmente

    // Cria as threads dos filósofos
    tids = malloc(N_FILOS * sizeof(pthread_t));
    for (i = 0; i < N_FILOS; i++)
        pthread_create(&tids[i], NULL, filosofo, (void *)i);

    // Aguarda as threads
    for (i = 0; i < N_FILOS; i++)
        pthread_join(tids[i], NULL);

    // Destroi os semáforos
    for (i = 0; i < N_FILOS; i++)
        sem_destroy(&garfos[i]);

    free(garfos);
    free(tids);

    return 0;
}

void *filosofo(void *id)
{
    long i = (long)id;
    int esq = i;
    int dir = (i + 1) % N_FILOS;

    printf("Filósofo %ld está pensando\n", i);
    usleep(gera_rand(1000000));

    if (i % 2 == 0) {
        // filósofos pares pegam primeiro o garfo esquerdo
        sem_wait(&garfos[esq]);
        printf("Filósofo %ld pegou o garfo esquerdo (%d)\n", i, esq);
        sem_wait(&garfos[dir]);
        printf("Filósofo %ld pegou o garfo direito (%d)\n", i, dir);
    } else {
        // filósofos ímpares pegam primeiro o garfo direito
        sem_wait(&garfos[dir]);
        printf("Filósofo %ld pegou o garfo direito (%d)\n", i, dir);
        sem_wait(&garfos[esq]);
        printf("Filósofo %ld pegou o garfo esquerdo (%d)\n", i, esq);
    }

    printf("Filósofo %ld está comendo\n", i);
    usleep(gera_rand(1000000));

    // Libera os garfos
    sem_post(&garfos[esq]);
    sem_post(&garfos[dir]);

    printf("Filósofo %ld terminou de comer e liberou os garfos\n", i);
    return NULL;
}

int gera_rand(int limit)
{
    return rand() % limit;
}
