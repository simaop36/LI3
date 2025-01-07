#ifndef CATALOGO_ARTISTAS_H
#define CATALOGO_ARTISTAS_H

#include "artistas.h"
#include "estatisticas.h"
#include <glib.h>

typedef struct catalogo_artistas *Catalogo_Artistas;
typedef struct artista *Artista;

Catalogo_Artistas create_catalogo_artistas();
void build_Artista(char **linha, void *cat, Stats stats);
void add_artista_valido(Catalogo_Artistas catalogo, Artista artista);
GPtrArray *get_keys_artistas(Catalogo_Artistas catalogo);
void build_keys_artistas(Catalogo_Artistas catalogo);
Artista get_artista_valido(Catalogo_Artistas catalogo, gpointer id);
void free_catalogo_artistas(Catalogo_Artistas catalogo);
void escreve_artista(const char *dir_path, char **linha);

#endif