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
} *Catalogo_Musicas;

Catalogo_Musicas create_Catalogo_Musicas()
{
    Catalogo_Musicas catalogo = malloc(sizeof(struct Catalogo_Musicas));
    catalogo->musicas_validas = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_musica);

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
    //linha[7] lyrics


    if (!(verifica_musicas(linha)))
    {
        
        free_musica(m);
        escreve_musica("./resultados",linha);
    }
    else
    {
        if (segVerMusica(m, joint))
        {   
            
            add_musica_valida(catalogo, m);
        }
        else
        {
            free_musica(m);
            escreve_musica("./resultados",linha);
        }
    }
}

void add_musica_valida(Catalogo_Musicas catalogo, musica musica)
{
    g_hash_table_insert(catalogo->musicas_validas, getId_Musica_gpointer(musica), musica);
}


musica get_musica_valida(Catalogo_Musicas catalogo, gpointer id)
{
    return (musica)g_hash_table_lookup(catalogo->musicas_validas, id);
}


GHashTable *getMusicasValidas(Catalogo_Musicas musicas)
{
    return musicas->musicas_validas;
}


void free_Catalogo_Musicas(Catalogo_Musicas catalogo)
{
    if (catalogo->musicas_validas)
    {
        g_hash_table_unref(catalogo->musicas_validas);
    }
    free(catalogo);
}

void escreve_musica(const char *dir_path, char **linha)
{
    const char *file_Name = "/musics_errors.csv";
    const char *header = "\"id\";\"title\";\"artist_id\";\"album_id\";\"duration\";\"genre\";\"year\";\"lyrics\"";

    char *musics_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(musics_errors, dir_path);
    strcat(musics_errors, file_Name);

    FILE *file_musics = fopen(musics_errors, "a");
    free(musics_errors);
    if (file_musics == NULL)
    {
        perror("Erro ao abrir ficheiro musics_errors.csv");
        return;
    }
    
    fseek(file_musics, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    long size = ftell(file_musics); // Obtém a posição atual do ponteiro (tamanho do arquivo)
    if (size == 0){
        fprintf(file_musics, "%s\n", header);
    }

    fprintf(file_musics, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            linha[0],
            linha[1],
            linha[2],
            linha[3],
            linha[4],
            linha[5],
            linha[6],
            linha[7]);


    fclose(file_musics);


}
