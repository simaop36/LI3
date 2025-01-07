#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>

#include "utils.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "catalogo_artista.h"
#include "catalogo_albuns.h"
#include "joint.h"
#include "users.h"
#include "musica.h"
#include "estatisticas.h"

// return 0 : Inválido
// return 1 : Válido

void stringToUpper(char *str) {
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

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
    int result = 0;
    char *aux = strdup(tipo);
    stringToUpper(aux);

    if (strcmp(aux, "INDIVIDUAL") == 0)
    {
        if (strcmp(id_Constituent, "[]") == 0)
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
    } else if(strcmp(aux, "GROUP") == 0)
    {
        result = 1;
    }
    free(aux);
    return result;
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

int converteDuration(const char *duration)
{
    int horas, minutos, segundos;
    if (sscanf(duration, "%2d:%2d:%2d", &horas, &minutos, &segundos) != 3)
    {
        printf("Formato de duração inválido: %s\n", duration);
        return -1;
    }
    int total_segundos = horas * 3600 + minutos * 60 + segundos;
    return total_segundos;
}

char *formataDuration(int total_segundos)
{
    int horas = total_segundos / 3600;
    int minutos = (total_segundos % 3600) / 60;
    int segundos = total_segundos % 60;

    char *duration = malloc(9);
    if (duration == NULL)
    {
        printf("Erro de alocação de memória\n");
        return NULL;
    }
    snprintf(duration, 9, "%02d:%02d:%02d", horas, minutos, segundos);
    return duration;
}

int extrair_numero(const char *str)
{
    const char *ptr = str;
    while (*ptr && !isdigit(*ptr))
    {
        ptr++;
    }
    if (*ptr)
    {
        return atoi(ptr);
    }
    return 0;
}


void free_lista_strings(char **array)
{
    if (array == NULL)
        return;

    // Free cada elemento ate NULL
    for (size_t i = 0; array[i] != NULL; i++)
    {
        free(array[i]);
    }

    free(array);
}

int calcula_idade(const char *birth_date)
{
    if (birth_date == NULL || strlen(birth_date) < 10)
    {
        printf("Data de nascimento inválida: %s\n", birth_date);
        return -1;
    }
    int ano_atual, mes_atual, dia_atual;
    int ano_nascimento, mes_nascimento, dia_nascimento;
    const char data_atual[] = "2024/09/09";

    if (sscanf(data_atual, "%4d/%2d/%2d", &ano_atual, &mes_atual, &dia_atual) != 3)
    {
        printf("Erro ao extrair data atual\n");
        return -1;
    }
    if (sscanf(birth_date, "%4d/%2d/%2d", &ano_nascimento, &mes_nascimento, &dia_nascimento) != 3)
    {
        printf("Erro ao extrair data de nascimento: %s\n", birth_date);
        return -1;
    }
    int idade = ano_atual - ano_nascimento;

    if ((mes_atual < mes_nascimento) || (mes_atual == mes_nascimento && dia_atual < dia_nascimento))
    {
        idade--;
    }
    return idade;
}

char *compara_resultados(const char *pasta1, const char *pasta2)
{
    DIR *dir1, *dir2;
    struct dirent *entrada1;
    size_t resultado_size = 2048;
    char *resultado = malloc(resultado_size * sizeof(char));
    if (resultado == NULL)
    {
        perror("Erro ao alocar memória para resultado");
        return NULL;
    }
    resultado[0] = '\0'; // Inicializa a string vazia

    dir1 = opendir(pasta1);
    dir2 = opendir(pasta2);
    if (dir1 == NULL || dir2 == NULL)
    {
        perror("Erro ao abrir uma das pastas");
        free(resultado);
        return NULL;
    }
    int aux[4] = {0, 0, 0,0}; // Para as queries 1, 2, 3 e 5
    int nr_querie = 0;
    int encontrou_erro_total = 0;

    while ((entrada1 = readdir(dir1)) != NULL)
    {
        if (entrada1->d_type == DT_REG && strstr(entrada1->d_name, "_output.txt") != NULL)
        {
            int nr_command = extrair_numero(entrada1->d_name);

            if (nr_command > 0)
            {
                if (nr_command < 121)
                {
                    nr_querie = 0; // Query 1
                }
                else if (nr_command >= 121 && nr_command <= 240)
                {
                    nr_querie = 1; // Query 2
                }
                else if (nr_command >= 241 && nr_command <= 300)
                {
                    nr_querie = 2; // Query 3
                }else if (nr_command >= 451 && nr_command <= 500)
                {
                    nr_querie = 3; // Query 5
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }

            char caminho1[1024];
            snprintf(caminho1, sizeof(caminho1), "%s/%s", pasta1, entrada1->d_name);

            char caminho2[1024];
            snprintf(caminho2, sizeof(caminho2), "%s/%s", pasta2, entrada1->d_name);

            FILE *file1 = fopen(caminho1, "r");
            FILE *file2 = fopen(caminho2, "r");

            if (file1 == NULL || file2 == NULL)
            {
                size_t len = strlen(resultado);
                size_t needed = snprintf(NULL, 0, "Erro ao abrir um dos arquivos: %s ou %s\n", caminho1, caminho2);
                if (len + needed + 1 > resultado_size)
                {
                    resultado_size = len + needed + 1;
                    resultado = realloc(resultado, resultado_size);
                    if (resultado == NULL)
                    {
                        perror("Erro ao realocar memória para resultado");
                        fclose(file1);
                        fclose(file2);
                        closedir(dir1);
                        closedir(dir2);
                        return NULL;
                    }
                }
                snprintf(resultado + len, resultado_size - len, "Erro ao abrir um dos arquivos: %s ou %s\n", caminho1, caminho2);
                encontrou_erro_total = 1;
                if (file1)
                    fclose(file1);
                if (file2)
                    fclose(file2);
                continue;
            }

            int posicao = 1;
            char ch1, ch2;
            int encontrou_erro_no_arquivo = 0;

            while (((ch1 = fgetc(file1)) != EOF) && ((ch2 = fgetc(file2)) != EOF))
            {
                if (ch1 != ch2)
                {
                    size_t len = strlen(resultado);
                    size_t needed = snprintf(NULL, 0, "Diferença encontrada em %s na posição %d: '%c' != '%c'\n",
                                             entrada1->d_name, posicao, ch1, ch2);
                    if (len + needed + 1 > resultado_size)
                    {
                        resultado_size = len + needed + 1;
                        resultado = realloc(resultado, resultado_size);
                        if (resultado == NULL)
                        {
                            perror("Erro ao realocar memória para resultado");
                            fclose(file1);
                            fclose(file2);
                            closedir(dir1);
                            closedir(dir2);
                            return NULL;
                        }
                    }
                    snprintf(resultado + len, resultado_size - len, "Diferença encontrada em %s na posição %d: '%c' != '%c'\n",
                             entrada1->d_name, posicao, ch1, ch2);
                    encontrou_erro_total = 1;
                    encontrou_erro_no_arquivo = 1;
                    aux[nr_querie]++;
                    break;
                }
                posicao++;
            }

            if (!encontrou_erro_no_arquivo && (fgetc(file1) != EOF || fgetc(file2) != EOF))
            {
                size_t len = strlen(resultado);
                size_t needed = snprintf(NULL, 0, "Os arquivos %s têm tamanhos diferentes\n", entrada1->d_name);
                if (len + needed + 1 > resultado_size)
                {
                    resultado_size = len + needed + 1;
                    resultado = realloc(resultado, resultado_size);
                    if (resultado == NULL)
                    {
                        perror("Erro ao realocar memória para resultado");
                        fclose(file1);
                        fclose(file2);
                        closedir(dir1);
                        closedir(dir2);
                        return NULL;
                    }
                }
                snprintf(resultado + len, resultado_size - len, "Os arquivos %s têm tamanhos diferentes\n", entrada1->d_name);
                encontrou_erro_total = 1;
                encontrou_erro_no_arquivo = 1;
                aux[nr_querie]++;
            }
            fclose(file1);
            fclose(file2);
        }
    }
    closedir(dir1);
    closedir(dir2);

    if (!encontrou_erro_total)
    {
        size_t len = strlen(resultado);
        const char *msg = "Não foram encontrados erros nos resultados obtidos\n";
        size_t needed = strlen(msg);
        if (len + needed + 1 > resultado_size)
        {
            resultado_size = len + needed + 1;
            resultado = realloc(resultado, resultado_size);
            if (resultado == NULL)
            {
                perror("Erro ao realocar memória para resultado");
                return NULL;
            }
        }
        strcat(resultado, msg);
    }

    // Adicionar o resumo das queries
    int q1 = 120 - aux[0];
    int q2 = 120 - aux[1];
    int q3 = 60 - aux[2];
    int q5 = 50 - aux[3];


    size_t len = strlen(resultado);
    size_t needed = snprintf(NULL, 0, "Querie 1: %d de 120 corretas\n", q1) +
                    snprintf(NULL, 0, "Querie 2: %d de 120 corretas\n", q2) +
                    snprintf(NULL, 0, "Querie 3: %d de 60 corretas\n", q2) +
                    snprintf(NULL, 0, "Querie 5: %d de 50 corretas\n", q5);

    if (len + needed + 1 > resultado_size)
    {
        resultado_size = len + needed + 1;
        resultado = realloc(resultado, resultado_size);
        if (resultado == NULL)
        {
            perror("Erro ao realocar memória para resultado");
            return NULL;
        }
    }

    snprintf(resultado + len, resultado_size - len, "Querie 1: %d de 120 corretas\n", q1);
    len = strlen(resultado);
    snprintf(resultado + len, resultado_size - len, "Querie 2: %d de 120 corretas\n", q2);
    len = strlen(resultado);
    snprintf(resultado + len, resultado_size - len, "Querie 3: %d de 60 corretas\n", q3);
    len = strlen(resultado);
    snprintf(resultado + len, resultado_size - len, "Querie 5: %d de 50 corretas\n", q5);


    return resultado;
}

void substituiPonto_E_Virgula(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ';') {
            str[i] = '=';
        }
    }
}

// Definição do tipo de callback
typedef void (*IteratorCallback)(const char* key, const char* value, void* user_data);

// Estrutura genérica para encapsular a implementação
typedef struct {
    void* data;  // Ponteiro genérico para a estrutura interna
    void (*iterate)(void* data, IteratorCallback callback, void* user_data);
} GenericContainer;

void hashtable_iterate(void* data, IteratorCallback callback, void* user_data) {
    GHashTable* hash_table = (GHashTable*)data;
    g_hash_table_foreach(hash_table, (GHFunc)callback, user_data);
}


char *escreve_lista(char **elems, int tipo) {
    // tipo 0 = artistas;
    // tipo 1 = musica;
    // tipo 2 = user;

    // Verifica o número de elementos até NULL
    int num_elems = 0;
    while (elems[num_elems] != NULL) {
        num_elems++;
    }

    // Caso especial: se há apenas um elemento e o tipo é user (tipo == 2), retorna o elemento diretamente
    if (num_elems == 1 && tipo == 2) {
        char *single_elem = strdup(elems[0]); // copia o único elemento para evitar vazamento
        free(elems[0]);
        free(elems);
        return single_elem;
    }

    // Se a lista estiver vazia, retorna "[]"
    if (num_elems == 0) {
        char *resultado_vazio = malloc(3 * sizeof(char));
        if (resultado_vazio == NULL) {
            perror("Erro ao alocar memória");
            return NULL;
        }
        strcpy(resultado_vazio, "[]");
        free(elems);
        return resultado_vazio;
    }

    // Calcula o tamanho total necessário para a string final
    int tamanho_total = 2; // para os colchetes []

    if (tipo != 3) {
        for (int i = 0; i < num_elems; i++) {
            tamanho_total += strlen(elems[i]) + 3; // 3 caracteres para aspas e vírgula
        }
        tamanho_total -= 1; // Remove o último caractere extra de vírgula
    } else {
        for (int i = 0; i < num_elems; i++) {
            tamanho_total += strlen(elems[i]) + 4; // 4 caracteres para aspas, vírgula e espaço
        }
        tamanho_total -= 2; // Remove os últimos dois caracteres ", "
    }

    // Aloca memória para a string resultante
    char *resultado = malloc((tamanho_total + 1) * sizeof(char));
    if (resultado == NULL) {
        perror("Erro ao alocar memória");
        free(elems);
        return NULL;
    }

    // Preenche a string com o formato desejado
    strcpy(resultado, "[");
    for (int i = 0; i < num_elems; i++) {
        strcat(resultado, "'");
        strcat(resultado, elems[i]);
        strcat(resultado, "'");
        if (i < num_elems - 1) {
            strcat(resultado, ",");
            if (tipo == 3) {
                strcat(resultado, " ");
            }
        }
        free(elems[i]);
    }

    free(elems); // Libera o array de ponteiros após o uso
    strcat(resultado, "]");

    return resultado;
}



// Função de comparação para strings
gint compare_strings(gconstpointer a, gconstpointer b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    return strcmp(str_a, str_b);
}

gpointer int_gpointer(int i)
{
    return GINT_TO_POINTER(i);
}

int gpointer_int(gpointer p)
{
    return GPOINTER_TO_INT(p);
}


