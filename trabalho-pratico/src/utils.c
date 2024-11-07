#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "users.h"
#include "catalogo_artista.h"
#include "joint.h"

// return 0 : Inválido
// return 1 : Válido

int valida_data(const char *data)
{
    // Verificar se o comprimento total da string é exatamente 10
    if (strlen(data) != 10)
    {
        return 0;
    }

    // Verificar o formato "aaaa/mm/dd"
    if (data[4] != '/' || data[7] != '/')
    {
        return 0;
    }

    // Verificar ano, mês e dia
    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(data[i]))
        {
            return 0;
        }
    }
    for (int i = 5; i < 7; i++)
    {
        if (!isdigit(data[i]))
        {
            return 0;
        }
    }
    for (int i = 8; i < 10; i++)
    {
        if (!isdigit(data[i]))
        {
            return 0;
        }
    }

    int ano = atoi(&data[0]);
    int mes = atoi(&data[5]);
    int dia = atoi(&data[8]);

    // Verificar valores válidos do ano, mês e dia
    if (ano < 0 || ano > 2024 || mes < 1 || mes > 12 || dia < 1 || dia > 31)
    {
        return 0;
    }

    // Verificar datas após 2024/09/09
    if (ano == 2024 && mes > 9)
    {
        return 0;
    }
    if (ano == 2024 && mes == 9 && dia > 9)
    {
        return 0;
    }

    return 1;
}

int valida_duracao(const char *duracao)
{
    // Verificar se o comprimento total da string é exatamente 8 caracteres
    if (strlen(duracao) != 8)
    {
        return 0;
    }

    // Verificar o formato hh:mm:ss
    if (duracao[2] != ':' || duracao[5] != ':')
    {
        return 0;
    }

    // Verificar horas, minutos e segundos
    for (int i = 0; i < 2; i++)
    {
        if (!isdigit(duracao[i]))
        {
            return 0;
        }
    }
    for (int i = 3; i < 5; i++)
    {
        if (!isdigit(duracao[i]))
        {
            return 0;
        }
    }
    for (int i = 6; i < 8; i++)
    {
        if (!isdigit(duracao[i]))
        {
            return 0;
        }
    }

    int horas = atoi(&duracao[0]);
    int minutos = atoi(&duracao[3]);
    int segundos = atoi(&duracao[6]);

    // Verificar valores válidos de horas, minutos e segundos
    if (horas < 0 || horas > 99 || minutos < 0 || minutos > 59 || segundos < 0 || segundos > 59)
    {
        return 0;
    }

    return 1;
}

int valida_email(const char *email)
{
    // Verifica se o comprimento minimo: a@a.aa
    if (strlen(email) < 6)
    {
        return 0;
    }

    // Encontrar a posição do '@' no email
    const char *arroba = strchr(email, '@');
    if (!arroba)
    {
        return 0; // nao tem @
    }

    // Verifica existe mais de um '@'
    if (strchr(arroba + 1, '@'))
    {
        return 0; // Mais de um '@'
    }

    // Dividir a string
    int username_length = arroba - email;
    if (username_length < 1)
    {
        return 0; // Username vazio
    }

    // Verificar cada caractere de username
    for (int i = 0; i < username_length; i++)
    {
        if (!isalnum(email[i]) || (isalpha(email[i]) && !islower(email[i])))
        {
            return 0; // Username deve conter apenas [a-z0-9]
        }
    }

    // Separar o domínio após o '@'
    const char *dominio = arroba + 1;

    // Encontrar a posição do ponto no domínio
    const char *ponto = strrchr(dominio, '.');
    if (!ponto || ponto == dominio)
    {
        return 0; // Não há ponto ou lstring está vazio
    }

    // lstring deve ter pelo menos 1 caractere
    int lstring_length = ponto - dominio;
    if (lstring_length < 1)
    {
        return 0;
    }

    // Verificar se todos os caracteres de lstring estão no intervalo [a-z]
    for (int i = 0; i < lstring_length; i++)
    {
        if (!isalpha(dominio[i]) || !islower(dominio[i]))
        {
            return 0;
        }
    }

    // Verificar o rstring
    const char *rstring = ponto + 1;
    int rstring_length = strlen(rstring);
    if (rstring_length < 2 || rstring_length > 3)
    {
        return 0; // rstring deve ter exatamente 2 ou 3 caracteres
    }

    // Verificar se todos os caracteres de rstring estão no intervalo [a-z]
    for (int i = 0; i < rstring_length; i++)
    {
        if (!isalpha(dominio[i]) || !islower(dominio[i]))
        {
            return 0;
        }
    }

    return 1;
}

int valida_tipo_user(const char *tipo)
{
    if (strcmp(tipo, "normal") == 0 || strcmp(tipo, "premium") == 0)
    {
        return 1;
    }
    return 0;
}

int valida_tipo_artista(const char *tipo, const char *id_Constituent)
{
    if (strcmp(tipo, "individual") == 0)
    {
        if (strcmp(id_Constituent, "[]") == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int valida_lista(const char *str)
{
    int len = strlen(str);
    // Verificar o comprimento para ter pelo menos [ e ]
    if (len < 2)
    {
        return 0;
    }
    if (str[0] == '[' && str[len - 1] == ']')
    {
        return 1;
    }
    return 0;
}

char **parse_lista(char *input)
{
    // Verifica se o input é nulo ou vazio, ou se contém apenas []
    if (input == NULL || strcmp(input, "[]") == 0)
    {
        return NULL; // Retorna NULL se não houver elementos
    }

    // Remove []
    if (*input == '[')
        input++;
    if (input[strlen(input) - 1] == ']')
        input[strlen(input) - 1] = '\0';

    // Inicializa um array dinâmico para os tokens
    char **result = NULL;
    int num_tokens = 0;
    char *token = strtok(input, ", ");

    // Percorre cada token separado por ", "
    while (token != NULL)
    {
        // Remove aspas simples, se existirem
        if (*token == '\'')
            token++;
        if (token[strlen(token) - 1] == '\'')
            token[strlen(token) - 1] = '\0';

        // Redimensiona o array para adicionar mais um token
        char **temp = realloc(result, (num_tokens + 1) * sizeof(char *));
        if (!temp)
        {
            perror("Erro ao realocar memória");
            for (int i = 0; i < num_tokens; i++)
            {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        result = temp;

        // Copia o token atual para o array
        result[num_tokens] = strdup(token);
        if (!result[num_tokens])
        {
            perror("Erro ao alocar memória para o token");
            for (int i = 0; i < num_tokens; i++)
            {
                free(result[i]);
            }
            free(result);
            return NULL;
        }

        num_tokens++;
        token = strtok(NULL, ", ");
    }
    // Adiciona um último elemento NULL para marcar o fim do array
    char **final_result = realloc(result, (num_tokens + 1) * sizeof(char *));
    if (!final_result)
    {
        perror("Erro ao realocar memória final");
        for (int i = 0; i < num_tokens; i++)
        {
            free(result[i]);
        }
        free(result);
        return NULL;
    }
    final_result[num_tokens] = NULL;

    return final_result;
}

/*
void aux_valida_liked_music(utilizador u, Joint catalogo) {
    Catalogo_Musicas catM = get_catalogo_musicas(catalogo);
    catalogo_utilizadores catU = get_catalogo_utilizadores(catalogo);
    
    char **liked_musics = get_liked_musics_id(u);
    int i = 0;

    // array termina com NULL
    if(liked_musics == NULL) return;
    while (liked_musics[i] != NULL) {
        if (!g_hash_table_contains(getMusicasValidas(catM), liked_musics[i])) {
            add_utilizador_invalido(catU, u);
            char *username = get_username(u);
            if(username == NULL) return;
            if (!(g_hash_table_remove(getUtilizadoresValidos(catU), username))) printf("erro remove user\n");
            return;
        }
        i++;
    }
    return;
}
*/

bool verifica_artista_valido(musica m, GHashTable *artista_valido){
    char **artistas_id = getId_Artistas(m);
    
    for (int i = 0; artistas_id[i] != NULL; i++){
        if(!(g_hash_table_contains(artista_valido,artistas_id[i]))){
            return false;
        }
    }
    for (int i = 0; artistas_id[i] != NULL; i++) free(artistas_id[i]);
    free(artistas_id);
    return true;
}

bool verifica_musica_valida(utilizador utilizador, GHashTable *musicas_validas) {
    char **liked_musics = get_liked_musics_id(utilizador);

    for (int i = 0; liked_musics[i] != NULL; i++) {
        if (!(g_hash_table_contains(musicas_validas, liked_musics[i]))) {
            return false; // Encontrou um artista inválido
        }
    }
    for(int i = 0; liked_musics[i] != NULL; i++) free(liked_musics[i]);
    free(liked_musics);
    return true;
}
void mover_musicas_invalidos(GHashTable *musicas_validas, GHashTable *musicas_invalidas, GHashTable *artistas_validos) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, musicas_validas);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        musica m = (musica)value;


        if (!verifica_artista_valido(m, artistas_validos)) {

            g_hash_table_insert(musicas_invalidas, key, m);

            g_hash_table_iter_remove(&iter);
        }
    }
}

void mover_utilizadores_invalidos(GHashTable *utilizadores_validos, GHashTable *utilizadores_invalidos, GHashTable *musicas_validas) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, utilizadores_validos);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        utilizador ut = (utilizador)value;

        if (!verifica_musica_valida(ut, musicas_validas)) {

            g_hash_table_insert(utilizadores_invalidos, key, ut);

            g_hash_table_iter_remove(&iter);
        }
    }
}

void valida_artistasDamusica(musica m, Joint catalogo) {
    Catalogo_Artistas catA = get_catalogo_artistas(catalogo);
    Catalogo_Musicas catM = get_catalogo_musicas(catalogo);
    
    char **artistas = getId_Artistas(m);
    int i = 0;

    // array termina com NULL
    while (artistas[i] != NULL) {
        if (!g_hash_table_contains(getArtistasValidos(catA), artistas[i])) {
            add_musica_invalida(catM, m);
            g_hash_table_remove(getMusicasValidas(catM), getId_Musica(m));
            
            break;
        }
        i++;
    }
    return;
}

void free_lista_strings(char **array) {
    if (array == NULL) return;

    // Free cada elemento ate NULL
    for (size_t i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }

    free(array);
}
