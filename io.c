#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "io.h"

counts num_accounts_clients(FILE *fp, counts *inp)
{
    int a = 0;
    int c = 0;
    char str[1000];
    while(fgets(str, 1000, fp) != NULL){
        if(str[0] == 'a'){
            a++;
        }else if(str[0] == 'c'){
            c++;
        }
    }
    fclose(fp);
    inp->a=a;
    inp->c=c;
    return *inp;
}

int num_c(char * line){
    int num = 0;
    char index = line[0];
    while(index != '\n'){
        num++;
        index = line[num];

    }
    return num;
}

int read_input_file(char *filename, input_data *input){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        perror(filename);
        exit(1);
    }

    // Get number of accounts and clients, store in input data
    counts inp;
    inp = num_accounts_clients(fp, &inp);
    int * bankAccounts = malloc(sizeof(int) * inp.a);
    char ** clients = malloc(sizeof(char *) * inp.c);

    // Get account balances, and store the balance in its respective account location
    fp = fopen(filename, "r");
    char str[1000];
    int integer;
    for(int i = 0; i < inp.a; i++){
        fgets(str, 1000, fp);
        char * split;
        split = strtok(str, " ");
        split = strtok(NULL, " ");
        split = strtok(NULL, " ");
        integer = atoi(split);
        bankAccounts[i] = integer;
    }

    // Loop through rest of file and store all clients transactions in clients pointer
	size_t len = 0;
	char *tok;
	const char delim[2] = " ";
	ssize_t nread;
    int var;
    for(int i = 0; i < inp.c; i++){
        char *buffer = NULL;
        nread = getline(&buffer, &len, fp);
        // This is making the strings longer than then should be.
        // Maybe check this later if running into errors
        var = num_c(buffer);
        clients[i] = malloc(sizeof(char) * var);
        clients[i] = buffer;
    }

    // Done with files so close it
    fclose(fp);

    // Pass all values you retrieved to the input_data variable this function was called with
    input->nAccounts = inp.a;
    input->nClients = inp.c;
    input->bankAccounts = bankAccounts;
    input->clients = clients;

    return 0;
}
