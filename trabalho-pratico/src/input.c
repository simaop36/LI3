#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "input.h"
#include "joint.h"
#include "parser.h"

void ler_csvs(const char *dir_path, Joint catalogo)
{
    char file_path[256]; // Buffer para armazenar o caminho completo
    FILE *csv_file;

    // CSV esperados
    const char *file_Names[] = {"artists.csv", "musics.csv", "users.csv"};

    for (int i = 0; i < 3; i++)
    {
        // junta o path com o file_Names
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, file_Names[i]);

        // Abre o arquivo CSV em modo leitura
        csv_file = fopen(file_path, "r");
        if (csv_file == NULL)
        {
            fprintf(stderr, "Erro ao abrir o arquivo: %s\n", file_path);
            continue;
        }

        file_reader(csv_file, file_Names[i], catalogo);
        fclose(csv_file);
    }
}

char *ler_queries(const char *file_path, Joint joint)
{
    FILE *queries_file = fopen(file_path, "r");
    if (queries_file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o ficheiro: %s\n", file_path);
        return NULL;
    }
    char *resultado = parse_queries(queries_file, joint);
    fclose(queries_file);
    return resultado;
}
