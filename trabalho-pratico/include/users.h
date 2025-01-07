#ifndef USERS_H
#define USERS_H

#include "catalogo_users.h"
#include "catalogo_musica.h"
#include <limits.h>

typedef struct utilizador *utilizador;
typedef struct generoContagem *GeneroContagem;


utilizador create_utilizador();

int verifica_utilizadores(char **linha);

int get_age(utilizador u);

GArray*getArray(utilizador u);

gpointer get_username_gpointer(utilizador u);

//int get_username_Musica_int(utilizador u);

char *get_username_string(utilizador u);

char* get_email(utilizador u);

char* get_first_name(utilizador u);

char* get_last_name(utilizador u);

char* get_birth_date(utilizador u);

char* get_country(utilizador u);

char* get_subscription_style(utilizador u);

gpointer *get_liked_musics_id(utilizador u);

void setArray(GArray *gc, utilizador u);

void set_username(char* username,utilizador u);

void set_email(char* email,utilizador u);

void set_first_name(char* fisrt_name,utilizador u);

void set_last_name(char* last_name,utilizador u);

void set_birth_date(char* birth_date,utilizador u);

void set_age(char* birth_date,utilizador u);

void set_country(char* country,utilizador u);

void set_subscription_style(char* subscription_style,utilizador u);

void set_liked_musics_id(char* liked_musics_id,utilizador u);

void free_utilizador(utilizador novo_utilizador);


#endif