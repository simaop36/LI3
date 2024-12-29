#include <glib.h>

#include "album.h"
#include "catalogo_albuns.h"

typedef struct catalogo_albuns
{
    GHashTable *albuns_validos;
} *Catalogo_Albuns;

Catalogo_Albuns create_catalogo_albuns()
{
    Catalogo_Albuns catalogo = malloc(sizeof(struct catalogo_albuns));
    catalogo->albuns_validos = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)free_album);
    return catalogo;
}

void build_Album(char **linha,void *cat){

    Album album = create_Album();
    Catalogo_Albuns catalogo = (Catalogo_Albuns)cat;
    
    setId_Album(linha[0], album );
    setTitle_album(linha[1], album);
    setArtists_id(linha[2], album);
    setYear_album(atoi(linha[3]), album);
    setProducers(linha[4], album);

    add_album(catalogo,album);
}

void add_album(Catalogo_Albuns catalogo, Album album)
{
    int *key = malloc(sizeof(int));
    *key = getIdAlbum_int(album);
    g_hash_table_insert(catalogo->albuns_validos, key, album);
}

Album get_album_valido(Catalogo_Albuns catalogo, int id)
{
    return (Album)g_hash_table_lookup(catalogo->albuns_validos, &id);
}

GHashTable *getAlbunsValidos(Catalogo_Albuns albuns)
{
    return albuns->albuns_validos;
}

void free_catalogo_albuns(Catalogo_Albuns catalogo){
    if (catalogo->albuns_validos) {
        g_hash_table_unref(catalogo->albuns_validos);
    }
    free(catalogo);
}
