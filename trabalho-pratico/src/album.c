#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "album.h"

typedef struct album
{
    char *id;
    char *title;
    char **artists_id;
    int year;
    char **producers;
} *Album;

Album create_Album()
{
    Album novo_album = malloc(sizeof(struct album));
    novo_album->id = NULL;
    novo_album->title = NULL;
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
    char *aCopy = strdup(a->title);
    return aCopy;
}
