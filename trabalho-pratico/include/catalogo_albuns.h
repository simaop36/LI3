#ifndef CATALOGO_ALBUNS_H
#define CATALOGO_ALBUNS_H

#include <glib.h>
#include "album.h"

typedef struct catalogo_albuns *Catalogo_Albuns;
typedef struct album *Album;

Catalogo_Albuns create_catalogo_albuns();
void build_Album(char **linha,void *cat);
void add_album(Catalogo_Albuns catalogo, Album album);
Album get_album_valido(Catalogo_Albuns catalogo, int id);
GHashTable *getAlbunsValidos(Catalogo_Albuns albuns);
void free_catalogo_albuns(Catalogo_Albuns catalogo);

#endif