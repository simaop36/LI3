#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "input.h"
#include "artistas.h"
#include "musica.h"
#include "users.h"

void *file_reader(FILE *csv, char *file_name, void *catalogo) {
    char *linha = NULL;
    size_t tamanho_linha = 0;
    getline(&linha, &tamanho_linha, csv); // salta a primeira linha
    
    if (strcmp(file_name, "artists.csv") == 0) {
        while (getline(&linha, &tamanho_linha, csv) != -1){
            linha[strlen(linha) - 1] = '\0'; // remove o \n e substitui por \0
            char **tokens = parser_linha(linha,7);
            build_Artista(tokens,catalogo);
            free(tokens);
        }
        free(linha);
    }

    if (strcmp(file_name, "musics.csv") == 0) {
        while (getline(&linha, &tamanho_linha, csv) != -1){
            linha[strlen(linha) - 1] = '\0'; // remove o \n e substitui por \0
            char **tokens = parser_linha(linha,7);
            build_musica(tokens,catalogo);
            free(tokens);
        }
        free(linha);
    }

    if (strcmp(file_name, "users.csv") == 0){
        while (getline(&linha, &tamanho_linha, csv) != -1){
            linha[strlen(linha) - 1] = '\0'; // remove o \n e substitui por \0
            char **tokens = parser_linha(linha,8);
            build_utilizador(tokens,catalogo);
            free(tokens);
        }
        free(linha);
    }
}

char **parse_linha(char *line, int max_tokens) {
  char **tokens = malloc(sizeof(char *) * max_tokens);
  char *temp = strstr(line, ";");
  char *token = NULL;

  int i = 0;
  while (temp != NULL) {
    token = temp != line ? line : NULL;

    tokens[i] = token;
    line = temp + 1;
    *temp = '\0';
    temp = strstr(line, ";");
    i++;
  }

  token = line;
  tokens[i] = token;

  return tokens;
}
