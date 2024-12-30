#ifndef Catalogo_MusicasS_H
#define Catalogo_MusicasS_H

#include "musica.h"
#include <glib.h>

typedef struct Catalogo_Musicas *Catalogo_Musicas;
typedef struct musica *musica;

Catalogo_Musicas create_Catalogo_Musicas();
void build_musica(char **linha, void *cat);
void add_musica_valida(Catalogo_Musicas catalogo, musica musica);
musica get_musica_valida(Catalogo_Musicas catalogo, gpointer id);
GHashTable *getMusicasValidas(Catalogo_Musicas musicas);
void free_Catalogo_Musicas(Catalogo_Musicas catalogo);
void escreve_musica(const char *dir_path, char **linha);

#endif