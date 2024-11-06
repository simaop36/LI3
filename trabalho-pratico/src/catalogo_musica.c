#include <glib.h>
#include "musica.h"
#include "catalogo_musica.h"

typedef struct Catalogo_Musicas
{
    GHashTable *musicas_validas;
    GHashTable *musicas_invalidas;
} *Catalogo_Musicas;

Catalogo_Musicas create_Catalogo_Musicas()
{
    Catalogo_Musicas catalogo = malloc(sizeof(struct Catalogo_Musicas));
    catalogo->musicas_validas = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_musica);
    catalogo->musicas_invalidas = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_musica);

    return catalogo;
}

void add_musica_valida(Catalogo_Musicas catalogo, musica musica)
{
    char *key = getId_Musica(musica);
    g_hash_table_insert(catalogo->musicas_validas, key, musica);
}

void add_musica_invalida(Catalogo_Musicas catalogo, musica musica)
{
    char *key = getId_Musica(musica);
    g_hash_table_insert(catalogo->musicas_invalidas, key, musica);
}

musica get_musica_valida(Catalogo_Musicas catalogo, char *id)
{
    return (musica)g_hash_table_lookup(catalogo->musicas_validas, id);
}

musica get_musica_invalida(Catalogo_Musicas catalogo, char *id)
{
    return (musica)g_hash_table_lookup(catalogo->musicas_invalidas, id);
}

GHashTable *getMusicasValidas(Catalogo_Musicas musicas)
{
    return musicas->musicas_validas;
}

GHashTable *getMusicasInvalidas(Catalogo_Musicas musicas)
{
    return musicas->musicas_invalidas;
}

void free_Catalogo_Musicas(Catalogo_Musicas catalogo)
{
    g_hash_table_destroy(catalogo->musicas_validas);
    g_hash_table_destroy(catalogo->musicas_invalidas);
    free(catalogo);
}