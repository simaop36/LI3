#ifndef Catalogo_MusicasS_H
#define Catalogo_MusicasS_H

#include "musica.h"

typedef struct Catalogo_Musicas *Catalogo_Musicas;

Catalogo_Musicas create_Catalogo_Musicas();
void add_musica_valida(Catalogo_Musicas catalogo, musica musica);
void add_musica_invalida(Catalogo_Musicas catalogo, musica musica);
musica get_musica_valida(Catalogo_Musicas catalogo, char *id);
musica get_musica_invalida(Catalogo_Musicas catalogo, char *id);
void free_Catalogo_Musicas(Catalogo_Musicas catalogo);

#endif