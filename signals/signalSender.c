#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() { 
	int signal, pid;

	printf("Digite o PID desejado.\n");
	scanf("%d", &pid);

	if ((getpgid(pid) < 0))	{
		printf("O processo digitado não foi encontrado.\n");
		return 1;
	}

	printf("Digite o número do sinal desejado.\n");
	scanf("%d", &signal);

	kill(pid, signal);

	return 0;
}