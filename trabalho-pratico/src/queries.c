#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "joint.h"
#include "users.h"
#include "utils.h"

typedef struct generoContagem
{
    char *genero;
    int likes;
} *generoContagem;

char *Q1(char *ID, Joint catalogo)
{
    catalogo_utilizadores catU = getUtilizadoresValidos(catalogo);
    utilizador u = get_utilizador_valido(catU, ID);
    char *email = get_email(u);
    char *first_name = get_first_name(u);
    char *last_name = get_last_name(u);
    char *birth_date = get_birth_date(u);
    char *country = get_country(u);
    int idade = calcula_idade(birth_date);

    size_t buffer_size = strlen(email) + strlen(first_name) + strlen(last_name) +
                         strlen(country) + 50;
    char *resposta = malloc(buffer_size);

    if (resposta == NULL)
    {

        return NULL;
    }

    snprintf(resposta, buffer_size, " %s;%s;%s;%d;%s\n",
             email, first_name, last_name, idade, country);

    return resposta;
}

int comparar_generos(gconstpointer a, gconstpointer b)
{
    generoContagem g1 = *(generoContagem *)a;
    generoContagem g2 = *(generoContagem *)b;

    if (g2->likes != g1->likes)
    {
        return g2->likes - g1->likes;
    }
    return strcmp(g1->genero, g2->genero);
}

void Q3(int min, int max, Joint catalogo)
{
    catalogo_utilizadores utilizadores = getUtilizadoresValidos(catalogo);
    Catalogo_Musicas musicas = getMusicasValidas(catalogo);
    GHashTable *generosContagem = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    GList *keys = g_hash_table_get_keys(utilizadores);
    for (GList *iter = keys; iter != NULL; iter = iter->next)
    {
        gpointer key = iter->data;
        gpointer u = g_hash_table_lookup(utilizadores, key);
        if (calcula_idade(u) >= min && calcula_idade(u) <= max)
        {
            char **likedMusics = get_liked_musics_id(u);
            for (int i = 0; likedMusics[i] != NULL; i++)
            {
                char *idMusica = likedMusics[i];
                char *genero = getGenre(get_musica_valida(musicas, idMusica));

                generoContagem contagem = g_hash_table_lookup(generosContagem, genero);
                if (contagem == NULL)
                {
                    generoContagem contador = malloc(sizeof(generoContagem));
                    contador->genero = strdup(genero);
                    contador->likes = 0;
                    g_hash_table_insert(generosContagem, contador->genero, contador);
                }
                contagem->likes++;
            }
        }
    }

    GList *generos_lista = g_hash_table_get_values(generosContagem);

    generos_lista = g_list_sort(generos_lista, comparar_generos);

    for (GList *iter = generos_lista; iter != NULL; iter = iter->next)
    {
        generoContagem contagem = (generoContagem)iter->data;
        printf("%s;%d\n", contagem->genero, contagem->likes);

        free(contagem->genero);
        free(contagem);
    }
    g_list_free(generos_lista);
    g_hash_table_destroy(generosContagem);
}