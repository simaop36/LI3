#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "musica.h"
#include "catalogo_musica.h"
#include "joint.h"
#include "utils.h"

typedef struct Catalogo_Musicas
{
    GHashTable *musicas_validas;
    GHashTable *musicas_invalidas;
} *Catalogo_Musicas;

Catalogo_Musicas create_Catalogo_Musicas()
{
    Catalogo_Musicas catalogo = malloc(sizeof(struct Catalogo_Musicas));
    catalogo->musicas_validas = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_musica);
    catalogo->musicas_invalidas = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_musica);

    return catalogo;
}

void build_musica(char **linha, void *cat)
{

    musica m = create_Musica();
    Joint joint = (Joint)cat;
    Catalogo_Musicas catalogo = get_catalogo_musicas(joint);

    setId_Musica(linha[0], m);
    setTitle(linha[1], m);
    setId_Artistas(linha[2], m);
    setAlbum_id(linha[3],m);
    setDuration(linha[4], m);
    setGenre(linha[5], m);
    setYear(linha[6], m);
    setLyrics(linha[7], m);

    if (!(verifica_musicas(linha)))
    {
        add_musica_invalida(catalogo, m);
    }
    else
    {
        if (segVerMusica(m, joint))
        {
            add_musica_valida(catalogo, m);
        }
        else
        {
            add_musica_invalida(catalogo, m);
        }
    }
}

void add_musica_valida(Catalogo_Musicas catalogo, musica musica)
{
    char *key = getId_Musica(musica);
    g_hash_table_insert(catalogo->musicas_validas, key, musica);
}

void add_musica_invalida(Catalogo_Musicas catalogo, musica musica)
{
    char *key = getId_Musica(musica);
    g_hash_table_insert(catalogo->musicas_invalidas, key, musica);
}

musica get_musica_valida(Catalogo_Musicas catalogo, char *id)
{
    return (musica)g_hash_table_lookup(catalogo->musicas_validas, id);
}

musica get_musica_invalida(Catalogo_Musicas catalogo, char *id)
{
    return (musica)g_hash_table_lookup(catalogo->musicas_invalidas, id);
}

GHashTable *getMusicasValidas(Catalogo_Musicas musicas)
{
    return musicas->musicas_validas;
}

GHashTable *getMusicasInvalidas(Catalogo_Musicas musicas)
{
    return musicas->musicas_invalidas;
}

void free_catalogo_musicas_invalidos(Catalogo_Musicas catalogo)
{
    g_hash_table_destroy(catalogo->musicas_invalidas);
}

void free_catalogo_musicas_validos(Catalogo_Musicas catalogo)
{
    g_hash_table_destroy(catalogo->musicas_validas);
}

void free_Catalogo_Musicas(Catalogo_Musicas catalogo)
{
    if (catalogo->musicas_validas)
    {
        g_hash_table_unref(catalogo->musicas_validas);
    }
    if (catalogo->musicas_invalidas)
    {
        g_hash_table_unref(catalogo->musicas_invalidas);
    }
    free(catalogo);
}


void aux_escreve_musica(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    musica m = (musica)value;

    char *id = getId_Musica(m);
    char *title = getTitle(m);
    char *artists = escreve_lista(getId_Artistas(m), 2);
    char *duration = getDuration(m);
    char *genre = getGenre(m);
    char *year = getYear(m);
    char *lyrics = getLyrics(m);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            id,
            title,
            artists,
            duration,
            genre,
            year,
            lyrics);

    free(id);
    free(title);
    free(artists);
    free(duration);
    free(genre);
    free(year);
    free(lyrics);
}

void escreve_musicas(const char *dir_path, Catalogo_Musicas catalogo)
{
    const char *file_Name = "/musics_errors.csv";
    const char *header = "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"";

    char *musics_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(musics_errors, dir_path);
    strcat(musics_errors, file_Name);

    GHashTable *musicas_invalidas = getMusicasInvalidas(catalogo);
    if (g_hash_table_size(musicas_invalidas) == 0)
    {
        free(musics_errors);
        return;
    }

    FILE *file_musics = fopen(musics_errors, "w");
    free(musics_errors);
    if (file_musics == NULL)
    {
        perror("Erro ao abrir ficheiro musics_errors.csv");
        return;
    }

    fprintf(file_musics, "%s\n", header);

    g_hash_table_foreach(musicas_invalidas, aux_escreve_musica, file_musics);

    fclose(file_musics);
}