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

};

Semaforo::Semaforo(int ValorInicial = 0 ){
Lab3ff
	id = semget(KEY,1, 0775 | IPC_CREAT);

	if(id < 0){
      		cout << "No se pudo generar el semaforo.\n"<< strerror(id) << endl;
      		exit(0);
   	}
}

Semaforo::Wait() {
	this.ValorInicial--;
	if (this.ValorInicial < 0) {
		this.Cola.push(process);
		block();
	}
}

Semaforo::Signal() {
	this.ValorInicial++;
	if (this.ValorInicial <= 0) {
		this.Cola.pop(process);
		wakeup(process);
	}
}
