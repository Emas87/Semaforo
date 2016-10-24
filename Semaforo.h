#define KEY 0xA12345	// Valor de la llave del recurso
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/semaphore.h>
#include <iostream.h>
#include <errno.h>

class Semaforo {
   Semaforo( int ValorInicial = 0 );
   ~Semaforo();
   int Signal();	// Puede llamarse V
   int Wait();	// Puede llamarse P
   private:
   int id;		// Identificador del semaforo
   struct sembuf sbuf;
};

Semaforo::Semaforo(int ValorInicial = 0 ){
	id = semget(KEY,1, 0775 | IPC_CREAT);
	semun init;
	init.val = ValorInicial;
	semctl(id, 1, SETVAL, init);
	if(id != 1){
      	/* Initialize the semaphore. */
        sbuf.sem_num = 0;
        sbuf.sem_op = ValorInicial;  /* This is the number of runs
                             without queuing. */
        sbuf.sem_flg = 0;
        if (semop(id, &sbuf, 1) == -1) {
            perror("IPC error: semop"); exit(1);
        }
   	}
	else if (errno == EEXIST) {
        if ((id = semget(KEY, 0, 0)) == -1) {
            perror("IPC error 1: semget"); exit(1);
        }
    }
    else {
        perror("IPC error 2: semget"); exit(1);
    }
}

Semaforo::Wait() {
	sbuf.sem_num = 0;
	sbuf.sem_op = -1;  /* This is the number of runs without queuing. */
	sbuf.sem_flg = 0;
	if (semop(id, &sbuf, 1) == -1) {
		perror("IPC error: semop"); exit(1);
	}
}

Semaforo::Signal() {
	sbuf.sem_num = 0;
	sbuf.sem_op = 1;  /* This is the number of runs without queuing. */
	sbuf.sem_flg = 0;
	if (semop(id, &sbuf, 1) == -1) {
		perror("IPC error: semop"); exit(1);
	}
}
