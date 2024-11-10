#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "joint.h"
#include "users.h"
#include "utils.h"
#include "output.h"
#include "artistas.h"
#include "estatisticas.h"


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


int compara_artistas(Artista a, Artista b){
    if(getDiscography_Duration(a) != getDiscography_Duration(b)){
        return getDiscography_Duration(b) - getDiscography_Duration(a);
    }else{
        char *idA = getId_Artista(a);
        char *idB = getId_Artista(b);
        int result = strcmp(idA,idB);
        free(idA);
        free(idB);
        return result;
    }
}

void insere_artista_ordenado(Artista top[], int n, Artista novo) {
    for (int i = 0; i < n; i++) {
        if (top[i] == NULL) {//posição vazia
            top[i] = novo;
            return;
        }
        if (compara_artistas(novo, top[i]) < 0) {
            //abrir espaço para o novo artista
            if (top[n - 1] != NULL) {
                top[n - 1] = NULL;
            }
            for (int j = n - 1; j > i; j--) {
                top[j] = top[j - 1];
            }
            top[i] = novo;
            return;
        }
    }
}

char *Q2(int n, char *c, Joint j){
    GHashTable *artistas = getArtistasValidos(get_catalogo_artistas(j));
    Artista top[n];
    memset(top, 0, sizeof(top)); // Inicializa o array a NULL
    if(n == 0) return strdup("\n");

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, artistas);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artista artista = (Artista)value;
        if (c == NULL) {
            insere_artista_ordenado(top, n, artista);
        } else {
            char *country = getCountry(artista);
            if (strcmp(country, c) == 0) {
                insere_artista_ordenado(top, n, artista);
            }
            free(country);
        }
    }

    size_t buffer_size = 300;
    char *resultado = malloc(buffer_size);
    resultado[0] = '\0';

    for (int i = 0; i < n && top[i] != NULL; i++) {
        Artista a = top[i];
        char *name = getName(a);
        char *type = getType(a);
        char *duration = formataDuration(getDiscography_Duration(a));
        char *country = getCountry(a);

        // Calcula o espaço necessário para adicionar o novo artista ao resultado
        size_t required_size = strlen(name) + strlen(type) + strlen(duration) + strlen(country) + 20;
        if (strlen(resultado) + required_size >= buffer_size) {
            buffer_size *= 2;
            resultado = realloc(resultado, buffer_size);
        }
        char line[200];
        snprintf(line, sizeof(line), "%s;%s;%s;%s\n",name,type,duration,country);
        strcat(resultado, line);
        free(name);
        free(type);
        free(duration);
        free(country);
        
    }

    return resultado;


}



char *Q3(int min, int max, Joint catalogo){
    GHashTable *utilizadores = getUtilizadoresValidos(get_catalogo_utilizadores(catalogo));
    GeneroContagem *array_resultado = build_Array_GC();
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, utilizadores);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        utilizador u = (utilizador)value;
        int age = get_age(u);
        if(age<min || age > max){
            continue;
        } else {
            incrementa_likes_array(array_resultado,getArray(u));
        }
    }
    for(int i = 0; i < 10; i++){
        for(int j = i; j < 10; j++){
            if(comparar_generosC(array_resultado[i],array_resultado[j]) > 0){
                troca_generosC(i,j,array_resultado);
            }
        }
    }

    // Build the result string
    int total_length = 1; // For the null terminator
    int any_non_zero_likes = 0;

    for(int i = 0; i < 10; i++){
        if(getLikes(array_resultado[i]) > 0){
            any_non_zero_likes = 1;
            int genero_length = strlen(getGenero(array_resultado[i]));
            int likes_length = snprintf(NULL, 0, "%d", getLikes(array_resultado[i]));
            total_length += genero_length + likes_length + 3; // Including ": " and "\n"
        }
    }

    if(!any_non_zero_likes){
        char *result = malloc(2); // For "\n" and null terminator
        if(result == NULL) {
            // Handle memory allocation failure
            return NULL;
        }
        strcpy(result, "\n");
        return result;
    } else {
        char *result = malloc(total_length);
        if(result == NULL) {
            // Handle memory allocation failure
            return NULL;
        }
        char *ptr = result;
        for(int i = 0; i < 10; i++){
            if(getLikes(array_resultado[i]) > 0){
                int n = sprintf(ptr, "%s;%d\n", getGenero(array_resultado[i]), getLikes(array_resultado[i]));
                ptr += n;
            }
        }
        *ptr = '\0'; // Null-terminate the string
        return result;
    }
}


/*
char *Q3(int min, int max, Joint catalogo) {
    GHashTable *utilizadores = getUtilizadoresValidos(get_catalogo_utilizadores(catalogo));
    Catalogo_Musicas musicas = get_catalogo_musicas(catalogo);
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
                printf("O utilizador não tem iked_musics\n");
                free(birth_date);
                continue;
            }

            for (int i = 0; likedMusics[i] != NULL; i++) {
                char *idMusica = likedMusics[i];
                char *genero = getGenre(get_musica_valida(musicas, idMusica));

                generoContagem contagem = g_hash_table_lookup(generosContagem, genero);

                if (contagem == NULL) {
                    contagem = malloc(sizeof(struct generoContagem));
                    contagem->genero = strdup(genero);
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

    GList *generos_lista = g_hash_table_get_values(generosContagem);

    if (generos_lista == NULL || g_list_length(generos_lista) == 0) {
        g_list_free(keys);
        g_hash_table_destroy(generosContagem);
        return strdup("\n");
    }
    generos_lista = g_list_sort(generos_lista, comparar_generos);

    size_t buffer_size = 300;
    char *resultado = malloc(buffer_size);
    resultado[0] = '\0';

    for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
        generoContagem contagem = (generoContagem)iter->data;
        size_t required_size = strlen(contagem->genero) + 20;
        
        if (strlen(resultado) + required_size >= buffer_size) {
            buffer_size *= 2;
            resultado = realloc(resultado, buffer_size);
        }

        char line[100];
        snprintf(line, sizeof(line), "%s;%d\n", contagem->genero, contagem->likes);
        strcat(resultado, line);
    }

    g_list_free(generos_lista);
    g_list_free(keys);
    g_hash_table_destroy(generosContagem);


    return resultado;
}
*/

void excuta_queries(char *linha, int contador, Joint joint){
    switch (linha[0])
    {
    /*case '1': {
        char *id = linha+2;
        char *resposta = Q1(id,joint);
        escreve_querie(resposta,contador);
        free(resposta);
        
        break;
    }
    case '2':{
        char *country = NULL;
        char *resto_linha = linha + 2;
        long int n = strtol(resto_linha, &resto_linha, 10);

        while (*resto_linha == ' ') {
            resto_linha++;
        }
        //remove ""
        if (*resto_linha == '"') {
            resto_linha++;
            country = resto_linha;
            char *aspa_fim = strchr(resto_linha, '"');
            if (aspa_fim != NULL) {
                *aspa_fim = '\0';
            }
        }
        char* resposta = Q2(n,country,joint);
        escreve_querie(resposta,contador);
        free(resposta);
        break;
    }*/
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