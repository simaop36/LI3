#include <glib.h>

#include "artistas.h"
#include "catalogo_artista.h"

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
