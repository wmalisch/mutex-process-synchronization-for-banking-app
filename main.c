#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "io.h"
#include "types.h"

void *execute(void * client){
    char *client_transactions = (char *)client;
    char client_num = client_transactions[1];
    printf("Printing client transactions: %s...\nCalled from thread %c\n", client, client_num);
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

    // Create a thread pointer for each client
    pthread_t * threads = malloc(sizeof(pthread_t) * input.nClients);
    for(int i = 0; i < input.nClients; i++){
        pthread_create(&threads[i], NULL, &execute, input.clients[i]);
    }

    for(int i = 0; i < input.nClients; i++){
        pthread_join(threads[i], NULL);
    }




    return 0;
}