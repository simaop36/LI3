#ifndef CATALOGO_ALBUNS_H
#define CATALOGO_ALBUNS_H

#include <glib.h>
#include "album.h"
#include "estatisticas.h"

typedef struct catalogo_albuns *Catalogo_Albuns;
typedef struct album *Album;

Catalogo_Albuns create_catalogo_albuns();
void build_Album(char **linha, void *cat, Stats stats);
void add_album(Catalogo_Albuns catalogo, Album album);
GPtrArray *get_keys_albuns(Catalogo_Albuns catalogo);
void build_keys_albuns(Catalogo_Albuns catalogo);
Album get_album_valido(Catalogo_Albuns catalogo, gpointer id);
// GHashTable *getAlbunsValidos(Catalogo_Albuns albuns);
void free_catalogo_albuns(Catalogo_Albuns catalogo);

#endif