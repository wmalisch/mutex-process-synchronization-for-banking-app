#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "io.h"
#include "types.h"
#include "transactions.h"

// Initialize mutex lock
pthread_mutex_t lock;

// Structure for arguments
struct arg_struct {
    int * accounts;
    char * clients;
};

// Function called by thread to perform transactions on bank accounts
void *execute_transactions(void * args){

    // Convert client transactions to char array
    struct arg_struct *arguments = args;
    int * accounts = arguments->accounts;
    char * client_transactions = arguments->clients;
    char client_num = client_transactions[1];
    
    // Variables for transaction execution
    int acc;
    int amount;
    int acc2;

    // Skip client number to the transactions
    char * split;
    split = strtok(client_transactions, " ");

    // First transaction
    split = strtok(NULL, " ");
    char * hold;

    // Loop until done all transactions
    while(split != NULL){
        if(split[0] == 'd'){
            split = strtok(NULL, " "); // Get bank account
            memmove(split, split+1, strlen(split)); // get rid of the a
            sscanf(split, "%d", &acc); // convert to int
            split = strtok(NULL, " "); // get amount to deposit
            amount = atoi(split); // convert to int
            printf("Deposit called from thread %c\n\n",client_num);
            deposit(accounts, acc, amount);
        }else if(split[0] == 'w'){
            split = strtok(NULL, " "); // Get bank account
            memmove(split, split+1, strlen(split)); // get rid of the a
            sscanf(split, "%d", &acc); // convert to int
            split = strtok(NULL, " "); // get amount to widthdraw
            amount = atoi(split); // convert to int
            printf("Widthdraw called from thread %c\n\n",client_num);
            widthdraw(accounts, acc, amount);
        }else if(split[0] == 't'){
            
            split = strtok(NULL, " "); // Get first bank account
            memmove(split, split+1, strlen(split)); // get rid of the a
            sscanf(split, "%d", &acc); // convert to int
            split = strtok(NULL, " "); // Get second bank account
            memmove(split, split+1, strlen(split)); // get rid of the a
            sscanf(split, "%d", &acc2); // convert to int
            split = strtok(NULL, " "); // get amount to transfer
            amount = atoi(split); // convert to int
            printf("Transfer called from thread %c\n\n",client_num);
            transfer(accounts, acc, acc2, amount);
        }
        split = strtok(NULL," ");
    }

}

int main(int argc,char * argv[])
{
    if(argc != 2){
        printf("Usage: %s you_desired_input.txt\n", argv[0]);
        exit(1);
    }

    input_data input;

    int fp_outfile = open("output.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    
    // Parse input data to get no. accounts, clients, and list for client transactions and bank account values
    read_input_file(argv[1], &input);
    // Create a thread pointer for each client, and argument structure for each thread
    pthread_t * threads = malloc(sizeof(pthread_t) * input.nClients);
    struct arg_struct * args = malloc(sizeof(struct arg_struct) * input.nClients);
    for(int i = 0; i < input.nClients; i++){
        args[i].clients = input.clients[i];
        args[i].accounts = input.bankAccounts;
    }

    // Create threads
    for(int i = 0; i < input.nClients; i++){
        pthread_create(&threads[i], NULL, &execute_transactions, &args[i]);
    }


    // Join threads
    for(int i = 0; i < input.nClients; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock); 

    printf("SIMULATION DONE!\n\n");
    printf("Account balances are as follows:\n");
    for(int i = 0; i < input.nAccounts; i++){
        printf("a%d: %d\n",i, input.bankAccounts[i]);
    }

    return 0;
}