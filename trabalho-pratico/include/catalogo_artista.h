#ifndef CATALOGO_ARTISTAS_H
#define CATALOGO_ARTISTAS_H

#include "artistas.h"
#include <glib.h>

typedef struct catalogo_artistas *Catalogo_Artistas;
typedef struct artista *Artista;

Catalogo_Artistas create_catalogo_artistas();
void build_Artista(char **linha,void *cat);
void add_artista_valido(Catalogo_Artistas catalogo, Artista artista);
void add_artista_invalido(Catalogo_Artistas catalogo, Artista artista);
Artista get_artista_valido(Catalogo_Artistas catalogo, char *id);
Artista get_artista_invalido(Catalogo_Artistas catalogo, char *id);
GHashTable *getArtistasValidos(Catalogo_Artistas artistas);
GHashTable *getArtistasInvalidos(Catalogo_Artistas artistas);
void free_catalogo_artistas_invalidos(Catalogo_Artistas catalogo);
void free_catalogo_artistas_validos(Catalogo_Artistas catalogo);
void free_catalogo_artistas(Catalogo_Artistas catalogo);
void aux_escreve_artista(gpointer key, gpointer value, gpointer user_data);
void escreve_artistas(const char *dir_path, Catalogo_Artistas catalogo_artistas);


#endif