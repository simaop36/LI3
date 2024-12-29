#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "album.h"
#include "utils.h"

typedef struct album
{
    int id;
    char *title_album;
    char **artists_id;
    int year;
    char **producers;
} *Album;

Album create_Album()
{
    Album novo_album = malloc(sizeof(struct album));
    novo_album->title_album = NULL;
    novo_album->artists_id = NULL;
    novo_album->producers = NULL;

    return novo_album;
}

int getIdAlbum_int(Album a)
{
    return a->id;
}

char *getIdAlbum_string(Album a)
{
    char *result = malloc(9);
    snprintf(result, 9, "AL%06d", a->id);
    return result;
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
    int num;
    if(sscanf(copy,"AL%d",&num) ==1){
        a->id = num;
    }
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
    free_lista_strings(a->producers);
    free(a->title_album);
    free(a);
}
