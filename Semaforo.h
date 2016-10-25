#define KEY 0xA12345	// Valor de la llave del recurso
#include <sys/types.h>
#include <sys/ipc.h>
// #include <semaphore.h>
#include <sys/sem.h>
#include <iostream>
#include <cstdlib>
#include <errno.h>

using namespace std;
class Semaforo {
   public:
      Semaforo( int ValorInicial);
      ~Semaforo(){ semctl(id, 0, 2, IPC_RMID); };
      int Signal();	// Puede llamarse V
      int Wait();	// Puede llamarse P
   private:
      int id;		// Identificador del semaforo
      struct sembuf sbuf;
};

Semaforo::Semaforo(int ValorInicial = 0 ){
	if(id = semget(KEY,1, 0775 | IPC_CREAT) < 0){
      printf("Can\'t get id\n");
      exit(-1);
   } else if (id != -1){
   
        sbuf.sem_num = 0;
        sbuf.sem_op = ValorInicial;  /* This is the number of runs
                             without queuing. */
        sbuf.sem_flg = 0;
        if (semop(id, &sbuf, 1) == -1) {
            perror("IPC error: semop"); exit(1);
        }
   } else if (errno == EEXIST) {
        if ((id = semget(KEY, 0, 0)) == -1) {
            perror("IPC error 1: semget"); exit(1);
        }
    } else {
       cout << "id: " << id << endl;
        perror("IPC error 2: semget"); exit(1);
    }
}

int Semaforo::Wait() {
	sbuf.sem_num = 0;
	sbuf.sem_op = -1;  /* This is the number of runs without queuing. */
	sbuf.sem_flg = 0;
	if (semop(id, &sbuf, 1) == -1) {
		perror("IPC error: semop"); exit(1);
	}
}

int Semaforo::Signal() {
	sbuf.sem_num = 0;
	sbuf.sem_op = 1;  /* This is the number of runs without queuing. */
	sbuf.sem_flg = 0;
	if (semop(id, &sbuf, 1) == -1) {
		perror("IPC error: semop"); exit(1);
	}
}
