#ifndef USERS_H
#define USERS_H

typedef struct utilizador *utilizador;

utilizador create_utilizador();

void build_utilizador(char **linha,catalogo_utilizadores catalogo);

char* get_username(utilizador u);

char* get_email(utilizador u);

char* get_first_name(utilizador u);

char* get_last_name(utilizador u);

char* get_birth_date(utilizador u);

char* get_country(utilizador u);

char* get_subscription_style(utilizador u);

char** get_liked_musics_id(utilizador u);

void set_username(char* username,utilizador u);

void set_email(char* email,utilizador u);

void set_first_name(char* fisrt_name,utilizador u);

void set_last_name(char* last_name,utilizador u);

void set_birth_date(char* birth_date,utilizador u);

void set_country(char* country,utilizador u);

void set_subscription_style(char* subscription_style,utilizador u);

void set_liked_musics_id(char** liked_musics_id,utilizador u);


void free_utilizador(utilizador novo_utilizador);

#endif