#include <glib.h>
#include <stdio.h>

#include "album.h"
#include "catalogo_albuns.h"
#include "joint.h"
#include "utils.h"
#include "estatisticas.h"
#include "segVer.h"

typedef struct catalogo_albuns
{
    GHashTable *albuns_validos;
    GPtrArray *keys_albuns;
} *Catalogo_Albuns;

Catalogo_Albuns create_catalogo_albuns()
{
    Catalogo_Albuns catalogo = malloc(sizeof(struct catalogo_albuns));
    catalogo->albuns_validos = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_album);
    catalogo->keys_albuns = NULL;
    return catalogo;
}

int aux_id_album(char *id)
{
    int num;
    sscanf(id, "AL%d", &num);
    return num;
}

void build_Album(char **linha, void *cat, Stats stats)
{

    Album album = create_Album();
    Joint joint = (Joint)cat;
    Catalogo_Albuns catalogo = get_catalogo_albuns(joint);

    int aux = aux_id_album(linha[0]);

    setId_Album(aux, album);
    setTitle_album(linha[1], album);
    setArtists_id(linha[2], album);
    setYear_album(atoi(linha[3]), album);
    setProducers(linha[4], album);

    segVerAlbum(album, joint);
    add_album(catalogo, album);
}

void add_album(Catalogo_Albuns catalogo, Album album)
{
    g_hash_table_insert(catalogo->albuns_validos, getIdAlbum_gpointer(album), album);
}

GPtrArray *get_keys_albuns(Catalogo_Albuns catalogo)
{
    return catalogo->keys_albuns;
}

void build_keys_albuns(Catalogo_Albuns catalogo)
{
    GHashTable *hash_table = catalogo->albuns_validos;

    if (catalogo->keys_albuns != NULL)
    {
        g_ptr_array_free(catalogo->keys_albuns, TRUE);
        catalogo->keys_albuns = NULL;
    }

    GPtrArray *keys = g_ptr_array_new();
    if (keys == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for GPtrArray.\n");
        return;
    }

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_ptr_array_add(keys, key);
    }

    catalogo->keys_albuns = keys;
}

Album get_album_valido(Catalogo_Albuns catalogo, gpointer id)
{
    return (Album)g_hash_table_lookup(catalogo->albuns_validos, id);
}

GHashTable *getAlbunsValidos(Catalogo_Albuns albuns)
{
    return albuns->albuns_validos;
}

void free_catalogo_albuns(Catalogo_Albuns catalogo)
{
    if (catalogo->albuns_validos)
    {
        g_hash_table_unref(catalogo->albuns_validos);
    }
    g_ptr_array_free(catalogo->keys_albuns, TRUE);
    free(catalogo);
}