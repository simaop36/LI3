#include <stdlib.h>
#include <glib.h>
#include "users.h"

typedef struct utilizador {
    char *username;
    char *email;
    char *first_name;
    char *last_name;
    char *birth_date;
    char *country;
    char *subscription_style;
    char **liked_musics_id;
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
    
    return novo_utilizador;
}

void build_utilizador(char *username,char *email,char *first_name,char *last_name,char *birth_date,char *country,char *subscription_style,char **liked_musics_id){
    utilizador u = create_utilizador();

    set_username(username,u);
    set_email(email,u);
    set_first_name(first_name,u);
    set_last_name(last_name,u);
    set_birth_date(birth_date,u);
    set_country(country,u);
    set_subscription_style(subscription_style,u);
    set_liked_musics_id(liked_musics_id,u);
}

char* get_username(utilizador u){
    char* uCopy = strdup(u->username);
    return uCopy;
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

char** get_liked_musics_id(utilizador u){
    char** uCopy = g_strdupv(u->liked_musics_id);
    return uCopy;
}

void set_username(char* username,utilizador u){
    char* copy = strdup(username);
    u->username = copy;
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

void set_country(char* country,utilizador u){
    char* copy = strdup(country);
    u->country = copy;
}

void set_subscription_style(char* subscription_style,utilizador u){
    char* copy = strdup(subscription_style);
    u->subscription_style = copy;
}

void set_liked_musics_id(char** liked_musics_id,utilizador u){
    char** copy = g_strdupv(liked_musics_id);
    u->liked_musics_id = copy;
}