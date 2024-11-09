#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "joint.h"
#include "users.h"
#include "utils.h"
#include "output.h"

typedef struct generoContagem
{
    char *genero;
    int likes;
} *generoContagem;

char *Q1(char *ID, Joint catalogo)
{
    catalogo_utilizadores catU = get_catalogo_utilizadores(catalogo);
    utilizador u = get_utilizador_valido(catU, ID);
    if (u == NULL) {
        char *empty_response = malloc(2); // Aloca espaço para "\n" e o caractere nulo
        if (empty_response == NULL) return NULL; // Falha na alocação
        strcpy(empty_response, "\n");
        return empty_response;
    }
    
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

    snprintf(resposta, buffer_size, "%s;%s;%s;%d;%s\n",
             email, first_name, last_name, idade, country);
    
    free(email);
    free(first_name);
    free(last_name);
    free(birth_date);
    free(country);

    return resposta;
}

int comparar_generos(gconstpointer a, gconstpointer b)
{
    // conversao de void * para generoContagem
    generoContagem g1 = (generoContagem)a;
    generoContagem g2 = (generoContagem)b;

    if (g2->likes != g1->likes)
    {
        return g2->likes - g1->likes; // ordem descendente por likes
    }
    return strcmp(g1->genero, g2->genero); // ordem alfabetica
}



char *Q3(int min, int max, Joint catalogo) {
    GHashTable *utilizadores = getUtilizadoresValidos(get_catalogo_utilizadores(catalogo));
    Catalogo_Musicas musicas = get_catalogo_musicas(catalogo);

    // Configura a hash table para liberar automaticamente a chave e o valor
    GHashTable *generosContagem = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    GList *keys = g_hash_table_get_keys(utilizadores);
    for (GList *iter = keys; iter != NULL; iter = iter->next) {
        gpointer key = iter->data;
        gpointer u = g_hash_table_lookup(utilizadores, key);
        char *birth_date = get_birth_date(u);

        int idade = calcula_idade(birth_date);

        if (idade >= min && idade <= max) {
            char **likedMusics = get_liked_musics_id(u);
            if (likedMusics == NULL) {
                printf("O utilizador não tem músicas curtidas.\n");
                free(birth_date);
                continue;
            }

            for (int i = 0; likedMusics[i] != NULL; i++) {
                char *idMusica = likedMusics[i];
                char *genero = getGenre(get_musica_valida(musicas, idMusica));

                if (genero == NULL) {
                    printf("Gênero não encontrado para a música: %s\n", idMusica);
                    continue;
                }

                generoContagem contagem = g_hash_table_lookup(generosContagem, genero);

                if (contagem == NULL) {
                    contagem = malloc(sizeof(struct generoContagem));
                    contagem->genero = strdup(genero);  // strdup da chave, será liberada por g_free
                    contagem->likes = 1;
                    g_hash_table_insert(generosContagem, contagem->genero, contagem);
                } else {
                    contagem->likes++;
                }
                free(genero);
                free(likedMusics[i]);
            }
            free(likedMusics);
        }
        free(birth_date);
    }

    // Ordena os gêneros pela popularidade e em seguida alfabeticamente
    GList *generos_lista = g_hash_table_get_values(generosContagem);

    if (generos_lista == NULL || g_list_length(generos_lista) == 0) {
        printf("Nenhum gênero foi contabilizado.\n");
        g_list_free(keys);
        g_hash_table_destroy(generosContagem);
        return strdup(""); // Retorna uma string vazia indicando ausência de dados
    }
    generos_lista = g_list_sort(generos_lista, comparar_generos);

    // Cria um buffer dinâmico para armazenar o resultado formatado
    size_t buffer_size = 256;
    char *resultado = malloc(buffer_size);
    resultado[0] = '\0'; // Inicializa a string como vazia

    for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
        generoContagem contagem = (generoContagem)iter->data;
        size_t required_size = strlen(contagem->genero) + 20;

        // Redimensiona o buffer se necessário
        if (strlen(resultado) + required_size >= buffer_size) {
            buffer_size *= 2;
            resultado = realloc(resultado, buffer_size);
        }

        // Formata e adiciona cada linha ao buffer resultado
        char line[100];
        snprintf(line, sizeof(line), "%s;%d\n", contagem->genero, contagem->likes);
        strcat(resultado, line);
    }

    // Libera recursos
    g_list_free(generos_lista);
    g_list_free(keys);
    g_hash_table_destroy(generosContagem);

    printf("%s\n", resultado);

    return resultado;
}

void excuta_queries(char *linha, int contador, Joint joint){
    switch (linha[0])
    {
    case '1': {
        char *id = linha+2;
        char *resposta = Q1(id,joint);
        escreve_querie(resposta,contador);
        free(resposta);
        
        break;
    }
    case '2':

        break;
    case '3':{
        char buffer[50];
        strncpy(buffer, linha, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        char *token = strtok(buffer, " ");
        int valores[3];
        int i = 0;

        while (token != NULL && i < 3) {
            valores[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
        if (i >= 3) {  // Garante que temos pelo menos três valores na linha
            int min = valores[1];
            int max = valores[2];
            char *resposta = Q3(min, max, joint);
            escreve_querie(resposta,contador);
            free(resposta);
        }

        break;
    }
    default:
        break;
    }

}