#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "utils.h"

typedef struct historico
{
    char *id;
    char *user_id;
    char *music_id;
    char *timestamp;
    char *duration;
    char *plataform;
} *Historico;

Historico create_Historico()
{
    Historico novo_historico = malloc(sizeof(struct historico));
    novo_historico->id = NULL;
    novo_historico->user_id = NULL;
    novo_historico->music_id = NULL;
    novo_historico->timestamp = NULL;
    novo_historico->duration = NULL;
    novo_historico->plataform = NULL;

    return novo_historico;
}




char *get_IDHistorico(Historico h)
{
    char *hCopy = strdup(h->id);
    return hCopy;
}

char *get_UserId(Historico h)
{
    char *hCopy = strdup(h->user_id);
    return hCopy;
}

char *get_MusicId(Historico h)
{
    char *hCopy = strdup(h->music_id);
    return hCopy;
}

char *get_Timestamp(Historico h)
{
    char *hCopy = strdup(h->timestamp);
    return hCopy;
}

char *get_Duration(Historico h)
{
    char *hCopy = strdup(h->duration);
    return hCopy;
}

char *get_Plataform(Historico h)
{
    char *hCopy = strdup(h->plataform);
    return hCopy;
}

void setId_Historico(char *id, Historico h)
{
    char *copy = strdup(id);
    h->id = copy;
}

void set_UserId(char *user_id, Historico h)
{
    char *copy = strdup(user_id);
    h->user_id = copy;
}


void set_MusicId(char *music_id, Historico h){

    char *copy = strdup(music_id);
    h->music_id = copy;
}

void set_Timestamp(char *timestamp, Historico h)
{
    char *copy = strdup(timestamp);
    h->timestamp = copy;
}

void set_Duration(char *duration, Historico h)
{
    char *copy = strdup(duration);
    h->duration = copy;
}

void set_Plataform(char *plataform, Historico h)
{
    char *copy = strdup(plataform);
    h->plataform = copy;
}


int verifica_plataform(char* plataform){
    char* aux = strdup(plataform);
    int i = 0; 
    stringToUpper(aux);
    if(strcmp(aux, "MOBILE") == 0 || strcmp(aux, "DESKTOP") == 0) i = 1;
    free(aux);
    return i;
}

int verifica_historico(char **linha){
    //verifica se linha[x]==NULL
    if(!(linha[0])) return 0;
    if(!(linha[1])) return 0;
    if(!(linha[2])) return 0;
    if(!(linha[3])) return 0;
    if(!(linha[5])) return 0;

    if(!(verifica_plataform(linha[5]))) return 0;

    return 1;
}

void free_historico(Historico novo_historico) {

    free(novo_historico->id);
    free(novo_historico->user_id);
    free(novo_historico->music_id);
    free(novo_historico->timestamp);
    free(novo_historico->duration);
    free(novo_historico->plataform);
    free(novo_historico);

}