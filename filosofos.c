#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

sem_t *garfos;
int N_FILOS;

void *filosofo(void *);
int gera_rand(int);

int main(int argc, char **argv) {
    pthread_t *tids;
    long i;

    if (argc < 2) {
        printf("Usage: %s num_filosofos\n", argv[0]);
        return 0;
    }

    N_FILOS = atoi(argv[1]);

    // Verificação de entrada mínima
    if (N_FILOS < 2) {
        printf("Número de filósofos deve ser pelo menos 2 para simulação.\n");
        return 1;
    }

    srand(time(NULL));

    // Inicializa os semáforos dos garfos
    garfos = malloc(N_FILOS * sizeof(sem_t));
    for (i = 0; i < N_FILOS; i++)
        sem_init(&garfos[i], 0, 1);

    // Cria as threads dos filósofos
    tids = malloc(N_FILOS * sizeof(pthread_t));
    for (i = 0; i < N_FILOS; i++)
        pthread_create(&tids[i], NULL, filosofo, (void *)i);
    for (i = 0; i < N_FILOS; i++)
        pthread_join(tids[i], NULL);

    // Destroi os semáforos
    for (i = 0; i < N_FILOS; i++)
        sem_destroy(&garfos[i]);

    free(garfos);
    free(tids);
    return 0;
}

void *filosofo(void *id) {
    long i = (long)id;
    int esq = i;
    int dir = (i + 1) % N_FILOS;

    printf("Filosofo %ld pensando\n", i);
    usleep(gera_rand(1000000));

    if (i % 2 == 0) {
        sem_wait(&garfos[esq]);
        printf("Filosofo %ld pegou garfo esquerdo (%d)\n", i, esq);
        sem_wait(&garfos[dir]);
        printf("Filosofo %ld pegou garfo direito (%d)\n", i, dir);
    } else {
        sem_wait(&garfos[dir]);
        printf("Filosofo %ld pegou garfo direito (%d)\n", i, dir);
        sem_wait(&garfos[esq]);
        printf("Filosofo %ld pegou garfo esquerdo (%d)\n", i, esq);
    }

    printf("Filosofo %ld comendo\n", i);
    usleep(gera_rand(1000000));

    sem_post(&garfos[esq]);
    sem_post(&garfos[dir]);

    printf("Filosofo %ld terminou de comer\n", i);
    return NULL;
}

int gera_rand(int limit) {
    return rand() % limit;
}
