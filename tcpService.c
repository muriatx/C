#include <stdio.h>

// Socket
#include <sys/types.h>        
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h>

#include <string.h>


#define SERVER_PORT 3010
#define SERVER_IP "127.0.0.1"
#define MAX_CLIENTS 5

#define BUFFER_SIZE 256

// +-+-+-++-+-+-+-+-+ Variables +-+-+-++-+-+-+-+-+
int serversocketfd,
		clientsocketfd,
		bytesRecibidos,
		bytesEnviados,
		tamSockaddr = sizeof(struct sockaddr);

char buffer[BUFFER_SIZE];

struct sockaddr_in server,
					client;

// +-+-+-++-+-+-+-+-+ Metodos +-+-+-++-+-+-+-+-+

void encenderServidorTCP(){

	
	// 1. Creacion del socket SERVIDOR
        // int socket(int domain, int type, int protocol);
        if((serversocketfd = socket(AF_INET,SOCK_STREAM,0))){
        /*
         *  AF_INET      IPv4 Internet protocols
         * 
         *  SOCK_STREAM     Provides  sequenced,  reliable,  two-way,  connection-
                           based byte streams.  An out-of-band data  transmission
                           mechanism may be supported.
         * 
         * 0 => Hace referencia al protocolo IP
         * 
         */
            printf("Error al crear socket\n");
            exit(1);
        }

    // 2. Especificamos la direccion donde se va a atender el Servidor(Dir IP y puerto)
		//memset(&server,0,sizeof(struct sockaddr_in)); // memset - fill memory with a constant byte
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(SERVER_IP); // char *ip = inet_ntoa(cliente.sin_addr);
								//  o tambn = INADDR_ANY;
		server.sin_port = htons(SERVER_PORT); 

	// 3. Asociar direccion del servidor al socket creado para atender el servicio
    if(bind(serversocketfd,(struct sockaddr *)&server,sizeof(struct sockaddr))== -1){
        printf("Error al hacer bind\n");
        exit(1);
    }    

	// 4. Escucha
    if(listen(serversocketfd,MAX_CLIENTS) == -1){ 
        // si hay varias solicitudes las va encolando
        // 3 = MaxNum de peticiones, si hay más de 3 se les echa
        printf("Error al hacer listen\n");
        exit(1);
    }

	

	printf("Servicio TCP iniciado\n");

	while(1){
		
	  // 5. Atencion a las solicitudes	
		if((clientsocketfd = accept(serversocketfd,(struct sockaddr *)&server,&tamSockaddr)) == -1){ 
       
			printf("Error al crear socket de atencion al cliente\n");
			exit(1);
		} 

 	 // 6. Comunicacion

		if(fork() == 0){
			
			printf("Esperando recibir mensaje, pid del proceso %d\n",getpid());

			close(serversocketfd);
			while(recibir(buffer) > 0){
				
				procesarPeticionCliente();

			}
			close(clientsocketfd);
			exit(0);
		}
		
	}	

	
}

void procesarPeticionCliente(){


}


void encenderClienteTCP(){

	// 1. Creacion del socket CLIENTE
        // int socket(int domain, int type, int protocol);
        if((clientsocketfd = socket(AF_INET,SOCK_STREAM,0))){
        /*
         *  AF_INET      IPv4 Internet protocols
         * 
         *  SOCK_STREAM     Provides  sequenced,  reliable,  two-way,  connection-
                           based byte streams.  An out-of-band data  transmission
                           mechanism may be supported.
         * 
         * 0 => Hace referencia al protocolo IP
         * 
         */
            printf("Error al crear socket\n");
            exit(1);
        }

    // 2. Especificamos la direccion donde se va a atender el CLIENTE(Dir IP y puerto)
		//memset(&server,0,sizeof(struct sockaddr_in)); // memset - fill memory with a constant byte
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(SERVER_IP); // char *ip = inet_ntoa(cliente.sin_addr);
								//  o tambn = INADDR_ANY;
		server.sin_port = htons(SERVER_PORT); 

	// 3. Asociar direccion del servidor al socket creado para atender el servicio
    if(connect(clientsocketfd,(struct sockaddr *)&server,tamSockaddr) == -1){
        printf("Error al hacer connect\n");
        exit(1);
    }

	procesarCxConServer();
	close(clientsocketfd);

}    



void procesarCxConServer(){


	if(buffer[strlen(buffer)] == '\n')
            buffer[strlen(buffer)] = '\0';
}


int transmitir(char * buffer, int bytesAEnviar){

	bytesEnviados = write(clientsocketfd, buffer, bytesAEnviar);
	printf("Enviados >%d< bytes\n",bytesEnviados);

	return bytesEnviados;
}

int recibir(char * buffer){

	bytesRecibidos = read(clientsocketfd,buffer,BUFFER_SIZE);
	buffer[bytesRecibidos] = '\0';	
	printf("Recibidos >%d< bytes\n",bytesRecibidos);

	return bytesRecibidos;
}

void cerrarConector(int socketfd){
	close(socketfd);
}

/**
 *  int howto: SHUT_
 * 					RD:   (0) Deshabilita la recepcion de mensajes
 * 					WR:   (1) Deshabilita el envio de mensajes
 * 					RDWR: (2) Deshabilita la recepcion y el envio de mensajes
 */	
int cerrarConectorAmbosSentidos(int socketfd, int howto){
	
	return shutdown(socketfd,howto);
}





int main(){

	
	printf("Hello World!\n");

	return (0);
}