#include <stdlib.h>
#include <string.h>
#include <glib.h>


#include "artistas.h"
#include "utils.h"
#include "catalogo_artista.h"

typedef struct artista {
    char *id;
    char *name;
    char *description;
    double recipe_per_stream;
    char **id_constituent;
    char *country;
    char *type;
} *Artista;

Artista create_Artista()
{
    Artista novo_artista = malloc(sizeof(struct artista));
    novo_artista->id = NULL;
    novo_artista->name = NULL;
    novo_artista->description = NULL;
    novo_artista->id_constituent = NULL;
    novo_artista->country = NULL;
    novo_artista->type = NULL;

    return novo_artista;
}

int verifica_artistas(char **linha){
    //verifica se linha[x]==NULL
    if(!(linha[0])) return 0;
    if(!(linha[1])) return 0;
    if(!(linha[2])) return 0;
    if(!(linha[3])) return 0;
    if(!(linha[4])) return 0;
    if(!(linha[5])) return 0;
    if(!(linha[6])) return 0;

    if(!(valida_lista(linha[4]))) return 0;
    if(!(valida_tipo_artista(linha[6],linha[4]))) return 0;

    return 1;
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

char *getId_Artista(Artista a)
{
    char *aCopy = strdup(a->id);
    return aCopy;
}
char *getName(Artista a)
{
    char *aCopy = strdup(a->name);
    return aCopy;
}
char *getDescription(Artista a)
{
    char *aCopy = strdup(a->description);
    return aCopy;
}
double getRecipe_Per_Stream(Artista a)
{
    return a->recipe_per_stream;
}
char **getId_Constituent(Artista a)
{
    char **aCopy = g_strdupv(a->id_constituent);
    return aCopy;
}

char *getCountry(Artista a)
{
    char *aCopy = strdup(a->country);
    return aCopy;
}
char *getType(Artista a)
{
    char *aCopy = strdup(a->type);
    return aCopy;
}

void setId_Artista(char *id, Artista a)
{
    char *copy = strdup(id);
    a->id = copy;
}
void setName(char *name, Artista a)
{
    char *copy = strdup(name);
    a->name = copy;
}
void setDescription(char *description, Artista a)
{
    char *copy = strdup(description);
    a->description = copy;
}
void setRecipe_Per_Stream(double recipe_per_stream, Artista a)
{
    a->recipe_per_stream = recipe_per_stream;
}
void setId_Constituent(char *id_constituent, Artista a)
{
    char *copy = strdup(id_constituent);
    char **result = parse_lista(copy);
    free(copy);
    a->id_constituent = result;
}
void setCountry(char *country, Artista a)
{
    char *copy = strdup(country);
    a->country = copy;
}
void setType(char *type, Artista a)
{
    char *copy = strdup(type);
    a->type = copy;
}




void free_artista(Artista novo_artista) {

    free(novo_artista->id);
    free(novo_artista->name);
    free(novo_artista->description);
    free_lista_strings(novo_artista->id_constituent);
    free(novo_artista->country);
    free(novo_artista->type);
    free(novo_artista);
}
