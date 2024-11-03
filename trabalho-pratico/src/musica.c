#include "musica.h"
#include <stdlib.h>
#include "catalogo_musica.h"

typedef struct musica
{
    char *id;
    char *title;
    char **id_musica;
    char *duration;
    char *genre;
    char *year;
    char *lyrics;
} *musica;

musica create_Musica()
{
    musica nova_musica = malloc(sizeof(struct musica));
    nova_musica->id = NULL;
    nova_musica->title = NULL;
    nova_musica->id_musica = NULL;
    nova_musica->duration = NULL;
    nova_musica->genre = NULL;
    nova_musica->year = NULL;
    nova_musica->lyrics = NULL;

    return nova_musica;
}

void build_musica(char **linha, Catalogo_Musicas catalogo)
{

    musica m = create_Musica();

    setId(linha[0], m);
    setId_musica(linha[1], m);
    setTitle(linha[2], m);
    setDuration(linha[3], m);
    setGenre(linha[4], m);
    setYear(linha[5], m);
    setLyrics(linha[6], m);

    if (verifica_musicas(linha))
    {
        add_musica_valida(catalogo, m);
    }
    else
    {
        add_musica_invalida(catalogo, m);
    }
}

char *getId(musica m)
{
    char mCopy = strdup(m->id);
    return mCopy;
}

char *getTitle(musica m)
{
    char mCopy = strdup(m->title);
    return mCopy;
}

char *getDuration(musica m)
{
    char mCopy = strdup(m->duration);
    return mCopy;
}

char *getGenre(musica m)
{
    char mCopy = strdup(m->genre);
    return mCopy;
}

char *getYear(musica m)
{
    char mCopy = strdup(m->year);
    return mCopy;
}

char *getLyrics(musica m)
{
    char mCopy = strdup(m->lyrics);
    return mCopy;
}

char **getId_Musica(musica m)
{
    char **aCopy = g_strdupv(m->id_musica);
    return aCopy;
}

void setId(char *id, musica m)
{
    char *copy = strdup(id);
    m->id = copy;
}

void setTitle(char *title, musica m)
{
    char *copy = strdup(title);
    m->id = copy;
}

void setId_Artist(char **id_musica, musica m)
{
    char **copy = g_strdupv(id_musica);
    m->id_musica = copy;
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

void setLyrics(char *lyrics, musica m)
{
    char *copy = strdup(lyrics);
    m->lyrics = copy;
}

void free_musica(musica m)
{
    free(m->id);
    free(m->title);
    free(m->id_musica);
    free(m->duration);
    free(m->genre);
    free(m->year);
    free(m->lyrics);
    free(m);
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
    return 1;
}