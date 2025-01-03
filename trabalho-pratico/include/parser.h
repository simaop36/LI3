#ifndef PARSER_H
#define PARSER_H

#include "joint.h"
#include "estatisticas.h"

typedef void (*build_function)(char**,void*, struct estatisticas *);

#define MAX_ARTISTA_TOKENS 7
#define MAX_MUSIC_TOKENS 8
#define MAX_USERS_TOKENS 8
#define MAX_ALBUM_TOKENS 5
#define MAX_HISTORICO_TOKENS 6


void file_parser(FILE *csv, void *cat, build_function builder, int max_tokens, Stats stats);
char **parser_linha(char *line, int max_tokens);
char *parse_queries(FILE *queries_file, Joint joint,Stats s);

#endif