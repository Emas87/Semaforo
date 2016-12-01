#include <stdio.h>
#include <unistd.h>
#include "Semaforo.h"

int main() {
    Semaforo s;
    int j;

    if ( fork() ) {
       	for (int i = 0; i < 10; i++ ){
           printf( "Esperando para activar el semaforo %d \n", i );
	}
       	scanf( "%d", &j );
	exit(-1);
       	s.Signal();
    }
    else {
       printf( "Esperando que el semaforo se active  ...\n" );
       s.Wait();
       printf( "Semaforo activado\n" );
    }
}
