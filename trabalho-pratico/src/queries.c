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
#include "catalogo_artista.h"
#include "recomendador.h"

void calculate_total_value(Joint joint)
{

    Catalogo_Artistas catalogo = get_catalogo_artistas(joint);
    GPtrArray *keys = get_keys_artistas(catalogo);


    for (guint i = 0; i < keys->len; i++) {

        gpointer id = keys->pdata[i];
        Artista artista = get_artista_valido(catalogo,id);

        char *type = getType(artista);

        if(strcmp(type,"individual") == 0)
        {
            double rate = getRecipe_Per_Stream(artista);
            size_t plays = getPlays(artista);
            double num = rate * plays;
            increaseTotal_recipe(num,artista);
            free(type);
            continue;
        }

        double rate = getRecipe_Per_Stream(artista);
        size_t plays = getPlays(artista);
        double num = rate * plays;

        increaseTotal_recipe(num,artista);

        int elem = 0;
        gpointer *constituent =  getId_Constituent(artista);
        for (int i = 0; constituent[i] != NULL; i++) elem++;

        double part = num / elem;

        for (int j = 0; constituent[j] != NULL; j++)
        {
            Artista art = get_artista_valido(catalogo,constituent[j]);
            if(art == NULL) continue;
            increaseTotal_recipe(part,art);
        }
        
        free(type);

    }

}

char *Q1(char *ID, Joint catalogo)
{
    static int first_time = 0;
    if (first_time == 0)
    {
        calculate_total_value(catalogo);
        first_time++;    
    }

    if (ID[0] == 'U')
    {
        catalogo_utilizadores catU = get_catalogo_utilizadores(catalogo);
        int num;
        sscanf(ID, "U%d", &num);
        gpointer p = GINT_TO_POINTER(num);

        utilizador u = get_utilizador_valido(catU, p);
        if (u == NULL)
        {
            char *empty_response = malloc(2); // Aloca espaço para "\n" e o caractere nulo
            if (empty_response == NULL)
                return NULL; // Falha na alocação
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
    Catalogo_Artistas cat_artistas = get_catalogo_artistas(catalogo);
    int num;
    sscanf(ID, "A%d", &num);
    gpointer p = GINT_TO_POINTER(num);

    Artista a = get_artista_valido(cat_artistas, p);

    if (a == NULL)
    {
        char *empty_response = malloc(2); // Aloca espaço para "\n" e o caractere nulo
        if (empty_response == NULL)
            return NULL; // Falha na alocação
        strcpy(empty_response, "\n");
        return empty_response;
    }

    char *name = getName(a);
    char *type = getType(a);
    char *country = getCountry(a);
    size_t albuns = getNum_albums_indiv(a);
    double total_recipe = get_total_recipe(a);

    size_t buffer_size = strlen(name) + strlen(type) + strlen(country) + 100;
    char *resposta = malloc(buffer_size);

    snprintf(resposta, buffer_size, "%s;%s;%s;%zu;%.2f\n",
             name, type, country, albuns, total_recipe);

    free(name);
    free(type);
    free(country);

    return resposta;
}

int compara_artistas(Artista a, Artista b)
{
    if (getDiscography_Duration(a) != getDiscography_Duration(b))
    {
        return getDiscography_Duration(b) - getDiscography_Duration(a);
    }
    else
    {
        char *idA = getId_Artista_String(a);
        char *idB = getId_Artista_String(b);
        int result = strcmp(idA, idB);
        free(idA);
        free(idB);
        return result;
    }
}

void insere_artista_ordenado(Artista top[], int n, Artista novo)
{
    for (int i = 0; i < n; i++)
    {
        if (top[i] == NULL)
        { // posição vazia
            top[i] = novo;
            return;
        }
        if (compara_artistas(novo, top[i]) < 0)
        {
            // abrir espaço para o novo artista
            if (top[n - 1] != NULL)
            {
                top[n - 1] = NULL;
            }
            for (int j = n - 1; j > i; j--)
            {
                top[j] = top[j - 1];
            }
            top[i] = novo;
            return;
        }
    }
}

char *Q2(int n, char *c, Joint j){
    Catalogo_Artistas cat_artistas = get_catalogo_artistas(j);
    GPtrArray *keys = get_keys_artistas(cat_artistas);
    Artista top[n];
    memset(top, 0, sizeof(top)); // Inicializa o array a NULL
    if(n == 0) return strdup("\n");


    for (guint i = 0; i < keys->len; i++) {
        gpointer id = keys->pdata[i];
        Artista artista = get_artista_valido(cat_artistas,id);
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

char *Q3(int min, int max, Joint catalogo, Stats s){
    catalogo_utilizadores cat_users = get_catalogo_utilizadores(catalogo);

    GPtrArray *keys = get_keys_users(cat_users);

    GArray *array_resultado = build_Array_GC();


    for (guint i = 0; i < keys->len; i++){  
        gpointer id = keys->pdata[i];
        utilizador u = get_utilizador_valido(cat_users,id);
        int age = get_age(u);
        if(age<min || age > max){
            continue;
        } else {
            incrementa_likes_array(array_resultado,getArray(u));
        }
    }
    if(array_resultado->len == 0){
        char *result = malloc(2);
        free_Array_GC(array_resultado);
        strcpy(result, "\n");
        return result;
    }
    //printf("%d\n",array_resultado->len);
    gboolean swapped = TRUE;
    while (swapped) {
        swapped = FALSE;
        for (guint i = 0; i < array_resultado->len - 1; i++) {
            GeneroContagem gc_1 = g_array_index(array_resultado, GeneroContagem, i);
            GeneroContagem gc_2 = g_array_index(array_resultado, GeneroContagem, i + 1);

            // Se o gc_i1 for "maior" que gc_i pela nossa regra, trocamos
            if (comparar_generosC(gc_1, gc_2) > 0) {
                swap_generos(array_resultado, i, i + 1);
                swapped = TRUE;
            }
        }
    }

    int total_length = 1;//para o \0

     for (guint i = 0; i < array_resultado->len; i++) {
        GeneroContagem gc = g_array_index(array_resultado, GeneroContagem, i);
        //printf("%d\n",getLikes(gc));
        if(getLikes(gc) > 0){
            int genero_length = strlen(getGenero(gc));
            int likes_length = snprintf(NULL, 0, "%d", getLikes(gc));
            total_length += genero_length + likes_length + 2; //inclui ";" e "\n"
        }
    }


    char *result = malloc(total_length);
    char *ptr = result;
    for (guint i = 0; i < array_resultado->len; i++) {
        GeneroContagem gc = g_array_index(array_resultado, GeneroContagem, i);
        if(getLikes(gc) > 0){
            int n = sprintf(ptr, "%s;%d\n", getGenero(gc), getLikes(gc));
            ptr += n;
        }
    }
    free_Array_GC(array_resultado);
    *ptr = '\0'; //termina a string
    return result;
    
}




char *Q5(char *username, int num, Joint j, Stats s)
{
    catalogo_utilizadores u = get_catalogo_utilizadores(j);
    GPtrArray *keys = get_keys_users(u);
    
    static int cont = 0;
    if (cont == 0){
        build_stats(s,keys,u);
        cont++;
    }
    int **matriz = getMatriz(s);
    char **ids = get_ids_users(s);
    char **generos = get_nome_Generos(s);
    int tam_ids = get_size_idsUtilizadores(s);
    int tam_generos = get_size_nomesGeneros(s);

    int user_int;
    sscanf(username,"U%d",&user_int);
    gpointer user = int_gpointer(user_int);

    if(get_utilizador_valido(u,user) == NULL){
        char *empty_response = malloc(2); // Aloca espaço para "\n" e o caractere nulo
        if (empty_response == NULL) return NULL; // Falha na alocação
        strcpy(empty_response, "\n");
        return empty_response;
    }


    char **result = recomendaUtilizadores(username,matriz,ids,generos,tam_ids,tam_generos,num);
    if (result == NULL){
        char *empty_response = malloc(2); // Aloca espaço para "\n" e o caractere nulo
        if (empty_response == NULL) return NULL; // Falha na alocação
        strcpy(empty_response, "\n");
        return empty_response;
    }
    size_t total_length = 0;
    int count;
    for (count = 0; count < num; count++) {
        total_length += strlen(result[count]) + 1;  // +1 para o '\n'
    }
    total_length++;

    if (count == 0){
        char *empty_response = malloc(2);
        if (empty_response == NULL) return NULL;
        strcpy(empty_response, "\n");
        return empty_response;
    }

    char *final_str = malloc(total_length);
    final_str[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(final_str, result[i]);
        strcat(final_str, "\n");
    }

    return final_str;

}


void excuta_queries(char *linha, int contador, Joint joint, Stats s){
    switch (linha[0])
    {
    case '1': {
        if(linha[1]=='S')
        {
            char *id = linha+3;
            char *resposta = Q1(id,joint);
            substituiPonto_E_Virgula(resposta);
            escreve_querie(resposta,contador);
            free(resposta);
        } else {
            char *id = linha+2;
            char *resposta = Q1(id,joint);
            escreve_querie(resposta,contador);
            free(resposta); 
        }
        
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
        if(linha[1]=='S') substituiPonto_E_Virgula(resposta);
        escreve_querie(resposta,contador);
        free(resposta);
        break;
    }
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
            char *resposta = Q3(min, max, joint,s);
            if(linha[1]=='S') substituiPonto_E_Virgula(resposta);
            escreve_querie(resposta,contador);
            free(resposta);
        }

        break;
    } case '5':{
        if(linha[1]=='S')
        {
            char *id = linha+3;
            char *username = malloc(9*sizeof(char));
            int num;
            sscanf(id,"%s %d",username,&num);
            //printf("%s %d\n",username,num);
            char *resposta = Q5(username,num,joint,s);
            substituiPonto_E_Virgula(resposta);
            escreve_querie(resposta,contador);
            free(username);
            free(resposta);
        } else {
            char *id = linha+2;
            char *username = malloc(9*sizeof(char));
            int num;
            sscanf(id,"%s %d",username,&num);
            //printf("%s %d\n",username,num);
            char *resposta = Q5(username,num,joint,s);
            escreve_querie(resposta,contador);
            free(username);
            free(resposta); 
        }
    }
    default:
        break;
    }

}

char *excuta_queries_iterativo(int n_querie,int separador, char * linha, Joint joint, Stats s)
{
    switch (n_querie)
    {
    case 1:
    {
        char *resposta = Q1(linha,joint);

        if (separador) substituiPonto_E_Virgula(resposta);

        return resposta;

    }
    case 2:
    {
        char *country = NULL;
        long int n = strtol(linha, &linha, 10);

        while (*linha == ' ')
        {
            linha++;
        }
        // remove ""
        if (*linha == '"')
        {
            linha++;
            country = linha;
            char *aspa_fim = strchr(linha, '"');
            if (aspa_fim != NULL)
            {
                *aspa_fim = '\0';
            }
        }
        char *resposta = Q2(n, country, joint);
        if (separador)
            substituiPonto_E_Virgula(resposta);
        return resposta;
    }
    case 3:
    {
        int min;
        int max;
        if (sscanf(linha,"%d %d",&min,&max) != 2){
            return NULL;
        }
        char *resposta = Q3(min, max, joint,s);
        if (separador)
            substituiPonto_E_Virgula(resposta);
        return resposta;

    }
    case 5:
    {
        char *username = malloc(9*sizeof(char));
        int num;
        sscanf(linha,"%s %d",username,&num);
        char *resposta = Q5(username,num,joint,s);

        if(separador) substituiPonto_E_Virgula(resposta);

        free(username);
        return resposta;
    }
    default:
        return NULL;
    }
}