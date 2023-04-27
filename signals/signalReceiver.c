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
    printf("SIGABRT\n"); //6
}

void sigbusHandler(int signalNumber) {
    printf("SIGBUS\n"); // 7
}

void sigstrapHandler(int signalNumber) {
    printf("SIGTRAP\n"); //5
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