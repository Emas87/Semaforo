#define KEY 0xA12345	// Valor de la llave del recurso
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
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

	if(id != 1){
      	/* Initialize the semaphore. */
        sbuf.sem_num = 0;
        sbuf.sem_op = ValorInicial;  /* This is the number of runs
                             without queuing. */
        sbuf.sem_flg = 0;
        if (semop(semid, &sbuf, 1) == -1) {
            perror("IPC error: semop"); exit(1);
        }
   	}
	else if (errno == EEXIST) {
        if ((semid = semget(semkey, 0, 0)) == -1) {
            perror("IPC error 1: semget"); exit(1);
        }
    }
    else {
        perror("IPC error 2: semget"); exit(1);
    }
}

Semaforo::Wait() {
	while(this.ValorInicial == 0) {
		block(process);
	}
	this.ValorInicial--;
}

Semaforo::Signal() {
	wakeup(process);
	this.ValorInicial++;
}
