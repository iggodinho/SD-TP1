#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <netdb.h>
#include <strings.h>
#include <sys/socket.h>

#define MAX 20
#define PORT 8080
#define SA struct sockaddr

bool isPrime(int num) {
    if (num <= 1) return 0;
 
    for (int i = 2; i < num; i++) {
        if (num % i == 0) return 0;
    }

    return 1;
}

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Erro ao criar o socket\n");
		exit(0);
	}
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Bind socket criado ao IP
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Erro no bind\n");
		exit(0);
	}

	// Ouve
	if ((listen(sockfd, 5)) != 0) {
		printf("Erro ao ouvir\n");
		exit(0);
	}
	len = sizeof(cli);

	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("Erro ao aceitar conexao\n");
		exit(0);
	}

	// função
    char message[MAX];
    bool loop = 1;
    int num;

    do {
        bzero(message, sizeof(message));
		read(connfd, message, sizeof(message));
        num = atoi(message);
        sprintf(message, "%d", isPrime(num));
        write(connfd, message, sizeof(message));
        if (num == 0) loop = 0;
    } while (loop == 1);

	close(sockfd);
}
