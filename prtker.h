#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int function_basic_scan(char direccion[], char mensaje[], int number){
	int sock = socket(AF_INET, SOCK_STREAM, 0); //se crea un socket
    if(sock == -1){
    	printf("Error al crear el socket\n");
    }
    //configuracion de la direccion del servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(number);
    serverAddress.sin_addr.s_addr = inet_addr(direccion);

   	//se establece la conexion
    int result = connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if(result==-1){
        printf("close %s", mensaje);printf("%i", number);
    	close(sock);
    	return 1;
    }
    printf("open %s", mensaje);printf("%i", number);
    return 0;
}