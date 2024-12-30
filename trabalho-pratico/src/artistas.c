#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>


#include "artistas.h"
#include "utils.h"
#include "catalogo_artista.h"

typedef struct artista {
    gpointer id;
    char *name;
    double recipe_per_stream;
    char **id_constituent;
    char *country;
    char *type;
    long int discography_Duration;
} *Artista;

Artista create_Artista()
{
    Artista novo_artista = malloc(sizeof(struct artista));
    novo_artista->id = NULL;
    novo_artista->name = NULL;
    novo_artista->id_constituent = NULL;
    novo_artista->country = NULL;
    novo_artista->type = NULL;
    novo_artista->discography_Duration = 0;

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

gpointer *getId_Artista(Artista a)
{
    return a->id;
}

int getId_Artista_int(Artista a)
{
    int num = GPOINTER_TO_INT(a->id);
    return num - OFFSET_ARTISTA;
}

char *getId_Artista_String(Artista a)
{
    char *result = malloc(9);
    snprintf(result, 9, "A%07d", getId_Artista_int(a));
    return result;
}

char *getName(Artista a)
{
    char *aCopy = strdup(a->name);
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
double getDiscography_Duration(Artista a)
{
    return a->discography_Duration;
}

void setId_Artista(char *id, Artista a)
{

    int num;
    if(sscanf(id,"A%d",&num) == 1){
        gpointer p = GINT_TO_POINTER(num+ OFFSET_ARTISTA);
        a->id = p;
    } else {
        return;
    }

    
}
void setName(char *name, Artista a)
{
    char *copy = strdup(name);
    a->name = copy;
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

void setDiscography_Duration(long int disc_Duration, Artista a)
{
    a->discography_Duration = disc_Duration;
}
void increaseDiscography_Duration(long int disc_Duration, Artista a){
    a->discography_Duration += disc_Duration;
}


void free_artista(Artista novo_artista) {

    free(novo_artista->name);
    free_lista_strings(novo_artista->id_constituent);
    free(novo_artista->country);
    free(novo_artista->type);
    free(novo_artista);
}
