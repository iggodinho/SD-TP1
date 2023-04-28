#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <strings.h>
#include <sys/socket.h>

#define MAX 20
#define PORT 8080
#define SA struct sockaddr

double newNum(int num) {
    int delta = (rand() % 99) + 1;
    return num + delta;
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr;

    int numeros_restantes;
    printf("Numeros a serem gerados: ");
    scanf("%d", &numeros_restantes);

	// cria o socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Erro ao criar o socket\n");
		exit(0);
	}
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Conecta ao servidor
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Erro ao conectar ao servidor\n");
		exit(0);
	}

    char message[MAX];
    int num = 1;
    bool loop = 1;

    do {
        bzero(message, sizeof(message));
        num = newNum(num);
        sprintf(message, "%d", num);
		write(sockfd, message, sizeof(message));
        printf("Número enviado: %s\n", message);
		bzero(message, sizeof(message));
		read(sockfd, message, sizeof(message));
		printf("É primo? %s\n", atoi(message) ? "true" : "false");
        numeros_restantes--;
    } while (loop == 1 && numeros_restantes > 1);

    sprintf(message, "%d", 0);
    write(sockfd, message, sizeof(message));
    printf("Número final enviado: %s\n", message);
    bzero(message, sizeof(message));
    read(sockfd, message, sizeof(message));
    printf("É primo? %s\n", atoi(message) ? "true" : "false");

	// Fecha
	close(sockfd);
}
