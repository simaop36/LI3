#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "album.h"
#include "utils.h"

typedef struct album
{
    char *id;
    char *title_album;
    char **artists_id;
    int year;
    char **producers;
} *Album;

Album create_Album()
{
    Album novo_album = malloc(sizeof(struct album));
    novo_album->id = NULL;
    novo_album->title_album = NULL;
    novo_album->artists_id = NULL;
    novo_album->producers = NULL;

    return novo_album;
}

char *getIdAlbum(Album a)
{
    char *aCopy = strdup(a->id);
    return aCopy;
}
char *getTitleAlbum(Album a)
{
    char *aCopy = strdup(a->title_album);
    return aCopy;
}

char **getArtists_id(Album a)
{
    char **aCopy = g_strdupv(a->artists_id);
    return aCopy;
}

int getYear_album(Album a)
{
    return a->year;
}

char **getProducers(Album a)
{
    char **aCopy = g_strdupv(a->producers);
    return aCopy;
}

void setArtists_id(char *artists_id, Album a)
{
    char *copy = strdup(artists_id);
    char **result = parse_lista(copy);
    free(copy);
    a->artists_id = result;
}
void setId_Album(char *id, Album a)
{
    char *copy = strdup(id);
    a->id = copy;
}

void setProducers(char *producers, Album a)
{
    char *copy = strdup(producers);
    char **result = parse_lista(copy);
    free(copy);
    a->producers = result;
}
void setTitle_album(char *title, Album a)
{
    char *copy = strdup(title);
    a->title_album = copy;
}
void setYear_album(int year, Album a)
{
    a->year = year;
}

void free_album(Album a)
{
    free_lista_strings(a->artists_id);
    free(a->id);
    free_lista_strings(a->producers);
    free(a->title_album);
    free(a);
}
