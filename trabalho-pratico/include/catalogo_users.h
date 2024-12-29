#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H

#include "users.h"
#include <glib.h>

typedef struct catalogo_utilizadores *catalogo_utilizadores;
typedef struct utilizador *utilizador;

catalogo_utilizadores create_catalogo_utilizadores();

void build_utilizador(char **linha,void *cat);

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u);

void add_utilizador_invalido(catalogo_utilizadores catalogo, utilizador u);

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, char *id);

utilizador get_utilizador_invalido(catalogo_utilizadores catalogo, char *id);

GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores);

GHashTable *getUtilizadoresInvalidos(catalogo_utilizadores utilzadores);

void free_catalogo_users_invalidos(catalogo_utilizadores catalogo);

void free_catalogo_users_validos(catalogo_utilizadores catalogo);

void free_catalogo_utilizadores(catalogo_utilizadores catalogo);

void aux_escreve_user(gpointer key, gpointer value, gpointer user_data);

void escreve_users(const char *dir_path, catalogo_utilizadores catalogo);

#endif