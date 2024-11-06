#include <glib.h>

#include "artistas.h"
#include "catalogo_artista.h"

typedef struct catalogo_artistas
{
    GHashTable *artistas_validos;
    GHashTable *artistas_invalidos;
} *Catalogo_Artistas;

Catalogo_Artistas create_catalogo_artistas()
{
    Catalogo_Artistas catalogo = malloc(sizeof(struct catalogo_artistas));
    catalogo->artistas_validos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_artista);
    catalogo->artistas_invalidos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_artista);

    return catalogo;
}

void add_artista_valido(Catalogo_Artistas catalogo, Artista artista)
{

    char *key = getId_Artista(artista);

    g_hash_table_insert(catalogo->artistas_validos, key, artista);
}
void add_artista_invalido(Catalogo_Artistas catalogo, Artista artista)
{

    char *key = getId_Artista(artista);

    g_hash_table_insert(catalogo->artistas_invalidos, key, artista);
}

Artista get_artista_valido(Catalogo_Artistas catalogo, char *id)
{
    return (Artista)g_hash_table_lookup(catalogo->artistas_validos, id);
}

Artista get_artista_invalido(Catalogo_Artistas catalogo, char *id)
{
    return (Artista)g_hash_table_lookup(catalogo->artistas_invalidos, id);
}

GHashTable *getArtistasValidos(Catalogo_Artistas artistas)
{
    return artistas->artistas_validos;
}

GHashTable *getArtistasInvalidos(Catalogo_Artistas artistas)
{
    return artistas->artistas_invalidos;
}

void free_catalogo_artistas(Catalogo_Artistas catalogo)
{
    g_hash_table_destroy(catalogo->artistas_validos);
    g_hash_table_destroy(catalogo->artistas_invalidos);
    free(catalogo);
}
