#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include<pthread.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "transactions.h"

pthread_mutex_t lock;

void deposit(int * accounts, int acc, int amount){
    printf("Depositing into account %d. Current balance: %d\n\n", acc, accounts[acc]);
    accounts[acc] += amount;
    printf("Deposit complete. Account %d has a new balance of: %d\n\n", acc, accounts[acc]);
}

void widthdraw(int * accounts, int acc, int amount){
    pthread_mutex_lock(&lock);
    printf("Widthdrawing from account %d. Current balance: %d\n\n", acc, accounts[acc]);
    if(accounts[acc] < amount){
        printf("DECLINED. You tried to widthraw %d, when the account balance was %d.\n\n", amount, accounts[acc]);
    }else{
        printf("Widthdraw from account %d ACCEPTED. ", acc);
        accounts[acc] -= amount;
        printf("Widthdraw complete. Account %d has a new balance of: %d\n\n", acc, accounts[acc]);
    }
    pthread_mutex_unlock(&lock);
}

void transfer(int * accounts, int a1, int a2, int amount){
    pthread_mutex_lock(&lock);
    printf("Transfer from account %d to account %d. Current balance: %d, and %d, respectively\n\n", a1, a2, accounts[a1], accounts[a2]);
    if(accounts[a1] < amount){
        printf("DECLINED. You tried to transfer %d from account %d, when the account balance was %d.\n\n", amount, accounts[a1]);
    }else{
        printf("Transfer from account %d, to account %d ACCEPTED.", a1, a2);
        accounts[a1] -= amount;
        accounts[a2] += amount;
        printf("Transfer complete, account %d has a new balance of: %d, and account %d has a new balance of: %d\n\n", a1, accounts[a1], a2, accounts[a2]);
    }
    pthread_mutex_unlock(&lock);
}


