#ifndef MUSICAS_H
#define MUSICAS_H

typedef struct musica *musica;
musica create_Musica();
void build_musica(char **linha, Catalogo_Musicas catalogo);
char *getId(musica m);
char *getTitle(musica m);
char *getDuration(musica m);
char *getGenre(musica m);
char *getYear(musica m);
char *getLyrics(musica m);
char **getId_Musica(musica m);
void setId(char *id, musica m);
void setTitle(char *title, musica m);
void setId_Artist(char **id_musica, musica m);
void setDuration(char *duration, musica m);
void setGenre(char *genre, musica m);
void setYear(char *year, musica m);
void setLyrics(char *lyrics, musica m);
void free_musica(musica m);
int verifica_musicas(char **linha);

#endif