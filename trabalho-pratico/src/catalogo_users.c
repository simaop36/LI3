#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "users.h"
#include "catalogo_users.h"
#include "joint.h"
#include "utils.h"

typedef struct catalogo_utilizadores
{
    GHashTable *utilizadores_validos;
    GHashTable *utilizadores_invalidos;
} *catalogo_utilizadores;

catalogo_utilizadores create_catalogo_utilizadores()
{
    catalogo_utilizadores catalogo = malloc(sizeof(struct catalogo_utilizadores));
    catalogo->utilizadores_validos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_utilizador);
    catalogo->utilizadores_invalidos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_utilizador);

    return catalogo;
}

void build_utilizador(char **linha,void *cat){
    utilizador u = create_utilizador();
    Joint joint = (Joint)cat;
    catalogo_utilizadores catalogo = get_catalogo_utilizadores(joint);


    set_username(linha[0],u);
    set_email(linha[1],u);
    set_first_name(linha[2],u);
    set_last_name(linha[3],u);
    set_birth_date(linha[4],u);
    set_country(linha[5],u);
    set_subscription_style(linha[6],u);
    set_liked_musics_id(linha[7],u);

    if(!(verifica_utilizadores(linha)))
    {
        add_utilizador_invalido(catalogo,u);
    }
    else
    {
        if(segVerUser(u,joint)){
            char *bDay = get_birth_date(u);
            set_age(bDay,u);
            free(bDay);
            add_utilizador_valido(catalogo,u);
        }
        else {
            add_utilizador_invalido(catalogo,u);
        }
        
    }
}

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u)
{
    char *key = get_username(u);
    g_hash_table_insert(catalogo->utilizadores_validos, key, u);
}
void add_utilizador_invalido(catalogo_utilizadores catalogo, utilizador u)
{
    char *key = get_username(u);
    g_hash_table_insert(catalogo->utilizadores_invalidos, key, u);
}

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, char *username)
{
    return (utilizador)g_hash_table_lookup(catalogo->utilizadores_validos, username);
}

utilizador get_utilizador_invalido(catalogo_utilizadores catalogo, char *username)
{
    return (utilizador)g_hash_table_lookup(catalogo->utilizadores_invalidos, username);
}

GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores)
{
    return utilzadores->utilizadores_validos;
}

GHashTable *getUtilizadoresInvalidos(catalogo_utilizadores utilzadores)
{
    return utilzadores->utilizadores_invalidos;
}

void free_catalogo_users_invalidos(catalogo_utilizadores catalogo){
    g_hash_table_destroy(catalogo->utilizadores_invalidos);
}

void free_catalogo_users_validos(catalogo_utilizadores catalogo){
    g_hash_table_destroy(catalogo->utilizadores_validos);
}

void free_catalogo_utilizadores(catalogo_utilizadores catalogo)
{
    if (catalogo->utilizadores_validos) {
        g_hash_table_destroy(catalogo->utilizadores_validos);
    }
    if (catalogo->utilizadores_invalidos) {
        g_hash_table_destroy(catalogo->utilizadores_invalidos);
    }
    free(catalogo);
}


void aux_escreve_user(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    utilizador u = (utilizador)value;

    char *username = get_username(u);
    char *email = get_email(u);
    char *first_name = get_first_name(u);
    char *last_name = get_last_name(u);
    char *birth_date = get_birth_date(u);
    char *country = get_country(u);
    char *subscription_style = get_subscription_style(u);
    char *liked_musics = escreve_lista(get_liked_musics_id(u), 3);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            username,
            email,
            first_name,
            last_name,
            birth_date,
            country,
            subscription_style,
            liked_musics);

    free(username);
    free(email);
    free(first_name);
    free(last_name);
    free(birth_date);
    free(country);
    free(subscription_style);
    free(liked_musics);
}


void escreve_users(const char *dir_path, catalogo_utilizadores catalogo)
{
    const char *file_Name = "/users_errors.csv";
    const char *header = "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"";

    char *users_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(users_errors, dir_path);
    strcat(users_errors, file_Name);

    GHashTable *users_invalidos = getUtilizadoresInvalidos(catalogo);
    if (g_hash_table_size(users_invalidos) == 0)
    {
        free(users_errors);
        return;
    }

    FILE *file_users = fopen(users_errors, "w");
    free(users_errors);
    if (file_users == NULL)
    {
        perror("Erro ao abrir ficheiro users_errors.csv");
        return;
    }

    fprintf(file_users, "%s\n", header);

    g_hash_table_foreach(users_invalidos, aux_escreve_user, file_users);

    fclose(file_users);

}