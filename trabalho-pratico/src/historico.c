#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "utils.h"

typedef struct historico
{
    gpointer id;
    gpointer user_id;
    gpointer music_id;
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



gpointer get_IDHistorico_gpointer(Historico h)
{
    return h->id;
}


int get_IDHistorico_int(Historico h)
{
    int num = GPOINTER_TO_INT(h->id);
    return num - OFFSET_HISTORY;
}

char *get_IDHistorico_string(Historico h)
{
    char *result = malloc(11);
    snprintf(result, 11, "H%09d", get_IDHistorico_int(h));
    return result;
}


gpointer get_user_id_gpointer(Historico h){
    return h->user_id;
}

int get_user_id_int(Historico h)
{
    int num = GPOINTER_TO_INT(h->user_id);
    return num - OFFSET_USER;
}

char *get_user_id_string(Historico h)
{
    char *result = malloc(9);
    snprintf(result, 9, "U%07d", get_user_id_int(h));
    return result;
}


gpointer get_musica_id_gpointer(Historico h)
{
    return h->music_id;
}

int get_musica_id_int(Historico h)
{
    int num = GPOINTER_TO_INT(h->music_id);
    return num - OFFSET_MUSICA;
}

char *get_musica_id_string(Historico h)
{
    char *result = malloc(9);
    snprintf(result, 9, "S%07d", get_musica_id_int(h));
    return result;
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
    int num;
    if(sscanf(id,"H%d",&num) == 1){
        gpointer p = GINT_TO_POINTER(num + OFFSET_HISTORY);
        h->id = p;
    } else {
        return;
    }
}

void set_UserId(char *user_id, Historico h)
{
    int num;
    if(sscanf(user_id,"U%d",&num) == 1){
        gpointer p = GINT_TO_POINTER(num + OFFSET_USER);
        h->user_id = p;
    } else {
        return;
    }
}


void set_MusicId(char *music_id, Historico h){

    int num;
    if(sscanf(music_id,"S%d",&num) == 1){
        gpointer p = GINT_TO_POINTER(num + OFFSET_MUSICA);
        h->music_id= p;
    } else {
        return;
    }
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

    free(novo_historico->timestamp);
    free(novo_historico->duration);
    free(novo_historico->plataform);
    free(novo_historico);

}