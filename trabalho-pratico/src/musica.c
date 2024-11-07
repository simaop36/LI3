#include "musica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "catalogo_musica.h"
#include "catalogo_artista.h"
#include "utils.h"
#include "artistas.h"

typedef struct musica
{
    char *id;
    char *title;
    char **id_artista;
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
    nova_musica->id_artista = NULL;
    nova_musica->duration = NULL;
    nova_musica->genre = NULL;
    nova_musica->year = NULL;
    nova_musica->lyrics = NULL;

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
    

    if (!(valida_duracao(linha[3])))
        return 0;

    return 1;
}

void build_musica(char **linha, void *cat)
{

    musica m = create_Musica();
    Catalogo_Musicas catalogo = (Catalogo_Musicas)cat;

    setId_Musica(linha[0], m);
    setTitle(linha[1], m);
    setId_Artistas(linha[2], m);
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

char *getId_Musica(musica m)
{
    char *mCopy = strdup(m->id);
    return mCopy;
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

char *getLyrics(musica m)
{
    char *mCopy = strdup(m->lyrics);
    return mCopy;
}

char **getId_Artistas(musica m)
{
    char **aCopy = g_strdupv(m->id_artista);
    return aCopy;
}

void setId_Musica(char *id, musica m)
{
    char *copy = strdup(id);
    m->id = copy;
}

void setTitle(char *title, musica m)
{
    char *copy = strdup(title);
    m->title = copy ;
}

void setId_Artistas(char *id_musica, musica m)
{
    char *copy = strdup(id_musica);
    char **result = parse_lista(copy);
    m->id_artista = result;
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

int valida_artistasDamusica(musica m, Catalogo_Artistas a)
{
    int i = 0;
    while (getId_Artistas(m) + i != NULL)
    {
        if (!(g_hash_table_contains(getArtistasValidos(a), getId_Artistas(m) + i)))
            return 0;
        i++;
    }
    return 1;
}

void free_musica(musica m)
{
    free(m->id);
    free(m->title);
    free(m->id_artista);
    free(m->duration);
    free(m->genre);
    free(m->year);
    free(m->lyrics);
    free(m);
}

