#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "types.h"

void deposit(int * accounts, int acc, int amount);
void widthdraw(int * accounts, int acc, int amount);
void transfer(int * accounts, int a1, int a2, int amount);

#endif