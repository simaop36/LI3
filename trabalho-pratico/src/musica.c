#include "musica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "joint.h"
#include "catalogo_musica.h"
#include "catalogo_artista.h"
#include "utils.h"
#include "artistas.h"

typedef struct musica
{
    gpointer id;
    char *title;
    gpointer *id_artista;
    gpointer album_id;
    char *duration;
    char *genre;
    char *year;
} *musica;

musica create_Musica()
{
    musica nova_musica = malloc(sizeof(struct musica));
    nova_musica->id = NULL;
    nova_musica->title = NULL;
    nova_musica->id_artista = NULL;
    nova_musica->album_id = NULL;
    nova_musica->duration = NULL;
    nova_musica->genre = NULL;
    nova_musica->year = NULL;


    return nova_musica;
}

int verifica_musicas(char **linha)
{
    // verifica se linha[x]==NULL
    if (!(linha[0]))
        return 0;
    if (!(linha[1]))
        return 0;
    if (!(linha[2]))
        return 0;
    if (!(linha[3]))
        return 0;
    if (!(linha[4]))
        return 0;
    if (!(linha[5]))
        return 0;
    if (!(linha[6]))
        return 0;
    if (!(linha[7]))
        return 0;

    if (!(valida_duracao(linha[4])))
        return 0;

    return 1;
}

gpointer getId_Musica_gpointer(musica m)
{
    return m->id;
}

int getId_Musica_int(musica m)
{
    int num = GPOINTER_TO_INT(m->id);
    return num;
}

char *getId_Musica_string(musica m)
{
    char *result = malloc(9);
    snprintf(result, 9, "S%07d", getId_Musica_int(m));
    return result;
}

char *getTitle(musica m)
{
    char *mCopy = strdup(m->title);
    return mCopy;
}

char *getDuration(musica m)
{
    char *mCopy = strdup(m->duration);
    return mCopy;
}

char *getGenre(musica m)
{
    char *mCopy = strdup(m->genre);
    return mCopy;
}

char *getYear(musica m)
{
    char *mCopy = strdup(m->year);
    return mCopy;
}


gpointer *getId_Artistas_gpointer(musica m)
{
    return m->id_artista;
}

gpointer getAlbum_id_gpointer(musica m)
{
    return m->album_id;
}

int getAlbum_id_int(musica m)
{
    int num = gpointer_int(m->album_id);
    return num;
}

char *getAlbum_id_string(musica m)
{
    char *result = malloc(9);
    snprintf(result, 9, "AL%06d", getAlbum_id_int(m->album_id));
    return result;
}

void setId_Musica(char *id, musica m)
{
    int num;
    if(sscanf(id,"S%d",&num) == 1){
        gpointer p = int_gpointer(num);
        m->id= p;
    } else {
        return;
    }
}

void setTitle(char *title, musica m)
{
    char *copy = strdup(title);
    m->title = copy;
}

void setId_Artistas(char *id_musica, musica m)
{
    char *copy = strdup(id_musica);
    char **result = parse_lista(copy); // NULL terminated
    free(copy);
    int size = 1; // +1 para dar espaço ao NULL final
    for(int i = 0;result[i] != NULL;i++) size++;

    m->id_artista = malloc(size*sizeof(gpointer));

    for(int j = 0; result[j] != NULL; j++)
    {
        int num;
        if (sscanf(result[j], "A%d", &num) != 1) {
            return;
        }
        m->id_artista[j] = int_gpointer(num);
        free(result[j]);
    }
    m->id_artista[size - 1] = NULL;
    free(result);

}
void setDuration(char *duration, musica m)
{
    char *copy = strdup(duration);
    m->duration = copy;
}

void setGenre(char *genre, musica m)
{
    char *copy = strdup(genre);
    m->genre = copy;
}

void setYear(char *year, musica m)
{
    char *copy = strdup(year);
    m->year = copy;
}


void setAlbum_id(char *album_id, musica m)
{
    int num;
    if(sscanf(album_id,"AL%d",&num) == 1){
        gpointer p = int_gpointer(num);
        m->album_id= p;
    } else {
        return;
    }

}


void free_musica(musica m)
{
    free(m->title);
    free(m->id_artista);
    free(m->duration);
    free(m->genre);
    free(m->year);
    free(m);
}

