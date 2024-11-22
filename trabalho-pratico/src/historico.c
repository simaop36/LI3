#include <stdlib.h>
#include <string.h>
#include <glib.h>



typedef struct historico {
    char *id;
    char *user_id;
    char *music_id;
    char *timestamp;
    long int duration;
    char *plataform;
} *Historico;

Historico create_Historico()
{
    Historico novo_historico = malloc(sizeof(struct historico));
    novo_historico->id = NULL;
    novo_historico->user_id = NULL;
    novo_historico->music_id = NULL;
    novo_historico->timestamp = NULL;
    novo_historico->duration = 0;
    novo_historico->plataform = NULL;

    return novo_historico;
}

int verifica_artistas(char **linha){
    //verifica se linha[x]==NULL
    if(!(linha[0])) return 0;
    if(!(linha[1])) return 0;
    if(!(linha[2])) return 0;
    if(!(linha[3])) return 0;
    if(!(linha[4])) return 0;
    if(!(linha[5])) return 0;

    return 1;
}

char *get_IDHistorico(Historico h){
    char *hCopy = strdup(h->id);
    return hCopy;
}

char *get_UserId(Historico h){
    char *hCopy = strdup(h->user_id);
    return hCopy;
}

char *get_MusicId(Historico h){
    char *hCopy = strdup(h->music_id);
    return hCopy;
}

char *get_Timestamp(Historico h){
    char *hCopy = strdup(h->timestamp);
    return hCopy;
}

double get_Duration(Historico h){
    return h->duration;
}

char *get_Plataform(Historico h){
    char *hCopy = strdup(h->plataform);
    return hCopy;
}

void setId_Artista(char *id, Historico h){
    char *copy = strdup(id);
    h->id = copy;
}

void set_UserId(char *user_id, Historico h){
    char *copy = strdup(user_id);
    h->user_id = copy;
}

void setId_MusicId(char *music_id, Historico h){
    char *copy = strdup(music_id);
    h->music_id = copy;
}

void set_Timestamp(char *timestamp, Historico h){
    char *copy = strdup(timestamp);
    h->timestamp = copy;
}

void set_Duration(long int duration, Historico h){
    h->duration = duration;
}

void set_Plataform(char *plataform, Historico h){
    char *copy = strdup(plataform);
    h->plataform = copy;
}
