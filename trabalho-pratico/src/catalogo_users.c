#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "users.h"
#include "catalogo_users.h"
#include "joint.h"
#include "utils.h"
#include "estatisticas.h"
#include "segVer.h"

typedef struct catalogo_utilizadores
{
    GHashTable *utilizadores_validos;
    GPtrArray *keys_users;
} *catalogo_utilizadores;

catalogo_utilizadores create_catalogo_utilizadores()
{
    catalogo_utilizadores catalogo = malloc(sizeof(struct catalogo_utilizadores));
    catalogo->utilizadores_validos = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_utilizador);
    catalogo->keys_users = NULL;
    return catalogo;
}

void build_utilizador(char **linha, void *cat, Stats stats)
{

    Joint joint = (Joint)cat;
    catalogo_utilizadores catalogo = get_catalogo_utilizadores(joint);

    if (!(verifica_utilizadores(linha)))
    {

        escreve_user("./resultados", linha);
    }
    else
    {
        utilizador u = create_utilizador();

        set_username(linha[0], u);
        set_email(linha[1], u);
        set_first_name(linha[2], u);
        set_last_name(linha[3], u);
        set_birth_date(linha[4], u);
        set_country(linha[5], u);
        set_subscription_style(linha[6], u);
        set_liked_musics_id(linha[7], u);

        if (segVerUser(u, joint))
        {
            char *bDay = get_birth_date(u);
            set_age(bDay, u);
            free(bDay);
            add_utilizador_valido(catalogo, u);
        }
        else
        {
            free_utilizador(u);
            escreve_user("./resultados", linha);
        }
    }
}

void add_utilizador_valido(catalogo_utilizadores catalogo, utilizador u)
{
    g_hash_table_insert(catalogo->utilizadores_validos, get_username_gpointer(u), u);
}

GPtrArray *get_keys_users(catalogo_utilizadores catalogo)
{
    return catalogo->keys_users;
}

void build_keys_users(catalogo_utilizadores catalogo)
{
    GHashTable *hash_table = catalogo->utilizadores_validos;

    if (catalogo->keys_users != NULL)
    {
        g_ptr_array_free(catalogo->keys_users, TRUE);
        catalogo->keys_users = NULL;
    }

    GPtrArray *keys = g_ptr_array_new();
    if (keys == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for GPtrArray.\n");
        return;
    }

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_ptr_array_add(keys, key);
    }

    catalogo->keys_users = keys;
}

utilizador get_utilizador_valido(catalogo_utilizadores catalogo, gpointer username)
{
    return (utilizador)g_hash_table_lookup(catalogo->utilizadores_validos, username);
}

GHashTable *getUtilizadoresValidos(catalogo_utilizadores utilzadores)
{
    return utilzadores->utilizadores_validos;
}

void free_catalogo_utilizadores(catalogo_utilizadores catalogo)
{
    if (catalogo->utilizadores_validos)
    {
        g_hash_table_destroy(catalogo->utilizadores_validos);
    }
    g_ptr_array_free(catalogo->keys_users, TRUE);
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
    long size = ftell(file_users);  // Obtém a posição atual do ponteiro (tamanho do arquivo)
    if (size == 0)
    {
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
