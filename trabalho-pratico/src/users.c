#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>

#include "users.h"
#include "catalogo_users.h"
#include "catalogo_musica.h"
#include "utils.h"
#include "musica.h"
#include "estatisticas.h"

typedef struct utilizador {
    gpointer username;
    char *email;
    char *first_name;
    char *last_name;
    char *birth_date;
    char *country;
    char *subscription_style;
    gpointer *liked_musics_id;
    GArray *array;
    int idade;
} *utilizador;

utilizador create_utilizador(){
    utilizador novo_utilizador = malloc(sizeof(struct utilizador));
    novo_utilizador->username = NULL;
    novo_utilizador->email = NULL;
    novo_utilizador->first_name = NULL;
    novo_utilizador->last_name = NULL;
    novo_utilizador->birth_date = NULL;
    novo_utilizador->country = NULL;
    novo_utilizador->subscription_style = NULL;
    novo_utilizador->liked_musics_id = NULL;
    novo_utilizador->array=build_Array_GC();
    novo_utilizador->idade=0;
    
    return novo_utilizador;
}

int verifica_utilizadores(char **linha){
    //verifica se linha[x]==NULL
    if(!(linha[0])) return 0;
    if(!(linha[1])) return 0;
    if(!(linha[2])) return 0;
    if(!(linha[3])) return 0;
    if(!(linha[4])) return 0;
    if(!(linha[5])) return 0;
    if(!(linha[6])) return 0;
    if(!(linha[7])) return 0;

    if(!(valida_email(linha[1]))) return 0;
    if(!(valida_data(linha[4]))) return 0;
    if(!(valida_tipo_user(linha[6]))) return 0;
    if(!(valida_lista(linha[7]))) return 0;

    return 1;
}


int get_age(utilizador u){
    return u->idade;
}

GArray*getArray(utilizador u){
    return u->array;
}

gpointer get_username_gpointer(utilizador u){
    return u->username;
}

int get_username_Musica_int(utilizador u)
{
    int num = GPOINTER_TO_INT(u->username);
    return num;
}

char *get_username_string(utilizador u)
{
    char *result = malloc(9);
    snprintf(result, 9, "U%07d", get_username_Musica_int(u));
    return result;
}

char* get_email(utilizador u){
    char* uCopy = strdup(u->email);
    return uCopy;
}

char* get_first_name(utilizador u){
    char* uCopy = strdup(u->first_name);
    return uCopy;
}

char* get_last_name(utilizador u){
    char* uCopy = strdup(u->last_name);
    return uCopy;
}

char* get_birth_date(utilizador u){
    char* uCopy = strdup(u->birth_date);
    return uCopy;
}

char* get_country(utilizador u){
    char* uCopy = strdup(u->country);
    return uCopy;
}

char* get_subscription_style(utilizador u){
    char* uCopy = strdup(u->subscription_style);
    return uCopy;
}

gpointer *get_liked_musics_id(utilizador u){

    return u->liked_musics_id;
}

void setArray(GArray *gc, utilizador u){
    u->array=gc;
}

void set_username(char* username,utilizador u){
    int num;
    if(sscanf(username,"U%d",&num) == 1){
        gpointer p = GINT_TO_POINTER(num);
        u->username = p;
    } else {
        return;
    }
}

void set_email(char* email,utilizador u){
    char* copy = strdup(email);
    u->email = copy;
}

void set_first_name(char* fisrt_name,utilizador u){
    char* copy = strdup(fisrt_name);
    u->first_name = copy;
}

void set_last_name(char* last_name,utilizador u){
    char* copy = strdup(last_name);
    u->last_name = copy;
}

void set_birth_date(char* birth_date,utilizador u){
    char* copy = strdup(birth_date);
    u->birth_date = copy;
}

void set_age(char* birth_date,utilizador u){
    u->idade=calcula_idade(birth_date);
}

void set_country(char* country,utilizador u){
    char* copy = strdup(country);
    u->country = copy;
}

void set_subscription_style(char* subscription_style,utilizador u){
    char* copy = strdup(subscription_style);
    u->subscription_style = copy;
}

void set_liked_musics_id(char* liked_musics_id,utilizador u){

    char *copy = strdup(liked_musics_id);
    char **result = parse_lista(copy); // NULL terminated
    free(copy);
    int size = 1;
    for(int i = 0;result[i] != NULL;i++) size++;

    u->liked_musics_id = malloc(size*sizeof(gpointer));

    for(int j = 0; result[j] != NULL; j++)
    {
        int num;
        if (sscanf(result[j], "S%d", &num) != 1) {
            return;
        }
        u->liked_musics_id[j] = int_gpointer(num);
        
        free(result[j]);
    }
    u->liked_musics_id[size - 1] = NULL;
    free(result);
    
}


void free_utilizador(utilizador novo_utilizador) {

    free(novo_utilizador->email);
    free(novo_utilizador->first_name);
    free(novo_utilizador->last_name);
    free(novo_utilizador->birth_date);
    free(novo_utilizador->country);
    free(novo_utilizador->subscription_style);
    free(novo_utilizador->liked_musics_id);
    free_Array_GC(novo_utilizador->array);
    free(novo_utilizador);
}



