#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

bool finished = false;

void busyWait() {
    while (!finished);
}

void blockWait() {
    while (!finished) {
        pause();
    }
}

void sigabrtHandler(int signalNumber){
    printf("Esse BRT não é expresso!\n"); //6
}

void sigbusHandler(int signalNumber) {
    printf("Esse não é o seu ônibus!\n"); // 7
}

void sigtrapHandler(int signalNumber) {
    printf("É uma cilada Bino!\n"); //5
    printf("O programa será encerrado...\n");
    finished=true;
}

int main() {
    int choice;
    printf("Quer utilizar busy waiting? Se sim, digite 1.\n");
    
    scanf("%d", &choice);

    signal(SIGABRT, sigabrtHandler);
    signal(SIGBUS, sigbusHandler);
    signal(SIGTRAP, sigtrapHandler); 

    printf("My PID is %d.\n", getpid());

    if (choice == 1) {
        busyWait(); 
    }
    else {
        blockWait(); 
    }
    
    return 0;
}