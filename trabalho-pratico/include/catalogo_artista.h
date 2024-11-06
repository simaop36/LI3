#ifndef CATALOGO_ARTISTAS_H
#define CATALOGO_ARTISTAS_H

#include "artistas.h"
#include <glib.h>

typedef struct catalogo_artistas *Catalogo_Artistas;
typedef struct artista *Artista;

Catalogo_Artistas create_catalogo_artistas();
void add_artista_valido(Catalogo_Artistas catalogo, Artista artista);
void add_artista_invalido(Catalogo_Artistas catalogo, Artista artista);
Artista get_artista_valido(Catalogo_Artistas catalogo, char *id);
Artista get_artista_invalido(Catalogo_Artistas catalogo, char *id);
GHashTable *getArtistasValidos(Catalogo_Artistas artistas);
GHashTable *getArtistasInvalidos(Catalogo_Artistas artistas);
void free_catalogo_artistas(Catalogo_Artistas catalogo);

#endif