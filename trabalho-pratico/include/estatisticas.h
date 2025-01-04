#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#define MAX_AGE 60
#define MIN_AGE 17

#include <glib.h>
#include <stdio.h>
#include "historico.h"
// #include "catalogo_users.h"

typedef struct generoContagem *GeneroContagem;

size_t getReproducoes(GeneroContagem gc);
char *getGenero(GeneroContagem gc);
int getLikes(GeneroContagem gc);
void setReproducoes(size_t num, GeneroContagem gc);
void setGenero(char *genero, GeneroContagem gc);
void setLikes(int like, GeneroContagem gc);
GeneroContagem build_genero_contagem(int i, char *g);
void free_genero_contagem(GeneroContagem g);
gint comparar_generosC(GeneroContagem a, GeneroContagem b);
void swap_generos(GArray *arr, guint i, guint j);
GArray *build_Array_GC();
void incrementa_likes_genero(GArray *array, char *genero);
void incrementa_likes_array(GArray *a, GArray *b);
void incrementa_reproducoes_array(GArray *array, char *genero);
void free_Array_GC(GArray *array);

typedef struct estatisticas *Stats;

// typedef struct catalogo_utilizadores *catalogo_utilizadores;

Stats create_estatisticas();
int **getMatriz(Stats s);
char **get_ids_users(Stats s);
char **get_nome_Generos(Stats s);
int get_size_idsUtilizadores(Stats s);
int get_size_nomesGeneros(Stats s);

void build_stats(Stats s, GPtrArray *keys_users, void *cat);

void free_stats(Stats s);

#endif