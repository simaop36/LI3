#ifndef PARSER_H
#define PARSER_H

#include "joint.h"

void file_reader(FILE *csv,const char *file_name, Joint catalogo);
char **parser_linha(char *line, int max_tokens);
void parse_queries(FILE *queries_file,Joint joint);

#endif