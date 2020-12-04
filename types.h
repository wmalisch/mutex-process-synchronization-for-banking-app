#ifndef TYPES_H
#define TYPES_H

typedef struct input_data
{
    int nAccounts;
    int nClients;
    int * bankAccounts;
    char ** clients;

} input_data;

typedef struct counts
{
    int a;
    int c;
} counts;

#endif