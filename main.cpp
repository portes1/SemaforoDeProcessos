#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <queue>

#define FALSE 0
#define TRUE 1

#define N 1000

struct timespec t;
sem_t  mutex, empty, full;

int fila[N], frente, final, count;

void *produtor(void *);
void *consumidor(void *);

int main(void)
{

 srand(time(NULL));
 count = 0;
 frente = 0;
 final = 0;
 
 sem_init (&mutex, 0 , 1);
 sem_init(&empty, 0, N);
 sem_init(&full, 0, 0);
 
 pthread_t proc1, proc2, proc3, proc4, proc5, proc6, proc7, proc8, proc9, proc10;

  pthread_create(&proc1, 0, produtor, NULL);
  pthread_create(&proc2, 0, produtor, NULL);
  pthread_create(&proc3, 0, produtor, NULL);
  pthread_create(&proc4, 0, produtor, NULL);
  pthread_create(&proc5, 0, produtor, NULL);
  pthread_create(&proc6, 0, consumidor, NULL);
  pthread_create(&proc7, 0, consumidor, NULL);
  pthread_create(&proc8, 0, consumidor, NULL);
  pthread_create(&proc9, 0, consumidor, NULL); 
  pthread_create(&proc10, 0, consumidor, NULL);
 
 pthread_join(proc1,0);
 pthread_join(proc2,0);
pthread_join(proc3,0);
 pthread_join(proc4,0);
  pthread_join(proc5,0);
 pthread_join(proc6,0);
  pthread_join(proc7,0);
 pthread_join(proc8,0);
  pthread_join(proc9,0);
 pthread_join(proc10,0);
 
 exit(0);
}


int insereDado(int carga)
{
 int val;
 val = rand() % 10000;
 printf("\n CARGA: %d INSERIU: %d",carga, val);
 return val;
}

void apagaDado(int item, int carga)
{
 printf("\n CARGA: %d APAGOU: %d",carga, item);
}

void insert_item(int val)
{
 if(count < N)
 {
  fila[final] = val;
  final = (final + 1) % N; 
  count = count + 1;
  if(count == N)
   printf("\n ~~~MEMORIA CHEIA~~");
 }
}

int removeItem(){
 int val;
 if(count > 0){
  val = fila[frente];
  frente = (frente + 1) % N;
  count = count - 1;
  return val;
 }
}

void *produtor(void *p_arg)
{
 int item;
 
 for(int i = 0; i <= 199;i++){
  item = insereDado(i);

  sem_wait(&empty);
  sem_wait(&mutex);
  insert_item(item);
  sem_post(&mutex);
  sem_post(&full);
//	sleep(10);
 }
}

void *consumidor(void *p_arg)
{
 int item;

 for(int i = 0; i <= 199;i++) {

  sem_wait(&full);
  sem_wait(&mutex);
  item = removeItem();
  sem_post(&mutex);
  sem_post(&empty);
  apagaDado(item, i);
  
 // sleep(10);
 }
}
