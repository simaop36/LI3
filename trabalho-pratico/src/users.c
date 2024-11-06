#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "users.h"
#include "catalogo_users.h"
#include "utils.h"

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

void build_utilizador(char **linha,void *cat){
    utilizador u = create_utilizador();

    catalogo_utilizadores catalogo = (catalogo_utilizadores)cat;

    set_username(linha[0],u);
    set_email(linha[1],u);
    set_first_name(linha[2],u);
    set_last_name(linha[3],u);
    set_birth_date(linha[4],u);
    set_country(linha[5],u);
    set_subscription_style(linha[6],u);
    set_liked_musics_id(linha[7],u);

    if(verifica_utilizadores(linha)){
        add_utilizador_valido(catalogo,u);
    } else{
        add_utilizador_invalido(catalogo,u);
    }
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

void set_liked_musics_id(char* liked_musics_id,utilizador u){
    char* copy = strdup(liked_musics_id);
    char **result = parse_lista(copy);
    u->liked_musics_id = result;
}



void free_utilizador(utilizador novo_utilizador) {

    free(novo_utilizador->username);
    free(novo_utilizador->email);
    free(novo_utilizador->first_name);
    free(novo_utilizador->last_name);
    free(novo_utilizador->birth_date);
    free(novo_utilizador->country);
    free(novo_utilizador->subscription_style);
    free(novo_utilizador->liked_musics_id);
    free(novo_utilizador);
}