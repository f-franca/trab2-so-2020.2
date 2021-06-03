#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define NTHREADS  2

/* Variaveis globais */
int x = 0;
pthread_mutex_t mutex;
pthread_cond_t a, b;

/* Thread A */
void *Processo_A (void *t) {
  //printf("Processo_A: Comecei\n");
  //pthread_mutex_lock(&mutex);
  pthread_cond_wait(&a, &mutex);
  //printf("Processo_A: vai sinalizar a condicao \n");
  printf("A\n");
  printf("B\n\n");
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&b);
  pthread_exit(NULL);
}

/* Thread B */
void *Processo_B (void *t) {
  //printf("Processo_B: Comecei\n");
  pthread_cond_signal(&a);
  pthread_cond_wait(&b, &mutex);
  //printf("Processo_B: vai se bloquear...\n");
  printf("C\n");
  printf("D\n\n");
  //pthread_mutex_lock(&mutex);
  //printf("Processo_B: sinal recebido e mutex realocado\n");
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&a); 
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init (&a, NULL);
  pthread_cond_init (&b, NULL);

  /* Cria as threads */
  pthread_cond_signal(&a);
  while (1) {
    pthread_create(&threads[0], NULL, Processo_A, NULL);
    pthread_create(&threads[1], NULL, Processo_B, NULL);
  }
  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&a);
  pthread_cond_destroy(&b);
  pthread_exit (NULL);
}
