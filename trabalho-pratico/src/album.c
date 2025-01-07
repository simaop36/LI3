#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "album.h"
#include "utils.h"

typedef struct album
{
    gpointer id;
    char *title_album;
    gpointer *artists_id;
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

gpointer getIdAlbum_gpointer(Album a)
{
    return a->id;
}

int getIdAlbum_int(Album a)
{
    int num = GPOINTER_TO_INT(a->id);
    return num;
}

char *getIdAlbum_string(Album a)
{
    char *result = malloc(9);
    snprintf(result, 9, "AL%06d", getIdAlbum_int(a));
    return result;
}
char *getTitleAlbum(Album a)
{
    char *aCopy = strdup(a->title_album);
    return aCopy;
}

gpointer *getArtists_id(Album a)
{
    return a->artists_id;
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
    char **result = parse_lista(copy); // NULL terminated
    free(copy);
    int size = 1; // +1 para dar espaço ao NULL final
    for(int i = 0;result[i] != NULL;i++) size++;

    a->artists_id = malloc(size*sizeof(gpointer));

    for(int j = 0; result[j] != NULL; j++)
    {
        int num;
        if (sscanf(result[j], "A%d", &num) != 1) {
            return;
        }
        a->artists_id[j] = int_gpointer(num);
        free(result[j]);
    }
    a->artists_id[size - 1] = NULL;
    free(result);
}
void setId_Album(int num, Album a)
{
    gpointer p = GINT_TO_POINTER(num);
    a->id = p;
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
    free(a->artists_id);
    free_lista_strings(a->producers);
    free(a->title_album);
    free(a);
}





