#ifndef ALBUM_H
#define ALBUM_H


typedef struct album *Album;

#define OFFSET_ALBUM 0

Album create_Album();

gpointer getIdAlbum_gpointer(Album a);
int getIdAlbum_int(Album a);
char *getIdAlbum_string(Album a);
char *getTitleAlbum(Album a);
gpointer *getArtists_id(Album a);
int getYear_album(Album a);
char **getProducers(Album a);
void setArtists_id(char *artists_id, Album a);
void setId_Album(int num, Album a);
void setProducers(char *producers, Album a);
void setTitle_album(char *title, Album a);
void setYear_album(int year, Album a);
void free_album(Album a);

gpointer int_gpointer_album(int i);
int gpointer_int_album(gpointer p);

#endif