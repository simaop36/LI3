#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utils.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "users.h"
#include "catalogo_artista.h"

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

int valida_liked_music(utilizador *u, Catalogo_Musicas catalogo_m)
{
    int i = 0;
    while (get_liked_musics_id(u) + i != NULL)
    {
        if (g_hash_table_contains(get_musicas_validas(catalogo_m), get_liked_musics_id(u) + i))
            return 0;
        i++;
    }
    return 1;
}

int valida_artistasDamusica(musica u, Catalogo_Artistas a)
{
    int i = 0;
    while (getId_Artista(a) + i != NULL)
    {
        if (!(g_hash_table_contains(get_artistas_validos(a), getId_Artista(u) + i)))
            return 0;
        i++;
    }
    return 1;
}