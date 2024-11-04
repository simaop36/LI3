#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H

typedef struct catalogo_utilizadores *catalogo_utilizadores;

catalogo_utilizadores create_catalogo_utilizadores();

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u);

void add_utilizador_invalido(catalogo_utilizadores catalogo, utilizador u);

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, char *id);

utilizador get_utilizador_invalido(catalogo_utilizadores catalogo, char *id);

GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores);

GHashTable *getUtilizadoresInvalidos(catalogo_utilizadores utilzadores);

void free_catalogo_utilizadores(catalogo_utilizadores catalogo);

#endif