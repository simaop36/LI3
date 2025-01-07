#ifndef MUSICAS_H
#define MUSICAS_H

#include "catalogo_musica.h"
#include "catalogo_artista.h"
#include <limits.h>

typedef struct musica *musica;


musica create_Musica();
int verifica_musicas(char **linha);
gpointer getId_Musica_gpointer(musica m);
//int getId_Musica_int(musica m);
char *getId_Musica_string(musica m);

char *getTitle(musica m);
char *getDuration(musica m);
char *getGenre(musica m);
char *getYear(musica m);
gpointer *getId_Artistas_gpointer(musica m);
gpointer getAlbum_id_gpointer(musica m);
int getAlbum_id_int(musica m);
char *getAlbum_id_string(musica m);
void setId_Musica(char *id, musica m);
void setTitle(char *title, musica m);
void setId_Artistas(char *id_musica, musica m);
void setDuration(char *duration, musica m);
void setGenre(char *genre, musica m);
void setYear(char *year, musica m);
void setAlbum_id(char *album_id, musica m);
void free_musica(musica m);



#endif