#include <glib.h>

#include "users.h"
#include "catalogo_users.h"

typedef struct catalogo_utilizadores
{
    GHashTable *utilizadores_validos;
    GHashTable *utilizadores_invalidos;
} *catalogo_utilizadores;

catalogo_utilizadores create_catalogo_utilizadores()
{
    catalogo_utilizadores catalogo = malloc(sizeof(struct catalogo_utilizadores));
    catalogo->utilizadores_validos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_utilizador);
    catalogo->utilizadores_invalidos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_utilizador);

    return catalogo;
}

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u)
{
    char *key = get_username(u);
    g_hash_table_insert(catalogo->utilizadores_validos, key, u);
}
void add_utilizador_invalido(catalogo_utilizadores catalogo, utilizador u)
{
    char *key = get_username(u);
    g_hash_table_insert(catalogo->utilizadores_invalidos, key, u);
}

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, char *username)
{
    return (utilizador)g_hash_table_lookup(catalogo->utilizadores_validos, username);
}

utilizador get_utilizador_invalido(catalogo_utilizadores catalogo, char *username)
{
    return (utilizador)g_hash_table_lookup(catalogo->utilizadores_invalidos, username);
}

GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores)
{
    return utilzadores->utilizadores_validos;
}

GHashTable *getUtilizadoresInvalidos(catalogo_utilizadores utilzadores)
{
    return utilzadores->utilizadores_invalidos;
}

void free_catalogo_users_invalidos(catalogo_utilizadores catalogo){
    g_hash_table_destroy(catalogo->utilizadores_invalidos);
}

void free_catalogo_users_validos(catalogo_utilizadores catalogo){
    g_hash_table_destroy(catalogo->utilizadores_validos);
}

void free_catalogo_utilizadores(catalogo_utilizadores catalogo)
{
    if (catalogo->utilizadores_validos) {
        g_hash_table_destroy(catalogo->utilizadores_validos);
    }
    if (catalogo->utilizadores_invalidos) {
        g_hash_table_destroy(catalogo->utilizadores_invalidos);
    }
    free(catalogo);
}