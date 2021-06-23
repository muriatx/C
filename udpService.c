#include <stdio.h>

// Socket
#include <sys/types.h>        
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>


#define SERVER_PORT 3010
#define SERVER_IP "127.0.0.1"

#define BUFFER_SIZE 256

// +-+-+-++-+-+-+-+-+ Variables +-+-+-++-+-+-+-+-+
int socketfd,
		bytesRecibidos,
		bytesEnviados,
		tamCliente = sizeof(struct sockaddr);

char buffer[BUFFER_SIZE];

struct sockaddr_in server,
					client;

// +-+-+-++-+-+-+-+-+ Metodos +-+-+-++-+-+-+-+-+

void encenderServicioUDP(){

	socketfd = socket(AF_INET,SOCK_DGRAM,0);

	//memset(&server,0,sizeof(struct sockaddr_in)); // memset - fill memory with a constant byte
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_IP); // char *ip = inet_ntoa(cliente.sin_addr);
	server.sin_port = htons(SERVER_PORT);


	bind(socketfd,(struct sockaddr *)&server,sizeof(struct sockaddr));

	printf("Servicio UDP iniciado\n");
}

int transmitir(char * buffer, int bytesAEnviar){

	bytesEnviados = sendto(socketfd,buffer,bytesAEnviar,0,(struct sockaddr *)&client,sizeof(struct sockaddr));
	printf("Enviados >%d< bytes\n",bytesEnviados);

	return bytesEnviados;
}

int recibir(char * buffer, int bytesAEnviar){


	bytesRecibidos = recvfrom(socketfd,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client,&tamCliente);
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