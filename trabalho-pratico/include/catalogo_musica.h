#ifndef Catalogo_MusicasS_H
#define Catalogo_MusicasS_H

#include "musica.h"
#include <glib.h>

typedef struct Catalogo_Musicas *Catalogo_Musicas;
typedef struct musica *musica;

Catalogo_Musicas create_Catalogo_Musicas();
void build_musica(char **linha, void *cat);
void add_musica_valida(Catalogo_Musicas catalogo, musica musica);
void add_musica_invalida(Catalogo_Musicas catalogo, musica musica);
musica get_musica_valida(Catalogo_Musicas catalogo, char *id);
musica get_musica_invalida(Catalogo_Musicas catalogo, char *id);
GHashTable *getMusicasValidas(Catalogo_Musicas musicas);
GHashTable *getMusicasInvalidas(Catalogo_Musicas musicas);
void free_catalogo_musicas_invalidos(Catalogo_Musicas catalogo);
void free_catalogo_musicas_validos(Catalogo_Musicas catalogo);
void free_Catalogo_Musicas(Catalogo_Musicas catalogo);
void aux_escreve_musica(gpointer key, gpointer value, gpointer user_data);
void escreve_musicas(const char *dir_path, Catalogo_Musicas catalogo);

#endif