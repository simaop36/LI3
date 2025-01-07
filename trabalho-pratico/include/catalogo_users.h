#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H

#include "users.h"
#include "estatisticas.h"
#include <glib.h>

typedef struct catalogo_utilizadores *catalogo_utilizadores;
typedef struct utilizador *utilizador;

catalogo_utilizadores create_catalogo_utilizadores();

void build_utilizador(char **linha, void *cat, Stats stats);

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u);

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, gpointer username);

// GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores);

GPtrArray *get_keys_users(catalogo_utilizadores catalogo);

void build_keys_users(catalogo_utilizadores catalogo);

void free_catalogo_utilizadores(catalogo_utilizadores catalogo);

void escreve_user(const char *dir_path, char **linha);

#endif