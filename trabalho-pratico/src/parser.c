#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <errno.h>

#include "parser.h"
#include "artistas.h"
#include "musica.h"
#include "users.h"
#include "joint.h"

char **parser_linha(char *line, int max_tokens) {
    // Aloca memória para o array de tokens
    char **parsed_tokens = malloc(sizeof(char *) * max_tokens);
    if (!parsed_tokens) {
        perror("erro malloc");
        return NULL;  // erro ao alocar memória
    }

    // Encontra a posição do primeiro separador ";"
    char *separator_position = strstr(line, ";");
    char *token = NULL;
    int token_count = 0;

    // Itera enquanto houver separadores e não se atingir o limite de tokens
    while (separator_position != NULL && token_count < max_tokens - 1) {
        *separator_position = '\0';  // Termina o token atual com null

        // Define o ponteiro do token e remove aspas se existirem
        token = line;
        if (*token == '"' && *(token + strlen(token) - 1) == '"') {
            token++;  // Ignora a aspa inicial
            *(token + strlen(token) - 1) = '\0';  // Remove a aspa final
        }

        // Aloca memória e copia o token
        parsed_tokens[token_count] = strdup(token);
        if (!parsed_tokens[token_count]) {
            // Liberta a memória dos tokens previamente alocados em caso de erro
            for (int j = 0; j < token_count; j++) {
                free(parsed_tokens[j]);
            }
            free(parsed_tokens);
            return NULL;
        }

        // Avança para o próximo token
        line = separator_position + 1;
        separator_position = strstr(line, ";");
        token_count++;
    }

    // Processa o último token após o último separador
    token = line;
    if (*token == '"' && *(token + strlen(token) - 1) == '"') {
        token++;
        *(token + strlen(token) - 1) = '\0';
    }

    parsed_tokens[token_count] = strdup(token);
    if (!parsed_tokens[token_count]) {
        // Liberta toda a memória previamente alocada em caso de erro
        for (int j = 0; j <= token_count; j++) {
            free(parsed_tokens[j]);
        }
        free(parsed_tokens);
        return NULL;
    }

    return parsed_tokens;
}



void file_reader(FILE *csv,const char *file_name, Joint catalogo) {
    char *linha = NULL;
    size_t tamanho_linha = 0;
    getline(&linha, &tamanho_linha, csv); // salta a primeira linha
    
    if (strcmp(file_name, "artists.csv") == 0) {
        while (getline(&linha, &tamanho_linha, csv) != -1){
            linha[strlen(linha) - 1] = '\0'; // remove o \n e substitui por \0
            char **tokens = parser_linha(linha,7);
            build_Artista(tokens,get_catalogo_artistas(catalogo));
            free(tokens);
        }
        free(linha);
    }

    if (strcmp(file_name, "musics.csv") == 0) {
        while (getline(&linha, &tamanho_linha, csv) != -1){
            linha[strlen(linha) - 1] = '\0'; // remove o \n e substitui por \0
            char **tokens = parser_linha(linha,7);
            build_musica(tokens,get_catalogo_musicas(catalogo));
            free(tokens);
        }
        free(linha);
    }

    if (strcmp(file_name, "users.csv") == 0){
        while (getline(&linha, &tamanho_linha, csv) != -1){
            linha[strlen(linha) - 1] = '\0'; // remove o \n e substitui por \0
            char **tokens = parser_linha(linha,8);
            build_utilizador(tokens,get_catalogo_utilizadores(catalogo));
            free(tokens);
        }
        free(linha);
    }
}


