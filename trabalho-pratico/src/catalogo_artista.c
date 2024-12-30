#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "artistas.h"
#include "catalogo_artista.h"
#include "utils.h"

typedef struct catalogo_artistas
{
    GHashTable *artistas_validos;
} *Catalogo_Artistas;

Catalogo_Artistas create_catalogo_artistas()
{
    Catalogo_Artistas catalogo = malloc(sizeof(struct catalogo_artistas));
    catalogo->artistas_validos = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_artista);

    return catalogo;
}

void build_Artista(char **linha,void *cat){

    Artista artista = create_Artista();
    Catalogo_Artistas catalogo = (Catalogo_Artistas)cat;
    

    setId_Artista(linha[0],artista);
    setName(linha[1],artista);
    //linha[2] description
    setRecipe_Per_Stream(strtod(linha[3],NULL),artista);//strtod converte char* em double, NULL é o apontador para o final do numero na string
    setId_Constituent(linha[4],artista);
    setCountry(linha[5],artista);
    setType(linha[6],artista);

    if(verifica_artistas(linha)){
        add_artista_valido(catalogo,artista);
    } else{
        free_artista(artista);
        escreve_artista("./resultados",linha);
    }
}

void add_artista_valido(Catalogo_Artistas catalogo, Artista artista)
{
    g_hash_table_insert(catalogo->artistas_validos, getId_Artista(artista), artista);
}


Artista get_artista_valido(Catalogo_Artistas catalogo, gpointer id)
{
    return (Artista)g_hash_table_lookup(catalogo->artistas_validos, id);
}


GHashTable *getArtistasValidos(Catalogo_Artistas artistas)
{
    return artistas->artistas_validos;
}

void free_catalogo_artistas(Catalogo_Artistas catalogo)
{
    if (catalogo->artistas_validos) {
        g_hash_table_unref(catalogo->artistas_validos);
    }
    free(catalogo);
}

void escreve_artista(const char *dir_path, char **linha)
{
    const char *file_Name = "/artists_errors.csv";
    const char *header = "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"";

    char *artists_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(artists_errors, dir_path);
    strcat(artists_errors, file_Name);

    FILE *file_artists = fopen(artists_errors, "a");
    free(artists_errors); // Liberta a memória alocada para o caminho do ficheiro
    if (file_artists == NULL)
    {
        perror("Erro ao abrir ficheiro artists_errors.csv");
        return;
    }
    
    fseek(file_artists, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    long size = ftell(file_artists); // Obtém a posição atual do ponteiro (tamanho do arquivo)
    if (size == 0){
        fprintf(file_artists, "%s\n", header);
    }

    fprintf(file_artists, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            linha[0],
            linha[1],
            linha[2],
            linha[3],
            linha[4],
            linha[5],
            linha[6]);


    fclose(file_artists);


}

