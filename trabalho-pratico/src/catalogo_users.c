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
} *catalogo_utilizadores;

catalogo_utilizadores create_catalogo_utilizadores()
{
    catalogo_utilizadores catalogo = malloc(sizeof(struct catalogo_utilizadores));
    catalogo->utilizadores_validos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_utilizador);

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
        escreve_user("./resultados",linha);
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
            escreve_user("./resultados",linha);
        }
        
    }
}

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u)
{
    char *key = get_username(u);
    g_hash_table_insert(catalogo->utilizadores_validos, key, u);
}

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, char *username)
{
    return (utilizador)g_hash_table_lookup(catalogo->utilizadores_validos, username);
}

GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores)
{
    return utilzadores->utilizadores_validos;
}

void free_catalogo_utilizadores(catalogo_utilizadores catalogo)
{
    if (catalogo->utilizadores_validos) {
        g_hash_table_destroy(catalogo->utilizadores_validos);
    }
    free(catalogo);
}

void escreve_user(const char *dir_path, char **linha)
{
    const char *file_Name = "/users_errors.csv";
    const char *header = "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"";

    char *users_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(users_errors, dir_path);
    strcat(users_errors, file_Name);

    FILE *file_users = fopen(users_errors, "a");
    free(users_errors);
    if (file_users == NULL)
    {
        perror("Erro ao abrir ficheiro users_errors.csv");
        return;
    }
    
    fseek(file_users, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    long size = ftell(file_users); // Obtém a posição atual do ponteiro (tamanho do arquivo)
    if (size == 0){
        fprintf(file_users, "%s\n", header);
    }

    fprintf(file_users, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            linha[0],
            linha[1],
            linha[2],
            linha[3],
            linha[4],
            linha[5],
            linha[6],
            linha[7]);


    fclose(file_users);

}

