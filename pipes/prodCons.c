#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#define MAX 20
#define MAXITER 50

pid_t pid;
int pipeTunnel[2];

bool isPrime(int num) {
    if (num <= 1) return 0;
 
    for (int i = 2; i < num; i++) {
        if (num % i == 0) return 0;
    }

    return 1;
}

double newNum(int num) {
    int delta = (rand() % 99) + 1;
    return num + delta;
}

int main(void) {
    int numeros_restantes;
    printf("Numeros a serem gerados: ");
    scanf("%d", &numeros_restantes);

    pipe(pipeTunnel);
    pid = fork();

    if (pid == 0) {  // filho - consumidor
        char message[MAX];
        int limit = MAXITER;

        close(pipeTunnel[1]);

        do {
            read(pipeTunnel[0], message, MAX);
            printf("[PID: %d] Número recebido %s é primo?  %s\n", pid, message, isPrime(atoi(message)) ? "true" : "false");
            limit--;
        } while (atoi(message) > 0 && limit > 0);

        exit(0);
    }

    else {  // pai - produtor
        char message[MAX];
        int num = 1;
        int limit_ = MAXITER;

        close(pipeTunnel[0]);

        do {
            sprintf(message, "%d", num);
            write(pipeTunnel[1], message, MAX);
            printf("[PID: %d] Número enviado: %s\n", pid, message);
            num = newNum(num);
            numeros_restantes--;
            limit_--;
        } while (numeros_restantes > 1 && limit_ > 0);
        sprintf(message, "%d", 0);
        write(pipeTunnel[1], message, MAX);
        printf("[PID: %d] Número final enviado: %s\n", pid, message);

        exit(0);
    }

    return 0;
}