#ifndef IO_H
#define IO_H

#include "types.h"

counts num_accounts_clients(FILE *fp, counts * inp);
int read_input_file(char *filename, input_data *input);
int num_c(char *line);

#endif