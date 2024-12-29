#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "artistas.h"
#include "catalogo_artista.h"
#include "utils.h"

typedef struct catalogo_artistas
{
    GHashTable *artistas_validos;
    GHashTable *artistas_invalidos;
} *Catalogo_Artistas;

Catalogo_Artistas create_catalogo_artistas()
{
    Catalogo_Artistas catalogo = malloc(sizeof(struct catalogo_artistas));
    catalogo->artistas_validos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_artista);
    catalogo->artistas_invalidos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_artista);

    return catalogo;
}

void build_Artista(char **linha,void *cat){

    Artista artista = create_Artista();
    Catalogo_Artistas catalogo = (Catalogo_Artistas)cat;
    
    setId_Artista(linha[0],artista);
    setName(linha[1],artista);
    setDescription(linha[2],artista);
    setRecipe_Per_Stream(strtod(linha[3],NULL),artista);//strtod converte char* em double, NULL é o apontador para o final do numero na string
    setId_Constituent(linha[4],artista);
    setCountry(linha[5],artista);
    setType(linha[6],artista);

    if(verifica_artistas(linha)){
        add_artista_valido(catalogo,artista);
    } else{
        add_artista_invalido(catalogo,artista);
    }
}

void add_artista_valido(Catalogo_Artistas catalogo, Artista artista)
{

    char *key = getId_Artista(artista);

    g_hash_table_insert(catalogo->artistas_validos, key, artista);
}
void add_artista_invalido(Catalogo_Artistas catalogo, Artista artista)
{

    char *key = getId_Artista(artista);

    g_hash_table_insert(catalogo->artistas_invalidos, key, artista);
}

Artista get_artista_valido(Catalogo_Artistas catalogo, char *id)
{
    return (Artista)g_hash_table_lookup(catalogo->artistas_validos, id);
}

Artista get_artista_invalido(Catalogo_Artistas catalogo, char *id)
{
    return (Artista)g_hash_table_lookup(catalogo->artistas_invalidos, id);
}

GHashTable *getArtistasValidos(Catalogo_Artistas artistas)
{
    return artistas->artistas_validos;
}

GHashTable *getArtistasInvalidos(Catalogo_Artistas artistas)
{
    return artistas->artistas_invalidos;
}

void free_catalogo_artistas_invalidos(Catalogo_Artistas catalogo){
    if (catalogo->artistas_invalidos) {
        g_hash_table_unref(catalogo->artistas_invalidos);
    }
}

void free_catalogo_artistas_validos(Catalogo_Artistas catalogo){
    if (catalogo->artistas_validos) {
        g_hash_table_unref(catalogo->artistas_validos);
    }
}

void free_catalogo_artistas(Catalogo_Artistas catalogo)
{
    if (catalogo->artistas_validos) {
        g_hash_table_unref(catalogo->artistas_validos);
    }
    if (catalogo->artistas_invalidos) {
        g_hash_table_unref(catalogo->artistas_invalidos);
    }
    free(catalogo);
}


void aux_escreve_artista(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    Artista artista = (Artista)value;

    char *id = getId_Artista(artista);
    char *name = getName(artista);
    char *description = getDescription(artista);
    char *id_constituent = escreve_lista(getId_Constituent(artista), 1);
    char *country = getCountry(artista);
    char *type = getType(artista);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%.2f\";\"%s\";\"%s\";\"%s\"\n",
            id,
            name,
            description,
            getRecipe_Per_Stream(artista),
            id_constituent,
            country,
            type);

    free(id);
    free(name);
    free(description);
    free(id_constituent);
    free(country);
    free(type);
}

void escreve_artistas(const char *dir_path, Catalogo_Artistas catalogo_artistas)
{
    const char *file_Name = "/artists_errors.csv";
    const char *header = "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"";

    char *artists_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(artists_errors, dir_path);
    strcat(artists_errors, file_Name);

    GHashTable *artistas_invalidos = getArtistasInvalidos(catalogo_artistas);

    if (g_hash_table_size(artistas_invalidos) == 0)
    {
        free(artists_errors);
        return;
    }

    // Abre o ficheiro para escrita
    FILE *file_artists = fopen(artists_errors, "w");
    free(artists_errors); // Liberta a memória alocada para o caminho do ficheiro
    if (file_artists == NULL)
    {
        perror("Erro ao abrir ficheiro artists_errors.csv");
        return;
    }

    fprintf(file_artists, "%s\n", header);

    g_hash_table_foreach(artistas_invalidos, aux_escreve_artista, file_artists);

    fclose(file_artists);

}
