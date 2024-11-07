#ifndef MUSICAS_H
#define MUSICAS_H

#include "catalogo_musica.h"
#include "catalogo_artista.h"

typedef struct musica *musica;
musica create_Musica();
void build_musica(char **linha, void *cat);
char *getId_Musica(musica m);
char *getTitle(musica m);
char *getDuration(musica m);
char *getGenre(musica m);
char *getYear(musica m);
char *getLyrics(musica m);
char **getId_Artistas(musica m);
void setId_Musica(char *id, musica m);
void setTitle(char *title, musica m);
void setId_Artistas(char *id_musica, musica m);
void setDuration(char *duration, musica m);
void setGenre(char *genre, musica m);
void setYear(char *year, musica m);
void setLyrics(char *lyrics, musica m);
//int valida_artistasDamusica(musica u, Catalogo_Artistas a);
void free_musica(musica m);
int verifica_musicas(char **linha);

#endif