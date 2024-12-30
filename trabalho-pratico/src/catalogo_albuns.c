#include <glib.h>
#include <stdio.h>

#include "album.h"
#include "catalogo_albuns.h"

typedef struct catalogo_albuns
{
    GHashTable *albuns_validos;
} *Catalogo_Albuns;

Catalogo_Albuns create_catalogo_albuns()
{
    Catalogo_Albuns catalogo = malloc(sizeof(struct catalogo_albuns));
    catalogo->albuns_validos = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_album);
    return catalogo;
}

int aux_id_album(char *id)
{
    int num;
    sscanf(id,"AL%d",&num);
    return num;
}

void build_Album(char **linha,void *cat){

    Album album = create_Album();
    Catalogo_Albuns catalogo = (Catalogo_Albuns)cat;
    int aux = aux_id_album(linha[0]);
    
    setId_Album(aux, album );
    setTitle_album(linha[1], album);
    setArtists_id(linha[2], album);
    setYear_album(atoi(linha[3]), album);
    setProducers(linha[4], album);


    add_album(catalogo,album);
}

void add_album(Catalogo_Albuns catalogo, Album album)
{
    g_hash_table_insert(catalogo->albuns_validos, getIdAlbum_gpointer(album), album);
}

Album get_album_valido(Catalogo_Albuns catalogo, gpointer id)
{
    return (Album)g_hash_table_lookup(catalogo->albuns_validos, id);
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
