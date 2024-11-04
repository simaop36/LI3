#ifndef INPUT_H
#define INPUT_H

void *file_reader(FILE *csv, char *file_name, void *catalogo);
char **parse_linha(char *line, int max_tokens);

#endif